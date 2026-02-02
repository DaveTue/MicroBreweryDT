from pythonfmu3.fmi3slave import Fmi3Slave, Fmi3Causality, Fmi3Variability
from pythonfmu3 import Float64, Int32, Boolean, String  # Types directly from main package

class ThermoDynamics(Fmi3Slave):
    modelName = "ThermoDynamics"
    author = "David manrique"
    description = "Simple thermodynamics model with cooling and pump effects"

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        # Parameters
        self.delta_t = Float64("delta_t", causality=Fmi3Causality.parameter, variability=Fmi3Variability.fixed, start=0.1)
        self.Cp = Float64("Cp", causality=Fmi3Causality.parameter, variability=Fmi3Variability.fixed, start=4180.0)
        self.Vol = Float64("Vol", causality=Fmi3Causality.parameter, variability=Fmi3Variability.fixed, start=1.0)
        self.delta_H = Float64("delta_H", causality=Fmi3Causality.parameter, variability=Fmi3Variability.fixed, start=-5e5)
        self.h = Float64("h", causality=Fmi3Causality.parameter, variability=Fmi3Variability.fixed, start=100.0)
        self.A = Float64("A", causality=Fmi3Causality.parameter, variability=Fmi3Variability.fixed, start=1.0)

        # Inputs
        self.T_k = Float64("T_k", causality=Fmi3Causality.input, variability=Fmi3Variability.discrete, start=300.0)
        self.T_cool = Float64("T_cool", causality=Fmi3Causality.input, variability=Fmi3Variability.discrete, start=290.0)
        self.delta_C = Float64("delta_C", causality=Fmi3Causality.input, variability=Fmi3Variability.discrete, start=0.0)
        self.pump = Float64("pump", causality=Fmi3Causality.input, variability=Fmi3Variability.discrete, start=1.0)
        self.density = Float64("density", causality=Fmi3Causality.input, variability=Fmi3Variability.discrete, start=1000.0)

        # Output
        self.T_k1 = Float64("T_k1", causality=Fmi3Causality.output, variability=Fmi3Variability.discrete, start=300.0)

    def do_step(self, current_time: float, step_size: float) -> bool:
        # Read inputs and parameters (use .value)
        T_k = self.T_k.value
        T_cool = self.T_cool.value
        delta_C = self.delta_C.value
        pump = self.pump.value
        rho = self.density.value

        delta_t = self.delta_t.value
        Cp = self.Cp.value
        Vol = self.Vol.value
        delta_H = self.delta_H.value
        h = self.h.value
        A = self.A.value

        # Discrete update
        factor = delta_t / (rho * Cp * Vol)
        self.T_k1.value = factor * (-delta_H * delta_C - pump * h * A * (T_k - T_cool)) + T_k

        return True
