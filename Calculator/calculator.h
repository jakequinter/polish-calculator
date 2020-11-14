//
//  calculator.hpp
//  Calculator
//
//  Created by Jake Quinter on 11/13/20.
//

#ifndef calculator_h
#define calculator_h

#define OPERATOR 0
#define DATA 1

#define FAIL 1
#define SUCCEED 0

#include <iostream>

using namespace std;

typedef struct {
    int data;
    int dataType;
} DataNode;

typedef struct node {
    DataNode *nodeData;
    struct node *leftChild;
    struct node *rightChild;
} TreeNode;

int evaluate(TreeNode *treeNode, int leftData, int rightData);
int deleteNode(TreeNode *treeNode, int leftData, int rightData);
int print(TreeNode *treeNode, int leftData, int rightData);

class calculator {
public:
    void calculate();
    
private:
    TreeNode *make_TreeNode(DataNode *data);
    void insertTreeNode( TreeNode *newTreeNode, TreeNode **root);
    int scan(DataNode *data, FILE *fptr);
    int inOrderTraversal(TreeNode *treeNode, int (*fn)(TreeNode *, int, int));
    int preOrderTraversal(TreeNode *treeNode, int (*fn)(TreeNode *, int, int));
    int postOrderTraversal(TreeNode *treeNode, int (*visit)(TreeNode *, int, int));
};

#endif
