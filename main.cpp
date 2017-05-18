//
//  main.cpp
//  CodeU_ass1
//
//  Created by Elizaveta on 18/05/2017.
//  Copyright © 2017 Elizaveta. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string is_permutation(string str1, string str2) {
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    
    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());
    
    return str1 == str2 ? "True" : "False";
}

struct Node {
    Node* head;
    Node* next;
    int value;
};

void find_k_to_end(struct Node* head, int k, int &result_value) {
    int length = 0;
    int i = 0;
    struct Node *curr = head;
    
    while (curr) {
        curr = curr -> next;
        length++;
    }
    
    if (length < k) {
        return;
    }
    
    curr = head;
    for (i = 1; i < length - k + 1; ++i) {
        curr = curr -> next;
    }
    
    result_value = curr -> value;
    return;
}

int main(int argc, const char * argv[]) {
    
    // Task1
    cout << is_permutation("Listen", "Silent") << "\n";
    cout << is_permutation("Triangle", "Integral") << "\n";
    cout << is_permutation("Apple", "Pabble") << "\n";
    cout << is_permutation("", "") << "\n";
    
    // Task2
    Node* head = new Node;
    head -> value = 5;
    Node* next = new Node;
    next -> value = 10;
    next -> next = NULL;
    head -> next = next;
    
    int result_value;
    
    find_k_to_end(head, 1, result_value);
    cout << result_value << "\n";
    
    find_k_to_end(head, 2, result_value);
    cout << result_value << "\n";
    
    return 0;
}
