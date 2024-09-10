//
/// Sets the values for the DEVNAMES structure.
//
void
TPrintDialog::TData::SetDevNames(const tstring& driver, const tstring& device, const tstring& output)
{
  ClearDevNames();

  // Calculate the required buffer size, as the number of characters incl. null-terminators,
  // and the resulting total size, in bytes, of the DEVNAMES structure including trailing strings.
  // Then allocate and lock the required amount of global memory.
  //
  const int n = driver.length() + 1 + device.length() + 1 + output.length() + 1; 
  const int size = sizeof(DEVNAMES) + (n * sizeof(tchar));
  HDevNames = ::GlobalAlloc(GHND, size); 
  DevNames = static_cast<DEVNAMES*>(::GlobalLock(HDevNames));
  DevNames->wDefault = false;

  // Calculate the offsets to the strings within DEVNAMES.
  // Then copy the given names into DEVNAMES (actually, behind the fixed part of DEVNAMES).
  //
  // NB! Offsets are in character counts. Here we assume the size of the fixed part of DEVNAMES is divisible 
  // by the character size. Otherwise the driver name will overwrite the last byte of the fixed part.
  // But DEVNAMES is divisible and forever set in stone, so we don't need to consider an odd struct size.
  //
  CHECK(sizeof(DEVNAMES) % sizeof(tchar) == 0); 
  const LPTSTR base = reinterpret_cast<LPTSTR>(DevNames);
  const LPTSTR pDriver = reinterpret_cast<LPTSTR>(DevNames + 1); // Jump past the the fixed part, assuming even struct size.
  const LPTSTR pDevice = pDriver + driver.length() + 1; // Jump past the preceding string, including null-terminator.
  const LPTSTR pOutput = pDevice + device.length() + 1;
  DevNames->wDriverOffset = static_cast<WORD>(pDriver - base);
  DevNames->wDeviceOffset = static_cast<WORD>(pDevice - base);
  DevNames->wOutputOffset = static_cast<WORD>(pOutput - base);
  _tcscpy(pDriver, driver.c_str());
  _tcscpy(pDevice, device.c_str());
  _tcscpy(pOutput, output.c_str());
}