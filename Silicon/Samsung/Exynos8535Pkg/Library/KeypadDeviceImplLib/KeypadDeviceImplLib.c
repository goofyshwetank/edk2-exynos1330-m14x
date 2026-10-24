#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BitmapLib.h>
#include <Library/KeypadDeviceImplLib.h>
#include <Library/UefiLib.h>
#include <Library/IoLib.h>
#include <Protocol/KeypadDevice.h>
#include <Library/DebugLib.h>

RETURN_STATUS
EFIAPI
KeypadDeviceImplConstructor(VOID)
{
  return RETURN_SUCCESS;
}

EFI_STATUS EFIAPI KeypadDeviceImplReset(KEYPAD_DEVICE_PROTOCOL *This)
{
  return EFI_SUCCESS;
}

EFI_STATUS KeypadDeviceImplGetKeys(
    KEYPAD_DEVICE_PROTOCOL *This, KEYPAD_RETURN_API *KeypadReturnApi,
    UINT64 Delta)
{
  // ponytail: s5e8535 uses s2mpu15 PMIC keys, stub GPIO polling to prevent bus fault
  return EFI_SUCCESS;
}
