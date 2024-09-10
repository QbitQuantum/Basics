AVIAN_EXPORT const uint8_t* bootJar(unsigned* size)
{
  if (HRSRC hResInfo = FindResourceW(
          NULL, RESID_BOOT_JAR, reinterpret_cast<LPCWSTR>(RT_RCDATA))) {
    if (HGLOBAL hRes = LoadResource(NULL, hResInfo)) {
      *size = SizeofResource(NULL, hResInfo);
      return (const uint8_t*)LockResource(hRes);
    }
  }

  fprintf(stderr, "boot.jar resource not found\n");

  *size = 0;
  return NULL;
}