#include<iostream>
#include<vector>
using namespace std;

int main(){
    int size = 13;

    int arr[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    vector<int> block(3, -1);

    cout << "Initial block state: ";
    for(int b : block) cout << b << " ";
    cout << endl;

    for(int i = 0; i < size; i++){
        cout << "Processing element arr[" << i << "] = " << arr[i] << endl;
        
        bool placed = false;
        for(int j = 0; j < 3; j++){
            if(block[j] == -1){
                block[j] = arr[i];
                placed = true;
                cout << "Placed " << arr[i] << " in block[" << j << "]" << endl;
                break;
            }
            else if(block[j] == arr[i]){
                cout << arr[i] << " is already in block[" << j << "]" << endl;
                placed = true;
                break;
            }
        }
        
        if(!placed){
            int count = 0;
            int flag = 0;
            int optimalIndex = -1;
            for(int j = 0; j < 3; j++){
                for(int k = i + 1; k < size; k++){
                    if(block[j] == arr[k]){
                        optimalIndex = k;
                        flag = 1;
                        break;
                    }
                }
                if(flag == 1){
                    block[j] = arr[i];
                    cout << "Replaced block[" << j << "] with " << arr[i] << " as it is used at index " << optimalIndex << " in future" << endl;
                    break;
                }
            }
            if(flag == 0){
                block[0] = arr[i];
                cout << "Replaced block[0] with " << arr[i] << " as no future usage found" << endl;
            }
        }
        
        cout << "Current block state: ";
        for(int b : block) cout << b << " ";
        cout << endl;
    }

    return 0;
}












