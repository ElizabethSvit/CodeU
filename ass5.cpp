#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define ALPHABET_SIZE 50

class Graph {
    vector<vector<int> > adj_list;
    void topologicalSortUtil(int v, vector<bool> &visited, stack<int> &stack);
    
public:
    Graph () {
        adj_list.resize(ALPHABET_SIZE);
    }
    
    void addEdge(int v, int w) {
        adj_list[v].push_back(w);
    }
    
    stack<int> topologicalSort(vector<int> letter_ids);
};

void Graph::topologicalSortUtil(int v, vector<bool> &visited, stack<int> &stack) {
    visited[v] = true;
    
    for (auto i : adj_list[v]) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, stack);
        }
    }
    
    stack.push(v);
}

stack<int> Graph::topologicalSort(vector<int> letter_ids) {
    stack<int> stack;
    vector<bool> visited(letter_ids.size(), false);

    for (auto i: letter_ids) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, stack);
        }
    }
    
    return stack;
}

vector<char> return_alphabet(vector<string> words) {
    Graph graph;
    vector<char> output_chars;
    
    vector<int> letter_ids;
    stack<int> ordered_alphabet;
    
    if (words.size() == 1) {
        for (char letter: words[0]) {
            output_chars.push_back(letter);
        }
    }
    
    else {
        for (int i = 0; i < words.size() - 1; ++i) {
            string str_first = words[i];
            string str_sec = words[i + 1];
            
            for (int j = 0; j < min(str_first.length(), str_sec.length()); ++j) {
                if (str_first[j] != str_sec[j]) {
                    graph.addEdge(str_first[j] - 'A', str_sec[j] - 'A');
                    letter_ids.push_back(str_first[j] - 'A');
                    letter_ids.push_back(str_sec[j] - 'A');
                    break;
                }
            }
        }

        ordered_alphabet = graph.topologicalSort(letter_ids);
    }
    
    while (!ordered_alphabet.empty()) {
        output_chars.push_back((char) ('A' + ordered_alphabet.top()));
        ordered_alphabet.pop();
    }
    return output_chars;
}

void assert_output(vector<char> output_str, vector<char> exp_output, int case_num) {
    if (output_str == exp_output) {
        cout << "Test case " << case_num << " - OK" << endl;
    } else {
        
        cout << "Function output chars: ";
        for (char letter: output_str) {
            cout << letter << " ";
        }
        cout << "is not equal to expected output chars: ";
        for (char letter: exp_output) {
            cout << letter << " ";
        }
        cout << endl;
        cout << "Please, check if the test input is lexicographically correct." << endl;
    }
}

void test_func() {
    
    // case 1
    vector<string> words = {"maa", "aab", "ab", "c"};
    vector<char> output_str = return_alphabet(words);
    vector<char> exp_output = {'m', 'a', 'c', 'b'};
    
    assert_output(output_str, exp_output, 1);
    
    // case 2
    words = {"A", "B", "c", "b"};
    output_str = return_alphabet(words);
    exp_output = {'A', 'B', 'c', 'b'};
    
    assert_output(output_str, exp_output, 2);
    
    // case 3
    words = {"C", "z", "Z", "c"};
    output_str = return_alphabet(words);
    exp_output = {'C', 'z', 'Z', 'c'};
    
    assert_output(output_str, exp_output, 3);
    
    // case 4
    words = {"ABC"};
    output_str = return_alphabet(words);
    exp_output = {'A', 'B', 'C'};
    
    assert_output(output_str, exp_output, 4);
}


int main() {
    test_func();
    
    return 0;
}
