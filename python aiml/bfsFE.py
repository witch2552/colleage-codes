from collections import deque

def bfs(graph, start, goal):
    frontier = deque([[start]])  # Each path is a list of states
    explored = set()

    while frontier:
        path = frontier.popleft()
        state = path[-1]

        if state == goal:
            return path

        if state not in explored:
            explored.add(state)
            for neighbor in graph.get(state, []):
                if neighbor not in explored:
                    new_path = path + [neighbor]
                    frontier.append(new_path)

    return None

# Example usage
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

result = bfs(graph, 'S', 'H')
print("Path from S to H:", result)
