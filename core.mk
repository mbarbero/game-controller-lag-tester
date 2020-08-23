include target.mk
include arduino.mk

SRC_DIR = $(BOARD_PACKAGE_PATH)/cores/$(BUILD_CORE)
TARGET_DIR = target/core

SRCS := $(filter-out $(SRC_DIR)/main.%, $(SRCS))

$(TARGET_DIR)/core.a: $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^

include arduino.rules.mk