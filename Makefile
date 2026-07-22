TARGET := macosx:clang:latest:12.0
export ARCHS = arm64 arm64e x86_64
include $(THEOS)/makefiles/common.mk

LIBRARY_NAME = jvmfix_noamfi

jvmfix_noamfi_FILES = main.c
jvmfix_noamfi_CFLAGS = -fobjc-arc -Wno-unused-variable -Wno-incompatible-pointer-types -Wno-int-conversion
jvmfix_noamfi_INSTALL_PATH = /opt/homebrew/lib

include $(THEOS_MAKE_PATH)/library.mk
