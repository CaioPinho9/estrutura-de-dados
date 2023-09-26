import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df = pd.read_csv("benchmark.csv")

# Access the columns as pandas Series
listSizeData = df['listSizeData']
positionData = df['positionData']
sequentialTimeData = df['sequentialTimeData']
binaryTimeData = df['binaryTimeData']
mapTimeData = df['mapTimeData']

plt.scatter(sequentialTimeData, mapTimeData, marker='o')

# Add labels and a title

# Show the chart
plt.grid(True)

percentiles = [25, 50, 75, 100]

print("Sequential: ")
for percentile in percentiles:
    result = np.percentile(sequentialTimeData, percentile)
    print(f"{percentile}% Percentile: {result}", end=" | ")

print("\nBinary: ")
for percentile in percentiles:
    result = np.percentile(binaryTimeData, percentile)
    print(f"{percentile}% Percentile: {result}", end=" | ")

print("\nHash: ")
for percentile in percentiles:
    result = np.percentile(mapTimeData, percentile)
    print(f"{percentile}%: {result}", end=" | ")
plt.show()
