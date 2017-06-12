#include <iostream>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

#define ROW_SIZE 2
#define COL_SIZE 3


class Dictionary {
    set<string> dict_words;
    set<string> dict_prefixes;
public:
    Dictionary() {};
    
    void fill_dict(vector<string> words) {
        for (int i = 0; i < words.size(); ++i) {
            dict_words.insert(words[i]);
            
            string prefix = "";
            for (int j = 0; j < words[i].length(); ++j) {
                prefix += words[i][j];
                dict_prefixes.insert(prefix);
            }
        }
    }


    bool isWord(string s) {
        return dict_words.find(s) != dict_words.end();
    }
    
    bool isPrefix(string s) {
        return dict_prefixes.find(s) != dict_prefixes.end();
    }
};

void find_pref_word(char table[ROW_SIZE][COL_SIZE], vector<vector<bool> > visited, int i, int j, string &str, Dictionary dict, set<string> &result_words) {
    visited[i][j] = true;
    str += table[i][j];
    
    if (!dict.isPrefix(str)) {
        str.erase(str.length() - 1);
        visited[i][j] = false;
        return;
    }
    
    if (dict.isWord(str))
        result_words.insert(str);
    
    for (int row = i - 1; row <= i + 1 && row < ROW_SIZE; ++row) {
        for (int col = j - 1; col <= j + 1 && col < COL_SIZE; ++col) {
            if (row >= 0 && col >= 0 && !visited[row][col]) {
                find_pref_word(table, visited, row, col, str, dict, result_words);
            }
        }
    }

    str.erase(str.length() - 1);
    visited[i][j] = false;
}

void find_all_words(char table[ROW_SIZE][COL_SIZE], Dictionary dict, set<string> &result_words) {
    vector<vector<bool> > visited;
    vector<bool> row_visited(COL_SIZE, false);
    for (int i = 0; i < ROW_SIZE; ++i) {
        visited.push_back(row_visited);
    }
    
    string str = "";

    for (int i = 0; i < ROW_SIZE; ++i) {
        for (int j = 0; j < COL_SIZE; ++j) {
            find_pref_word(table, visited, i, j, str, dict, result_words);
        }
    }
}

int main(int argc, const char * argv[]) {
    Dictionary dict;
    dict.fill_dict({"CAR", "CARD", "CART", "CAT"});

   char table[ROW_SIZE][COL_SIZE] = {{'A','A','R'}, {'T','C','D'}};

    set<string> result_words;
    find_all_words(table, dict, result_words);

    for (auto it = result_words.begin(); it != result_words.end(); ++it) {
        std::cout << *it << endl;
    }

    return 0;
}
