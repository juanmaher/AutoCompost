# Compile options
VERBOSE=n
OPT=g
USE_NANO=y
SEMIHOST=n
USE_FPU=y

# Libraries
USE_LPCOPEN=y
USE_SAPI=y
USE_FREERTOS=n
FREERTOS_HEAP_TYPE=5
LOAD_INRAM=n

# For LCD connected via I2C PCF8574T I/O expander
DEFINES+=LCD_HD44780_I2C_PCF8574T

# Yakindu SCT - To Compile and Link Generated Sate Machine Code
INCLUDES = -I$(PROGRAM_PATH_AND_NAME)/gen
INCLUDES += -I$(PROGRAM_PATH_AND_NAME)/inc
SRC = $(wildcard $(PROGRAM_PATH_AND_NAME)/gen/*.c)