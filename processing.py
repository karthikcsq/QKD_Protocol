import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

raw_data_df = pd.read_csv('cat_data_times.csv', header=None)


def process(raw_data_df):
    data_df = raw_data_df.iloc[21:, :3]
    data_df.columns = ['Time', 'CH1', 'CH2']
    data_df.reset_index(drop=True, inplace=True)
    return data_df

data_df = process(raw_data_df)
print(data_df.head())
print(data_df.shape)

data_np = data_df.to_numpy().astype(float)
difference_np = data_np[:, 1] - data_np[:, 2]
# Concatenate the times
difference_np = np.column_stack((data_np[:, 0], difference_np))


# Plot the data
plt.plot(data_np[:, 0], data_np[:, 1], label='CH1')
plt.plot(data_np[:, 0], data_np[:, 2], label='CH2')
plt.legend()


# Plot the difference, make horizontal axis is longer in display
plt.plot(difference_np[:, 0], difference_np[:, 1])
plt.figure(figsize=(50, 10))
plt.show()
