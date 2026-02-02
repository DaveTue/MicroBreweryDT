from pythonfmu.fmi2slave import Fmi2Slave, Fmi2Causality, Fmi2Variability



class ThermoDynamics(Fmi2Slave):
    modelName = "ThermoDynamics"
    author = "David manrique"
    description = "Simple thermodynamics model with cooling and pump effects"

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
    

        # Parameters
        self.delta_t = self.register_variable(
            # name="delta_t",
            causality=Fmi2Causality.parameter,
            variability=Fmi2Variability.fixed,
            initial=0.1
        )
        self.Cp = self.register_variable(
            # name="Cp",
            causality=Fmi2Causality.parameter,
            variability=Fmi2Variability.fixed,
            initial=4180.0
        )
        self.Vol = self.register_variable(
            # name="Vol",
            causality=Fmi2Causality.parameter,
            variability=Fmi2Variability.fixed,
            initial=1.0
        )
        self.delta_H = self.register_variable(
            # name="delta_H",
            causality=Fmi2Causality.parameter,
            variability=Fmi2Variability.fixed,
            initial=-5e5
        )
        self.h = self.register_variable(
            # name="h",
            causality=Fmi2Causality.parameter,
            variability=Fmi2Variability.fixed,
            initial=100.0
        )
        self.A = self.register_variable(
            # name="A",
            causality=Fmi2Causality.parameter,
            variability=Fmi2Variability.fixed,
            initial=1.0
        )

        # Inputs
        self.T_k = self.register_variable(
            # name="T_k",
            causality=Fmi2Causality.input,
            variability=Fmi2Variability.discrete,
            initial=300.0
        )
        self.T_cool = self.register_variable(
            # name="T_cool",
            causality=Fmi2Causality.input,
            variability=Fmi2Variability.discrete,
            initial=290.0
        )
        self.delta_C = self.register_variable(
            # name="delta_C",
            causality=Fmi2Causality.input,
            variability=Fmi2Variability.discrete,
            initial=0.0
        )
        self.pump = self.register_variable(
            # name="pump",
            causality=Fmi2Causality.input,
            variability=Fmi2Variability.discrete,
            initial=1.0
        )
        self.density = self.register_variable(
            # name="density",
            causality=Fmi2Causality.input,
            variability=Fmi2Variability.discrete,
            initial=1000.0
        )

        # Output
        self.T_k1 = self.register_variable(
            # name="T_k1",
            causality=Fmi2Causality.output,
            variability=Fmi2Variability.discrete,
            initial=300.0
        )

    def do_step(self, current_time: float, step_size: float) -> bool:
        # Read inputs and parameters
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

# def create_fmu_instance():
#     return ThermoDynamics()