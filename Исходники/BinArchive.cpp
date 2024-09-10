bool BinOArchive::operator()(ContainerInterface& ser, const char* name, const char* label)
{
	openNode(name, false);

	unsigned int size = (unsigned int)ser.size();
	if(size < SIZE16)
		stream_.write((unsigned char)size);
	else if(size < 0x10000){
		stream_.write(SIZE16);
		stream_.write((unsigned short)size);
	}
	else{
		stream_.write(SIZE32);
		stream_.write(size);
	}

	if(strlen(name)){
		if(size > 0){
			int i = 0;
			do {
				char buffer[16];
#ifdef _MSC_VER
				_itoa(i++, buffer, 10);
#else
				sprintf(buffer, "%d", i++);
#endif
				ser(*this, buffer, "");
			} while (ser.next());
		}

		closeNode(name, false);
	}
	else{
		if(size > 0)
			do 
				ser(*this, "", "");
				while (ser.next());
	}

    return true;
}