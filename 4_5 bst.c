#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left, *right;
};

struct node* create(int v){
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->data = v;
    n->left = n->right = NULL;
    return n;
}

struct node* insert(struct node* r, int v){
    if (!r) return create(v);
    struct node *cur = r, *par = NULL;
    while (cur){
        par = cur;
        cur = (v < cur->data) ? cur->left : cur->right;
    }
    (v < par->data) ? (par->left = create(v)) : (par->right = create(v));
    return r;
}

void inorder(struct node* r){
    if (r){
        inorder(r->left);
        printf("%d\t", r->data);
        inorder(r->right);
    }
}

void preorder(struct node* r) {
    if (r) {
        printf("%d\t", r->data);
        preorder(r->left);
        preorder(r->right);
    }
}

void postorder(struct node* r){
    if (r) {
        postorder(r->left);
        postorder(r->right);
        printf("%d\t", r->data);
    }
}

struct node* search(struct node* r, int k){
    return (!r || r->data == k) ? r : (k < r->data ? search(r->left, k) : search(r->right, k));
}

struct node* del(struct node* r, int k){
    if (!r) return r;
    if (k < r->data) r->left = del(r->left, k);
    else if (k > r->data) r->right = del(r->right, k);
    else {
        if (!r->left) {
            struct node* t = r->right;
            free(r);
            return t;
        } else if (!r->right) {
            struct node* t = r->left;
            free(r);
            return t;
        }
        struct node* t = r->right;
        while (t->left) t = t->left;
        r->data = t->data;
        r->right = del(r->right, t->data);
    }
    return r;
}

int main() {
    struct node* root = NULL;
    int ch, v;
    while (1) {
        printf("\n1.ins\n2.Pre\n3.Post\n4.In\n5.search\n6.del\n7.exit\nenter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("enter value: ");
                scanf("%d", &v);
                root = insert(root, v);
                break;
            case 2:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 3:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("enter value: ");
                scanf("%d", &v);
                printf(search(root, v) ? "found\n" : "not found\n");
                break;
            case 6:
                printf("Enter value: ");
                scanf("%d", &v);
                root = del(root, v);
                printf("deleted\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid\n");
        }
    }
}
