import heapq
def dijkstra(graph, start):
    dist = [float('inf')] * len(graph)
    dist[start] = 0
    pq = [(0, start)]
    while pq:
        d, u = heapq.heappop(pq)
        if d > dist[u]:
            continue
        for v, w in graph[u]:
            if d + w < dist[v]:
                dist[v] = d + w
                heapq.heappush(pq, (dist[v], v))
    return dist
n = int(input("Enter number of vertices: "))
e = int(input("Enter number of edges: "))
graph = [[] for _ in range(n)]
print("Enter edges (u v weight):")
for _ in range(e):
    u, v, w = map(int, input().split())
    graph[u].append((v, w))
    graph[v].append((u, w))
s = int(input("Enter source vertex: "))
dist = dijkstra(graph, s)
print("Shortest distances:")
for i in range(n):
    print(s, "to", i, "=", dist[i])
