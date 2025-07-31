#include <stdio.h>
#include <limits.h>
#define INF 9999
#define MAX_NODES 10
void dijkstra(int graph[MAX_NODES][MAX_NODES], int src, int n) {
int dist[MAX_NODES], visited[MAX_NODES];
for (int i = 0; i < n; i++) {
dist[i] = INF;
visited[i] = 0;
}
dist[src] = 0;
for (int i = 0; i < n - 1; i++) {
int min = INF, u = -1;
for (int j = 0; j < n; j++) {
if (!visited[j] && dist[j] < min) {
min = dist[j];
u = j;
}
}
visited[u] = 1;
for (int v = 0; v < n; v++) {
if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
dist[v] = dist[u] + graph[u][v];
}
}
}
printf("Shortest distances from node %d:\n", src);
for (int i = 0; i < n; i++) {
printf("To %d: %d\n", i, dist[i]);
}
}
int main() {
int n;
printf("Enter the number of nodes: ");
scanf("%d", &n);
int graph[MAX_NODES][MAX_NODES];
printf("Enter adjacency matrix (9999 for INF):\n");
for (int i = 0; i < n; i++)
for (int j = 0; j < n; j++)
scanf("%d", &graph[i][j]);
int src;
printf("Enter the source node: ");
scanf("%d", &src);
dijkstra(graph, src, n);
return 0;
}