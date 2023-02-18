LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_SRCS += \
	$(LOCAL_DIR)/libefi.cpp \
	$(LOCAL_DIR)/bootloader.cpp

.PHONY: $(LOCAL_DIR)/vmlinuz.cpp

$(LOCAL_DIR)/vmlinuz.cpp: $(BUILDDIR)/vmlinuz.o

$(BUILDDIR)/vmlinuz.o: $(LOCAL_DIR)/vmlinuz
	ld -r -b binary -o $@ $<

$(LOCAL_DIR)/bootloader.cpp: $(BUILDDIR)/vmlinuz.o

EXTRA_OBJS += $(BUILDDIR)/vmlinuz.o

include make/module.mk

