	unsigned char* bcGetRawFile(const char* filename) {
		FILE* file;
		fopen_s(&file, filename, "rb");
		unsigned int size = 0;
		unsigned char* data;
		if (file) {

			FSEEK(file, 0, SEEK_END);
			size = FTELL(file);
			FSEEK(file, 0, SEEK_SET);

			data = new unsigned char[size];
			FREAD(data, size, file);

			fclose(file);
		} else {
			LOG("Failed To Open File: %s\n", filename);
		}

		return data;
	}