#include <iostream>
using namespace std;

class Node {
public:
    int numb;
    Node* right;
    Node* left;
    int height;

    Node(int value) {
        numb = value;
        right = 0;
        left = 0;
        height = 1;
    }
};

class Tree {
private:
    Node* b;

    void UpdateHeight(Node* node) {
        if (node == 0) return;
        int l = 0;
        int r = 0;
        if (node->left != 0) l = node->left->height;
        if (node->right != 0) r = node->right->height;
        node->height = max(l, r) + 1;
    }

    Node* rotateRight(Node* node) {
        Node* l = node->left;
        Node* lr = l->right;
        l->right = node;
        node->left = lr;

        UpdateHeight(node);
        UpdateHeight(l);
        return l;
    }

    Node* rotateLeft(Node* node) {
        Node* r = node->right;
        Node* rl = r->left;

        r->left = node;
        node->right = rl;
        UpdateHeight(node);
        UpdateHeight(r);

        return r;
    }

    Node* rotateLeftRight(Node* node) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    Node* rotateRightLeft(Node* node) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }


    int Balance(Node* node) {
        if (node == 0) return 0;
        int l = 0;
        int r = 0;
        if (node->left != 0) l = node->left->height;
        if (node->right != 0) r = node->right->height;
        return l - r;
    }

    Node* balanceNode(Node* node) {
        if (node == 0) return node;

        int balance = Balance(node);
        if (balance > 1 && Balance(node->left) >= 0) {
            return rotateRight(node);
        }
        if (balance > 1 && Balance(node->left) < 0) {
            return rotateLeftRight(node);
        }
        if (balance < -1 && Balance(node->right) <= 0) {
            return rotateLeft(node);
        }
        if (balance < -1 && Balance(node->right) > 0) {
            return rotateRightLeft(node);
        }
        return node;
    }

    Node* Add(Node* node, int value) {
        if (node == 0) {
            return new Node(value);
        }
        if (value > node->numb) {
            node->right = Add(node->right, value);
        }
        else if (value < node->numb) {
            node->left = Add(node->left, value);
        }
        UpdateHeight(node);
        return balanceNode(node);
    }

    Node* Search(Node* node, int value) {
        if (node == 0) {
            return 0;
        }
        if (value == node->numb) {
            return node;
        }
        if (value < node->numb) {
            return Search(node->left, value);
        }
        else {
            return Search(node->right, value);
        }
    }

    Node* Min(Node* node) {
        if (node == 0) {
            return 0;
        }
        if (node->left == 0) {
            return node;
        }
        return Min(node->left);
    }

    Node* Max(Node* node) {
        if (node == 0) {
            return 0;
        }
        if (node->right == 0) {
            return node;
        }
        return Max(node->right);
    }

    Node* Delete(Node* node, int value) {
        if (node == 0) {
            return 0;
        }
        else if (value < node->numb) {
            node->left = Delete(node->left, value);
        }
        else if (value > node->numb) {
            node->right = Delete(node->right, value);
        }
        else {
            if (node->left == 0) {
                Node* a = node->right;
                delete node;
                return a;
            }
            else if (node->right == 0) {
                Node* a = node->left;
                delete node;
                return a;
            }
            Node* a = Min(node->right);
            node->numb = a->numb;
            node->right = Delete(node->right, a->numb);
        }

        if (node == 0) return node;

        UpdateHeight(node);
        return balanceNode(node);
    }

    void PreOrder(Node* node) {
        if (node == 0) return;
        cout << node->numb << "(" << node->height << ") ";
        PreOrder(node->left);
        PreOrder(node->right);
    }

    void ClassicOrder(Node* node) {
        if (node == 0) return;
        ClassicOrder(node->left);
        cout << node->numb << "(" << node->height << ") ";
        ClassicOrder(node->right);
    }

    void PostOrder(Node* node) {
        if (node == 0) return;
        PostOrder(node->left);
        PostOrder(node->right);
        cout << node->numb << "(" << node->height << ") ";
    }

public:
    Tree() {
        b = 0;
    }

    void Add(int value) {
        b = Add(b, value);
    }

    void PostOrder() {
        PostOrder(b);
        cout << endl;
    }

    void PreOrder() {
        PreOrder(b);
        cout << endl;
    }

    void ClassicOrder() {
        ClassicOrder(b);
        cout << endl;
    }
};

int main() {
    Tree a;
    a.Add(5);
    a.Add(3);
    a.Add(0);
    a.Add(4);
    a.PostOrder();
}