"# Automatic Car Parking System

An intelligent Arduino-based car parking management system that automatically controls entry and exit gates using ultrasonic sensors and servo motors. The system tracks available parking slots and displays real-time information on an LCD screen.

## Features

- **Automated Gate Control**: Servo-controlled entry and exit gates
- **Ultrasonic Detection**: HC-SR04 sensors detect vehicle presence
- **Real-time Slot Tracking**: Monitors and displays available parking slots (4 slots)
- **LCD Display**: 16x2 I2C LCD shows parking status and slot availability
- **Smart Logic**: Prevents simultaneous gate operations and handles parking full scenarios
- **Auto-close Gates**: Gates automatically close after 3 seconds

## Hardware Requirements

### Components
- Arduino Uno
- 2x HC-SR04 Ultrasonic Sensors (Entry & Exit detection)
- 2x Servo Motors (Gate control)
- 16x2 LCD Display with I2C module (Address: 0x27)
- Breadboard
- Jumper wires
- Power supply

### Pin Configuration

| Component | Arduino Pin |
|-----------|-------------|
| Entry Sensor (Trig) | D5 |
| Entry Sensor (Echo) | D4 |
| Exit Sensor (Trig) | D3 |
| Exit Sensor (Echo) | D2 |
| Entry Servo | D9 |
| Exit Servo | D6 |
| LCD (I2C SDA) | A4 |
| LCD (I2C SCL) | A5 |

## Software Requirements

- Arduino IDE (1.8.x or higher) OR PlatformIO
- **Libraries:**
  - Wire (built-in)
  - LiquidCrystal_I2C
  - Servo (built-in)

## Installation

### Option 1: Arduino IDE

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/Automatic-car-parking-system.git
   ```

2. Install required libraries via Arduino Library Manager:
   - LiquidCrystal_I2C

3. Open the `.ino` file from the project folder

4. Select **Arduino Uno** as the board

5. Upload the code to your Arduino

### Option 2: PlatformIO

1. Clone the repository

2. Open the `Automatic car parking system` folder in VS Code with PlatformIO

3. Build and upload:
   ```bash
   pio run --target upload
   ```

## How It Works

1. **Initialization**: System starts with 4 available slots, displays welcome message
2. **Vehicle Entry**: 
   - Ultrasonic sensor detects vehicle at entry
   - If slots available, entry gate opens (servo rotates to 0°)
   - Slot count decreases
   - LCD displays "Car Entering"
   - Gate closes after 3 seconds
3. **Vehicle Exit**:
   - Exit sensor detects departing vehicle
   - Exit gate opens
   - Slot count increases
   - LCD displays "Car Exiting"
   - Gate closes after 3 seconds
4. **Parking Full**: System displays "Parking Full" when no slots available

## LCD Display States

- **Idle**: Shows available slots (e.g., "Slots Left: 3/4")
- **Entry**: "Car Entering - Please proceed"
- **Exit**: "Car Exiting - Have a nice day"
- **Full**: "SORRY :( - Parking Full"

## Configuration

You can modify these parameters in the code:

```cpp
const int TOTAL_SLOTS = 4;              // Total parking slots
int distanceLimit = 10;                  // Detection distance (cm)
const unsigned long GATE_OPEN_DURATION = 3000;  // Gate open time (ms)
```

## Simulation

The project includes a Wokwi simulation configuration:
- Open [diagram.json](Automatic%20car%20parking%20system/diagram.json) in Wokwi simulator
- View the complete circuit and test the system virtually

## Project Structure

```
Project/
├── README.md
├── Automatic car parking system/      # PlatformIO project
│   ├── diagram.json                   # Wokwi simulation
│   ├── platformio.ini                 # PlatformIO config
│   ├── src/
│   │   └── main.cpp                   # Main source code
│   └── ...
├── Automatic_car_parking_system/      # Arduino IDE project
│   └── Automatic_car_parking_system.ino
└── code_II/III/IV/                    # Alternative versions
```

## Troubleshooting

### LCD not displaying
- Check I2C address (default: 0x27, try 0x3F if not working)
- Verify SDA/SCL connections
- Adjust LCD contrast potentiometer

### Servo not moving
- Ensure servo power supply is adequate (consider external power for multiple servos)
- Check servo signal wire connections

### Ultrasonic sensor issues
- Verify trigger and echo pin connections
- Ensure sensors are not obstructed
- Check detection distance setting

## Author

Pasan Kalhara

## [License](./LICENSE.md): Proprietary – Permission Required


## Future Enhancements

- Add slot-specific detection using individual sensors
- Implement reservation system
- Add wireless connectivity for mobile app integration
- Include payment system integration
- Add security camera integration" 
