def dfs(graph, start, goal):
    # Stack will store paths, not just nodes
    stack = [[start]]
    visited = set()

    while stack:
        path = stack.pop()          # Get last path
        node = path[-1]             # Current node = last element in path

        if node == goal:
            return path             # Found goal → return path

        if node not in visited:
            visited.add(node)
            for neighbor in graph.get(node, []):
                if neighbor not in visited:
                    new_path = list(path)  # Copy current path
                    new_path.append(neighbor)
                    stack.append(new_path)

    return None  # Goal not found

# Example usage
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
result = dfs(graph, start_node, goal_node)
print("Path found:", result)
