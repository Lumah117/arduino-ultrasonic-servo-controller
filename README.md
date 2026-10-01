# Arduino Ultrasonic Servo Controller

An Arduino-based sensor and actuator control project developed during my university studies.

The system uses an ultrasonic distance sensor to measure the distance of an object and uses the resulting measurement to control the position of a servo motor. Real-time distance information is simultaneously displayed through an I²C LCD and the Arduino serial interface.

## Project Overview

The project combines sensing, processing, actuation and user feedback within a single embedded control system.

```text
       Physical Object
             |
             v
     Ultrasonic Sensor
             |
             | Echo duration
             v
          Arduino
             |
       Calculate Distance
             |
        +----+----+
        |         |
        v         v
   Servo Motor   Display
                 |
              +--+--+
              |     |
             LCD  Serial
```

The Arduino continuously measures the distance between the ultrasonic sensor and an object.

That measurement is then used both as feedback to the user and as an input to the servo-control logic.

## Technologies

- Arduino
- Embedded C/C++
- Ultrasonic distance sensing
- Servo control
- I²C communication
- LCD output
- Serial communication

## Hardware

The implementation uses:

- Arduino-compatible microcontroller
- Ultrasonic distance sensor
- Servo motor
- 20×4 I²C LCD
- Associated wiring and power connections

## Repository Structure

```text
arduino-ultrasonic-servo-controller/
│
├── README.md
├── LICENSE
│
└── src/
    └── ultrasonic_servo_controller.ino
```

## Libraries

The project uses the Arduino:

```cpp
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

libraries to provide servo control and communication with the I²C LCD.

## Ultrasonic Distance Measurement

The ultrasonic sensor uses separate trigger and echo connections:

```cpp
#define trigPin 3
#define echoPin 2
```

To perform a measurement, the controller generates a short pulse on the trigger pin.

The duration of the returned echo pulse is then measured using:

```cpp
pulseIn(echoPin, HIGH);
```

The original implementation converts this duration into an estimated distance using:

```cpp
distance = (duration / 2) / 29.1;
```

The division by two accounts for the ultrasonic pulse travelling to the object and returning to the sensor.

## Servo Control

The servo is connected to Arduino pin 6.

The measured distance determines the commanded servo position.

### Close Range

When the measured distance is below 15 cm:

```text
Distance < 15 cm
       |
       v
Servo = 0°
```

This establishes a minimum operating threshold.

### Active Control Range

When the measured distance is between approximately 15 cm and 180 cm, the original implementation calculates:

```cpp
servo_limits = distance / 2;
```

and sends the resulting value to the servo.

For example:

| Measured Distance | Servo Command |
|---:|---:|
| 20 cm | 10° |
| 60 cm | 30° |
| 100 cm | 50° |
| 140 cm | 70° |
| 180 cm | Outside active condition |

This creates a simple proportional relationship between sensed distance and actuator position.

### Beyond Measurement Range

For distances outside the configured active range, the system displays a message indicating that the measured distance exceeds 180 cm.

## LCD Feedback

The project uses a 20×4 I²C LCD configured at address:

```text
0x27
```

Distance measurements are displayed directly on the LCD together with the `cm` unit.

This provides local feedback without requiring the system to remain connected to a computer.

## Serial Feedback

Measurements are also transmitted over the Arduino serial connection at:

```text
9600 baud
```

This provided an additional method of observing and debugging sensor measurements during development.

## Control Flow

The original control behaviour can be represented as:

```text
            Start
              |
              v
       Trigger Ultrasonic
              |
              v
       Measure Echo Time
              |
              v
       Calculate Distance
              |
              v
       +------+------+
       |             |
   < 15 cm       15–180 cm
       |             |
       v             v
  Servo = 0°    Distance / 2
       |             |
       +------+------+
              |
              v
       Update LCD
              |
              v
       Update Serial
              |
              v
            Repeat
```

Measurements are repeated approximately every 500 ms.

## Concepts Demonstrated

This project provided practical experience with:

- Embedded programming
- Sensor interfacing
- Actuator control
- Ultrasonic ranging
- Pulse-duration measurement
- Sensor-data processing
- Servo positioning
- I²C communication
- LCD interfacing
- Serial communication
- Conditional control logic
- Hardware/software integration

## Original Source Code

The source code in `src/ultrasonic_servo_controller.ino` preserves the original university implementation.

It has intentionally not been rewritten to make the project appear representative of my current embedded-software practices.

## Retrospective

This project represented a progression from simple digital input/output toward a basic closed interaction between sensing and actuation.

The software takes information from the physical environment, processes that measurement and uses it to determine the behaviour of another physical device.

With my current embedded and robotics experience, there are several aspects I would approach differently.

### LCD Initialisation

The original implementation calls:

```cpp
lcd.init();
lcd.backlight();
```

inside the main `loop()`.

These operations only need to occur during system initialisation and would therefore be moved into `setup()`.

### Non-Blocking Timing

The implementation uses:

```cpp
delay(500);
```

between measurement cycles.

For a larger embedded application I would use non-blocking timing based on `millis()` or a task-based architecture so that other system functions could continue operating while waiting for the next sensor update.

### Sensor Validation

The original implementation assumes that `pulseIn()` returns a valid echo measurement.

A more robust system would account for:

- Sensor timeout
- Missing echoes
- Out-of-range readings
- Spurious measurements
- Measurement noise

Filtering could also be introduced before the distance measurement is used for actuator control.

### Servo Mapping

The original controller uses:

```text
servo position = distance / 2
```

within the active range.

A more flexible implementation would explicitly map the sensor's operating range to the required servo range, allowing the relationship between sensing and actuation to be configured independently.

### Code Structure

The current implementation performs measurement, display and servo control within the main loop.

A larger system would separate these responsibilities into functions such as:

```text
readDistance()
     |
     v
validateMeasurement()
     |
     v
calculateServoPosition()
     |
     +----> updateServo()
     |
     +----> updateDisplay()
```

This would improve readability, maintainability and testability.

## Portfolio Context

This project demonstrates an early stage in my progression toward embedded systems and robotics.

Compared with my earlier Arduino traffic-light project, this system introduces a feedback relationship between the physical environment and an actuator:

```text
Traffic Light Project
        |
        | Digital I/O + sequencing
        v
Ultrasonic Servo Project
        |
        | Sensor measurement
        | Data processing
        | Actuator control
        | I²C peripheral
        v
Later Robotics Projects
```

It therefore provides an early example of integrating sensors, actuators and user-interface hardware within an embedded control application.
