# nRF52832 Multi-Channel ADC to PWM Controller

This project implements a thread-safe, real-time pipeline on the **Nordic nRF52832** SoC using **Zephyr RTOS**. It samples multiple analog inputs via the SAADC peripheral and maps those values to PWM-driven outputs with software-based signal conditioning.

## ✨ Technologies

* **Zephyr RTOS**: Powering multithreaded execution and hardware abstraction.
* **C (Embedded)**: Core logic for peripheral interfacing and data processing.
* **nRF52832 (ARM Cortex-M4)**: The target microcontroller hardware.
* **DeviceTree (DTS)**: Used for hardware-agnostic peripheral configuration (ADC and PWM nodes).
* **K-Config**: For enabling kernel features like Mutexes and peripheral drivers.

## 🚀 Features

* **Multithreaded Architecture**: Features a high-priority producer thread (`pot_thread_id`) for sampling and a main consumer thread for actuation.
* **Thread-Safe IPC**: Shared data is protected by a **Zephyr Mutex** (`my_mutex`) to prevent race conditions.
* **Signal Conditioning**: Implements a `DEADZONE_THRESHOLD` (25 units) to filter analog noise and prevent PWM jitter.
* **Boundary Clamping**: Soft-clamping logic ensures stable "Full-Off" and "Full-On" states at the voltage rail limits.
* **Real-time Monitoring**: Synchronized console output via `printk` for live debugging of raw and filtered values.

## 📍 The Process

The goal of this project was to create a responsive system where analog sensor data (like a potentiometer) directly controls digital actuators (like LEDs) without blocking the CPU. By separating the sensing and actuation into two distinct threads, the system remains stable and responsive even at high sample rates. 

I leveraged the nRF52832's 12-bit SAADC to obtain high-resolution input ($0$ to $4095$). To ensure a smooth user experience, I implemented a custom deadzone filter and a mutex-locking mechanism that allows the peripheral thread to update sensor data only when a significant physical change is detected.



## 🚦 Running the Project

1. **Set up the Environment**: Ensure you have the **nRF Connect SDK** and `west` tool installed.
2. **Clone the repository**:
   ```bash
   git clone [https://github.com/your-username/your-repo-name.git](https://github.com/your-username/your-repo-name.git)

## 📸 Preview

The system provides real-time feedback through the serial console. It uses ANSI escape codes to maintain a clean, stationary display in your terminal emulator (such as PuTTY or the nRF Connect Serial Terminal), showing the synchronized data between the producer and consumer threads.

### **Live Serial Output**
```text
Sent: Channel 1 Raw = 2050, Channel 2 Raw = 1012, Channel 4 Raw = 15
Actuated: Channel 1 Raw = 2050, Channel 2 Raw = 1012, Channel 4 Raw = 15
```
## 📺 Video Demo
[<img src="https://img.youtube.com/vi/JlQgS1oauD8/maxresdefault.jpg" width="600" style="border-radius:10px;">](https://youtu.be/JlQgS1oauD8)

*Demonstration of Thread-Safe Peripheral Interfacing in Zephyr RTOS.*
