#include <iostream>

using namespace std;

struct nodeT {
    string key;
    nodeT * left;
    nodeT * right;
};

void TrimLeaves(nodeT * & tree);
void display(nodeT * tree);

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
    cout << "Before trim leaves: " << endl;
    display(one);
    cout << endl;
    TrimLeaves(one);
    cout << "After trim leaves: " << endl;
    display(one);
    return 0;
}

void TrimLeaves(nodeT * & tree)
{
    if(tree != NULL) {
        if(tree->left == NULL && tree->right == NULL) {
            delete tree;
            tree = NULL;
        } else {
            TrimLeaves(tree->left);
            TrimLeaves(tree->right);
        }
    }
}

void display(nodeT * tree) {
    if(tree != NULL) {
        cout << tree->key << "  ";
        display(tree->left);
        display(tree->right);
    }
}
