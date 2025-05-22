# AVR Car Dashboard Simulation Project

## Overview
This project simulates a basic car dashboard system using an AVR microcontroller (e.g., ATmega series). It utilizes LEDs, an LCD, and a keypad to implement features such as engine start/stop, left/right/waiting turn signals, and an AC mode control.

---

## Features
- **Engine Start/Stop**: Start the engine with keypad input.
- **Turn Signals**: Activate left, right, or both (waiting) signals with LED blinking.
- **AC Mode**: Toggle the AC ON or OFF.
- **LCD Display**: Displays the current system state and instructions.
- **User Input**: Handled via a 4x4 keypad.

---

## Hardware Requirements
- AVR microcontroller (e.g., ATmega16/32)
- 16x2 LCD Display (4-bit mode)
- 4x4 Keypad
- LEDs connected to PORTC pins (PC0, PC1, PC2)
- Pull-up resistors for keypad columns

---

## Pin Configuration
| Peripheral      | Port/Pin         | Description           |
|-----------------|------------------|-----------------------|
| LEDs            | PORTC 0,1,2      | Turn signals and AC indicator |
| LCD Control     | PORTA 1 (RS), 2 (E) | LCD control pins       |
| LCD Data        | PORTA 3-6        | LCD data pins (4-bit)  |
| Keypad Rows     | PORTB 4-7        | Keypad rows (output/input control) |
| Keypad Columns  | PORTD 2-5        | Keypad columns (input with pull-ups) |

---

## Software Structure

### Main Application (`FinalProject_app.c`)
- Initializes the LEDs and LCD.
- Displays a start menu to begin engine operation.
- Handles the main menu to select various features.
- Controls LED blinking for signals.
- Accepts keypad inputs for user commands.

### Program Functions (`FinalProject_program.c`)
- `Display_MainMenu()`: Shows the main menu options on LCD and reads keypad input.
- LCD driver functions for initialization, commands, and display operations.
- Keypad driver functions to read and decode pressed keys.
- Utility functions like `LCD_intgerToString` and `LCD_clearScreen`.

---

## How to Use

1. Power on the device.
2. The LCD shows "Start Engine (1)".
3. Press `1` on the keypad to start the engine (LEDs blink).
4. The main menu will display options:
    - `1`: Engine OFF (blinks LEDs then returns to start menu)
    - `2`: Left Signal (blinking LED on PC2)
    - `3`: Right Signal (blinking LED on PC0)
    - `4`: Waiting Signal (both left and right LEDs blink)
    - `5`: AC Mode (toggle ON/OFF with keypad input `1` or `2`)
    - `6`: Redisplay menu
5. Select the desired option using the keypad.

---

## Important Notes
- The system uses software delays (`_delay_ms`) for timing LED blinking.
- Debouncing for keypad is done with a simple delay.
- Ensure proper hardware connections for keypad and LCD pins as per pin configuration.
- The LCD uses 4-bit mode for reduced pin usage.
- Make sure to define the macros like `SET_BIT`, `CLR_BIT`, and other constants in your included headers (`FinalProject_interface.h`).

---

## Author
**Youssef Hany**  
Embedded Systems Developer

---

Feel free to explore and modify the code for your learning or projects!
