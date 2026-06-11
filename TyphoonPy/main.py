import numpy as np
import control as ctl
import matplotlib.pyplot as plt
from src.proj_ctrl import FirstOrderSystem, PISystemApprox
exec_typ = False

s = ctl.TransferFunction.s
Kdc = 4.589
Tau_w = 0.11
p = 10      #number of machine pole pairs
b = 5e-4              #friction coefficient
Jm = 0.19445                #combined rotor and load moment of inertia
R = 0.35                   #stator phase resistance
L = 0.3e-3                #stator phase inductance
Km = 173.07                 #back-EMF constant

W_s = Kdc / (Tau_w * s + 1)
G_s = 1 / (L * s + R)
C_s = (s + 1000)/s

P_s = W_s * C_s

plt.figure(figsize=(10, 6))
# root_locus =ctl.root_locus(P_s)
Vcc = 36
ksi_i = 0.9
ts_i = 0.005
omega_n_i = 4 / (ksi_i * ts_i)

Kp_i = round(4 * L / (ts_i), 6)  # (2*ksi_i*omega_n_i * L - R)
Ki_i = round(R/L * Kp_i, 6)  # (omega_n_i**2) * L / Vcc
# print(f"Kp_i: {Kp_i}, Ki_i: {Ki_i}")

w_sys = FirstOrderSystem(Kdc, Tau_w)
ksi_w = 0.9
ts_w = 0.5
omega_n_w = 4 / (ksi_w * ts_w)
PI_w = PISystemApprox(w_sys, ksi_w, ts_w)

Kp_w = PI_w.Kp
Ki_w = PI_w.Ki
print(f"Kp_w: {Kp_w}, Ki_w: {Ki_w}")


Tau_s = 1/b /(Jm/b * s + 1) * 2*np.pi/60

# res = ctl.step_response(Tau_s, T=np.linspace(0, 2000, 10000))

# plt.plot(res.time, res.outputs)
# plt.title("Step Response of the System")
# plt.show()
ksi_torq = 0.9
ts_torq = 0.5
# omega_n_tau = 4 / (ksi_tau * ts_tau)



# rad_to_rpm = 60 / (2 * np.pi)

# Kp_tau = round((2*ksi_tau*omega_n_tau*(Jm/b) - 1)/(1/b), 6)
# Ki_tau = round((omega_n_tau**2) * (Jm/b) / (1/b), 6)
torq_sys = FirstOrderSystem(1/b, Jm/b)

PI = PISystemApprox(torq_sys, ksi_torq, ts_torq)

print(f"Kp_torq: {PI.Kp}, Ki_torq: {PI.Ki}")

R, L = 5.184, 100e-6

G_s = 1/ (L*s + R)
current_sys = FirstOrderSystem(1/R, L/R)
PI_current = PISystemApprox(current_sys, 0.8, 0.03)
print(f"Kp_current: {PI_current.Kp}, Ki_current: {PI_current.Ki}")

if exec_typ:
    from typhoon import exec
    exec(Kp_i=Kp_i, Ki_i=Ki_i)
