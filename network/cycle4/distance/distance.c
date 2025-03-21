#include <stdio.h>
#define INF 9999
#define MAX_NODES 10
typedef struct {
int dist[MAX_NODES];
int next[MAX_NODES];
} RoutingTable;
void distanceVector(int graph[MAX_NODES][MAX_NODES], int n) {
RoutingTable rt[MAX_NODES];
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
rt[i].dist[j] = graph[i][j];
rt[i].next[j] = j;
}
}
int updated;
do {
updated = 0;
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
for (int k = 0; k < n; k++) {
if (rt[i].dist[k] > rt[i].dist[j] + rt[j].dist[k]) {
rt[i].dist[k] = rt[i].dist[j] + rt[j].dist[k];
rt[i].next[k] = j;
updated = 1;
}
}
}
}
} while (updated);
for (int i = 0; i < n; i++) {
printf("Routing table for node %d:\n", i);
for (int j = 0; j < n; j++) {
printf("To %d via %d distance %d\n", j, rt[i].next[j], rt[i].dist[j]);
}
printf("\n");
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
distanceVector(graph, n);
return 0;
}