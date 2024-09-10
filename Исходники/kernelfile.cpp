/**
  * Provera da li je tekuca pozicija u fajlu kraj tog fajla
  */
char KernelFile::eof() const {
	if (getFileSize() == 0) return 1; // ako je prazan fajl, greska
	if (getFileSize() == pointer) return 2; // eof
	return 0;
}