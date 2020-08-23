.SECONDEXPANSION:
$(TARGET_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS_DIR)/%.d | $$(@D)/.
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(TARGET_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS_DIR)/%.d | $$(@D)/.
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(TARGET_DIR)/%.o: $(SRC_DIR)/%.S $(DEPS_DIR)/%.d | $$(@D)/.
	$(COMPILE.S) -o $@ $<

.PRECIOUS: $(TARGET_DIR)/. $(TARGET_DIR)%/.

$(TARGET_DIR)/.:
	mkdir -p $@

$(TARGET_DIR)%/.:
	mkdir -p $@

$(DEP_FILES): | $$(@D)/.
include $(wildcard $(DEP_FILES))