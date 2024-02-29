#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Task {
    int id;
    int duration;
    vector<int> dependencies;
    int earliestStart;
    int latestStart;
};

class NetworkPlanning {
public:
    vector<Task> tasks;

    void addTask(int id, int duration, vector<int> dependencies) {
        Task task = { id, duration, dependencies, 0, 0 };
        tasks.push_back(task);
    }

    void calculateEarliestStartTimes() {
        queue<int> q;
        for (int i = 0; i < tasks.size(); ++i) {
            if (tasks[i].dependencies.empty()) {
                q.push(i);
                tasks[i].earliestStart = 0;
            }
        }

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int dep : tasks[curr].dependencies) {
                tasks[dep].earliestStart = max(tasks[dep].earliestStart, tasks[curr].earliestStart + tasks[curr].duration);
                q.push(dep);
            }
        }
    }

    void calculateLatestStartTimes() {
        for (int i = tasks.size() - 1; i >= 0; --i) {
            if (tasks[i].dependencies.empty()) {
                tasks[i].latestStart = tasks[i].earliestStart;
            }
            else {
                int maxLatestStart = INT_MAX;
                for (int dep : tasks[i].dependencies) {
                    maxLatestStart = min(maxLatestStart, tasks[dep].latestStart - tasks[i].duration);
                }
                tasks[i].latestStart = maxLatestStart;
            }
        }
    }

    void calculateCriticalPath() {
        for (Task& task : tasks) {
            if (task.earliestStart == task.latestStart) {
                cout << "Task " << task.id << " is on the critical path." << endl;
            }
        }
    }
};

int main() {
    NetworkPlanning network;

    network.addTask(1, 5, {});
    network.addTask(2, 3, { 0 });
    network.addTask(3, 4, { 1 });
    network.addTask(4, 2, { 2 });

    network.calculateEarliestStartTimes();
    network.calculateLatestStartTimes();
    network.calculateCriticalPath();

    return 0;
}
