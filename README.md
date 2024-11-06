# Stopwatch System - ATmega32 Microcontroller

## Description

### This project implements a Stopwatch System using the ATmega32 microcontroller with a 1 MHz frequency. The system features a multiplexed display of six Common Anode 7-segment displays controlled through a 7447 decoder and NPN BJTs for switching between segments. The system includes features like starting, pausing, resetting, and resuming the stopwatch with the help of external interrupts.

## Features

### ATmega32 Microcontroller with a 1 MHz clock frequency.

### Timer1 in CTC mode to count stopwatch time.

### Six Common Anode 7-segment displays controlled using multiplexing.

### 7447 decoder to display digits on 7-segment displays.

### External Interrupts for stopwatch control:

#### a. Reset the stopwatch using INT0 (falling edge).

#### b. Pause the stopwatch using INT1 (rising edge).

#### c. Resume the stopwatch using INT2 (falling edge).

## How to Use

### 1. Power the system to start the stopwatch.

### 2. Press the reset button (connected to INT0) to reset the stopwatch.

### 3. Press the pause button (connected to INT1) to pause the stopwatch.

### 4. Press the resume button (connected to INT2) to resume the stopwatch.

## Hardware Setup

### ATmega32 Microcontroller running at 1 MHz.

### Timer1 configured in CTC mode for stopwatch counting.

### Six Common Anode 7-segment displays multiplexed using NPN transistors and 7447 decoder.

### External interrupt pins configured for controlling the stopwatch state (reset, pause, resume).

## Requirements

### ATmega32 Microcontroller or similar.

### 6 Common Anode 7-segment displays.

### 7447 decoder IC.

### NPN transistors for multiplexing.

### Push buttons for control (reset, pause, resume).

### C compiler for programming the microcontroller (e.g., AVR-GCC).

## License

### This project is open-source.
