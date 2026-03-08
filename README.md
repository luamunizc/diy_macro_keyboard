# 🎛️ BLE Macro Keyboard

A compact Bluetooth Low Energy macro keyboard built with ESP32, featuring a rotary encoder, 3 programmable buttons, and a dual-layer system for extended functionality.

---

## 📋 Features

- **Wireless BLE connectivity** — pairs as a standard Bluetooth keyboard
- **2 configurable layers** — Default and Alt, switchable via encoder click
- **3 programmable buttons** per layer (6 actions total)
- **Rotary encoder** for zoom control (Ctrl+/Ctrl-)
- **LED status indicator** — blinks while advertising, solid on layer state
- **Debounce logic** on all buttons for reliable input

---

## 🔌 Hardware

| Component         | Description                          |
|------------------|--------------------------------------|
| ESP32            | Main microcontroller                 |
| Rotary Encoder   | With click button, for zoom + layer switch |
| 3x Tactile Buttons | Programmable macro buttons         |
| LED              | Status indicator                     |

### Pin Mapping

| Pin | Function       |
|-----|----------------|
| 3   | Button 1       |
| 5   | Button 2       |
| 4   | Button 3       |
| 15  | Encoder A      |
| 18  | Encoder B      |
| 22  | Encoder Click  |
| 14  | LED            |

---

## 🗂️ Layers

### 🔵 Default Layer (LED off)

| Input             | Action             | Shortcut         |
|------------------|--------------------|------------------|
| Button 1         | Copy               | `Ctrl + C`       |
| Button 2         | Paste              | `Ctrl + V`       |
| Button 3         | Lock Computer      | `Win + L`        |
| Encoder Scroll   | Zoom In/Out        | `Ctrl + / Ctrl -`|
| Encoder Click    | Switch to Alt Layer | —               |

### 🟡 Alt Layer (LED on)

| Input             | Action             | Output           |
|------------------|--------------------|------------------|
| Button 1         | Git Status         | Types `git status` |
| Button 2         | Task Start         | Types `task start` |
| Button 3         | Never Forget       | Types `await `   |
| Encoder Scroll   | Zoom In/Out        | `Ctrl + / Ctrl -`|
| Encoder Click    | Switch to Default Layer | —           |

---

## 📦 Dependencies

Install the following libraries via the Arduino Library Manager or PlatformIO:

- [`ESP32 BLE Keyboard`](https://github.com/T-vK/ESP32-BLE-Keyboard) — by T-vK
- [`Encoder`](https://github.com/PaulStoffregen/Encoder) — by Paul Stoffregen
- `WiFi` — built-in with ESP32 Arduino core

---

## 🚀 Setup & Upload

1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/ble-macro-keyboard.git
   ```

2. Open the project in **Arduino IDE** or **PlatformIO**.

3. Install the required libraries listed above.

4. Select your ESP32 board under **Tools > Board**.

5. Upload the sketch to your ESP32.

6. Pair the device via Bluetooth — it will appear as **"ESP32 BLE Keyboard"**.

---

## 💡 LED Behavior

| State         | LED Behavior         |
|--------------|----------------------|
| Advertising  | Blinking (500ms)     |
| Default Layer | Off                 |
| Alt Layer    | Solid On             |

---

## 🔧 Customization

You can easily add new layers or remap actions:

- **Add a new layer:** Add a new value to the `State` enum and handle it in the `loop()` switch statement.
- **Change a macro:** Edit the corresponding function (e.g., `gitStatus()`, `taskStart()`) to type or press different keys.
- **Add more buttons:** Define new pins and create new action functions following the existing debounce pattern.

---

## ⚠️ Known Issues / TODOs

- [ ] `LOW_BATTERY` state is defined but not yet implemented
- [ ] Battery monitoring logic not connected

---

## 📄 License

MIT License — feel free to use, modify, and share.
