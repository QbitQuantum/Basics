bool TwoDAFile::writeCSV(const Common::UString &fileName) const {
	Common::WriteFile file;
	if (!file.open(fileName))
		return false;

	writeCSV(file);
	file.close();

	return true;
}