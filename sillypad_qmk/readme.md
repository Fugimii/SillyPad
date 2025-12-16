# fugimii/sillypad

![fugimii/sillypad](https://github.com/Fugimii/SillyPad/blob/main/sillypad_qmk/Sillypad.jpg)

A silly 5x4 macropad I made to learn PCB development!

* Keyboard Maintainer: [Fugimii](https://github.com/Fugimii)
* Hardware Supported: Pi Pico
* Hardware Availability: https://www.raspberrypi.com/products/raspberry-pi-pico/

Make example for this keyboard (after setting up your build environment):

    make fugimii/sillypad:default

Flashing example for this keyboard:

    make fugimii/sillypad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
