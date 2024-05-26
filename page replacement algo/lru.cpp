


#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int main() {
    vector<int> block(3, -1);
    deque<int> recentorder;
    int hit = 0, miss = 0;

    int arr[6] = {1, 2, 3, 2, 5, 8};

    for (int i = 0; i < 6; i++) {
        bool found = false;
        for (int j = 0; j < 3; j++) {
            if (block[j] == arr[i]) {
                hit++;
                recentorder.erase(remove(recentorder.begin(), recentorder.end(), j), recentorder.end());
                recentorder.push_back(j);
                found = true;
                break;
            }
        }

        if (!found) {
            miss++;
            if (find(block.begin(), block.end(), -1) != block.end()) {
                for (int j = 0; j < 3; j++) {
                    if (block[j] == -1) {
                        block[j] = arr[i];
                        recentorder.push_back(j);
                        break;
                    }
                }
            } else {
                int recentindex = recentorder.front();
                recentorder.pop_front();
                block[recentindex] = arr[i];
                recentorder.push_back(recentindex);
            }
        }

        cout << "Step " << i + 1 << " - Block State: ";
        for (int j = 0; j < 3; j++) {
            cout << block[j] << " ";
        }
        cout << "\nRecent Order: ";
        for (int idx : recentorder) {
            cout << idx << " ";
        }
        cout << "\nHits: " << hit << ", Misses: " << miss << "\n\n";
    }

    cout << "Final Hits: " << hit << ", Final Misses: " << miss << endl;
    return 0;
}

