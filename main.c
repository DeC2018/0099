#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1000

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Global pointers for recoverTree logic
struct TreeNode* first = NULL;
struct TreeNode* second = NULL;
struct TreeNode* prev = NULL;

// Inorder traversal to find misplaced nodes
void inorder(struct TreeNode* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    if (prev != NULL && prev->val > root->val) {
        if (first == NULL)
            first = prev;
        second = root;
    }
    prev = root;
    inorder(root->right);
}

void recoverTree(struct TreeNode* root) {
    first = second = prev = NULL;
    inorder(root);
    if (first != NULL && second != NULL) {
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }
}

// Helper to create a new node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

// Helper to parse input string like "[1,3,null,null,2]"
int parseInput(const char* s, char arr[][16], int* n) {
    int idx = 0, arr_idx = 0;
    char buf[16];
    int buf_idx = 0;
    while (s[idx]) {
        if (s[idx] == '[' || s[idx] == ']' || s[idx] == ' ' || s[idx] == '\n') {
            idx++;
            continue;
        }
        if (s[idx] == ',') {
            if (buf_idx > 0) {
                buf[buf_idx] = '\0';
                strcpy(arr[arr_idx++], buf);
                buf_idx = 0;
            }
            idx++;
            continue;
        }
        buf[buf_idx++] = s[idx++];
    }
    if (buf_idx > 0) {
        buf[buf_idx] = '\0';
        strcpy(arr[arr_idx++], buf);
    }
    *n = arr_idx;
    return arr_idx;
}

// Helper to build a tree from array of strings (level order, "null" for NULL)
struct TreeNode* buildTree(char arr[][16], int n) {
    if (n == 0 || strcmp(arr[0], "null") == 0) return NULL;
    struct TreeNode* nodes[MAX_NODES] = {0};
    int i, j = 1;
    nodes[0] = newNode(atoi(arr[0]));
    int front = 0, rear = 1;
    while (front < rear && j < n) {
        struct TreeNode* curr = nodes[front++];
        if (j < n && strcmp(arr[j], "null") != 0) {
            curr->left = newNode(atoi(arr[j]));
            nodes[rear++] = curr->left;
        }
        j++;
        if (j < n && strcmp(arr[j], "null") != 0) {
            curr->right = newNode(atoi(arr[j]));
            nodes[rear++] = curr->right;
        }
        j++;
    }
    return nodes[0];
}

// Helper to print tree in level order (as per example output)
void printTree(struct TreeNode* root) {
    struct TreeNode* queue[MAX_NODES];
    int front = 0, rear = 0;
    char* res[MAX_NODES];
    int res_len = 0;
    queue[rear++] = root;
    while (front < rear) {
        struct TreeNode* node = queue[front++];
        if (node) {
            char* buf = (char*)malloc(16);
            sprintf(buf, "%d", node->val);
            res[res_len++] = buf;
            queue[rear++] = node->left;
            queue[rear++] = node->right;
        } else {
            res[res_len++] = strdup("null");
        }
    }
    // Remove trailing "null"s
    while (res_len > 0 && strcmp(res[res_len-1], "null") == 0)
        res_len--;
    printf("[");
    for (int i = 0; i < res_len; ++i) {
        if (i) printf(",");
        printf("%s", res[i]);
        free(res[i]);
    }
    printf("]\n");
}

int main() {
    const char* inputs[] = {
        "[1,3,null,null,2]",
        "[3,1,4,null,null,2]"
    };
    int num_cases = sizeof(inputs) / sizeof(inputs[0]);
    for (int i = 0; i < num_cases; ++i) {
        printf("Input: root = %s\n", inputs[i]);
        char arr[MAX_NODES][16];
        int n = 0;
        parseInput(inputs[i], arr, &n);
        struct TreeNode* root = buildTree(arr, n);
        recoverTree(root);
        printf("Output: ");
        printTree(root);
    }
    return 0;
}
