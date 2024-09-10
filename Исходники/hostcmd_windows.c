void
destructHostCommandPackageData (HostCommandPackageData *pkg) {
  closeHandle(&pkg->inputHandle);
  closeHandle(&pkg->outputHandle);
}