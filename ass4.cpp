#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// First variant of algorithm using recursion

void flood_fill_recursive(vector<vector<bool> > &table, int y, int x) {
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

// Second variant of algorithm using data structure deque for storing islands

void flood_fill_queued(vector<vector<bool> > &table, int y, int x) {
    deque<pair<int, int>> tile_deque;
    tile_deque.push_back({y,x});
    
    while (!tile_deque.empty()) {
        pair<int, int> cur_tile = tile_deque.front();
    
        tile_deque.pop_front();
        
        if (cur_tile.first - 1 >= 0 && table[cur_tile.first - 1][cur_tile.second]) {
            table[cur_tile.first - 1][cur_tile.second] = false;
            tile_deque.push_back({cur_tile.first - 1, cur_tile.second});
        }
        if (cur_tile.first + 1 < table.size() && table[cur_tile.first + 1][cur_tile.second]) {
            table[cur_tile.first + 1][cur_tile.second] = false;
            tile_deque.push_back({cur_tile.first + 1, cur_tile.second});
        }
        if (cur_tile.second - 1 >= 0 && table[cur_tile.first][cur_tile.second - 1]) {
            table[cur_tile.first][cur_tile.second - 1] = false;
            tile_deque.push_back({cur_tile.first, cur_tile.second - 1});
        }
        if (cur_tile.second + 1 < table[0].size() && table[cur_tile.first][cur_tile.second + 1]) {
            table[cur_tile.first][cur_tile.second + 1] = false;
            tile_deque.push_back({cur_tile.first, cur_tile.second + 1});
        }
    }
}

int count_islands(vector<vector<bool> > table) {
    int counter = 0;
    for (int y = 0; y < table.size(); ++y) {
        for (int x = 0; x < table[y].size(); ++x) {
            if (table[y][x]) {
                flood_fill_queued(table, y, x);
                counter++;
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
