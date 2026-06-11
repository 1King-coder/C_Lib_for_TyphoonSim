import control as ctl
import numpy as np
import matplotlib.pyplot as plt

class FirstOrderSystem:
    def __init__(self, Kdc, Tau, fast_tol=0.001):
        self.Kdc = Kdc
        self.Tau = Tau
        self.fast_tol = fast_tol

    def is_fast(self) -> bool:
        return self.Tau <= self.fast_tol

    def transfer_function(self):
        s = ctl.TransferFunction.s
        return self.Kdc / (self.Tau * s + 1)
    
    def step_response(self, T=np.linspace(0, 5, 1000)):
        system = self.transfer_function()
        res = ctl.step_response(system, T=T)
        return res.time, res.outputs
    
def calc_PI_constants_slow_FOS(fos, ksi, ts):
    Kdc = fos.Kdc
    Tau = fos.Tau
    omega_n = 4 / (ksi * ts)
    
    Kp = round((2 * ksi * omega_n * Tau - 1) / Kdc, 6)
    Ki = round((omega_n**2) * Tau / Kdc, 6)
    
    return {
        "Kp": Kp,
        "Ki": Ki
    }

def calc_PI_constants_fast_FOS(fos, ts):
    Kdc = fos.Kdc
    Tau = fos.Tau
    
    Kp = round(4 * Tau / (ts * Kdc), 6)  # (2*ksi*omega_n * Tau - 1)
    Ki = round(Kp / Tau, 6)  # (omega_n**2) * Tau / Vcc
    
    return {
        "Kp": Kp,
        "Ki": Ki
    }

class PISystemApprox:
    def __init__ (self, plant: FirstOrderSystem, ksi, ts):
        self.plant = plant
        self.__controller_constants = None
        self.ksi = ksi
        self.ts = ts
        self.Kp = 0
        self.Ki = 0
        self.Kp, self.Ki = self.controller_constants().values()

    def controller_constants(self):
        if self.plant.is_fast():
            self.__controller_constants = calc_PI_constants_fast_FOS(self.plant, self.ts)
        
        self.__controller_constants = calc_PI_constants_slow_FOS(self.plant, self.ksi, self.ts)
        return self.__controller_constants
