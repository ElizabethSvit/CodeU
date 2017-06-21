#include <iostream>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

class Dictionary {
    set<string> dict_words;
    set<string> dict_prefixes;
public:
    Dictionary() {};
    
    void fill_dict(const vector<string> &words) {
        for (const string &word : words) {
            dict_words.insert(word);
            
            string prefix = "";
            for (char c : word) {
                prefix +=c;
                dict_prefixes.insert(prefix);
            }
        }
    }


    bool isWord(string const &s) {
        return dict_words.find(s) != dict_words.end();
    }
    
    bool isPrefix(string const &s) {
        return dict_prefixes.find(s) != dict_prefixes.end();
    }
};

void find_pref_word(vector<vector<char>> &table, vector<vector<bool> > &visited, int y, int x, string &str, Dictionary dict, set<string> &result_words) {
    int row_size = table.size();
    int col_size = table[0].size();
    
    str += table[y][x];
    
    if (!dict.isPrefix(str)) {
        str.erase(str.length() - 1);
        return;
    }
    
    visited[y][x] = true;
    
    if (dict.isWord(str))
        result_words.insert(str);
    
    for (int row = y - 1; row <= y + 1 && row < row_size; ++row) {
        for (int col = x - 1; col <= x + 1 && col < col_size; ++col) {
            if (row >= 0 && col >= 0 && !visited[row][col]) {
                find_pref_word(table, visited, row, col, str, dict, result_words);
            }
        }
    }

    str.erase(str.length() - 1);
    visited[y][x] = false;
}

void find_all_words(vector<vector<char>> table, Dictionary const &dict, set<string> &result_words) {
    vector<vector<bool> > visited(table.size(), vector<bool>(table[0].size(), false));
    
    string str = "";

    for (int y = 0; y < table.size(); ++y) {
        for (int x = 0; x < table[y].size(); ++x) {
            find_pref_word(table, visited, y, x, str, dict, result_words);
        }
    }
}

int main(int argc, const char * argv[]) {
    Dictionary dict;
    dict.fill_dict({"CAR", "CARD", "CART", "CAT"});

    vector<vector<char>> table = {{'A','A','R'}, {'T','C','D'}};

    set<string> result_words;
    find_all_words(table, dict, result_words);

    for (const string &word : result_words) {
        std::cout << word << endl;
    }

    return 0;
}
