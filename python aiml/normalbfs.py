from collections import deque

def bfs(graph, start):
    queue = deque([start])
    visited = set()
    

    while queue:
        node = queue.popleft()
        if node not in visited:
            print(node)  # Print the current node
            visited.add(node)

            for neighbor in graph.get(node, []):
                if neighbor not in visited:
                    queue.append(neighbor)

# Graph as adjacency list
graph = {
    'S': ['A', 'B', 'C'],
    'A': ['D'],
    'B': ['E'],
    'C': ['F', 'J'],
    'D': ['G'],
    'E': ['I', 'J'],
    'F': ['S'],
    'G': ['H'],
    'H': [],
    'I': [],
    'J': []
}

# Start BFS from node 'S'
bfs(graph, 'S')
