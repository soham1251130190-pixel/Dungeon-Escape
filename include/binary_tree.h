#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#define MAX_TREE_STR_LEN 50

// Binary tree node representing the hierarchical dungeon layout
// Recursion is used to traverse this structure in Preorder, Inorder, and Postorder.
typedef struct TreeNode {
    int roomId;
    char roomName[MAX_TREE_STR_LEN];
    char description[100];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function prototypes
TreeNode* createRoomNode(int roomId, const char *name, const char *description);
TreeNode* buildDungeonTree(void);
void preorderTraversal(const TreeNode *root);
void inorderTraversal(const TreeNode *root);
void postorderTraversal(const TreeNode *root);
void displayTreeHierarchical(const TreeNode *root, int space);
void freeTree(TreeNode *root);

#endif // BINARY_TREE_H
