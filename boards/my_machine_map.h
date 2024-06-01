/*
  st_morpho_map.h - driver code for STM32F4xx ARM processors

  Part of grblHAL

  Copyright (c) 2020-2022 Terje Io

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
#ifdef __CDT_PARSER__
#include "my_machine.h"
#include "grbl/driver_opts.h"
#endif


#if TRINAMIC_ENABLE == 2130
#include "trinamic\tmc2130.h"
#endif

#if TRINAMIC_ENABLE == 5160
#include "trinamic\tmc5160.h"
#endif

#if N_ABC_MOTORS > 1
#warning "Axis configuration is not supported!"
#endif

#define BOARD_NAME "STM324F407_DiscBoard"

#undef I2C_ENABLE
#undef EEPROM_ENABLE
#undef EEPROM_IS_FRAM

#define I2C_ENABLE      1
#define I2C_PORT        1
#define EEPROM_ENABLE   1
#define EEPROM_IS_FRAM  1
//#define SPINDLE_SYNC_ENABLE 1

//#define IS_NUCLEO_BOB
#define HAS_IOPORTS
//#define HAS_BOARD_INIT

#if SDCARD_ENABLE || TRINAMIC_SPI_ENABLE
#define SPI_PORT                3
#endif

// Define step pulse output pins.
#define STEP_PORT               GPIOE
#define X_STEP_PIN              9
#define Y_STEP_PIN              11
#define Z_STEP_PIN              10
#if N_GANGED
#define STEP_OUTMODE            GPIO_MAP
#else
#define STEP_OUTMODE            GPIO_MAP
#endif
//#define STEP_PINMODE            PINMODE_OD // Uncomment for open drain outputs

// Define step direction output pins.
#define DIRECTION_PORT          GPIOA
#define X_DIRECTION_PIN         1
#define Y_DIRECTION_PIN         3
#define Z_DIRECTION_PIN         2
#if N_GANGED
#define DIRECTION_OUTMODE       GPIO_BITBAND
#else
#define DIRECTION_OUTMODE       GPIO_MAP
#endif
//#define DIRECTION_PINMODE       PINMODE_OD // Uncomment for open drain outputs

// Define stepper driver enable/disable output pins.

#define X_ENABLE_PORT           GPIOB
#define X_ENABLE_PIN            11
#define Y_ENABLE_PORT           GPIOB
#define Y_ENABLE_PIN            13
#define Z_ENABLE_PORT           GPIOB
#define Z_ENABLE_PIN            14
//#define STEPPERS_ENABLE_PINMODE PINMODE_OD // Uncomment for open drain outputs

// Define homing/hard limit switch input pins.
#define LIMIT_PORT              GPIOC
#define X_LIMIT_PIN             8
#define Y_LIMIT_PIN             6
#define Z_LIMIT_PIN             9
#define LIMIT_INMODE            GPIO_BITBAND

// Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS == 1
#define M3_AVAILABLE
#define M3_STEP_PORT            GPIOE
#define M3_STEP_PIN             13
#define M3_DIRECTION_PORT       GPIOA
#define M3_DIRECTION_PIN        0
#define M3_LIMIT_PORT           GPIOC
#define M3_LIMIT_PIN            7
#define M3_ENABLE_PORT          GPIOB
#define M3_ENABLE_PIN           15
#endif

#define AUXOUTPUT2_PORT         GPIOE // Spindle PWM
#define AUXOUTPUT2_PIN          5
#define AUXOUTPUT3_PORT         GPIOB // Spindle direction
#define AUXOUTPUT3_PIN          0
#define AUXOUTPUT4_PORT         GPIOE // Spindle enable
#define AUXOUTPUT4_PIN          2

// Define driver spindle pins
#if DRIVER_SPINDLE_ENABLE
# define SPINDLE_ENABLE_PORT     AUXOUTPUT4_PORT
# define SPINDLE_ENABLE_PIN      AUXOUTPUT4_PIN
#if DRIVER_SPINDLE_PWM_ENABLE
# define SPINDLE_PWM_PORT        AUXOUTPUT2_PORT
# define SPINDLE_PWM_PIN         AUXOUTPUT2_PIN
#endif
#if DRIVER_SPINDLE_DIR_ENABLE
# define SPINDLE_DIRECTION_PORT  AUXOUTPUT3_PORT
# define SPINDLE_DIRECTION_PIN   AUXOUTPUT3_PIN
#endif
#endif //DRIVER_SPINDLE_ENABLE

// Define flood and mist coolant enable output pins.
#define COOLANT_FLOOD_PORT      GPIOD
#define COOLANT_FLOOD_PIN       3
#define COOLANT_MIST_PORT       GPIOD
#define COOLANT_MIST_PIN        6

// Define user-control controls (cycle start, reset, feed hold) input pins.
#define CONTROL_PORT            GPIOD
#define RESET_PIN               2
#define FEED_HOLD_PIN           1
#define CYCLE_START_PIN         0
#if SAFETY_DOOR_ENABLE
#define SAFETY_DOOR_PIN         1
#endif
#define CONTROL_INMODE          GPIO_BITBAND

// Define probe switch input pin.
#define AUXINPUT1_PORT          GPIOA // Probe input
#define AUXINPUT1_PIN           8

#if PROBE_ENABLE && defined(AUXINPUT1_PIN)
# define PROBE_PORT              AUXINPUT1_PORT
# define PROBE_PIN               AUXINPUT1_PIN
#endif


// Spindle encoder pins.
#if SPINDLE_SYNC_ENABLE

#define SPINDLE_INDEX_PORT      GPIOB
#define SPINDLE_INDEX_PIN       14
#define SPINDLE_INDEX_BIT       (1<<SPINDLE_INDEX_PIN)

#define SPINDLE_PULSE_PORT      GPIOD
#define SPINDLE_PULSE_PIN       2
#define SPINDLE_PULSE_BIT       (1<<SPINDLE_PULSE_PIN)

#endif

#if MPG_MODE == 1
#ifndef SPI_PORT
#define MPG_MODE_PORT           GPIOC
#define MPG_MODE_PIN            8
#elif N_ABC_MOTORS == 0
#define MPG_MODE_PORT           GPIOC
#define MPG_MODE_PIN            11
#endif
#endif

// Auxiliary I/O
//#define AUXINPUT0_PORT          GPIOB
//#define AUXINPUT0_PIN           14
//#define AUXINPUT1_PORT          GPIOA
//#define AUXINPUT1_PIN           15
//#define AUXINPUT2_PORT          GPIOB
//#define AUXINPUT2_PIN           13
//
//#define AUXOUTPUT0_PORT         GPIOB
//#define AUXOUTPUT0_PIN          15
//#define AUXOUTPUT1_PORT         GPIOB
//#define AUXOUTPUT1_PIN          2
//
#if I2C_STROBE_ENABLE
#define I2C_STROBE_PORT         GPIOB
#define I2C_STROBE_PIN          0
#else
//#define AUXINPUT3_PORT          GPIOB
//#define AUXINPUT3_PIN           0
#endif

#if TRINAMIC_SPI_ENABLE
	#define TRINAMIC_SPI_PORT_COMMON	GPIOB
	// MISO pin is also SWCLK from JTAG port, so can't debug with Trinamic SPI drivers:-(
	#define TRINAMIC_MOSI_PORT          TRINAMIC_SPI_PORT_COMMON
	#define TRINAMIC_MOSI_PIN           5
	#define TRINAMIC_SCK_PORT           TRINAMIC_SPI_PORT_COMMON
	#define TRINAMIC_SCK_PIN            3

	// BigTreeTech used PA14 (SWCLK) as MOT_MISO.
	// For debugging, change this to PA6 (on EXP2) and jumper directly to MISO pins on TMC2130s.
	#ifdef DEBUG
	 #define TRINAMIC_MISO_PORT          TRINAMIC_SPI_PORT_COMMON
	 #define TRINAMIC_MISO_PIN           4		// temporary EXP2-3 to use while debugging.  real one is PA14
	#else
	 #define TRINAMIC_MISO_PORT          TRINAMIC_SPI_PORT_COMMON
	 #define TRINAMIC_MISO_PIN           4
	#endif

	#define MOTOR_CSX_PORT              GPIOD
	#define MOTOR_CSX_PIN               6
	#define MOTOR_CSY_PORT              GPIOD
	#define MOTOR_CSY_PIN               4
	#define MOTOR_CSZ_PORT              GPIOD
	#define MOTOR_CSZ_PIN               0

	#ifdef  M3_AVAILABLE
	 #define MOTOR_CSM3_PORT             GPIOD
	 #define MOTOR_CSM3_PIN              2
	#endif

	#ifdef  M4_AVAILABLE
	 #define MOTOR_CSM4_PORT             GPIOD
	 #define MOTOR_CSM4_PIN              12
	#endif
#endif


#ifdef SPI_PORT

	#if SDCARD_ENABLE
	#define SD_CS_PORT              GPIOC
	#define SD_CS_PIN               8
	#endif
#endif


#if TRINAMIC_SPI_ENABLE
#else
//#define AUXOUTPUT2_PORT         GPIOA
//#define AUXOUTPUT2_PIN          6
//#define AUXOUTPUT3_PORT         GPIOA
//#define AUXOUTPUT3_PIN          5
//#define AUXOUTPUT4_PORT         GPIOA
//#define AUXOUTPUT4_PIN          7
//#define AUXOUTPUT5_PORT         GPIOB
//#define AUXOUTPUT5_PIN          7
//#if MPG_MODE == 0
//#define AUXOUTPUT6_PORT         GPIOC
//#define AUXOUTPUT6_PIN          8
//#endif
#endif


// EOF
