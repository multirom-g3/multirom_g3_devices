#!/bin/sh
# $1 - path to top of android build tree
# $2 path to /multirom/enc folder in installation zip
DEVICE_PATH="$(cd `dirname $0`; cd ..; pwd)"

QCOM_KEYMASTER_FILES="keymaste.b00 keymaste.b01 keymaste.b02 keymaste.b03 keymaste.mdt"
QCOM_CMNLIB_FILES="cmnlib.b00 cmnlib.b01 cmnlib.b02 cmnlib.b03 cmnlib.mdt"

# libQSEEComApi depends on libutils. These are built from omni source
cp -ra "$DEVICE_PATH/recovery/root/sbin/"* "$2/"
cp -ra "$DEVICE_PATH/multirom_enc_blobs/"* "$2/"

mkdir -p "$2/firmware/image"
mkdir -p "$2/vendor/firmware/keymaster"
mkdir -p "$2/vendor/lib/hw/"
cp -ra "$DEVICE_PATH/recovery/root/vendor/lib/hw/keystore.msm8974.so" "$2/vendor/lib/hw/keystore.default.so"
cp -ra "$DEVICE_PATH/recovery/root/vendor/lib/libQSEEComAPI.so" "$2/"
cp -ra "$DEVICE_PATH/recovery/root/vendor/lib/libQSEEComAPI.so" "$2/vendor/lib/"

for f in $QCOM_CMNLIB_FILES; do
	cp -a "$DEVICE_PATH/recovery/root/firmware/image/${f}" "$2/firmware/image/"
	cp -a "$DEVICE_PATH/recovery/root/firmware/image/${f}" "$2/vendor/firmware/"
done

for f in $QCOM_KEYMASTER_FILES; do
	cp -a "$DEVICE_PATH/recovery/root/firmware/image/${f}" "$2/firmware/image/"
	cp -a "$DEVICE_PATH/recovery/root/firmware/image/${f}" "$2/vendor/firmware/keymaster/"
done
