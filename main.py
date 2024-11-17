import matplotlib.pyplot as plt
import csv
import numpy as np
import os

def read_csv(filename):
    freqs = []
    amplitudes = []
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            freqs.append(float(row[0]))
            amplitudes.append(float(row[1]))
    return freqs, amplitudes


def plot_frequency_response(freqs, amplitudes, title="Frequency Response"):
    plt.figure(figsize=(10, 6))
    plt.plot(freqs, 20 * np.log10(amplitudes))
    plt.title(title)
    plt.xlabel("Frequency (rad/s)")
    plt.ylabel("Magnitude (dB)")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.axhline(y=0, color='k', linewidth=0.8)
    plt.show()


if __name__ == "__main__":
    filename = "butterworth_response.csv"

    if not os.path.exists(filename):
        filename = os.path.join("cmake-build-debug", filename)

    if not os.path.exists(filename):
        raise FileNotFoundError(f"{filename} dosyası bulunamadı! Mevcut dizin: {os.getcwd()}")

    freqs, amplitudes = read_csv(filename)
    plot_frequency_response(freqs, amplitudes, title="Butterworth Frequency Response")