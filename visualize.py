import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time

def read_grid_from_file(file_path):
    grid_data = []
    with open(file_path, 'r') as file:
        for line in file:
            i, j, k = map(int, line.strip().split())
            grid_data.append((i, j, k))
    return grid_data

def animate_grid(grid_data):
    max_i = max(grid_data, key=lambda x: x[0])[0]
    max_j = max(grid_data, key=lambda x: x[1])[1]

    grid = [[0 for _ in range(max_j + 1)] for _ in range(max_i + 1)]

    fig, ax = plt.subplots()

    def animate(frame):
        if frame < len(grid_data):
            i, j, k = grid_data[frame]
            grid[i][j] = k

        ax.clear()
        ax.imshow(grid, cmap='viridis', origin='upper')

        for i in range(max_i + 1):
            for j in range(max_j + 1):
                if grid[i][j] != 0:
                    ax.text(j, i, grid[i][j], ha='center', va='center', color='white')

        plt.xlabel("Column Index (j)")
        plt.ylabel("Row Index (i)")
        plt.title("Grid Visualization")
        plt.xticks(range(max_j + 1))
        plt.yticks(range(max_i + 1))
        plt.gca().invert_yaxis()  # Invert y-axis to match the standard grid layout

    anim = animation.FuncAnimation(fig, animate, frames=len(grid_data)+1, repeat=False, interval=1)

    plt.show()

if __name__ == "__main__":
    file_path = "bug.txt"  # Replace with the actual file path
    grid_data = read_grid_from_file(file_path)
    animate_grid(grid_data)
