PACKAGE_INDEX := $(ARDUINO_PATH)/package_index.json
BUILD_CORE := $(shell cut -d: -f1 <<<$(PACKAGE))
BUILD_ARCH := $(shell cut -d: -f2 <<<$(PACKAGE))
FQBN := $(PACKAGE):$(BOARD)
BOARD_PACKAGE_VERSION := $(shell jq -r '.packages[] | select(.name == "arduino") | .platforms[] | select(.architecture == "avr") | .version' $(PACKAGE_INDEX) | sort -V | tail -n 1)
BOARD_PACKAGE_PATH := $(ARDUINO_PATH)/packages/$(BUILD_CORE)/hardware/$(BUILD_ARCH)/$(BOARD_PACKAGE_VERSION)

BOARDS_TXT := $(BOARD_PACKAGE_PATH)/boards.txt
PLATFORM_TXT := $(BOARD_PACKAGE_PATH)/platform.txt
PROGRAMMERS_TXT := $(BOARD_PACKAGE_PATH)/programmers.txt

BOARD_NAME := $(shell grep "$(BOARD).name" $(BOARDS_TXT) | cut -d'=' -f2)
BOARD_BUILD_CORE := $(shell grep "$(BOARD).build.core" $(BOARDS_TXT) | cut -d'=' -f2)
BOARD_BUILD_VARIANT := $(shell grep "$(BOARD).build.variant" $(BOARDS_TXT) | cut -d'=' -f2)
BOARD_BUILD_BOARD := $(shell grep "$(BOARD).build.board" $(BOARDS_TXT) | cut -d'=' -f2)
BOARD_BUILD_MCU := $(shell grep "$(BOARD).build.mcu" $(BOARDS_TXT) | cut -d'=' -f2)
BOARD_BUILD_F_CPU := $(shell grep "$(BOARD).build.f_cpu" $(BOARDS_TXT) | cut -d'=' -f2)

BOARD_UPLOAD_PROTOCOL := $(shell grep "$(BOARD).upload.protocol" $(BOARDS_TXT) | cut -d'=' -f2)
BOARD_UPLOAD_SPEED := $(shell grep "$(BOARD).upload.speed" $(BOARDS_TXT) | cut -d'=' -f2)

ARDUINO_IDE_VERSION=10813

SRC_DIR = src
TARGET_DIR = target
DEPS_DIR = $(TARGET_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.S)
DEP_FILES = $(patsubst %,$(DEPS_DIR)/%.d,$(notdir $(basename $(SRCS))))
OBJ_FILES = $(patsubst %,$(TARGET_DIR)/%.o,$(notdir $(basename $(SRCS))))

LIB_PATHS = -I$(BOARD_PACKAGE_PATH)/cores/$(BUILD_CORE) -I$(BOARD_PACKAGE_PATH)/variants/$(BOARD_BUILD_VARIANT)
TARGET_DEF = -DF_CPU=${BOARD_BUILD_F_CPU} -DARDUINO=${ARDUINO_IDE_VERSION} -DARDUINO_${BOARD_BUILD_BOARD} -DARDUINO_ARCH_${BUILD_ARCH} -mmcu=${BOARD_BUILD_MCU}
FLAGS = -g -Os -Wall -Wextra -flto -ffunction-sections -fdata-sections -MMD $(TARGET_DEF) $(LIB_PATHS)

CC = avr-gcc
CFLAGS = $(FLAGS) -std=gnu11 -fno-fat-lto-objects

CXX = avr-g++
CXXFLAGS = $(FLAGS) -std=gnu++11 -fno-exceptions -fno-threadsafe-statics

LDFLAGS = -g -Os -Wall -Wextra -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=$(BOARD_BUILD_MCU)

AS = avr-gcc
ASFLAGS = -g -x assembler-with-cpp -flto -MMD $(TARGET_DEF) $(LIB_PATHS)

AR = avr-gcc-ar
ARFLAGS = rcsv

