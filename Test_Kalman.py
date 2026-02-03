# from kalman_filter import KalmanFilter

# # Create filter
# kf = KalmanFilter(P_init=1.0)

# # Single step
# result = kf.step(sigma_sensor=1.0, x_measure=5.2, x_cal=4.8)
# print(f"K: {result['K']:.3f}, x_hat: {result['x_hat']:.3f}")

# # Multiple steps
# for i in range(5):
#     result = kf.step(1.0, 5.1 + 0.1*i, 4.9 + 0.05*i)
#     print(f"Step {i}: K={result['K']:.3f}, x_hat={result['x_hat']:.3f}")

from kalman_filter import KalmanFilter  # Import the class

# Create filter instance
kf = KalmanFilter(P_init=1.0)

# Test single step
result = kf.step(sigma_sensor=1.0, x_measure=5.2, x_cal=4.8)
print(f"Kalman gain K: {result['K']:.3f}")
print(f"State estimate x_hat: {result['x_hat']:.3f}")

# Test multiple steps (simulating time series)
print("\nMultiple steps:")
measurements = [5.2, 5.1, 5.3, 5.0, 5.4]  # Simulated measurements
calculations = [4.8, 4.9, 5.0, 4.7, 5.1]   # Model calculations
for i, (x_m, x_c) in enumerate(zip(measurements, calculations)):
    result = kf.step(1.0, x_m, x_c)
    print(f"Step {i+1}: K={result['K']:.3f}, x_hat={result['x_hat']:.3f}")

# Reset and test again
kf.reset()
print("\nAfter reset:")
result = kf.step(1.0, 5.2, 4.8)
print(f"K: {result['K']:.3f}, x_hat: {result['x_hat']:.3f}")
