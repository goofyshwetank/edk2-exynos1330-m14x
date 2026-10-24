[Defines]
  PLATFORM_NAME                  = m14x
  PLATFORM_GUID                  = 78b2e564-942f-48d8-9fb5-632b5b3e2189
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010019
  OUTPUT_DIRECTORY               = Build/$(PLATFORM_NAME)
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = Platform/Samsung/exynos8535/exynos8535.fdf
  DEVICE_DXE_FV_COMPONENTS       = Platform/Samsung/exynos8535/exynos8535.fdf.inc

!include Platform/Samsung/exynos8535/exynos8535.dsc

[BuildOptions.common]
  GCC:*_*_AARCH64_CC_FLAGS = -DENABLE_SIMPLE_INIT

[PcdsFixedAtBuild.common]
  gSamsungTokenSpaceGuid.PcdMipiFrameBufferWidth|1080
  gSamsungTokenSpaceGuid.PcdMipiFrameBufferHeight|2408

  gSimpleInitTokenSpaceGuid.PcdGuiDefaultDPI|450

  gRenegadePkgTokenSpaceGuid.PcdDeviceVendor|"Samsung"
  gRenegadePkgTokenSpaceGuid.PcdDeviceProduct|"Galaxy M14 5G"
  gRenegadePkgTokenSpaceGuid.PcdDeviceCodeName|"m14x"
