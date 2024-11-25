import matplotlib.pyplot as plt
import csv
import os
import sys


def read_csv(filename):
    try:
        with open(filename, 'r') as file:
            reader = csv.reader(file)
            freqs, amplitudes = zip(*((float(row[0]), float(row[1])) for row in reader))
        return list(freqs), list(amplitudes)
    except Exception as e:
        raise ValueError(f"Error reading the file '{filename}': {e}")


def plot_frequency_response(freqs, amplitudes, title="Frequency Response",filename=""):
    min_amplitude = 1e-12
    amplitudes = [max(amp, min_amplitude) for amp in amplitudes]

    # Convert to decibels
    # dB_amplitudes = [20 * (math.log10(amp) if amp > 0 else -float('inf')) for amp in amplitudes]

    plt.figure(figsize=(10, 6))
    plt.plot(freqs, amplitudes)
    plt.title(title+" - "+filename)
    plt.xlabel("Frequency (rad/s)")
    plt.ylabel("Magnitude (dB)")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.axhline(y=0, color='k', linewidth=0.8)
    plt.show()


def validate_file_path(filename):
    if os.path.exists(filename):
        return filename

    alternate_path = os.path.join("cmake-build-debug", filename)
    if os.path.exists(alternate_path):
        return alternate_path

    raise FileNotFoundError(f"{filename} not found! Current directory: {os.getcwd()}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise ValueError("Please provide the CSV file name as a command-line argument.")

    input_filename = sys.argv[1]
    valid_filename = validate_file_path(input_filename)
    base_filename = os.path.basename(input_filename)

    freqs, amplitudes = read_csv(valid_filename)
    plot_frequency_response(freqs, amplitudes, title="Frequency Response", filename=base_filename)
