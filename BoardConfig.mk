TARGET_OTA_ASSERT_DEVICE := ls990

# Platform
TARGET_BOARD_PLATFORM := msm8974
TARGET_BOARD_PLATFORM_GPU := qcom-adreno330

# Architecture
TARGET_ARCH := arm
TARGET_ARCH_VARIANT := armv7-a-neon
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_CPU_VARIANT := krait

# Bootloader
TARGET_BOOTLOADER_BOARD_NAME := MSM8974
TARGET_NO_BOOTLOADER := true

# Bump
TARGET_REQUIRES_BUMP := true

# Kernel
BOARD_CUSTOM_BOOTIMG := true
BOARD_CUSTOM_BOOTIMG_MK := device/lge/ls990/mkbootimg.mk
BOARD_KERNEL_CMDLINE := console=none androidboot.hardware=g3 user_debug=31 msm_rtb.filter=0x0
BOARD_KERNEL_BASE := 0x0000000
BOARD_KERNEL_PAGESIZE := 2048
BOARD_KERNEL_SEPARATED_DT := true
BOARD_MKBOOTIMG_ARGS := --dt device/lge/ls990/dtb --kernel_offset 0x0008000 --ramdisk_offset 0x2000000 --second_offset 0x0f00000 --tags_offset 0x0000100
TARGET_PREBUILT_KERNEL := device/lge/ls990/kernel

# Partitions
BOARD_FLASH_BLOCK_SIZE := 131072
BOARD_BOOTIMAGE_PARTITION_SIZE := 16777216
BOARD_CACHEIMAGE_PARTITION_SIZE := 889192448
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 16777216
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 2692743168
BOARD_USERDATAIMAGE_PARTITION_SIZE := 27325360128
TARGET_USERIMAGES_USE_EXT4 := true
TARGET_USERIMAGES_USE_F2FS := true

# Recovery
BOARD_NO_SECURE_DISCARD := true
BOARD_SUPPRESS_EMMC_WIPE := true
BOARD_HAS_NO_SELECT_BUTTON := true
BOARD_SUPPRESS_SECURE_ERASE := true
TARGET_RECOVERY_PIXEL_FORMAT := "RGBX_8888"

# TWRP
TW_BRIGHTNESS_PATH := "/sys/class/leds/lcd-backlight/brightness"
TW_MAX_BRIGHTNESS := 255
TW_EXCLUDE_SUPERSU := true
TW_THEME := portrait_hdpi
TW_INCLUDE_JB_CRYPTO := true
TW_INCLUDE_CRYPTO := true

# MultiROM Recovery Version
MR_REC_VERSION := $(shell date -u +%Y%m%d)
BOARD_MKBOOTIMG_ARGS += --board mrom$(MR_REC_VERSION)-00

# MultiROM
TARGET_RECOVERY_IS_MULTIROM := true
MR_DEVICE_SPECIFIC_VERSION := d
MR_NO_KEXEC := enabled
MR_INPUT_TYPE := type_b
MR_INIT_DEVICES := device/lge/ls990/multirom/mr_init_devices.c
MR_DPI := xhdpi
MR_DPI_MUL := 1.5
MR_DPI_FONT := 420
MR_FSTAB := device/lge/ls990/recovery.fstab
MR_USE_MROM_FSTAB := true
MR_KEXEC_MEM_MIN := 0x0ff00000
MR_KEXEC_DTB := true
MR_RD_ADDR := 0x2200000
MR_DEVICE_HOOKS := device/lge/ls990/multirom/mr_hooks.c
MR_DEVICE_HOOKS_VER := 4
MR_DEFAULT_BRIGHTNESS := 80
MR_PIXEL_FORMAT := "RGBX_8888"
MR_USE_QCOM_OVERLAY := true
MR_QCOM_OVERLAY_HEADER := device/lge/ls990/multirom/mr_qcom_overlay.h
MR_QCOM_OVERLAY_CUSTOM_PIXEL_FORMAT := MDP_RGBX_8888
