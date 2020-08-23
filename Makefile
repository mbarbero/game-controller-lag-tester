include target.mk
include arduino.mk

SRCS := $(SRCS)

DIO2 := $(HOME)/Arduino/libraries/dio2
LIB_PATHS := $(LIB_PATHS) -I$(DIO2)/src -I$(DIO2)/board/$(BOARD_BUILD_VARIANT)

DEP_FILES = $(patsubst %,$(DEPS_DIR)/%.d,$(notdir $(basename $(SRCS)))) $(patsubst $(SRC_DIR)/gamepad/%.cpp,$(TARGET_DIR)/gamepad/%.d,$(wildcard $(SRC_DIR)/gamepad/*.cpp)) $(patsubst $(SRC_DIR)/main/%.cpp,$(TARGET_DIR)/main/%.d,$(wildcard $(SRC_DIR)/main/*.cpp))

OBJ_FILES = $(patsubst %,$(TARGET_DIR)/%.o,$(notdir $(basename $(SRCS)))) $(patsubst $(SRC_DIR)/gamepad/%.cpp,$(TARGET_DIR)/gamepad/%.o,$(wildcard $(SRC_DIR)/gamepad/*.cpp))

PROG_FILES = $(patsubst %,$(TARGET_DIR)/main/%.elf,$(notdir $(basename $(wildcard src/main/%.cpp))))

$(TARGET_DIR)/core/core.a:
	make -f core.mk $@

.SECONDEXPANSION:
$(TARGET_DIR)/main/%.o: src/main/%.cpp $(TARGET_DIR)/main/%.d | $$(@D)/.
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(TARGET_DIR)/main/%.elf: $(TARGET_DIR)/main/%.o $(OBJ_FILES) $(TARGET_DIR)/core/core.a
	$(CC) $(LDFLAGS) -o $@ $^ -L$(TARGET_DIR)/ -lm
	avr-size -A $@

$(TARGET_DIR)/main/%.eep: $(TARGET_DIR)/main/%.elf
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $^ $@

$(TARGET_DIR)/main/%.hex: $(TARGET_DIR)/main/%.elf
	avr-objcopy -O ihex -R .eeprom $^ $@

.PHONY: all
all: $(PROG_FILES)

.PHONY: all
upload_snes: $(TARGET_DIR)/main/lag_snes.hex
	avrdude -q -p$(BOARD_BUILD_MCU) -c$(BOARD_UPLOAD_PROTOCOL) "-P$(PORT)" -b$(BOARD_UPLOAD_SPEED) -D "-Uflash:w:$^:i"

.PHONY: clean compile
clean:
	rm -rf target/

include arduino.rules.mk