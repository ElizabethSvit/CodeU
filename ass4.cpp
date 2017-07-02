#include <iostream>
#include <vector>

using namespace std;

// Recursive "Flood fill" algorithm

void flood_fill_recursive(vector<vector<bool> > table, int y, int x) {
    if (y < 0 || y >= table.size() || x < 0 || x >= table[0].size()) {
        return;
    }
    
    if (!table[y][x]) {
        return;
    }
    table[y][x] = false;
    
    flood_fill_recursive(table, y - 1, x);
    flood_fill_recursive(table, y + 1, x);
    flood_fill_recursive(table, y, x - 1);
    flood_fill_recursive(table, y, x + 1);
}

int recursive_count_islands(vector<vector<bool> > table) {
    int counter = 0;
    for (int y = 0; y < table.size(); ++y) {
        for (int x = 0; x < table[y].size(); ++x) {
            if (table[y][x]) {
                flood_fill_recursive(table, y, x);
                counter++;
            }
        }
    }
    return counter;
}

// Algorithm "Union-Find" using Tree to store disjoint components as unique islands

class Disjoint_sets {
    vector<int> rank;
    vector<int> parent;
    
public:
    Disjoint_sets(int n) {
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent.push_back(i);
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            return find(parent[x]);
        }
        return x;
    }
    
    void func_union(int x, int y) {
        int x_ancestor = find(x);
        int y_ancestor = find(y);
        
        if (x_ancestor == y_ancestor) {
            return;
        }
        
        if (rank[x_ancestor] < rank[y_ancestor]) {
            parent[x_ancestor] = y_ancestor;
        }
        
        else if (rank[x_ancestor] > rank[y_ancestor]) {
            parent[y_ancestor] = x_ancestor;
        }
        
        else {
            parent[x_ancestor] = y_ancestor;
            rank[y_ancestor] = rank[y_ancestor] + 1;
        }
    }
};

int count_islands(vector<vector<bool> > table) {
    int max_width = 0;
    
    for (int y = 0; y < table.size(); ++y) {
        for (int x = 0; x < table[y].size(); ++x) {
            if (max_width < table[y].size()) {
                max_width = table[y].size();
            }
        }
    }
    
    Disjoint_sets islands = Disjoint_sets(table.size() * max_width);
    vector<pair<int, int>> delta_x_y = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int y = 0; y < table.size(); ++y) {
        for (int x = 0; x < table[y].size(); ++x) {
            if (table[y][x]) {
                for (auto delta : delta_x_y) {
                    if (y + delta.first >= 0 && y + delta.first < table.size()
                        && x + delta.second >= 0 && x + delta.second < table[y].size()
                        && table[y + delta.first][x + delta.second]) {
                        islands.func_union(y + delta.first * table[y + delta.first].size() + x + delta.second,
                                           (y + delta.first) * table[y + delta.first].size() + x + delta.second);
                    }
                }
            }
        }
    }

    vector<int> components(table.size() * max_width);
    
    int counter = 0;
    for (int y = 0; y < table.size(); ++y) {
        for (int x = 0; x < table[y].size(); ++x) {
            if (table[y][x]) {
                int value = islands.find(y * table[y].size() + x);
                
                if (!components[value]) {
                    counter++;
                }
                
                components[value]++;
            }
        }
    }
    return counter;
}


int main(int argc, const char * argv[]) {
    vector<vector<bool> > table = {{0,0,1}, {1,0,0}, {1,1,0}};
    cout << count_islands(table) << endl;
    
    return 0;
}
