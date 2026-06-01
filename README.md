# CrunchLabs Hack Pack — Arduino Source Code

This repository contains the Arduino source code for all [CrunchLabs Hack Pack](https://www.crunchlabs.com) projects, extracted from the [Hack Pack IDE](https://ide.crunchlabs.com) and organized for use with both **PlatformIO** and **Arduino IDE**.

The original source is copyright © 2024–2025 Crunchlabs LLC and is redistributed here under the MIT License included in this repository. See [LICENSE](LICENSE) for full details.

---

## Projects

| Product | Sketches |
|---|---|
| **BalanceBot** | stock, obstacle_avoidance, push_pull, remote_control, servo, IMU_Zero |
| **CardDealingBot** | stock, 52pickup, handsfree, cardturret, stealth |
| **ColorComposer** | StockCode, SpectralFM, TheChordinator, SystemTest |
| **DominoRobot** | stock, autoknockdown, lineracer, irremote |
| **IRTurret** | stock, passcode, roulette |
| **LabelMaker** | stock, sketch, mrlogo, lightdriver |
| **LaserTag** | stock, lights, ammo |
| **OmnibotForklift** | StockCode, AdvancedSwagDrive, Gyro |
| **RobotRanger** | StockCode |
| **RoboLamp** | StockCode, FastLED, Pomodoro, Sun, Remote |
| **SandGarden** | stock, sandtimer, liveinput |
| **StringPlottingRobot** | StockCode, EtchASketch, TicTacToe |
| **Synthesizer** | StockCode, Cloud9ChordBuilder, DrumnBass5 |
| **TankPlant** | StockCode, LEDBarHack, ServoHack, TouchpadHack, SnakeGame, MoistureSensorCalibration |

---

## Directory Structure

Projects originally built with PlatformIO (ColorComposer, RobotRanger, RoboLamp, TankPlant) keep their native structure and can be opened directly in VS Code + PlatformIO IDE.

All other projects support both IDEs and are laid out as follows:

```
ProductName/
  sketch_name/
    arduino/
      sketch_name/
        sketch_name.ino     ← open this folder in Arduino IDE
    platformio/
      src/
        sketch_name.ino
      platformio.ini        ← open this folder in PlatformIO
```

---

## Getting Started

### PlatformIO (recommended)

1. Install [VS Code](https://code.visualstudio.com) and the [PlatformIO IDE extension](https://platformio.org/platformio-ide).
2. Open any `platformio/` folder (or a native PlatformIO project folder) directly in VS Code.
3. PlatformIO will automatically download all required libraries on the first build.
4. Build with **✓ Build** or upload with **→ Upload**.

### Arduino IDE

1. Install [Arduino IDE 2.x](https://www.arduino.cc/en/software).
2. Open the `arduino/<sketch_name>/` folder — the IDE requires the folder and `.ino` file to share the same name, which is already the case here.
3. Install the required libraries via **Tools → Manage Libraries** before compiling. The `platformio.ini` beside each sketch lists all dependencies by name if you need a reference.

---

## Notable Changes From the Original IDE

The following changes were made to get all projects building outside of the CrunchLabs web IDE:

### `Servo.h` and `Stepper.h`
These ship bundled with Arduino IDE but are separate packages in PlatformIO. They are declared as `lib_deps` in each relevant `platformio.ini` (`arduino-libraries/Servo`, `arduino-libraries/Stepper`).

### `PID_v1_bc.h` (BalanceBot)
The BalanceBot sketches use a CrunchLabs-internal header named `PID_v1_bc.h`. This is the standard [br3ttb Arduino PID library](https://github.com/br3ttb/Arduino-PID-Library) under a different filename. A one-line shim (`PID_v1_bc.h`) is included in each BalanceBot PlatformIO `src/` directory that simply re-exports `PID_v1.h`.

### `NHY3274TH.h` (CardDealingBot)
The CardDealingBot uses a CrunchLabs-proprietary color sensor library (`NHY3274TH.h`) that is not publicly available. Its API (`begin()`, `setIntegrationTime()`, `setGain()`, `getRawData()`) is identical in signature to the [Adafruit TCS34725](https://github.com/adafruit/Adafruit_TCS34725) library. A compatibility shim (`CardDealingBot/NHY3274TH.h`) is included that wraps the TCS34725. The NHY3274TH chip's raw gain register value (`0x20`) is mapped to `TCS34725_GAIN_16X` as the closest equivalent. **If you have the genuine NHY3274TH library, replace the shim with it.**

### `Adafruit_TiCoServo` (RoboLamp)
The original IDE vendored a copy of `Adafruit_TiCoServo` inside each RoboLamp project. This has been removed and replaced with a proper `lib_deps` entry (`adafruit/Adafruit TiCoServo`) in each RoboLamp `platformio.ini`.

### Forward declarations (BalanceBot obstacle_avoidance, remote_control, servo)
Arduino IDE automatically generates forward declarations for all functions in `.ino` files. Three BalanceBot sketches define functions inside `#pragma region` blocks in a way that confuses PlatformIO's equivalent parser. Explicit forward declarations for `is_upright()` and `handle_sensors()` have been added near the top of those three files.

---

## Contributing

This repository tracks the source code published through the CrunchLabs Hack Pack IDE. Accordingly:

- **Bug reports and corrections** — please [file an issue](../../issues). If something doesn't compile or a library mapping is wrong, we want to know.
- **New Hack Pack projects** — if CrunchLabs releases a new product and its source becomes available in the IDE, please file an issue and we'll add it.
- **New features or modifications to the sketches** — this repository will not accept these. The code here should reflect what CrunchLabs ships; changes belong in your own fork.

---

## Disclaimer

This repository is not affiliated with or endorsed by CrunchLabs. All sketch content is copyright © 2024–2025 Crunchlabs LLC. See [LICENSE](LICENSE) for terms.
