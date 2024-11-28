import numpy as np
import matplotlib.pyplot as plt

# Parametreler
e_ripple = 0.12  # Dalgacık faktörü
n = 6           # Filtre derecesi
omega_p_lpf = 340
omega_p_hpf = 130
omega_c_bpf = 310
bw_bpf = 95

# Payda köklerini bulma
s = []
for k in range(1, n + 1):
    D_Re = -np.sin((2 * k - 1) * np.pi / (2 * n)) * np.sinh(np.arcsinh(1 / e_ripple) / n)
    D_Im = 1j * np.cos((2 * k - 1) * np.pi / (2 * n)) * np.cosh(np.arcsinh(1 / e_ripple) / n)
    s.append(D_Re + D_Im)

# Biquad payda polinomlarını bulma
Hch = []
for k in range((n + 1) // 2):
    if k == (n - k - 1):  # Eğer tek kök varsa
        Hch.append(np.real([0, 1, -s[k].real]))
    else:
        poly = np.convolve([1, -s[k]], [1, -s[n - k - 1]])
        Hch.append(np.real(poly))

Hch = np.array(Hch)

# Frekans ekseni ve cevapları hesaplama
w = np.linspace(0.02, 2, 100)  # Normalize frekans ekseni
w_real = np.linspace(1e-3, 600, 1000)  # Gerçek frekans ekseni (rad/s), sıfırdan başlatma engelleniyor
Hw = np.zeros_like(w, dtype=np.complex128)
Hw_lpf = np.zeros_like(w_real, dtype=np.complex128)
Hw_hpf = np.zeros_like(w_real, dtype=np.complex128)
Hw_bpf = np.zeros_like(w_real, dtype=np.complex128)

# Normalize filtre frekans cevabı
for l, freq in enumerate(w):
    Nw = 1
    Dw = 1
    for k in range(len(Hch)):
        Nw *= np.abs(Hch[k, 2])
        Dw *= np.abs(Hch[k, 0] * (1j * freq)**2 + Hch[k, 1] * (1j * freq) + Hch[k, 2])
    Hw[l] = Nw / Dw

# Denormalize filtre frekans cevapları
for l, freq in enumerate(w_real):
    Nw_lpf, Dw_lpf = 1, 1
    Nw_hpf, Dw_hpf = 1, 1
    Nw_bpf, Dw_bpf = 1, 1
    for k in range(len(Hch)):
        # LPF
        Dw_lpf *= np.abs(Hch[k, 0] * (1j * freq / omega_p_lpf)**2 +
                         Hch[k, 1] * (1j * freq / omega_p_lpf) +
                         Hch[k, 2])
        # HPF
        Dw_hpf *= np.abs(Hch[k, 0] * (1j * omega_p_hpf / freq)**2 +
                         Hch[k, 1] * (1j * omega_p_hpf / freq) +
                         Hch[k, 2])
        # BPF
        Dw_bpf *= np.abs(Hch[k, 0] * ((1j * (freq**2 - omega_c_bpf**2) / (freq * bw_bpf))**2) +
                         Hch[k, 1] * (1j * (freq**2 - omega_c_bpf**2) / (freq * bw_bpf)) +
                         Hch[k, 2])
    Hw_lpf[l] = 1 / Dw_lpf
    Hw_hpf[l] = 1 / Dw_hpf
    Hw_bpf[l] = 1 / Dw_bpf

# Grafikler
plt.figure(figsize=(12, 10))

plt.subplot(2, 2, 1)
plt.plot(w, np.abs(Hw))
plt.title("Normalize Frekans Genlik Grafiği")
plt.xlabel("Frekans (rad/s)")
plt.ylabel("|H(w)|")
plt.grid()

plt.subplot(2, 2, 2)
plt.plot(w_real, np.abs(Hw_lpf))
plt.title(f"Düşük Geçiren Filtre (LPF): $\\omega_p = {omega_p_lpf}$ rad/s")
plt.xlabel("Frekans (rad/s)")
plt.ylabel("|H(w)|")
plt.grid()

plt.subplot(2, 2, 3)
plt.plot(w_real, np.abs(Hw_hpf))
plt.title(f"Yüksek Geçiren Filtre (HPF): $\\omega_p = {omega_p_hpf}$ rad/s")
plt.xlabel("Frekans (rad/s)")
plt.ylabel("|H(w)|")
plt.grid()

plt.subplot(2, 2, 4)
plt.plot(w_real, np.abs(Hw_bpf))
plt.title(f"Bant Geçiren Filtre (BPF): $\\omega_c = {omega_c_bpf}$ rad/s, BW = {bw_bpf} rad/s")
plt.xlabel("Frekans (rad/s)")
plt.ylabel("|H(w)|")
plt.grid()

plt.tight_layout()
plt.show()
