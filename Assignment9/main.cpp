#include <iostream>

using namespace std;

struct TreeNode
{
    int key;
    TreeNode *leftChild;
    TreeNode *rightChild;
    TreeNode *parent;
};

int findHeight(TreeNode *node)
{
    if(node == NULL)
    {
        return 0;
    }
    return 1 + max(findHeight(node->leftChild), findHeight(node->rightChild));
}

int MaxHeightDifference(TreeNode *root)
{
    int left = findHeight(root->leftChild);
    int right = findHeight(root->rightChild);
    //cout << left << endl;
    //cout << right << endl;
    if(left > right)
    {
        return left-right;
    }
    else if(left < right)
    {
        return left-right;
    }
    else
    {
        return 0;
    }
}

void leftRotation(TreeNode *root)
{
    TreeNode *x = root;
    TreeNode *y = x->rightChild;
    x->rightChild = y->leftChild;
    if(y->leftChild != NULL)
    {
        y->leftChild->parent = x;
    }
    y->parent = x->parent;
    root = y;
    y->parent = NULL;
    y->leftChild = x;
    x->parent = y;
}

void rightRotation(TreeNode *root)
{
    TreeNode *x = root;
    TreeNode *y = x->leftChild;
    x->leftChild = y->rightChild;
    if(y->rightChild != NULL)
    {
        y->rightChild->parent = x;
    }
    y->parent = x->parent;
    root = x;
    y->parent = NULL;
    y->rightChild = x;
    x->parent = y;
}

TreeNode* CheckHeightAndRotate(TreeNode *root)
{
    while(abs(MaxHeightDifference(root)) > 1)
    {
        if(MaxHeightDifference(root) > 0)
        {
            rightRotation(root);
        }
        else
        {
            leftRotation(root);
        }
    }
    return root;
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
