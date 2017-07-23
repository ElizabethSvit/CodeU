#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

void rearrange_array(vector<int> &source, const vector<int> target) {
    
    // Hash map for finding zero element in O(N)
    unordered_map<int, int> elementMapOfSource;
    
    for (int i = 0; i < source.size(); i++) {
        elementMapOfSource.insert(pair<int,int>(source[i], i));
    }
    
    int indexOfTargetElement, zeroIndex;
    zeroIndex = elementMapOfSource.find(0)->second;
    
    for (int i = 0; i < target.size(); i++) {
        int prev_source = source[i]; // remember the real source value before it's swaped
        
        // Swap
        
        swap(source[i], source[zeroIndex]);
        
        elementMapOfSource[prev_source] = zeroIndex;
        elementMapOfSource[0] = i;
        indexOfTargetElement = elementMapOfSource.find(target[i])->second; // index of target element in source
        
        swap(source[indexOfTargetElement], source[i]);
        
        // Find the new zero index
        
        zeroIndex = indexOfTargetElement;
        elementMapOfSource[0] = zeroIndex;
    }

}

int main(int argc, const char * argv[]) {
    
    // Testing
    
    vector<int> source = { 1, 0, 2, 3, 7, 4, 8, 9 };
    vector<int> target = { 7, 2, 8, 3, 1, 9, 4, 0 };
    rearrange_array(source, target);
    
    for (int el : source) {
        cout << el << " ";
    }
    
    return 0;
}
