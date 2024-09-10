bool IsVolumeDesignatorAvailable(WCHAR chVolume)
{
	return IsDriveAvailable(towupper(chVolume) - L'A');
}