LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_SRCS += \
	$(LOCAL_DIR)/irc.c \

MODULE_DEPS := \
    lib/minip

include make/module.mk
