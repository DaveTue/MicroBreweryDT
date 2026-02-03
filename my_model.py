from pythonfmu3 import Fmi3Slave, Fmi3Causality, Float64

class MyModel(Fmi3Slave):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        # Register variables
        self.time= 0.0
        self.register_variable(Float64("time", causality=Fmi3Causality.independent))
        self.register_variable(Float64("input", causality=Fmi3Causality.input))
        self.register_variable(Float64("output", causality=Fmi3Causality.output))

        # Initialize values
        self.input = 0.0
        self.output = 0.0

    def do_step(self, current_time, step_size):
        # Your model logic here
        self.output = 2.0 * self.input
        self.time += step_size
        return True