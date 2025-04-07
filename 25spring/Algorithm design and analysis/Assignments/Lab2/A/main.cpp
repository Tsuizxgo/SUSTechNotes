#include <iostream>
#include <vector>
#include <queue>

using namespace std;
class Node
{
public:
    int v;
    vector<Node *> nexts;
    vector<Node *> prevs;
    int inDegree;
    int outDegree;
    Node(int v) : v(v), inDegree(0), outDegree(0) {}
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<Node *> nodes(n + 1);
    for (int i = 1; i <= n; i++)
        nodes[i] = new Node(i);
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        nodes[x]->nexts.push_back(nodes[y]);
        nodes[x]->outDegree++;
        nodes[y]->inDegree++;
        nodes[y]->prevs.push_back(nodes[x]);
    }
    long long mod = 1e9 + 7;
    vector<long long> count_up(n + 1, 0);
    vector<long long> count_down(n + 1, 0);
    queue<Node *> q_up;
    queue<Node *> q_down;
    for (int i = 1; i <= n; i++)
    {
        if (nodes[i]->inDegree == 0)
        {
            count_up[i] = 1;
            q_up.push(nodes[i]);
        }
        if (nodes[i]->outDegree == 0)
        {
            count_down[i] = 1;
            q_down.push(nodes[i]);
        }
    }
    while (!q_up.empty())
    {
        Node *cur = q_up.front();
        q_up.pop();
        for (Node *next : cur->nexts)
        {
            next->inDegree--;
            count_up[next->v] = (count_up[next->v] + count_up[cur->v]) % mod;
            if (next->inDegree == 0)
            {
                q_up.push(next);
            }
        }
    }
    while (!q_down.empty())
    {
        Node *cur = q_down.front();
        q_down.pop();
        for (Node *prev : cur->prevs)
        {
            prev->outDegree--;
            count_down[prev->v] = (count_down[prev->v] + count_down[cur->v]) % mod;
            if (prev->outDegree == 0)
            {
                q_down.push(prev);
            }
        }
    }
    vector<long long> ans(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        ans[i] = (count_up[i] * count_down[i]) % mod;
        cout << ans[i] << " ";
        delete nodes[i];
    }
    return 0;
}