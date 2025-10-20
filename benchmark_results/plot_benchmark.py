from datetime import datetime
from pathlib import Path

import pandas as pd
from pandas import DataFrame # For type hints
import matplotlib.pyplot as plt

from typing import Union


EXEC_TIME: str = datetime.now().strftime("%Y-%m-%d_%H:%M")
DATA_PATH = Path(__file__).parent.parent / "benchmark_dat/results.csv"
OUTPUT_IMAGE_PATH = Path(__file__).parent.parent / f"plots/benchmark_{EXEC_TIME}.png"
OUTPUT_IMAGE_PATH_PY_RM = Path(__file__).parent.parent / f"plots/benchmark_no_py_{EXEC_TIME}.png"


# Normalize Benchmark Labels to Group by Language
def simplify_labels(df: DataFrame) -> DataFrame:
    """Simplify benchmark labels to just language and optimization level."""
    df['Language'] = df['Benchmark'].str.replace(' Benchmark', '', regex=False)
    return df


def remove_outliers(df: DataFrame, columns: tuple[str, ...], factor: float = 1.5) -> DataFrame:
    """
    Remove outliers using IQR method for specified columns.
    
    Args:
        df: Original DataFrame.
        columns: Columns to check for outliers.
        factor: Multiplier for IQR (default 1.5).
    
    Returns:
        Filtered DataFrame without outliers.
    """
    filtered_df = df.copy()
    for col in columns:
        Q1 = filtered_df[col].quantile(0.25)
        Q3 = filtered_df[col].quantile(0.75)
        IQR = Q3 - Q1
        lower_bound = Q1 - factor * IQR
        upper_bound = Q3 + factor * IQR
        
        # Filter to keep only rows inside bounds for this column
        filtered_df = filtered_df[(filtered_df[col] >= lower_bound) & (filtered_df[col] <= upper_bound)]
    return filtered_df


# Group and Calculate Averages ===
def group_and_average(df: DataFrame) -> DataFrame:
    """Group the data by language and compute mean wall-clock and CPU time."""
    grouped: DataFrame = df.groupby('Language')[['Wall-Clock Time', 'CPU Time']] \
                           .mean() \
                           .sort_values('Wall-Clock Time')
    return grouped


def group_and_stats(df: DataFrame) -> DataFrame:
    """
    Group data by language and calculate mean and std dev for times.
    Returns a DataFrame with multi-level columns (mean and std).
    """
    #Group data
    grouped_mean = df.groupby('Language')[['Wall-Clock Time', 'CPU Time']].mean()
    grouped_std = df.groupby('Language')[['Wall-Clock Time', 'CPU Time']].std()
    
    # Combine mean and std into one DataFrame with multi-level columns
    grouped_stats = pd.concat([grouped_mean, grouped_std], axis=1, keys=['mean', 'std'])
    # Sort by mean wall-clock time
    grouped_stats = grouped_stats.sort_values(('mean', 'Wall-Clock Time'))
    return grouped_stats

def preprocess_data(df: DataFrame) -> DataFrame:
    return group_and_stats(simplify_labels(df)) #remove_outliers(df, ('Wall-Clock Time', 'CPU Time'))))



def plot_benchmark(grouped_stats: DataFrame, output_path: Union[str, Path]) -> None:
    """Plot bar chart with error bars representing std deviation."""
    # Plot config
    plt.figure(figsize=(12, 6))
    bar_width = 0.35
    index = range(len(grouped_stats))

    # Assign metrics to variables
    mean = grouped_stats['mean']
    std = grouped_stats['std']

    plt.bar( # Plot Wall-Clock time
        index, 
        mean['Wall-Clock Time'], 
        bar_width, 
        yerr=std['Wall-Clock Time'], 
        label='Wall-Clock Time', 
        color='skyblue', 
        capsize=5
    )

    plt.bar( # Plot CPU time
        [i + bar_width for i in index], 
        mean['CPU Time'], 
        bar_width, 
        yerr=std['CPU Time'], 
        label='CPU Time', 
        color='orange', 
        capsize=5
    )

    # Create labels and layout
    plt.xlabel('Language / Benchmark')
    plt.ylabel('Time (seconds)')
    plt.title('Average Wall-Clock and CPU Time per Language with Variance')
    plt.xticks([i + bar_width / 2 for i in index], grouped_stats.index, rotation=45, ha='right')
    plt.legend()
    plt.tight_layout()

    plt.savefig(output_path, dpi=300) # Save chart


def main() -> None:
    # Create bar chart plot of benchmark
    raw_data: DataFrame = pd.read_csv(DATA_PATH)
    processed_data: DataFrame = preprocess_data(raw_data)
    plot_benchmark(processed_data, OUTPUT_IMAGE_PATH)

    # Plot without Python benchmark
    processed_data_no_python = processed_data[~processed_data.index.isin(['Python', 'Python NumPy'])]
    plot_benchmark(processed_data_no_python, OUTPUT_IMAGE_PATH_PY_RM)

if __name__ == "__main__":
    main()
     
