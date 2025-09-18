import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Load benchmark results
df = pd.read_csv("data/results.csv")

# 1. Execution Time vs Matrix Size
plt.figure(figsize=(8,6))
sns.lineplot(data=df, x="MatrixSize", y="Time(s)", hue="Threads", marker="o")
plt.title("Execution Time vs Matrix Size")
plt.xlabel("Matrix Size (N x N)")
plt.ylabel("Time (seconds)")
plt.legend(title="Threads")
plt.grid(True)
plt.savefig("plots/time_vs_size.png", dpi=300)
plt.close()

# 2. Speedup vs Threads (for each matrix size)
plt.figure(figsize=(8,6))
for size in df["MatrixSize"].unique():
    base_time = df[(df["MatrixSize"] == size) & (df["Threads"] == 1)]["Time(s)"].values[0]
    subset = df[df["MatrixSize"] == size].copy()
    subset["Speedup"] = base_time / subset["Time(s)"]
    plt.plot(subset["Threads"], subset["Speedup"], marker="o", label=f"Size {size}x{size}")

plt.title("Speedup vs Threads")
plt.xlabel("Number of Threads")
plt.ylabel("Speedup (T1 / Tn)")
plt.legend()
plt.grid(True)
plt.savefig("plots/speedup.png", dpi=300)
plt.close()

print("✅ Plots saved in plots/ folder")
