platform_build_bootimg(){
	mkdir -p "${WORKSPACE}"
	touch /tmp/dummyramdisk
	gzip -c -9 /tmp/dummyramdisk > "Platform/Samsung/exynos8535/dummyramdisk"

	python3 /home/ubuntu/crdroid/system/tools/mkbootimg/mkbootimg.py \
		--header_version 4 \
		--kernel "${WORKSPACE}/uefi-${DEVICE}-kernel" \
		--ramdisk "Platform/Samsung/exynos8535/dummyramdisk" \
		--os_version "16.0.0" \
		--os_patch_level "2026-09" \
		-o "${WORKSPACE}/boot-${DEVICE}.img" \
		|| return "$?"

	cd "${WORKSPACE}"
	tar -c "boot-${DEVICE}.img" -f "boot-${DEVICE}.tar" || return "$?"
	echo "UEFI Boot image generated at ${WORKSPACE}/boot-${DEVICE}.tar"
}
