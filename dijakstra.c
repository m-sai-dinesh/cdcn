#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int main()
{
    int n, m, u, v, w, src;
    cout << "Enter vertices and edges: ";
    cin >> n >> m;
    vector<pair<int,int>> adj[n+1];
    cout << "Enter edges (u v weight):\n";
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    cout << "Enter source: ";
    cin >> src;
    vector<int> dist(n+1, 1e9);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[src] = 0;
    pq.push({0,src});
    while(!pq.empty())
    {
        int d = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        if(d > dist[node]) continue;
        for(auto x : adj[node])
        {
            int next = x.first;
            int wt = x.second;
            if(dist[node] + wt < dist[next])
            {
                dist[next] = dist[node] + wt;
                pq.push({dist[next], next});
            }
        }
    }
    cout << "Shortest distances:\n";
    for(int i = 1; i <= n; i++)
        cout << src << " to " << i << " = " << dist[i] << endl;
    return 0;
}
