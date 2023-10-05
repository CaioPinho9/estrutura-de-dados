import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df = pd.read_csv("benchmark.csv")

# Access the columns as pandas Series
listSizeData = df['listSizeData']
sequentialTimeData = df['sequentialTimeData']
treeTimeData = df['treeTimeData']

percentiles = [25, 50, 75, 100]

print("Sequential: ")
for percentile in percentiles:
    result = np.percentile(sequentialTimeData, percentile)
    print(f"{percentile}%: {result}", end=" | ")

print("\nTree: ")
for percentile in percentiles:
    result = np.percentile(treeTimeData, percentile)
    print(f"{percentile}%: {result}", end=" | ")

plt.show()

mean_times = df.groupby('listSizeData')[['treeTimeData', 'sequentialTimeData']].mean().reset_index()

# Step 2: Create a line chart
plt.figure(figsize=(10, 6))  # Set the figure size
plt.plot(mean_times['listSizeData'], mean_times['treeTimeData'], label='Mean Tree Time', marker='o')
plt.plot(mean_times['listSizeData'], mean_times['sequentialTimeData'], label='Mean Sequential Time', marker='o')
plt.xlabel('List Size')
plt.ylabel('Mean Time')
plt.title('Mean Times vs. List Size')
plt.legend()
plt.grid(True)
plt.show()