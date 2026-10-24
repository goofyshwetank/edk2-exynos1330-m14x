# EDK2 UEFI Port for Samsung Galaxy M14 5G (m14x / Exynos 1330)

**Status:** Experimental / Early Boot Working

## Hardware

- **Device:** Samsung Galaxy M14 5G (`SM-E146B`, `m14x`)
- **SoC:** Samsung Exynos 1330 (`s5e8535`, 2x Cortex-A78 @ 2.4 GHz + 6x Cortex-A55 @ 2.0 GHz)
- **RAM:** 4 GB LPDDR4X @ `0x80000000`
- **Display:** 1080x2408 @ `0xFA200000` (32bpp BGRA)
- **GIC:** ARM GIC-400 (GICv2) @ `0x12B00000`
- **UART:** Samsung S3C UART @ `0x13800000` (115200)
- **Storage:** UFS 2.2 @ `0x13520000`

## Current State

- [x] EDK2 PrePi / DXE initialization
- [x] ARM64 MMU and page tables
- [x] Framebuffer graphics output (GOP)
- [x] UEFI Shell boots
- [x] RAM persistent logging @ `0xFD010000`
- [ ] Physical button input (PMIC `s2mpu15` on SPMI bus)
- [ ] USB host mode (DWC3 @ `0x13200000` boots in peripheral mode)
- [ ] Mainline Linux device tree
- [ ] XNU / HackiOS boot experiments

## Build Instructions

### Prerequisites

```bash
sudo apt update
sudo apt install -y build-essential uuid-dev iasl git nasm python3 \
    gcc-aarch64-linux-gnu device-tree-compiler gettext
```

### Clone and Build

```bash
git clone https://github.com/YOUR_USERNAME/edk2-exynos1330-m14x.git
cd edk2-exynos1330-m14x
git submodule update --init --recursive --depth=1
make -C Common/edk2/BaseTools
./build.sh --device m14x --toolchain GCC5
```

Output: `workspace/boot-m14x.img` (flashable via Odin AP or TWRP).

## Flash Instructions

### Via Odin (Windows)

1. Boot into Download Mode: Hold `Vol Down + Vol Up` and plug USB cable.
2. Flash `boot-m14x.tar` to **AP** slot.

### Via TWRP

```bash
adb push workspace/boot-m14x.img /tmp/boot.img
adb shell "dd if=/tmp/boot.img of=/dev/block/by-name/boot bs=4M conv=fsync && sync"
adb reboot
```

## Restore Stock Android

Flash original `boot.img` backup via Odin or:

```bash
adb shell "dd if=/sdcard/boot_backup.img of=/dev/block/by-name/boot bs=4M conv=fsync"
```

## Known Issues

1. **No button input:** Volume/Power keys route through PMIC, not SoC GPIO. Stubbed to prevent bus faults.
2. **No USB keyboard:** DWC3 controller boots in device mode; host driver not implemented.
3. **Crashes on timer interrupts:** Fixed by updating `PcdArmArchTimer*IntrNum` to `13, 14, 11, 10` (from vendor DTS).

## Development Roadmap

1. **Phase 1:** Mainline Linux minimal DTS validation (serial console + initramfs).
2. **Phase 2:** PMIC power button driver (`s2mpu15-power-keys`).
3. **Phase 3:** USB host controller (DWC3 + PHY + role-switch).
4. **Phase 4:** XNU / HackiOS boot experiments.

## Credits

- **Base EDK2 port:** [sonic011gamer/edk2-exynos](https://github.com/sonic011gamer/edk2-exynos)
- **HackiOS reference:** [oosexgang/hackios-xnu-kernel](https://github.com/oosexgang/hackios-xnu-kernel)
- **Device tree sources:** [LineageOS/android_kernel_samsung_s5e8535](https://github.com/LineageOS/android_kernel_samsung_s5e8535)

## License

SPDX-License-Identifier: BSD-2-Clause-Patent
