#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

// Dynamically create a new room node in the binary tree
TreeNode* createRoomNode(int roomId, const char *name, const char *description) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed for tree node.\n");
        return NULL;
    }

    newNode->roomId = roomId;
    if (name != NULL) {
        strncpy(newNode->roomName, name, MAX_TREE_STR_LEN - 1);
        newNode->roomName[MAX_TREE_STR_LEN - 1] = '\0';
    } else {
        strcpy(newNode->roomName, "Unknown");
    }

    if (description != NULL) {
        strncpy(newNode->description, description, 99);
        newNode->description[99] = '\0';
    } else {
        strcpy(newNode->description, "");
    }

    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Build the hierarchical dungeon tree
/*
 Tree layout:
                        Entrance (0)
                       /            \
                Armory (1)         Dark Hall (3)
               /          \        /            \
          Library (2)  Potion (4) Monster (5)  Treasure (6)
                                                  \
                                                Boss Room (7)
                                                    \
                                                   Exit (8)
*/
TreeNode* buildDungeonTree(void) {
    TreeNode *root = createRoomNode(0, "Entrance", "The safe starting area of the dungeon.");
    if (root == NULL) return NULL;

    root->left = createRoomNode(1, "Armory", "Ancient armory filled with discarded weapons.");
    root->right = createRoomNode(3, "Dark Hall", "Ominous hallway echoing with strange noises.");

    if (root->left) {
        root->left->left = createRoomNode(2, "Library", "A dusty archive of ancient dungeon maps.");
        root->left->right = createRoomNode(4, "Potion Room", "A chamber stocked with revitalizing draughts.");
    }

    if (root->right) {
        root->right->left = createRoomNode(5, "Monster Room", "A dangerous den harboring hostile creatures.");
        root->right->right = createRoomNode(6, "Treasure Room", "Glittering chamber guarding the dungeon key!");

        if (root->right->right) {
            root->right->right->right = createRoomNode(7, "Boss Room", "Lair of the formidable Dungeon Dragon!");
            if (root->right->right->right) {
                root->right->right->right->right = createRoomNode(8, "Exit Portal", "The enchanted gateway leading back to freedom.");
            }
        }
    }

    return root;
}

// Recursion: Preorder Traversal (Root -> Left -> Right)
void preorderTraversal(const TreeNode *root) {
    if (root == NULL) return;

    printf("  -> [%d] %s", root->roomId, root->roomName);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Recursion: Inorder Traversal (Left -> Root -> Right)
void inorderTraversal(const TreeNode *root) {
    if (root == NULL) return;

    inorderTraversal(root->left);
    printf("  -> [%d] %s", root->roomId, root->roomName);
    inorderTraversal(root->right);
}

// Recursion: Postorder Traversal (Left -> Right -> Root)
void postorderTraversal(const TreeNode *root) {
    if (root == NULL) return;

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("  -> [%d] %s", root->roomId, root->roomName);
}

// Display tree hierarchically in ASCII for academic demonstration
void displayTreeHierarchical(const TreeNode *root, int space) {
    if (root == NULL) return;

    space += 8;
    displayTreeHierarchical(root->right, space);

    printf("\n");
    for (int i = 8; i < space; i++) printf(" ");
    printf("[%d: %s]\n", root->roomId, root->roomName);

    displayTreeHierarchical(root->left, space);
}

// Recursion: Free all tree nodes using postorder deallocation
void freeTree(TreeNode *root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
