void Pk::go(int argc, char *args[], std::string& ext) 
{
	Compress *mainCompressor;
	Compress *auxiliaryCompressor = 0;

	unsigned char n = 4;
	unsigned char p = 10;
	unsigned char c = 4;
	
	findMode(args);

	if(mode == 0 && argc == 2)
	{
		n = atoi(args[1]);
		mainCompressor = new RLE_Compress(&out, n);
	}
	else if(mode == 1 && argc == 3)
	{
		p = atoi(args[1]);
		c = atoi(args[2]);
		mainCompressor = new LZSS_Compress(&out, p, c);
	}
	else if(mode == 2 && argc == 4)
	{
		n = atoi(args[1]);
		p = atoi(args[2]);
		c = atoi(args[3]);
		mainCompressor = new RLE_Compress(auxiliaryCompressor = new LZSS_Compress(&out, p, c), n);
	}
	else
	{
		cout << "Argumentos inva'lidos." << endl;
		return;
	}
	
	this->writeHeader(ext);

	mainCompressor->putHeader(out);

	if(auxiliaryCompressor)
		auxiliaryCompressor->putHeader(out);

	int b;
	while((b = in.getByte()) != EOF) 
		mainCompressor->putByte(b);

	mainCompressor->close();
	delete mainCompressor;

	if(auxiliaryCompressor)
		delete auxiliaryCompressor;

	in.close();
}