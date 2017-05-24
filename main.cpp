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

bool is_permutation(string str1, string str2) {
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    
    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());
    
    return str1 == str2;
}

struct Node {
    Node* next = NULL;
    int value;
    
    Node(int val) {
        value = val;
    }
};

Node* find_k_to_end(struct Node* head, int k) {
    int length = 0;
    struct Node *curr = head;
    
    while (curr) {
        curr = curr -> next;
        length++;
    }

    if (k >= length || k < 0) {
        return NULL;
    }
    
    curr = head;
    for (int i = 0; i < length - k - 1; ++i) {
        curr = curr -> next;
    }
    
    return curr;
}

int main(int argc, const char * argv[]) {
    
    // Task1
    cout << is_permutation("Listen", "Silent") << "\n";
    cout << is_permutation("Triangle", "Integral") << "\n";
    cout << is_permutation("Apple", "Pabble") << "\n";
    cout << is_permutation("", "") << "\n";
    
    
    // Task2
    Node* head = new Node(5);
    Node* next = new Node(10);
    head -> next = next;
    
    cout << find_k_to_end(head, -1) << "\n";
    cout << find_k_to_end(head, 0) -> value << "\n";
    cout << find_k_to_end(head, 1) -> value << "\n";
    
    return 0;
}
