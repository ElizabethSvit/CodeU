#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define ALPHABET_SIZE 50

class Graph {
    vector<vector<int> > adj_list;
    
public:
    Graph () {
        adj_list.resize(ALPHABET_SIZE);
    }
    
    void addEdge(int v, int w) {
        adj_list[v].push_back(w);
    }
    
    void topologicalSortUtil(int v, vector<bool> &visited, stack<int> &stack);
    
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

string return_alphabet(vector<string> words) {
    Graph graph;
    vector<int> letter_ids;
    
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
    
    stack<int> ordered_alphabet = graph.topologicalSort(letter_ids);
    string output_str;
    
    while (!ordered_alphabet.empty()) {
        output_str = output_str + (char) ('A' + ordered_alphabet.top()) + " ";
        ordered_alphabet.pop();
    }
    return output_str;
}

void assert_output(string output_str, string exp_output, int case_num) {
    if (output_str == exp_output) {
        cout << "Test case " << case_num << " - OK" << endl;
    } else {
        cout << "Function output: \"" << output_str << "\" is not equal to expected output: \"" << exp_output << "\"" << endl;
        cout << "Please, check if the test input is lexicographically correct." << endl;
    }
}

void test_func() {
    
    // case 1
    vector<string> words = {"maa", "aab", "ab", "c"};
    string output_str = return_alphabet(words);
    string exp_output = "m a c b ";
    
    assert_output(output_str, exp_output, 1);
    
    // case 2
    words = {"A", "B", "c", "b"};
    output_str = return_alphabet(words);
    exp_output = "A B c b ";
    
    assert_output(output_str, exp_output, 2);
    
    // case 3
    words = {"C", "z", "Z", "c"};
    output_str = return_alphabet(words);
    exp_output = "C z Z c ";
    
    assert_output(output_str, exp_output, 3);
}


int main() {
    test_func();
    
    return 0;
}
