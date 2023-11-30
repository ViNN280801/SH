#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../include/splay_tree.h"

static Node *leftRotate(Node *node)
{
    // Takes a node as input, and it performs a left rotation on the node and its right child
    // The new root of the rotated subtree is returned
    Node *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    return newRoot;
}

static Node *rightRotate(Node *node)
{
    // Takes a node as input, and it performs a right rotation on the node and its left child
    // The new root of the rotated subtree is returned
    Node *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    return newRoot;
}

static Node *splay(Node *root, int key, int *comparisons)
{
    // Base case: If the root is null or the root node has the desired key, we return the root
    if (!root || root->key == key)
    {
        // Increment comparisons count since a comparison was made
        (*comparisons)++;
        return root;
    }

    // Increment comparisons count since a comparison was made
    (*comparisons)++;

    if (key < root->key)
    {
        if (!root->left)
            return root;

        if (key < root->left->key)
        {
            // Recursively splay the left child's left child
            root->left->left = splay(root->left->left, key, comparisons);
            root = rightRotate(root);
        }
        else if (key > root->left->key)
        {
            // Recursively splay the left child's right child
            root->left->right = splay(root->left->right, key, comparisons);
            if (root->left->right)
                root->left = leftRotate(root->left);
        }
        // Performing a right rotation if the left child is not null
        return (root->left) ? rightRotate(root) : root;
    }
    // If the desired key is greater than the root's key, we handle the right subtree
    else
    {
        // If the root's right child is null, we return the root
        if (!root->right)
            return root;

        if (key > root->right->key)
        {
            // Recursively splay the right child's right child
            root->right->right = splay(root->right->right, key, comparisons);
            root = leftRotate(root);
        }
        else if (key < root->right->key)
        {
            // Recursively splay the right child's left child
            root->right->left = splay(root->right->left, key, comparisons);
            if (root->right->left)
                root->right = rightRotate(root->right);
        }
        // Performing left rotation if the right child is not null
        return (root->right) ? leftRotate(root) : root;
    }
}

SplayTree *init_splay_tree()
{

    SplayTree *tree = (SplayTree *)calloc(1, sizeof(SplayTree));
    if (!tree)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    tree->root = NULL;
    return tree;
}

Node *create_node(int key)
{

    Node *node = (Node *)calloc(1, sizeof(Node));
    if (!node)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    node->key = key;
    node->left = node->right = NULL;

    return node;
}

void insert(SplayTree *tree, int key)
{
    // Check if the splay tree is valid
    if (!tree)
        return;

    // Dummy variable for 'splay()' function
    int comparisons = 0;

    // Splay the tree to bring the target node (or its parent) closer to the root
    tree->root = splay(tree->root, key, &comparisons);

    // Check if the root is NULL (does tree is empty?)
    if (!tree->root)
    {
        // Create a new node with the given key and make it the new root
        tree->root = create_node(key);
        return;
    }

    // The key is smaller than the root's key
    if (key < tree->root->key)
    {
        // Create a new node with the key and insert it to the left of the root
        Node *node = create_node(key);
        node->left = tree->root->left;
        node->right = tree->root;
        tree->root->left = NULL;
        tree->root = node;
    }
    // The key is larger than the root's key
    else if (key > tree->root->key)
    {
        // Create a new node with the key and insert it to the right of the root
        Node *node = create_node(key);
        node->right = tree->root->right;
        node->left = tree->root;
        tree->root->right = NULL;
        tree->root = node;
    }
}

void in_order_traverse(Node *root)
{
    if (root)
    {
        in_order_traverse(root->left);
        printf("%d ", root->key);
        in_order_traverse(root->right);
    }
}

Node *search(SplayTree *tree, int key, int *comparisons)
{
    *comparisons = 0;
    tree->root = splay(tree->root, key, comparisons);
    return (tree->root->key == key) ? tree->root : NULL;
}

static void free_splay_tree_helper(Node *root)
{
    if (root)
    {
        free_splay_tree_helper(root->left);
        free_splay_tree_helper(root->right);
        free(root);
        root = NULL;
    }
}

size_t splay_tree_memory_usage(Node *root)
{
    if (!root)
        return 0ul;

    // Calculate memory used by the root and its children recursively
    size_t node_memory = sizeof(Node),
           left_memory = splay_tree_memory_usage(root->left),
           right_memory = splay_tree_memory_usage(root->right);

    return node_memory + left_memory + right_memory;
}

void destroy_splay_tree(SplayTree *tree)
{
    if (tree)
    {
        free_splay_tree_helper(tree->root);
        free(tree);
        tree = NULL;
    }
}
