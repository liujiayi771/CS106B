#include <iostream>

using namespace std;

struct nodeT {
    string key;
    nodeT * left;
    nodeT * right;
};

bool treeEqual(nodeT * one, nodeT * two);

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
    nodeT * two = one;
    if(treeEqual(one, two)) {
        cout << "Equal" << endl;
    } else {
        cout << "Not equal" << endl;
    }
    return 0;
}

bool treeEqual(nodeT * one, nodeT * two)
{
    if(one == NULL  && two == NULL) {
        return true;
    }
    if(one == NULL || two == NULL) {
        return false;
    }
    return ((one->key == two->key) && treeEqual(one->left, two->left) && treeEqual(one->right, two->right));
}
