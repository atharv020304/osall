// #include <iostream>
// #include <vector>

// using namespace std;

// int n = 5;

// int m = 3;

// int main()
// {

//     int available[] = {3, 3, 2};

//     int Max[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};

//     int Allocation[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};

//     int Need[5][3] = {{7, 4, 3}, {1, 2, 2}, {6, 0, 0}, {0, 1, 1}, {4, 3, 1}};

//     vector<int> visited(n, 0);

//     vector<int> safe_order;


//     bool safe = true;

//     for (int i = 0; i < n; i++)
//     {
//         if (!visited[i])
//         {
//             bool can_allocate = true;
//             for (int j = 0; j < m; j++)
//             {
//                 if (available[j] < Need[i][j])
//                 {
//                     can_allocate = false;
//                     break;
//                 }
//             }
//             if (can_allocate)
//             {
//                 visited[i] = 1;
//                 safe_order.push_back(i);
//                 for (int k = 0; k < m; k++)
//                 {
//                     available[k] += Allocation[i][k];
//                 }
//                 i = -1;
//             }
//         }
//     }

//     for (int i = 0; i < n; i++)
//     {
//         if (!visited[i])
//         {
//             safe = false;
//             break;
//         }
//     }

//     if (safe)
//     {
//         cout << "System is in safe state. Safe execution order: ";
//         for (int i = 0; i < safe_order.size(); ++i)
//         {
//             cout << "P" << safe_order[i];
//             if (i != safe_order.size() - 1)
//             {
//                 cout << " -> ";
//             }
//         }
//         cout << endl;
//     }
//     else
//     {
//         cout << "System is in unsafe state\n";
//     }

//     return 0;
// }




