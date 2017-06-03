#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// TODO: Make two classes for each task with tests
// TODO: Make comments for each test case

// Task 1
// 
// Given a Binary Tree and a key, write a function that prints
// all the ancestors of the key in the given binary tree.
//

struct node {
    
    int data;
    struct node* left_child = nullptr;
    struct node* right_child = nullptr;
    
    node(int val) {
        data = val;
    }
};

bool have_ancestors(struct node* root, int node_data, vector<int> &nodes_to_print) {
    if (root == nullptr) {
        return false;
    }
    
    if (root -> data == node_data) {
        return true;
    }
    
    if (have_ancestors(root -> left_child, node_data, nodes_to_print) || have_ancestors(root -> right_child, node_data, nodes_to_print)) {
        nodes_to_print.push_back(root -> data);
        return true;
    }
    return false;
}

void assert_output_task1(struct node* root, int node_data, string output, int case_num) {
    std::stringstream ss;
    auto old_buf = std::cout.rdbuf(ss.rdbuf());
    
    vector<int> nodes_to_print;
    
    have_ancestors(root, node_data, nodes_to_print);
    for(int i = 0; i < nodes_to_print.size(); ++i) {
        
        cout << nodes_to_print[i] << " ";
    }
    
    std::cout.rdbuf(old_buf); // reset
    if (ss.str() == output) {
        cout << "case " << case_num << " - OK" << endl;
        return;
    }
    cout << "case " << case_num << " - FAIL for the reason: " << endl;
    if (ss.str() != output) {
        cout << "Function output: \"" << ss.str() << "\" is not equal to expected output: \"" << output  << "\"" << endl;
    }
}

void test_task1() {
    
    // case 1
    node* root = new node(16);
    root -> left_child = new node(9);
    root -> right_child = new node(18);
    
    assert_output_task1(root, 18, "16 ", 1);
    
    // case 2
    root = new node(16);
    root -> left_child = new node(9);
    root -> right_child = new node(18);
    root -> left_child -> left_child = new node(3);
    root -> left_child -> right_child = new node(14);
    root -> left_child -> right_child -> right_child = new node(5);
    
    assert_output_task1(root, 5, "14 9 16 ", 2);
    
    // case 3
    root = new node(16);
    
    assert_output_task1(root, 16, "", 3);
    
    // case 4
    root = nullptr;
    
    assert_output_task1(root, 5, "", 4);
    
    // case 5
    root = new node(16);
    
    assert_output_task1(root, 5, "", 5);
}

// Task 2
//
// Design an algorithm and write code to find the lowest common ancestor
// of two nodes in a binary tree. Avoid storing additional nodes in a data structure.
//

struct node* find_low_com_ancestor(struct node* root, int n1, int n2, pair<bool, bool> &values_exists) {
    if (root == nullptr) {
        return nullptr;
    }
    
    if (root -> data == n1 || root -> data == n2) {
        (root -> data == n1) ? values_exists.first = true : values_exists.second = true;
        return root;
    }
    
    node* left_lca  = find_low_com_ancestor(root -> left_child, n1, n2, values_exists);
    node* right_lca = find_low_com_ancestor(root -> right_child, n1, n2, values_exists);
    
    if (left_lca && right_lca) {
        return root;
    }

    return (left_lca != nullptr) ? left_lca : right_lca;
}

struct node* return_low_com_ancestor(struct node* root, int n1, int n2) {
    pair<bool, bool> values_exists;
    values_exists.first = false;
    values_exists.second = false;
    
    node* ancestor = find_low_com_ancestor(root, n1, n2, values_exists);
    if (values_exists.first && values_exists.second) {
        return ancestor;
    } else {
        return nullptr;
    }
}

void assert_output_task2(node* tree_root, int n1, int n2, node* output_node, int case_num) {
    
    
    node* ancestor = return_low_com_ancestor(tree_root, n1, n2);

    if (ancestor == output_node) {
        cout << "case " << case_num << " - OK" << endl;
        return;
    }
    cout << "case " << case_num << " - FAIL for the reason: " << endl;
    string func_output;
    if (ancestor == nullptr) {
        func_output = "nullptr";
    } else {
        func_output = to_string(ancestor -> data);
    }
    
    string exp_output;
    if (output_node == nullptr) {
        exp_output = "nullptr";
    } else {
        exp_output = to_string(output_node -> data);
    }
    cout << "Function output: \"" << func_output << "\" is not equal to expected output: \"" << exp_output << "\"" << endl;
    
}

void test_task2() {
    
    // case 1
    node* root = new node(16);
    root -> left_child = new node(9);
    root -> right_child = new node(18);
    
    assert_output_task2(root, 9, 18, root, 1);
    
    // case 2
    root = new node(16);
    root -> left_child = new node(9);
    root -> right_child = new node(18);
    root -> left_child -> left_child = new node(3);
    root -> left_child -> right_child = new node(14);
    root -> left_child -> right_child -> right_child = new node(5);
    
    assert_output_task2(root, 3, 14, root -> left_child, 2);
    
    // case 3
    root = new node(16);
    
    assert_output_task2(root, 16, 14, nullptr, 3);

    // case 4
    root = nullptr;
    
    assert_output_task2(root, 16, 14, nullptr, 4);

    // case 5
    root = new node(16);
    root -> left_child = new node(9);
    root -> right_child = new node(18);
    root -> left_child -> right_child = new node(14);
    root -> left_child -> right_child -> right_child = new node(90);
    root -> right_child -> right_child = new node(10);
    root -> right_child -> right_child -> right_child = new node(50);
    
    assert_output_task2(root, 90, 50, root, 5);
    
}


int main(int argc, const char * argv[]) {
    cout << "Testing task1..." << endl;
    test_task1();

    cout << "Testing task2..." << endl;
    test_task2();
    return 0;
}
