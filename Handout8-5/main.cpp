#include <iostream>

using namespace std;

struct nodeT {
    string key;
    nodeT * left;
    nodeT * right;
};

int height(nodeT * tree);
bool IsBalanced(nodeT * tree);

int main()
{
    nodeT * one = new nodeT;
    nodeT * left1 = new nodeT;
    nodeT * left2 = new nodeT;
    nodeT * right1 = new nodeT;
    nodeT * right2 = new nodeT;
    one->key = "one";one->left = left1;one->right = right1;
    left1->key = "left1";left1->left = left2;left1->right = right2;
    left2->key = "left2";left2->left = NULL;left2->right = NULL;
    right1->key = "right1";right1->left = NULL;right1->right = NULL;
    right2->key = "right2";right2->left = NULL;right2->right = NULL;
    if(IsBalanced(one)) {
        cout << "This is a balanced tree" << endl;
    } else {
        cout << "This is not a balanced tree" << endl;
    }
    return 0;
}

int height(nodeT * tree)
{
    if(tree == NULL) {
        return 0;
    } else {
        return (1 + max(height(tree->left), height(tree->right)));
    }
}

bool IsBalanced(nodeT * tree)
{
    if(tree == NULL) {
        return true;
    } else {
        return ((abs(height(tree->left) - height(tree->right)) <= 1) && IsBalanced(tree->left) && IsBalanced(tree->right));
    }
}
