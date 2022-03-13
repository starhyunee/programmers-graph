#include <string>
#include <vector>
#include<algorithm>
#include<queue>

using namespace std;

/*프로그래머스 고득점 kit - 가장 먼 노드 */
int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    vector<vector<int>> graph(n + 1);
    vector<int> counts(n + 1, 0);
    vector<bool> visited(n + 1, false);
    queue<int> queue;

    for (int i = 0; i < edge.size(); i++) {
        graph[edge[i][0]].push_back(edge[i][1]);
        graph[edge[i][1]].push_back(edge[i][0]);
    }
    queue.push(1);
    visited[1] = true;
    while (!queue.empty()) {
        int x = queue.front();
        queue.pop();
        for (int i = 0; i < graph[x].size(); i++) {
            if (!visited[graph[x][i]]) {
                int currentCount = counts[x] + 1;
                visited[graph[x][i]] = true;
                counts[graph[x][i]] = currentCount;
                queue.push(graph[x][i]);
            }
        }
    }
    sort(counts.begin(), counts.end(), greater<int>());
    for (int i = 0; i < counts.size(); i++) {
        if (counts[0] == counts[i])
            answer++;
        else
            break;
    }
    return answer;
}


/* 프로그래머스 고득점 kit - 순위 */
int winDFS(vector<vector<int>> results, vector<bool>& visited, int start) {
    int count = 0;
    visited[start] = true;
    for (int i = 0; i < results.size(); i++) {
        if (start == results[i][0] && !visited[results[i][1]]) {
            count = count + winDFS(results, visited, results[i][1]) + 1;
        }
    }
    return count;
}

int loseDFS(vector<vector<int>> results, vector<bool>& visited, int start) {
    int count = 0;
    visited[start] = true;
    for (int i = 0; i < results.size(); i++) {
        if (start == results[i][1] && !visited[results[i][0]]) {
            count = count + loseDFS(results, visited, results[i][0]) + 1;
        }
    }
    return count;
}
int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        vector<bool> winVisited(n + 1);
        vector<bool> loseVisited(n + 1);
        int count = winDFS(results, winVisited, i) + loseDFS(results, loseVisited, i);
        if (count == n - 1)
            answer++;
    }
    return answer;
}