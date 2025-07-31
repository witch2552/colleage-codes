def DFS(graph,start,goal):
    stack = [[start]]
    visited = set()
    while stack:
        path = stack.pop()
        node = path[-1]#current node last
        if node == goal:
            return path
        if node not in visited:
            visited.add(node)
            for neighbor in graph.get(node,[]):
                if neighbor not in visited:
                    new_path = list(path)
                    new_path.append(neighbor)
                    stack.append(new_path)
    return None
graph = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F'],
    'D': [],
    'E': ['F'],
    'F': []
}

start_node = 'A'
goal_node = 'D'
result = DFS(graph, start_node, goal_node)
print("Path found:", result)
