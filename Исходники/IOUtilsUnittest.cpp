void testSizeFunctions() {
	string filename(tmpnam(NULL));
	seb::io::text(filename, "storlekstest");
	assert(seb::io::size(filename) == 12);
	remove(filename.c_str());
}