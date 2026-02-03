
from kalman_filter import KalmanFilter  # Import the class

# Create filter instance
kf = KalmanFilter(P_init=1648.12)

# Test single step
result = kf.step(sigma_sensor=34.20, x_measure=1011.82, x_cal=1011.832075)
print(f"Kalman gain K: {result['K']:.3f}")
print(f"State estimate x_hat: {result['x_hat']:.3f}")

# Test multiple steps (simulating time series)
print("\nMultiple steps:")
measurements = [1011.832075,982.922587,968.467843,968.467843,982.922587,968.467843,954.013099,968.467843,982.922587]  # Simulated measurements
calculations = [1011.832075,1010.84837148217,1009.86526780627,1008.8827639723,1007.90085998027,1006.91955583017,1005.93885152201,1004.95874705577,1003.97924243148]   # Model calculations
# measurements = [5.2, 5.1, 5.3, 5.0, 5.4]  # Simulated measurements
# calculations = [4.8, 4.9, 5.0, 4.7, 5.1]   # Model calculations
for i, (x_m, x_c) in enumerate(zip(measurements, calculations)):
    result = kf.step(34.20, x_m, x_c)
    print(f"Step {i+1}: K={result['K']:.3f}, x_hat={result['x_hat']:.3f}")

# Reset and test again
kf.reset()
print("\nAfter reset:")
result = kf.step(34.1, 1011.82, 1011.82)
print(f"K: {result['K']:.3f}, x_hat: {result['x_hat']:.3f}")
