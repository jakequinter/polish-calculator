//
//  calculator.cpp
//  Calculator
//
//  Created by Jake Quinter on 11/13/20.
//

#include "calculator.h"

// ==============================================================================================================
// public methods
// ==============================================================================================================

void calculator::calculatorTest(calculator polishCalculator) {
    DataNode *node = NULL;
    TreeNode *treeNode = NULL;
    TreeNode *root = NULL;
    int result;
    int expressionResult;
    
    cout << "Enter an expression: ";
    
    // allocate the memory
    node = (DataNode*)malloc(sizeof(DataNode));
    
    while ((result = polishCalculator.scan(node, stdin)) != EOF) {
        if (result == FAIL) {
            cout << "Error: Please enter a valid expression\n";
            break;
        }
        
        treeNode = polishCalculator.make_TreeNode(node);
        polishCalculator.insertTreeNode(treeNode, &root);
        
        // make a new DataNode
        node = (DataNode*)malloc(sizeof(DataNode));
    }
    
    // ==============================================================================================================
    // traversals testing
    // ==============================================================================================================
    
    // inorder traversal
    polishCalculator.inOrderTraversal(root);
    cout << endl;
    
    // preorder traversal
    polishCalculator.preOrderTraversal(root);
    cout << endl;
    
    // postorder traversal
    polishCalculator.postOrderTraversal(root);
    cout << endl;
    
    // calculation
    expressionResult = polishCalculator.postOrderCalculate(root);
    cout << "Result of Calculation: " << expressionResult << endl;
    
    polishCalculator.postOrderDelete(root);
}

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

// inorder: left -> parent -> right
int calculator::inOrderTraversal(TreeNode *treeNode) {
    if (treeNode != (TreeNode*)NULL) {
        inOrderTraversal(treeNode->leftChild);
        print(treeNode);
        inOrderTraversal(treeNode->rightChild);
    }
    
    return 0;
}

// preorder: parent -> left -> right
int calculator::preOrderTraversal(TreeNode *treeNode) {
    if (treeNode != (TreeNode*)NULL) {
        print(treeNode);
        preOrderTraversal(treeNode->leftChild);
        preOrderTraversal(treeNode->rightChild);
    }
    
    return 0;
}

// postorder: left -> right -> parent
int calculator::postOrderTraversal(TreeNode *treeNode) {
    if (treeNode != (TreeNode*)NULL) {
        postOrderTraversal(treeNode->leftChild);
        postOrderTraversal(treeNode->rightChild);
        print(treeNode);
    }
    
    return 0;
}



int calculator::postOrderCalculate(TreeNode *treeNode)
{
    int nodeValue = 0;
    int leftData = 0;
    int rightData = 0;
    if ( treeNode != (TreeNode *)NULL )
    {
        leftData = postOrderCalculate(treeNode->leftChild);
        rightData = postOrderCalculate(treeNode->rightChild);
        
        nodeValue = evaluate(treeNode, leftData, rightData);
    }
    return nodeValue;
}

// call in post order delete form
void calculator::postOrderDelete(TreeNode *treeNode) {
    if (treeNode != (TreeNode *)NULL) {
        postOrderDelete(treeNode->leftChild);
        postOrderDelete(treeNode->rightChild);
        
        deleteNode(treeNode);
    }
}

// ==============================================================================================================
// private methods
// ==============================================================================================================

int calculator::evaluate(TreeNode *treeNode, int leftData, int rightData) {
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

void calculator::deleteNode(TreeNode *treeNode) {
    print(treeNode);
    
    free(treeNode->nodeData);
    free(treeNode);
}



void calculator::print(TreeNode *treeNode) {
    if (treeNode->nodeData->dataType == OPERATOR)
        cout << (char)treeNode->nodeData->data << " ";
    else
        cout << treeNode->nodeData->data << " ";
}
