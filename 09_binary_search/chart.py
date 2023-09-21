import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df = pd.read_csv("output.csv")

# Access the columns as pandas Series
list_size = df['list_size']
local_of_x = df['local_of_x']

plt.scatter(local_of_x, list_size, marker='o')

# Add labels and a title
plt.xlabel('local_of_x')
plt.ylabel('list_size')

# Show the chart
plt.grid(True)

percentiles = [25, 50, 75, 100]

for percentile in percentiles:
    result = np.percentile(list_size, percentile)
    print(f"{percentile}% Percentile: {result}")

plt.show()
