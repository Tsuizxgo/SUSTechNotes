#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(int a, int b)
{
    return a < b;
};
int main()
{
    int n, m, c, t;
    cin >> n >> m >> c >> t;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (t < 0)
        t = 0;
    vector<int> tuzi(n);
    vector<int> nests(m);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        tuzi[i] = x;
    }
    for (int i = 0; i < m; i++)
    {
        int y;
        cin >> y;
        nests[i] = y;
    }
    // sort(tuzi.begin(), tuzi.end(), compare);
    // sort(nests.begin(), nests.end(), compare);
    // vector<int> num(m);
    // int ans = 0;
    // int startSearch = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     int leftMost = tuzi[i] - t;
    //     int rightMost = tuzi[i] + t;
    //     for (int j = startSearch; j < m; j++)
    //     {
    //         if (nests[j] >= leftMost && nests[j] <= rightMost && num[j] <= c - 1)
    //         {
    //             num[j]++;
    //             if (num[j] >= c)
    //                 startSearch++;
    //             ans++;
    //             break;
    //         }
    //         else
    //             startSearch++;
    //     }
    // }
    // cout << ans << endl;
    // // for (int i = 1; i <= n; i++)
    // //     cout << tuzi[i] << " ";
    // // cout << endl;
    // // for (int i = 1; i <= m; i++)
    // //     cout << nests[i] << " ";
    // return 0;
}