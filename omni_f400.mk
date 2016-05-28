#
# Copyright 2012 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Sample: This is where we'd set a backup provider if we had one
# $(call inherit-product, device/sample/products/backup_overlay.mk)

# Get the prebuilt list of APNs
$(call inherit-product, vendor/omni/config/gsm.mk)

# Inherit from the common Open Source product configuration
$(call inherit-product, $(SRC_TARGET_DIR)/product/aosp_base_telephony.mk)

# Inherit from our custom product configuration
$(call inherit-product, vendor/omni/config/common.mk)

PRODUCT_PACKAGES += \
    charger_res_images \
    charger

PRODUCT_COPY_FILES += \
    device/lge/f400/kernel:kernel \
    device/lge/f400/dtb:dtb \
    device/lge/f400/img_info:img_info \
    device/lge/f400/init.recovery.g3.rc:root/init.recovery.g3.rc \
    device/lge/f400/postrecoveryboot.sh:recovery/root/sbin/postrecoveryboot.sh \
    device/lge/f400/multirom/sign:recovery/root/res/sign

PRODUCT_COPY_FILES += device/lge/f400/fstab.g3:recovery/root/fstab.g3
PRODUCT_COPY_FILES += device/lge/f400/multirom/twrp.fstab:recovery/root/etc/twrp.fstab

PRODUCT_NAME := omni_f400
PRODUCT_DEVICE := f400
PRODUCT_BRAND := LG
PRODUCT_MODEL := G3
PRODUCT_MANUFACTURER := LG

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_DEVICE="g3" \
    PRODUCT_NAME="g3_kt_kr" \
    BUILD_FINGERPRINT="lge/g3_kt_kr/g3:5.0/LRX21R/F400K20f.1419232865:user/release-keys" \
    PRIVATE_BUILD_DESC="g3_kt_kr-user 5.0 LRX21R F400K20f.1419232865 release-keys"

# Kernel inline build
#TARGET_KERNEL_CONFIG := f400_defconfig
#TARGET_VARIANT_CONFIG := f400_defconfig
#TARGET_SELINUX_CONFIG := f400_defconfig
