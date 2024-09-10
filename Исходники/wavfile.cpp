WavFile::WavFile(const string &fname, Logger &logger, FileStreamProducer &fsp) : filename(fname), fsp(fsp) {
	struct wavheader header;
	{
		boost::scoped_ptr<istream> file(fsp.readFile(filename.c_str())); // open the file

		file->read((char *)&header, sizeof(header)); // read the header
	}

	if (memcmp(&header.riff_header.riff, riff_val, sizeof(riff_val)) != 0)
		throw Exception(string("Bad RIFF header in wav file ") + filename);

	if (memcmp(&header.riff_header.wave, wave_val, sizeof(wave_val)) != 0)
		throw Exception(string("Bad WAVE header in wav file ") + filename);

	if (memcmp(&header.fmt_header.fmt, fmt_val, sizeof(fmt_val)) != 0)
		throw Exception(string("Bad fmt header in wav file ") + filename);

	if (memcmp(&header.data_header.data, data_val, sizeof(data_val)) != 0)
		throw Exception(string("Bad data header in wav file ") + filename);

	fmt.channels = header.fmt_header.channels;
	fmt.bits = header.fmt_header.samplebits;
	fmt.freq = header.fmt_header.samplerate;
	fmt.length = header.data_header.length;

	logger.log("audio", DEBUG) << "Loaded WAV " << filename << endl;
	logger.log("audio", DEBUG) << "  " << fmt << endl;
}