import numpy as np
import matplotlib.pyplot as plt

# Parametreler
e_ripple = 0.19  # Dalgacık faktörü
n = 6           # Filtre derecesi
omega_p_lpf = 340
omega_p_hpf = 130
omega_c_bpf = 310
bw_bpf = 95

# Payda kökleri (kutuplar) ve sıfırlar
D = []
Z = []
for k in range(1, n + 1):
    D_Re = -np.sin((2 * k - 1) * np.pi / (2 * n)) * np.sinh(np.arcsinh(1 / e_ripple) / n)
    D_Im = 1j * np.cos((2 * k - 1) * np.pi / (2 * n)) * np.cosh(np.arcsinh(1 / e_ripple) / n)
    D.append(1 / (D_Re + D_Im))  # Payda kökleri (kutuplar)
    Z.append(1 / (-1j * np.cos(np.pi * (2 * k - 1) / (2 * n))))  # Pay sıfırları

# Pay ve payda polinom katsayılarını hesaplama
HcN = []
HcD = []
for k in range((n + 1) // 2):
    if k == (n - k - 1):  # Eğer tek kök varsa
        HcN.append(np.real([0, 0, 1]))
        HcD.append(np.real([0, 1, -D[k]]))
    else:
        HcN.append(np.real(np.convolve([1, -Z[k]], [1, -Z[n - k - 1]])))
        HcD.append(np.real(np.convolve([1, -D[k]], [1, -D[n - k - 1]])))

HcN = np.array(HcN)
HcD = np.array(HcD)

# Kazanç çarpanı hesaplama
Gain = np.prod(HcD[:, 2]) / np.prod(HcN[:, 2])
HcN *= Gain**(1 / ((n + 1) // 2))

# Normalize frekans cevabı
w = np.linspace(0.02, 8, 200)  # Normalize frekans ekseni
Hw = np.zeros_like(w, dtype=np.complex128)

for l, freq in enumerate(w):
    Nw = 1
    Dw = 1
    for k in range(len(HcN)):
        Nw *= HcN[k, 0] * (1j * freq)**2 + HcN[k, 1] * (1j * freq) + HcN[k, 2]
        Dw *= HcD[k, 0] * (1j * freq)**2 + HcD[k, 1] * (1j * freq) + HcD[k, 2]
    Hw[l] = abs(Nw / Dw)

# Gerçek frekans cevabı
w_real = np.linspace(1e-3, 600, 1000)  # Gerçek frekans ekseni
Hw_lpf = np.zeros_like(w_real, dtype=np.complex128)
Hw_hpf = np.zeros_like(w_real, dtype=np.complex128)
Hw_bpf = np.zeros_like(w_real, dtype=np.complex128)

for l, freq in enumerate(w_real):
    Nw_lpf, Dw_lpf = 1, 1
    Nw_hpf, Dw_hpf = 1, 1
    Nw_bpf, Dw_bpf = 1, 1
    for k in range(len(HcN)):
        # LPF
        Nw_lpf *= HcN[k, 0] * (1j * freq / omega_p_lpf)**2 + HcN[k, 1] * (1j * freq / omega_p_lpf) + HcN[k, 2]
        Dw_lpf *= HcD[k, 0] * (1j * freq / omega_p_lpf)**2 + HcD[k, 1] * (1j * freq / omega_p_lpf) + HcD[k, 2]
        # HPF
        Nw_hpf *= HcN[k, 0] * (1j * omega_p_hpf / freq)**2 + HcN[k, 1] * (1j * omega_p_hpf / freq) + HcN[k, 2]
        Dw_hpf *= HcD[k, 0] * (1j * omega_p_hpf / freq)**2 + HcD[k, 1] * (1j * omega_p_hpf / freq) + HcD[k, 2]
        # BPF
        Nw_bpf *= HcN[k, 0] * (1j * (freq**2 - omega_c_bpf**2) / (freq * bw_bpf))**2 + \
                  HcN[k, 1] * (1j * (freq**2 - omega_c_bpf**2) / (freq * bw_bpf)) + HcN[k, 2]
        Dw_bpf *= HcD[k, 0] * (1j * (freq**2 - omega_c_bpf**2) / (freq * bw_bpf))**2 + \
                  HcD[k, 1] * (1j * (freq**2 - omega_c_bpf**2) / (freq * bw_bpf)) + HcD[k, 2]
    Hw_lpf[l] = abs(Nw_lpf / Dw_lpf)
    Hw_hpf[l] = abs(Nw_hpf / Dw_hpf)
    Hw_bpf[l] = abs(Nw_bpf / Dw_bpf)

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
