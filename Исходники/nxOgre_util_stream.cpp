UserStream::UserStream(const char* filename, bool load) : fp(NULL) {
	// Swap these two lines around if you get a compiling error.
	//	fp = fopen(filename, load ? "rb" : "wb");
	fopen_s(&fp,filename, load ? "rb" : "wb");

}