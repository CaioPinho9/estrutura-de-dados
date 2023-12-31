import time

import matplotlib.pyplot as plt
from matplotlib import image as mpimg


# Helper class to represent a node in the tree
class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


# Parse the BFS string into a binary tree
def parse_bfs_string(bfs_string):
    values = bfs_string.split()
    if not values:
        return None
    root = TreeNode(values[0])
    queue = [root]
    i = 1
    while i < len(values):
        node = queue.pop(0)
        left_val = values[i]
        i += 1
        node.left = TreeNode(left_val)
        queue.append(node.left)
        if i >= len(values):
            break
        right_val = values[i]
        i += 1
        node.right = TreeNode(right_val)
        queue.append(node.right)

    return root


# Calculate coordinates for the nodes
def calculate_coordinates(tree):
    coordinates = {}  # Store coordinates as (x, y)

    def dfs(node, level, left, right):
        if not node:
            return
        x = (left + right) / 2
        y = -level
        coordinates[node] = (x, y)
        mid = (left + right) / 2
        dfs(node.left, level + 1, left, mid)
        dfs(node.right, level + 1, mid, right)

    dfs(tree, 0, 0, 1)
    return coordinates


# Plot the binary tree
def plot_binary_tree(bfs_string):
    tree = parse_bfs_string(bfs_string)
    coordinates = calculate_coordinates(tree)
    fig, ax = plt.subplots()
    for node, (x, y) in coordinates.items():
        if node.value == "#":
            continue

        ax.text(
            x, y,
            str(node.value),
            ha='center',
            va='center',
            fontsize=20,
            bbox=dict(facecolor='white', edgecolor='black', boxstyle="circle")
        )
        if node.left and node.left.value != "#":
            x1, y1 = coordinates[node]
            x2, y2 = coordinates[node.left]
            ax.plot([x1, x2], [y1, y2], 'b-')
        if node.right and node.right.value != "#":
            x1, y1 = coordinates[node]
            x2, y2 = coordinates[node.right]
            ax.plot([x1, x2], [y1, y2], 'b-')

    ax.axis('off')

    watermark_image = mpimg.imread('logo.png')
    image_height, image_width = watermark_image.shape[:2]
    plot_width, plot_height = fig.get_size_inches()
    position_x = -0.15 * (plot_width - image_width)  # Center the watermark horizontally
    fig.figimage(watermark_image, xo=position_x, yo=1, alpha=0.2, zorder=-3)

    plt.tight_layout()

    plt.show()


# Example BFS string
trees = [
    "6 ",
    "6 5 # # ",
    "5 -2 6 # # # # ",
    "5 -2 6 # # # 7 # # # # # # # # # # ",
    "5 -2 6 # -1 # 7 # # # # # # # # # # # # ",
    "5 -1 6 -2 0 # 7 # # # # # # # # # # # # # # # # # # ",
    "5 -1 6 -2 0 6 7 # # # # # # # # # # # # # # # # # # # # # # # # ",
    "5 -1 6 -2 0 6 7 # # # # # # # # # # # # # # # # # # # # # # # # ", ]
for tree in trees:
    plot_binary_tree(tree)
    time.sleep(2)
