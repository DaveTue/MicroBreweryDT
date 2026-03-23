from pythonfmu3.fmi3slave import Fmi3Slave, Fmi3Causality, Fmi3Variability
from pythonfmu3 import Float64, Int32, Boolean, String  # Types directly from main package

class ThermoDynamics(Fmi3Slave):
    # modelName = "ThermoDynamics"
    

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.author = "David manrique"
        self.description = "Simple thermodynamics model with cooling and pump effects"
        #independent variable
        self.time= 0.0
        self.register_variable(Float64("time", causality=Fmi3Causality.independent))

        # Parameters
        
        self.register_variable(Float64("delta_t", causality=Fmi3Causality.parameter))
        self.register_variable(Float64("Cp", causality=Fmi3Causality.parameter))
        self.register_variable(Float64("Vol", causality=Fmi3Causality.parameter))
        self.register_variable(Float64("delta_H", causality=Fmi3Causality.parameter))
        self.register_variable(Float64("h", causality=Fmi3Causality.parameter))
        self.register_variable(Float64("A", causality=Fmi3Causality.parameter))
        
        # parameters value:
        self.delta_t = 1.0
        self.Cp = 1.2552
        self.Vol = 25.0
        self.delta_H = -91200
        self.h = 200.89
        self.A = 0.1817

        # Inputs
        self.register_variable(Float64("T_k", causality=Fmi3Causality.input))
        self.register_variable(Float64("T_cool", causality=Fmi3Causality.input))
        self.register_variable(Float64("delta_C", causality=Fmi3Causality.input))
        self.register_variable(Float64("pump", causality=Fmi3Causality.input))
        self.register_variable(Float64("density", causality=Fmi3Causality.input))
        
        # Inputs value:
        self.T_k = 291.15
        self.T_cool = 291.15
        self.delta_C = 0.0
        self.pump = 0
        self.density = 1.034
        
        # Output
        
        self.register_variable(Float64("T_k1", causality=Fmi3Causality.output))
        # self.register_variable(Float64("T_k1", causality=Fmi3Causality.output, variability=Fmi3Variability.discrete, start=291.15))
        self.T_k1 = 291.15  # Initialize output value
        
    def do_step(self, current_time: float, step_size: float) -> bool:
        # Read inputs and parameters (use .value)
        T_k = self.T_k
        T_cool = self.T_cool
        delta_C = self.delta_C
        pump = self.pump
        rho = self.density
        delta_t = self.delta_t
        Cp = self.Cp
        Vol = self.Vol
        delta_H = self.delta_H
        h = self.h
        A = self.A

        # Discrete update
        factor = delta_t / (rho * Cp * Vol)
        self.T_k1 = factor * (-delta_H * delta_C - pump * h * A * (T_k - T_cool)) + T_k

        return True
