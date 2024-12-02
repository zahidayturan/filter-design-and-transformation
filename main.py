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


def plot_frequency_response(freqs, amplitudes, filename=""):
    min_amplitude = 1e-12
    amplitudes = [max(amp, min_amplitude) for amp in amplitudes]
    type, filter_name = extract_type_and_filter(filename)

    x_max = max(freqs) * 1.1
    y_max = max(amplitudes) * 1.2
    # Convert to decibels
    # dB_amplitudes = [20 * (math.log10(amp) if amp > 0 else -float('inf')) for amp in amplitudes]

    plt.figure(figsize=(10, 6))
    plt.plot(freqs, amplitudes, label=type)
    plt.title(filter_name + " Filter")
    plt.xlabel("Frequency (rad/s)")
    plt.ylabel("Magnitude (dB)")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.axhline(y=0, color='k', linewidth=0.8)
    plt.xlim([0, x_max])
    plt.ylim([0, y_max])
    plt.legend()
    plt.show()


def validate_file_path(filename):
    if os.path.exists(filename):
        return filename

    alternate_path = os.path.join("cmake-build-debug", filename)
    if os.path.exists(alternate_path):
        return alternate_path

    raise FileNotFoundError(f"{filename} not found! Current directory: {os.getcwd()}")


def plot_multiple_in_one_window(file_list):
    plt.figure(figsize=(12, 8))

    for i, file in enumerate(file_list):
        try:
            valid_filename = validate_file_path(file)
            freqs, amplitudes = read_csv(valid_filename)
            type, filter_name = extract_type_and_filter(valid_filename)

            x_max = max(freqs) * 1.1
            y_max = max(amplitudes) * 1.2

            plt.subplot(2, 2, i + 1)
            plt.plot(freqs, amplitudes, label=type)
            plt.title(filter_name + " Filter")
            plt.xlabel("Frequency (rad/s)")
            plt.ylabel("Magnitude (dB)")
            plt.xlim([0, x_max])
            plt.ylim([0, y_max])
            plt.grid(True, which="both", linestyle="--", linewidth=0.5)
            plt.legend()

        except Exception as e:
            print(f"Error processing file {file}: {e}")

    plt.tight_layout()
    plt.show()


def extract_type_and_filter(filename):
    base_filename = os.path.basename(filename)

    if "normalized" in base_filename:
        type_ = "Normalized"
    elif "lpf" in base_filename:
        type_ = "LPF"
    elif "hpf" in base_filename:
        type_ = "HPF"
    elif "bpf" in base_filename:
        type_ = "BPF"
    else:
        type_ = None

    if "butterworth" in base_filename:
        filter_name = "Butterworth"
    elif "chebyshev" in base_filename:
        filter_name = "Chebyshev"
    elif "inverse_chebyshev" in base_filename:
        filter_name = "Inverse Chebyshev"
    else:
        filter_name = None

    return type_, filter_name


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise ValueError("Please provide the CSV file name as a command-line argument.")

    input_filename = sys.argv[1]

    bCsvFiles = [
        "normalized_butterworth.csv",
        "lpf_butterworth.csv",
        "hpf_butterworth.csv",
        "bpf_butterworth.csv"
    ]

    cCsvFiles = [
        "normalized_chebyshev.csv",
        "lpf_chebyshev.csv",
        "hpf_chebyshev.csv",
        "bpf_chebyshev.csv"
    ]

    iCsvFiles = [
        "normalized_inverse_chebyshev.csv",
        "lpf_inverse_chebyshev.csv",
        "hpf_inverse_chebyshev.csv",
        "bpf_inverse_chebyshev.csv"
    ]

    if input_filename == "b_all":
        plot_multiple_in_one_window(bCsvFiles)
    elif input_filename == "c_all":
        plot_multiple_in_one_window(cCsvFiles)
    elif input_filename == "i_all":
        plot_multiple_in_one_window(iCsvFiles)
    else:
        valid_filename = validate_file_path(input_filename)
        base_filename = os.path.basename(input_filename)

        freqs, amplitudes = read_csv(valid_filename)
        plot_frequency_response(freqs, amplitudes, filename=base_filename)


