#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    int v;
    vector<Node *> friends;
    bool isVisited;
    Node(int value) : v(value), isVisited(false) {};
    void addFriend(Node *newFriend)
    {
        this->friends.push_back(newFriend);
    }
};
void dfs(Node *start, int &n)
{
    start->isVisited = true;
    n++;

    for (Node *f : start->friends)
    {
        if (!f->isVisited)
            dfs(f, n);
    }
};
int main()
{
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<Node *> nodes(n + 1);
    nodes[0] = new Node(0);
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        if (!nodes[x])
            nodes[x] = new Node(x);
        if (!nodes[y])
            nodes[y] = new Node(y);
        nodes[x]->addFriend(nodes[y]);
        nodes[y]->addFriend(nodes[x]);
    }

    for (Node *node : nodes)
        node->isVisited = false;
    nodes[a]->isVisited = true;
    int numR = 0;
    dfs(nodes[b], numR);
    int nr = n - numR - 1;

    for (Node *node : nodes)
        node->isVisited = false;
    nodes[b]->isVisited = true;
    int numL = 0;
    dfs(nodes[a], numL);
    int nl = n - numL - 1;

    long long ans = (long long)nl * nr;
    cout << ans << endl;
    for (Node *node : nodes)
        delete node;
}
