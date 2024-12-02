import numpy as np
import matplotlib.pyplot as plt

# Parametreler
n = 6  # Filtre derecesi
omega_p_lpf = 340
omega_p_hpf = 130
omega_c_bpf = 310
bw_bpf = 95

# Butterworth filtresi için kutuplar (s)
s = []
for k in range(n):
    D_Re = -np.sin((2 * k + 1) * np.pi / (2 * n))
    D_Im = 1j * np.cos((2 * k + 1) * np.pi / (2 * n))
    s.append(D_Re + D_Im)

# İkinci derece (biquad) payda polinomlarını hesaplama
Hbt = []
for k in range((n + 1) // 2):
    if k == n - k - 1:  # Eğer tek kök varsa
        Hbt.append(np.real([0, 1, -s[k]]))
    else:
        Hbt.append(np.real(np.convolve([1, -s[k]], [1, -s[n - k - 1]])))

Hbt = np.array(Hbt)

# Normalize frekans cevabı
w = np.linspace(0.01, 3, 200)  # Normalize frekans ekseni
Hw = np.zeros_like(w, dtype=np.complex128)

for l, freq in enumerate(w):
    Nw = 1
    Dw = 1
    for k in range(len(Hbt)):
        Nw *= abs(Hbt[k, 2])
        Dw *= abs(Hbt[k, 0] * (1j * freq)**2 + Hbt[k, 1] * (1j * freq) + Hbt[k, 2])
    Hw[l] = Nw / Dw

# Gerçek frekans cevabı
w_real = np.linspace(1e-3, 600, 1000)  # Gerçek frekans ekseni
Hw_lpf = np.zeros_like(w_real, dtype=np.complex128)
Hw_hpf = np.zeros_like(w_real, dtype=np.complex128)
Hw_bpf = np.zeros_like(w_real, dtype=np.complex128)

for l, freq in enumerate(w_real):
    Nw_lpf, Dw_lpf = 1, 1
    Nw_hpf, Dw_hpf = 1, 1
    Nw_bpf, Dw_bpf = 1, 1
    for k in range(len(Hbt)):
        # LPF
        Nw_lpf *= Hbt[k, 2]
        Dw_lpf *= abs(Hbt[k, 0] * (1j * freq / omega_p_lpf)**2 +
                      Hbt[k, 1] * (1j * freq / omega_p_lpf) + Hbt[k, 2])
        # HPF
        Nw_hpf *= Hbt[k, 2]
        Dw_hpf *= abs(Hbt[k, 0] * (1j * omega_p_hpf / freq)**2 +
                      Hbt[k, 1] * (1j * omega_p_hpf / freq) + Hbt[k, 2])
        # BPF
        Nw_bpf *= Hbt[k, 2]
        Dw_bpf *= abs(Hbt[k, 0] * (1j * (freq**2 - omega_c_bpf**2) / (freq * bw_bpf))**2 +
                      Hbt[k, 1] * (1j * (freq**2 - omega_c_bpf**2) / (freq * bw_bpf)) + Hbt[k, 2])
    Hw_lpf[l] = Nw_lpf / Dw_lpf
    Hw_hpf[l] = Nw_hpf / Dw_hpf
    Hw_bpf[l] = Nw_bpf / Dw_bpf

# Grafikler
plt.figure(figsize=(12, 10))

plt.subplot(2, 2, 1)
plt.plot(w, Hw)
plt.title("Normalize Frekans Genlik Grafiği")
plt.xlabel("Frekans (rad/s)")
plt.ylabel("|H(w)|")
plt.grid()

plt.subplot(2, 2, 2)
plt.plot(w_real, Hw_lpf)
plt.title(f"Düşük Geçiren Filtre (LPF): $\\omega_p = {omega_p_lpf}$ rad/s")
plt.xlabel("Frekans (rad/s)")
plt.ylabel("|H(w)|")
plt.grid()

plt.subplot(2, 2, 3)
plt.plot(w_real, Hw_hpf)
plt.title(f"Yüksek Geçiren Filtre (HPF): $\\omega_p = {omega_p_hpf}$ rad/s")
plt.xlabel("Frekans (rad/s)")
plt.ylabel("|H(w)|")
plt.grid()

plt.subplot(2, 2, 4)
plt.plot(w_real, Hw_bpf)
plt.title(f"Bant Geçiren Filtre (BPF): $\\omega_c = {omega_c_bpf}$ rad/s, BW = {bw_bpf} rad/s")
plt.xlabel("Frekans (rad/s)")
plt.ylabel("|H(w)|")
plt.grid()

plt.tight_layout()
plt.show()
