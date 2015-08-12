# avr-mri-simulator
Hardware and software for a basic fMRI simulator

This AVR microcontroller project emulates the serial output of the Cedrus Lumina LP-400 response box.  This response box is typically used during functional magnetic resonance imaging (fMRI) to note the start time of each TR and to record participant responses to stimuli.

In its current configuration the eumlator can provide a trigger signal (ASCII code 53) every 1.5 or 2.0 seconds, depending on which button is pressed to start the emulation. Roughly 500 ms after the trigger pulse a single button press event will occur. Button presses will cycle from button 1 (ASCII 49) through button 4 (ASCII 52) and then repeat [TR1:49, TR2:50, TR3:51, TR4:52, TR5:49, etc]. You can modify the code to provide any event order you wish with just a few changes.

Eagle PCB layout files are also included.  These files define the hardware component of the emulator.

Send me a message if you run into any trouble. The nice bit about this device is that it can be reprogrammed to provide almost any sequence of serial events - very handy for prototyping and testing new experiments and equipment.
