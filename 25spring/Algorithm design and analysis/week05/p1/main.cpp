#include <iostream>

using namespace std;
class Node
{
public:
    int v;
    vector<Node *> nexts;
    int inDegree;
    Node(int value)
    {
        this->v = value;
        int inDegree = 0;
    }
};
struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->inDegree < b->inDegree;
    }
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
        nodes[x] = new Node(x);
        nodes[y] = new Node(y);
        nodes[x]->nexts.push_back(nodes[y]);
        nodes[y]->inDegree++;
    }
    priority_queue<Node *, vector<Node *>, Compare> minHeap;
    for (int i = 1; i <= n; i++)
    {
        if (nodes[i]->inDegree == 0)
            minHeap.push(nodes[i]);
    }
    vector<int> ans;
    while (!minHeap.empty())
    {
        Node *cur = minHeap.top();
        minHeap.pop();
        ans.push_back(cur->v);

        for (Node *next : cur->nexts)
        {
            next->inDegree--;
            if (next->inDegree == 0)
                minHeap.push(next);
        }
    }
    if (ans.size() < n)
        cout << "impossible" << endl;
    else
    {
        for (int num : ans)
            cout << num << " ";
        cout << endl;
    }
    for (int i = 1; i <= n; i++)
        delete nodes[i];
}