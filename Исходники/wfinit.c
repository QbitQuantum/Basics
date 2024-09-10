INT NEAR PASCAL GetDriveOffset(
register WORD wDrive)
{
  if (IsCDRomDrive(wDrive))
      return dxDriveBitmap * 0;

  switch (IsNetDrive(wDrive)) {
  case 1:
      return dxDriveBitmap * 4;
  case 2:
      return dxDriveBitmap * 5;
  }

  if (IsRemovableDrive(wDrive))
      return dxDriveBitmap * 1;

  if (IsRamDrive(wDrive))
      return dxDriveBitmap * 3;

  return dxDriveBitmap * 2;
}