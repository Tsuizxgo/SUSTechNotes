#include <vector>
#include <iostream>

using namespace std;
class Task
{
public:
    char name;
    int s;
    int f;
    Task(char name, int s, int f)
    {
        this->name = name;
        this->s = s;
        this->f = f;
    }
};
bool compareTasks(Task *a, Task *b)
{
    return a->f < b->f;
}

int main()
{
    vector<Task *> tasks;
    int n = 8;
    while (n--)
    {
        char name;
        int s, f;
        cin >> name >> s >> f;
        Task *task = new Task(name, s, f);
        tasks.push_back(task);
    }
    sort(tasks.begin(), tasks.end(), compareTasks);

    vector<Task *> ans;
    if (!tasks.empty())
    {
        ans.push_back(tasks[0]); // 选择第一个结束的任务
        int finishTime = tasks[0]->f;

        for (int i = 1; i < tasks.size(); ++i)
        {
            if (tasks[i]->s >= finishTime)
            {
                ans.push_back(tasks[i]);
                finishTime = tasks[i]->f;
            }
        }
    }
    for (Task *task : ans)
    {
        cout << task->name;
    }
    cout << endl;

    for (Task *task : tasks)
        delete task;
}