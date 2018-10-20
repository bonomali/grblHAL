/*
  driver.h - An embedded CNC Controller with rs274/ngc (g-code) support

  Driver code for ESP32

  Part of Grbl

  Copyright (c) 2018 Terje Io
  Copyright (c) 2011-2015 Sungeun K. Jeon
  Copyright (c) 2009-2011 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "soc/rtc.h"
#include "driver/gpio.h"
#include "driver/timer.h"
#include "driver/ledc.h"
#include "driver/rmt.h"

#include "GRBL/grbl.h"

// Configuration

//#define HAS_KEYPAD // uncomment to enable I2C keypad for jogging etc. NOTE: not yet ready
//#define PWM_RAMPED // uncomment to enable ramped spindle PWM.
//#define PROBE_ISR // uncomment to catch probe state change by interrupt TODO: needs verification!
//#define WIFI_COMMS
//#define BT_COMMS
#define SDCARD_SUPPORT

// End configuration

// timer definitions
#define STEP_TIMER_GROUP TIMER_GROUP_0
#define STEP_TIMER_INDEX TIMER_0

// Define step pulse output pins.
#define X_STEP_PIN      GPIO_NUM_12
#define Y_STEP_PIN      GPIO_NUM_14
#define Z_STEP_PIN      GPIO_NUM_27
#define HWSTEP_MASK     (1ULL << X_STEP_PIN|1ULL << Y_STEP_PIN|1ULL << Z_STEP_PIN) // All step bits

// Define step direction output pins. NOTE: All direction pins must be on the same port.
#define X_DIRECTION_PIN     GPIO_NUM_26
#define Y_DIRECTION_PIN     GPIO_NUM_25
#define Z_DIRECTION_PIN     GPIO_NUM_33
#define HWDIRECTION_MASK    (1ULL << X_DIRECTION_PIN|1ULL << Y_DIRECTION_PIN|1ULL << Z_DIRECTION_PIN) // All direction bits

// Define stepper driver enable/disable output pin(s).
#define STEPPERS_DISABLE_PIN    GPIO_NUM_13

// Define homing/hard limit switch input pins and limit interrupt vectors.
#define X_LIMIT_PIN     GPIO_NUM_2
#define Y_LIMIT_PIN     GPIO_NUM_4
#define Z_LIMIT_PIN     GPIO_NUM_15
#define HWLIMIT_MASK    (1ULL << X_LIMIT_PIN|1ULL << Y_LIMIT_PIN|1ULL << Z_LIMIT_PIN) // All limit bits

// Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_PIN      GPIO_NUM_18
#define SPINDLE_DIRECTION_PIN   GPIO_NUM_5
#define HWSPINDLE_MASK (1ULL << SPINDLE_ENABLE_PIN|1ULL << SPINDLE_DIRECTION_PIN)
#define SPINDLEPWMPIN     		GPIO_NUM_17

// Define flood and mist coolant enable output pins.

#define COOLANT_FLOOD_PIN   GPIO_NUM_16
#define COOLANT_MIST_PIN    GPIO_NUM_21
#define HWCOOLANT_MASK (1UL << COOLANT_FLOOD_PIN|1ULL << COOLANT_MIST_PIN)

// Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
#define RESET_PIN           GPIO_NUM_34
#define FEED_HOLD_PIN       GPIO_NUM_36
#define CYCLE_START_PIN     GPIO_NUM_39
#define SAFETY_DOOR_PIN     GPIO_NUM_35
#define HWCONTROL_MASK      (1UL << RESET_PIN|1UL << FEED_HOLD_PIN|1UL << CYCLE_START_PIN|1UL << SAFETY_DOOR_PIN)

// Define probe switch input pin.
#define PROBE_PIN       GPIO_NUM_32

void selectStream (stream_setting_t stream);

#endif