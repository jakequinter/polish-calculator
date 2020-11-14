//
//  calculator.cpp
//  Calculator
//
//  Created by Jake Quinter on 11/13/20.
//

#include "calculator.h"

// ==============================================================================================================
// outside methods
// ==============================================================================================================

int evaluate(TreeNode *treeNode, int leftData, int rightData) {
    int nodeValue = 0;
    switch ( treeNode->nodeData->data ) {
        case '+':
            nodeValue = leftData + rightData;
            break;
        case '-':
            nodeValue = leftData - rightData;
            break;
        case '*':
            nodeValue = leftData * rightData;
            break;
        case '/':
            nodeValue = leftData / rightData;
            break;
        default:
            nodeValue = treeNode->nodeData->data;
            break;
    }
    return nodeValue;
}

int deleteNode(TreeNode *treeNode, int leftData, int rightData) {
    print(treeNode, leftData, rightData);
    
    free(treeNode->nodeData);
    free(treeNode);
    
    return 0;
}

int print(TreeNode *treeNode, int leftData, int rightData) {
    if (treeNode->nodeData->dataType == OPERATOR)
        cout << (char)treeNode->nodeData->data << " ";
    else
        cout << treeNode->nodeData->data << " ";
    
    return 0;
}

// ==============================================================================================================
// public methods
// ==============================================================================================================

void calculator::calculate() {
    DataNode *node = NULL;
    TreeNode *treeNode = NULL;
    TreeNode *root = NULL;
    int result;
    int expressionResult;
    
    cout << "Enter an expression: ";
    
    // allocate the memory
    node = (DataNode*)malloc(sizeof(DataNode));
    
    while ((result = scan(node, stdin)) != EOF) {
        if (result == FAIL) {
            cout << "Error: Please enter a valid expression\n";
            break;
        }
        
        treeNode = make_TreeNode(node);
        insertTreeNode(treeNode, &root);
        
        // make a new DataNode
        node = (DataNode*)malloc(sizeof(DataNode));
    }
    
    // *********************
    // traversals testing
    // *********************
    
    // inorder traversal
    cout << "\nIn Order Traversal: ";
    inOrderTraversal(root, print);
    cout << endl;
    
    // preorder traversal
    cout << "Pre Order Traversal: ";
    preOrderTraversal(root, print);
    cout << endl;
    
    // postorder traversal
    cout << "Post Order Traversal: ";
    postOrderTraversal(root, print);
    cout << endl;
    
    // calculation
    expressionResult = postOrderTraversal(root, evaluate);
    cout << "\nResult of Calculation: " << expressionResult << endl << endl;
    
    cout << "Deleting Tree..."  << endl;
    postOrderTraversal(root, deleteNode);
    cout << endl << "Tree deleted" << endl << endl;
}

// ==============================================================================================================
// private methods
// ==============================================================================================================

TreeNode* calculator::make_TreeNode(DataNode *data) {
    TreeNode *newptr = NULL;
    if (( newptr = (TreeNode *)malloc(sizeof(TreeNode))) != (TreeNode *)NULL ) {
        newptr->nodeData = data;
        
        newptr->leftChild = (TreeNode *)NULL;
        newptr->rightChild = (TreeNode *)NULL;
    }
    // returns NULL if the TreeNode was not allocated
    return (newptr);
}

void calculator::insertTreeNode( TreeNode *newTreeNode, TreeNode **root) {
    /* is this the first TreeNode? */
    if (*root == (TreeNode*)NULL){
        *root = newTreeNode;
    } else {
        switch ( newTreeNode->nodeData->dataType )
        {
            case OPERATOR:
                newTreeNode->leftChild = *root;
                *root = newTreeNode;
                break;
            case DATA:
                (*root)->rightChild = newTreeNode;
                break;
        }
    }
    return;
}

int calculator::scan(DataNode *node, FILE *fptr) {
    char c = 0;
    int resultCode = SUCCEED;
    while ( isspace( c = (char)fgetc(fptr) ) && (c != '\n') )
        ; /* eat the whitespace */
    
    switch ( c ) {
        case '+': case '-':
        case '*': case '/':
            (*node).dataType = OPERATOR;
            (*node).data = c;
            // resultCode = SUCCEED; as it is initialized
            break;
        case '0': case '1':
        case '2': case '3':
        case '4': case '5':
        case '6': case '7':
        case '8': case '9':
            (*node).dataType = DATA;
            (*node).data = c - '0';
            // resultCode = SUCCEED; as it is initialized
            break;
            
        case '\n': case EOF:
            (*node).data = 0;
            resultCode = EOF;
            break;
        default:
            /* anything else is an error */
            (*node).data = c;
            resultCode = FAIL;
            break;
    }
    return resultCode;
}

// inorder: left -> parent -> right
int calculator::inOrderTraversal(TreeNode *treeNode, int (*fn)(TreeNode *, int, int)) {
    int nodeValue = 0;
    int leftData = 0;
    int rightData = 0;
    
    if (treeNode != (TreeNode*)NULL) {
        leftData = inOrderTraversal(treeNode->leftChild, fn);
        nodeValue = (*fn)(treeNode, leftData, rightData);
        rightData = inOrderTraversal(treeNode->rightChild, fn);
    }
    
    return nodeValue;
}

// preorder: parent -> left -> right
int calculator::preOrderTraversal(TreeNode *treeNode, int (*fn)(TreeNode *, int, int)) {
    int nodeValue = 0;
    int leftData = 0;
    int rightData = 0;
    
    if (treeNode != (TreeNode*)NULL) {
        nodeValue = (*fn)(treeNode, leftData, rightData);
        leftData = preOrderTraversal(treeNode->leftChild, fn);
        rightData = preOrderTraversal(treeNode->rightChild, fn);
    }
    
    return nodeValue;
}

// postorder: left -> right -> parent
int calculator::postOrderTraversal(TreeNode *treeNode, int (*fn)(TreeNode *, int, int)) {
    int nodeValue = 0;
    int leftData = 0;
    int rightData = 0;
    
    if (treeNode != (TreeNode*)NULL) {
        leftData = postOrderTraversal(treeNode->leftChild, fn);
        rightData = postOrderTraversal(treeNode->rightChild, fn);
        nodeValue = (*fn)(treeNode, leftData, rightData);
    }
    
    return nodeValue;
}


