# top level project rules for the msm8960_virtio project
#
LOCAL_DIR := $(GET_LOCAL_DIR)

TARGET := apollo

MODULES += app/aboot

DEBUG := 1
EMMC_BOOT := 1

#DEFINES += WITH_DEBUG_DCC=1
DEFINES += WITH_DEBUG_UART=1
#DEFINES += WITH_DEBUG_FBCON=1
DEFINES += DEVICE_TREE=1
#DEFINES += MMC_BOOT_BAM=1
DEFINES += CRYPTO_BAM=1
DEFINES += WITH_ENABLE_IDME=1 # ACOS_MOD_ONELINE
DEFINES += TARGET_TABLET=1

#Disable thumb mode
ENABLE_THUMB := false
DEFINES += ABOOT_FORCE_KERNEL_ADDR=0x00008000
DEFINES += ABOOT_FORCE_RAMDISK_ADDR=0x02000000
DEFINES += ABOOT_FORCE_TAGS_ADDR=0x01e00000

# Right now we are assuming these are the only default values
DEFINES += ABOOT_DEFAULT_KERNEL_ADDR=0x10008000
DEFINES += ABOOT_DEFAULT_RAMDISK_ADDR=0x1100000
DEFINES += ABOOT_DEFAULT_TAGS_ADDR=0x10000100

ifeq ($(EMMC_BOOT),1)
DEFINES += _EMMC_BOOT=1
endif
