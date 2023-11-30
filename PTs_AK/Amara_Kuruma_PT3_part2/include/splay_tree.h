#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

// Struct for the nodes in the splay-tree
typedef struct Node
{
    int key;            // Key value of the node
    struct Node *left;  // Ptr to the left child node
    struct Node *right; // Ptr to the right child node
} Node;

// Splay-tree structure, which includes a ptr to the root node
typedef struct SplayTree
{
    Node *root; // Ptr to the root node of the tree
} SplayTree;

// Initializing a new splay-tree
// Returns a ptr to it
SplayTree *init_splay_tree();

// Creating a new node with the given key value
// Returns a ptr to it
Node *create_node(int key);

// Inserting a new node with the given key into the splay-tree
void insert(SplayTree *tree, int key);

// Performs an in-order traversal of the splay-tree, starting from the specified root
void in_order_traverse(Node *root);

// Search for a node with the given key
// Returns "NULL" if key not found
Node *search(SplayTree *tree, int key, int *comparisons);

// Calculate memory usage of splay tree
size_t splay_tree_memory_usage(Node *root);

// Destoying object of splay-tree, freeing memory
void destroy_splay_tree(SplayTree *tree);

#endif // !SPLAY_TREE_H
