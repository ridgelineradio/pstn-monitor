# PSTN Monitor

## BOM

* Arduino Uno
* [DF Robot SIM7600G-H](https://www.dfrobot.com/product-1834.html) or equivalent
* Cable to convert "line in" into "microphone." [Our tested recommendation](https://www.amazon.com/dp/B00OAW85ZG).
* External power supply (required by shield)

## Setup instructions

1. Install SIM card into the DF Robot shield.
2. Flash the Arduino with code.
3. Press the "BOOT" button on the shield for about 1 second.
4. A few seconds after that, the "NET" light should start to light up and flash with activity.

## Usage

1. Call the phone number associated with your SIM card. The code will automatically answer the phone, allowing you to monitor your audio from anywhere as long as there is telephone connectivity available.
2. Text "Status" to the phone number to make sure it's alive. It will respond with the raw signal strength query, because that felt useful.
