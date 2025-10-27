#include <stdio.h>
#include <stdlib.h>

#define t 3

typedef struct BTreeNode{
    int keys[2*t-1];
    struct BTreeNode* child[2*t];
    int n;
    int leaf;
} BTreeNode;

BTreeNode* createNode(int leaf){
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for(int i = 0; i < 2*t; ++i) node->child[i] = NULL;
    return node;
}

void traverse(BTreeNode* root){
    int i;
    for(i = 0; i < root->n; ++i){
        if(!root->leaf) traverse(root->child[i]);
        printf("%d ", root->keys[i]);
    }
    if(!root->leaf) traverse(root->child[i]);
}

BTreeNode* search(BTreeNode* root, int k){
    int i = 0;
    while(i < root->n && k > root->keys[i]) ++i;
    if(i < root->n && root->keys[i] == k) return root;
    if(root->leaf) return NULL;
    return search(root->child[i], k);
}

void splitChild(BTreeNode* x, int i, BTreeNode* y){
    BTreeNode* z = createNode(y->leaf);
    z->n = t - 1;
    for(int j = 0; j < t - 1; ++j) z->keys[j] = y->keys[j + t];
    if(!y->leaf)
        for(int j = 0; j < t; ++j) z->child[j] = y->child[j + t];
    y->n = t - 1;
    for(int j = x->n; j >= i + 1; --j) x->child[j + 1] = x->child[j];
    x->child[i + 1] = z;
    for(int j = x->n - 1; j >= i; --j) x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[t - 1];
    x->n += 1;
}

void insertNonFull(BTreeNode* x, int k){
    int i = x->n - 1;
    if(x->leaf){
        while(i >= 0 && x->keys[i] > k){
            x->keys[i + 1] = x->keys[i];
            --i;
        }
        x->keys[i + 1] = k;
        x->n += 1;
    } else {
        while(i >= 0 && x->keys[i] > k) --i;
        ++i;
        if(x->child[i]->n == 2*t - 1){
            splitChild(x, i, x->child[i]);
            if(k > x->keys[i]) ++i;
        }
        insertNonFull(x->child[i], k);
    }
}

BTreeNode* insert(BTreeNode* root, int k){
    if(root->n == 2*t - 1){
        BTreeNode* s = createNode(0);
        s->child[0] = root;
        splitChild(s, 0, root);
        int i = 0;
        if(s->keys[0] < k) ++i;
        insertNonFull(s->child[i], k);
        return s;
    } else {
        insertNonFull(root, k);
        return root;
    }
}

/* helper for delete */
int getPred(BTreeNode* x, int idx){
    BTreeNode* cur = x->child[idx];
    while(!cur->leaf) cur = cur->child[cur->n];
    return cur->keys[cur->n - 1];
}

int getSucc(BTreeNode* x, int idx){
    BTreeNode* cur = x->child[idx + 1];
    while(!cur->leaf) cur = cur->child[0];
    return cur->keys[0];
}

void merge(BTreeNode* x, int idx){
    BTreeNode* c1 = x->child[idx];
    BTreeNode* c2 = x->child[idx + 1];
    c1->keys[t - 1] = x->keys[idx];
    for(int i = 0; i < c2->n; ++i) c1->keys[i + t] = c2->keys[i];
    if(!c1->leaf)
        for(int i = 0; i <= c2->n; ++i) c1->child[i + t] = c2->child[i];
    for(int i = idx + 1; i < x->n; ++i) x->keys[i - 1] = x->keys[i];
    for(int i = idx + 2; i <= x->n; ++i) x->child[i - 1] = x->child[i];
    c1->n += c2->n + 1;
    x->n -= 1;
    free(c2);
}

void borrowFromPrev(BTreeNode* x, int idx){
    BTreeNode* child = x->child[idx];
    BTreeNode* sibling = x->child[idx - 1];
    for(int i = child->n - 1; i >= 0; --i) child->keys[i + 1] = child->keys[i];
    if(!child->leaf)
        for(int i = child->n; i >= 0; --i) child->child[i + 1] = child->child[i];
    child->keys[0] = x->keys[idx - 1];
    if(!child->leaf) child->child[0] = sibling->child[sibling->n];
    x->keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

void borrowFromNext(BTreeNode* x, int idx){
    BTreeNode* child = x->child[idx];
    BTreeNode* sibling = x->child[idx + 1];
    child->keys[child->n] = x->keys[idx];
    if(!child->leaf) child->child[child->n + 1] = sibling->child[0];
    x->keys[idx] = sibling->keys[0];
    for(int i = 1; i < sibling->n; ++i) sibling->keys[i - 1] = sibling->keys[i];
    if(!sibling->leaf)
        for(int i = 1; i <= sibling->n; ++i) sibling->child[i - 1] = sibling->child[i];
    child->n += 1;
    sibling->n -= 1;
}

void fill(BTreeNode* x, int idx){
    if(idx != 0 && x->child[idx - 1]->n >= t)
        borrowFromPrev(x, idx);
    else if(idx != x->n && x->child[idx + 1]->n >= t)
        borrowFromNext(x, idx);
    else {
        if(idx != x->n) merge(x, idx);
        else merge(x, idx - 1);
    }
}

void removeNode(BTreeNode* x, int k){
    int idx = 0;
    while(idx < x->n && x->keys[idx] < k) ++idx;

    if(idx < x->n && x->keys[idx] == k){
        if(x->leaf){
            for(int i = idx + 1; i < x->n; ++i) x->keys[i - 1] = x->keys[i];
            x->n -= 1;
        } else {
            if(x->child[idx]->n >= t){
                int pred = getPred(x, idx);
                x->keys[idx] = pred;
                removeNode(x->child[idx], pred);
            } else if(x->child[idx + 1]->n >= t){
                int succ = getSucc(x, idx);
                x->keys[idx] = succ;
                removeNode(x->child[idx + 1], succ);
            } else {
                merge(x, idx);
                removeNode(x->child[idx], k);
            }
        }
    } else {
        if(x->leaf) return;
        int flag = (idx == x->n);
        if(x->child[idx]->n < t) fill(x, idx);
        if(flag && idx > x->n)
            removeNode(x->child[idx - 1], k);
        else removeNode(x->child[idx], k);
    }
}

BTreeNode* delete(BTreeNode* root, int k){
    if(!root) return NULL;
    removeNode(root, k);
    if(root->n == 0){
        BTreeNode* tmp = root;
        if(root->leaf) root = NULL;
        else root = root->child[0];
        free(tmp);
    }
    return root;
}

int main(){
    BTreeNode* root = createNode(1);
    int ch, val;
    while(1){
        printf("\n1.insert 2.delete 3.search 4.display 5.exit\nenter choice: ");
        scanf("%d", &ch);
        if(ch == 1){
            printf("enter value: ");
            scanf("%d", &val);
            root = insert(root, val);
        } else if(ch == 2){
            printf("enter value: ");
            scanf("%d", &val);
            root = delete(root, val);
        } else if(ch == 3){
            printf("enter value: ");
            scanf("%d", &val);
            BTreeNode* res = search(root, val);
            if(res) printf("found\n");
            else printf("not found\n");
        } else if(ch == 4){
            if(root) traverse(root);
            else printf("empty");
            printf("\n");
        } else break;
    }
    return 0;
}
