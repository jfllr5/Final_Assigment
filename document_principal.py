import subprocess
import time
import os
import tqdm

time_max = 0

for i in tqdm.trange(1000):
    start_time = time.time()
    os.system("./task4> /dev/null")
    end_time = time.time()

    elapsed_time = end_time - start_time

    if elapsed_time > time_max:
        time_max = elapsed_time

print("Temps maximal: {:.3f} secondes".format(time_max))