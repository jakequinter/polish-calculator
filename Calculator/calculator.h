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

class calculator {
public:
    void calculatorTest(calculator polishCalculator);
    TreeNode *make_TreeNode(DataNode *data);
    int scan(DataNode *data, FILE *fptr);
    void insertTreeNode( TreeNode *newTreeNode, TreeNode **root);
    int inOrderTraversal(TreeNode *treeNode);
    int preOrderTraversal(TreeNode *treeNode);
    int postOrderTraversal(TreeNode *treeNode);
    int postOrderCalculate(TreeNode *TreeNode);
    void postOrderDelete(TreeNode *currentTreeNode);
    
private:
    int evaluate(TreeNode *treeNode, int leftData, int rightData);
    void deleteNode(TreeNode *treeNode);
    void print(TreeNode *treeNode);
};

#endif
