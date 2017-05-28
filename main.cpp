#include <iostream>
#include <sstream>

using namespace std;

// TODO: Make two classes for each task with tests
// TODO: Make comments for each test case

// Task 1
// 
// Given a Binary Tree and a key, write a function that prints
// all the ancestors of the key in the givenbinary tree.
//

struct node {
    
    int data;
    struct node* left_child = nullptr;
    struct node* right_child = nullptr;
    
    node(int val) {
        data = val;
    }
};

bool have_ancestors(struct node* root, int node_data) {
    if (root == nullptr) {
        return false;
    }
    // cout << root -> data << endl;
    
    if (root -> data == node_data) {
        return true;
    }
    
    if (have_ancestors(root -> left_child, node_data) || have_ancestors(root -> right_child, node_data)) {
        cout << root -> data << " ";
        return true;
    }
    return false;
}

void test_task1() {
    
    // case 1
    node* root = new node(16);
    root -> left_child = new node(9);
    root -> right_child = new node(18);
    
    std::stringstream ss;
    auto old_buf = std::cout.rdbuf(ss.rdbuf());
    
    have_ancestors(root, 18);
    
    std::cout.rdbuf(old_buf); // reset

    if (ss.str() == "16 ") {
        cout << "case 1 - OK" << endl;
    }
    
    // case 2
    root = new node(16);
    root -> left_child = new node(9);
    root -> right_child = new node(18);
    root -> left_child -> left_child = new node(3);
    root -> left_child -> right_child = new node(14);
    root -> left_child -> right_child -> right_child = new node(5);
    
    old_buf = std::cout.rdbuf(ss.rdbuf());
    ss.str(std::string());
    
    have_ancestors(root, 5);
    
    std::cout.rdbuf(old_buf); // reset
    
    if (ss.str() == "14 9 16 ") {
        cout << "case 2 - OK" << endl;
    }
    
    // case 3
    root = new node(16);
    
    old_buf = std::cout.rdbuf(ss.rdbuf());
    ss.str(std::string());
    
    have_ancestors(root, 16);
    
    std::cout.rdbuf(old_buf); // reset
    
    if (ss.str() == "") {
        cout << "case 3 - OK" << endl;
    }
    
    // case 4
    root = nullptr;
    
    old_buf = std::cout.rdbuf(ss.rdbuf());
    ss.str(std::string());
    
    have_ancestors(root, 5);
    
    std::cout.rdbuf(old_buf); // reset
    
    if (ss.str() == "") {
        cout << "case 4 - OK" << endl;
    }
    
    // case 5
    root = new node(16);
    
    old_buf = std::cout.rdbuf(ss.rdbuf());
    ss.str(std::string());
    
    have_ancestors(root, 5);
    
    std::cout.rdbuf(old_buf); // reset
    
    if (ss.str() == "") {
        cout << "case 5 - OK" << endl;
    }
    
}

// Task 2
//
// Design an algorithm and write code to find the lowest common ancestor
// of two nodes in a binary tree. Avoid storing additional nodes in a data structure.
//

struct node* find_low_com_ancestor(struct node* root, int n1, int n2) {
    if (root == nullptr) {
        return nullptr;
    }
    
    if (root -> data == n1 || root -> data == n2) {
        return root;
    }
    
    node* left_lca  = find_low_com_ancestor(root -> left_child, n1, n2);
    node* right_lca = find_low_com_ancestor(root -> right_child, n1, n2);
    
    if (left_lca && right_lca) {
        return root;
    }
    
    return (left_lca != NULL) ? left_lca : right_lca;
}

void test_task2() {
    
    // case 1
    node* root = new node(16);
    root -> left_child = new node(9);
    root -> right_child = new node(18);
    
    if (find_low_com_ancestor(root, 9, 18) == root) {
        cout << "case 1 - OK" << endl;
    }
    
    // case 2
    root = new node(16);
    root -> left_child = new node(9);
    root -> right_child = new node(18);
    root -> left_child -> left_child = new node(3);
    root -> left_child -> right_child = new node(14);
    root -> left_child -> right_child -> right_child = new node(5);
    
    if (find_low_com_ancestor(root, 3, 14) == root -> left_child) {
        cout << "case 2 - OK" << endl;
    }
    
    // case 3
    root = new node(16);
    
    if (find_low_com_ancestor(root, 16, 14) == root) {
        cout << "case 3 - OK" << endl;
    }

    // case 4
    root = nullptr;
    
    if (find_low_com_ancestor(root, 16, 14) == nullptr) {
        cout << "case 4 - OK" << endl;
    }

    // case 5
    root = new node(16);
    root -> left_child = new node(9);
    root -> right_child = new node(18);
    root -> left_child -> right_child = new node(14);
    root -> left_child -> right_child -> right_child = new node(90);
    root -> right_child -> right_child = new node(10);
    root -> right_child -> right_child -> right_child = new node(50);
    
    if (find_low_com_ancestor(root, 90, 50) == root) {
        cout << "case 5 - OK" << endl;
    }
    
}


int main(int argc, const char * argv[]) {
    cout << "Testing task1..." << endl;
    test_task1();

    cout << "Testing task2..." << endl;
    test_task2();
    return 0;
}
