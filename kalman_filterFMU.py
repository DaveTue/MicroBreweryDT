# from pythonfmu import Fmi2Slave, Fmi2Status
# import math

# kalman_fmu.py

   
from pythonfmu3 import Fmi3Slave, Fmi3Status, Fmi3Causality

class KalmanFilter(Fmi3Slave):
    modelName = "KalmanFilter"
    author = "David manrique"
    description = "Simple Kalman filter for a brewery fermentation process"
    
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        # Internal state: P from previous step (p_prev)
        self._P_prev = 1.0  # or set via parameter

        # Inputs
        self.sigma_sensor = 1.0
        self.x_measure = 0.0
        self.x_cal = 0.0

        # Outputs
        self.K = 0.0
        self.x_hat = 0.0

        # Register variables with the FMU interface
        # Inputs
        self.register_variable(
            self.sigma_sensor, "sigma_sensor", "Sensor variance", causality=Fmi3Causality.input
        )
        self.register_variable(
            self.x_measure, "x_measure", "Measured value", causality=Fmi3Causality.input
        )
        self.register_variable(
            self.x_cal, "x_cal", "Calculated value", causality=Fmi3Causality.input
        )

        # Outputs
        self.register_variable(
            self.K, "K", "Kalman gain", causality=Fmi3Causality.output
        )
        self.register_variable(
            self.x_hat, "x_hat", "State estimate", causality=Fmi3Causality.output
        )

        # (Optional) parameter to set initial P
        self.register_variable(
            self._P_prev, "P_init", "Initial covariance", causality=Fmi3Causality.parameter
        )

    # ---- lifecycle (optional but helpful) ----
    def reset(self) -> Fmi3Status:
        self._P_prev = 1.0
        self.sigma_sensor = 1.0
        self.x_measure = 0.0
        self.x_cal = 0.0
        self.K = 0.0
        self.x_hat = 0.0
        return Fmi3Status.OK

    # ---- main step ----
    def do_step(self, current_time: float, step_size: float) -> Fmi3Status:
        p_prev = self._P_prev
        sigma = self.sigma_sensor
        x_m = self.x_measure
        x_c = self.x_cal

        # K = p_prev / (p_prev + sigma_sensor)
        denom = p_prev + sigma
        if denom <= 0.0:
            self.K = 0.0
        else:
            self.K = p_prev / denom

        # p_nn = (1 - K) * p_prev
        p_nn = (1.0 - self.K) * p_prev

        # x_hat = x_cal + K * (x_measure - x_cal)
        self.x_hat = x_c + self.K * (x_m - x_c)

        # P = p_nn + sigma_sensor
        P = p_nn + sigma

        # Store P for next step
        self._P_prev = P

        return Fmi3Status.OK
   
   

    

######### Kalmn filter with pythonfmu library
# from pythonfmu import Fmi2Slave, Fmi2Status
# class KalmanFilter(Fmi2Slave):
#     modelName = "KalmanFilter"
#     author = "David manrique"
#     description = "Simple Kalman filter for a brewery fermentation process"
    
#     def __init__(self, **kwargs):
#         super().__init__(**kwargs)

#         # Internal state: P from previous step (p_prev)
#         self._P_prev = 1.0  # or set via parameter

#         # Inputs
#         self.sigma_sensor = 1.0
#         self.x_measure = 0.0
#         self.x_cal = 0.0

#         # Outputs
#         self.K = 0.0
#         self.x_hat = 0.0

#         # Register variables with the FMU interface
#         # Inputs
#         self.register_real_variable(
#             "sigma_sensor", "Sensor variance", "input",
#             getter=lambda: self.sigma_sensor, setter=self._set_sigma
#         )
#         self.register_real_variable(
#             "x_measure", "Measured value", "input",
#             getter=lambda: self.x_measure, setter=self._set_x_measure
#         )
#         self.register_real_variable(
#             "x_cal", "Calculated value", "input",
#             getter=lambda: self.x_cal, setter=self._set_x_cal
#         )

#         # Outputs
#         self.register_real_variable(
#             "K", "Kalman gain", "output", getter=lambda: self.K
#         )
#         self.register_real_variable(
#             "x_hat", "State estimate", "output", getter=lambda: self.x_hat
#         )

#         # (Optional) parameter to set initial P
#         self.register_real_variable(
#             "P_init", "Initial covariance", "parameter",
#             getter=lambda: self._P_prev, setter=self._set_P_init
#         )

#     # ---- lifecycle (optional but helpful) ----
#     def reset(self) -> Fmi2Status:
#         self._P_prev = 1.0
#         self.sigma_sensor = 1.0
#         self.x_measure = 0.0
#         self.x_cal = 0.0
#         self.K = 0.0
#         self.x_hat = 0.0
#         return Fmi2Status.ok

#     # ---- setters for inputs/parameters ----
#     def _set_sigma(self, value: float):
#         self.sigma_sensor = float(value)

#     def _set_x_measure(self, value: float):
#         self.x_measure = float(value)

#     def _set_x_cal(self, value: float):
#         self.x_cal = float(value)

#     def _set_P_init(self, value: float):
#         self._P_prev = float(value)

#     # ---- main step ----
#     def do_step(self, current_time: float, step_size: float) -> Fmi2Status:
#         p_prev = self._P_prev
#         sigma = self.sigma_sensor
#         x_m = self.x_measure
#         x_c = self.x_cal

#         # K = p_prev / (p_prev + sigma_sensor)
#         denom = p_prev + sigma
#         if denom <= 0.0:
#             self.K = 0.0
#         else:
#             self.K = p_prev / denom

#         # p_nn = (1 - K) * p_prev
#         p_nn = (1.0 - self.K) * p_prev

#         # x_hat = x_cal + K * (x_measure - x_cal)
#         self.x_hat = x_c + self.K * (x_m - x_c)

#         # P = p_nn + sigma_sensor
#         P = p_nn + sigma

#         # Store P for next step
#         self._P_prev = P

#         return Fmi2Status.ok

