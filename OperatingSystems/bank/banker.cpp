
// Banker's Algorithm
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
int myatoi(char);
int main()
{
    // P0, P1, P2, P3, P4 are the Process names here

    const int n = 5; // Number of processes
    const int m = 3; // Number of resources
    char ch = 0;
    char input;
    int result;

    int alloc[5][3];
    int max[5][3];
    int avail[3];

    std::ifstream in;
    in.open("bank.txt");

    if (in.fail())
        exit(1);

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            in.get(input);
            result = myatoi(input);
            alloc[i][j] = result;
        }
        in.get(ch);
    }
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            in.get(input);
            result = myatoi(input);
            max[i][j] = result;
        }
        in.get(ch);
    }

    for (int i = 0; i < 3; ++i)
    {
        in.get(input);
        result = myatoi(input);
        avail[i] = result;
    }

    int f[n], ans[n], ind = 0;
    for (int k = 0; k < n; k++)
    {
        f[k] = 0;
    }
    int need[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (int k = 0; k < 5; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {

                int flag = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    int flag = 1;

    // To check if sequence is safe or not
    for (int i = 0; i < n; i++)
    {
        if (f[i] == 0)
        {
            flag = 0;
            cout << "The given sequence is not safe";
            break;
        }
    }

    if (flag == 1)
    {
        cout << "Following is the SAFE Sequence" << endl;
        for (int i = 0; i < n - 1; i++)
            cout << " P" << ans[i] << " ->";
        cout << " P" << ans[n - 1] << endl;
    }

    return (0);
}

int myatoi(char ch)
{
    return int(ch) - 48;
}
