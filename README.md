# Pimp-Boy 3 Billion (ESP32 Edition)

An ESP32-powered recreation of the Fallout *Pimp-Boy 3 Billion*.  
This project brings the iconic Pip-Boy interface to life with a 4-inch TFT display, animated Vault-Boy GIFs, DFPlayer Mini audio, a 5-position rotary mode selector, and glowing STAT / INV / DATA LEDs.

---

## 🧩 Hardware

| Component | Details |
|------------|----------|
| MCU | ESP32-WROOM-32 |
| Display | 4.0″ 480 × 320 SPI TFT (ST7796S driver) |
| Audio | DFPlayer Mini + 3 W speaker |
| LEDs | 3 × front indicator LEDs (STAT / INV / DATA) |
| Rotary switch | 5-position selector (Status / Inventory / Data / Radio / Clock) |
| Temperature sensor | SHT31-D (I²C) |
| Power | 5 V USB or Li-ion with step-down converter |

---

## LED Details

For this build, ultra-small **0402 SMD LEDs** were used (approx. 0.04 × 0.02 × 0.017 in.) with fine isolated wire leads (~0.01 in. diameter).  
These fit neatly into the front indicator ports without modifying the model.  
However, **any small LED type** (e.g., 3 mm, 5 mm, or surface-mount variants) can be used as long as current-limiting resistors are applied and wiring is adjusted to suit.

| Function | GPIO Pin |
|-----------|-----------:|
| **STAT LED** | 12 |
| **INV LED** | 13 |
| **DATA LED** | 14 |

---

## Rotary Switch (5 positions)

docs/Rotary switch pinout.jpeg  

The rotary selector’s **common** connects to **GND**.  
Each position pulls its assigned GPIO **LOW** when selected, switching between Pimp-Boy display modes.

| Function | GPIO Pin |
|-----------|-----------:|
| STATUS | 25 |
| INVENTORY | 26 |
| DATA | 27 |
| CLOCK | 32 |
| RADIO | 33 |

---

## DFPlayer Mini

docs/MP3 pinout.jpeg  

| Function | GPIO Pin |
|-----------|-----------:|
| RX (to DFPlayer TX) | 16 |
| TX (to DFPlayer RX) | 17 |

MP3 files are stored on a microSD card inside the DFPlayer.  
Each button press or mode change can trigger playback from a specific track or random folder range, as defined in the code.

---

## TFT Display

docs/screen pinout.jpeg  

| Signal | GPIO Pin (typical) |
|---------|--------------------:|
| MISO | 19 |
| MOSI | 23 |
| SCK | 18 |
| CS / DC / RESET | as defined in `TFT_eSPI/User_Setup.h` |

---

## Temperature & Humidity Sensor

docs/temp humitity pinout.jpeg  

| Signal | GPIO Pin |
|---------|-----------:|
| SDA | 21 |
| SCL | 22 |

---

## Wi-Fi & Time Sync

The ESP32 connects to your local Wi-Fi network and uses NTP to synchronize the internal clock.  
Update your credentials in the code:

```cpp
const char *ssid     = "insert SSID HERE"; 
const char *password = "Insert SSID PASSWORD HERE";

Install all required libraries.

Enter your Wi-Fi SSID and password at the top of the code.

Upload the sketch to your ESP32.

Wire components as shown in the pinout images above.

Copy your MP3 files into the /MP3 folder on the microSD card used by the DFPlayer.

3D Model

Printable Pimp-Boy 3 Billion shell available on Thingiverse:
https://www.thingiverse.com/thing:7162087

Original base models:

lfenske – https://www.thingiverse.com/thing:729866

jeje95 – https://www.thingiverse.com/thing:6654866

 Media

YouTube Build Playlist:
https://www.youtube.com/playlist?list=PLpsQMnwd0qYBT3ClF7cjuq53jtk2OYQxO

Instructables Project Page:
(coming soon — link will be added here)

 Credits

3D Model: lfenske (original)

Code Base: jeje95 (original)

Electronics & Integration: custom ESP32 adaptation

Artwork & Sound: Fallout universe assets used under fair use for fan project

 License

Released under the MIT License
Full text: https://opensource.org/licenses/MIT

Feel free to remix, modify, and share with credit.

“May your builds be S.P.E.C.I.A.L.”
