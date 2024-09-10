unsigned long	readImplicitFile( ifstream& input , unsigned long offset , bool bigEndian , unsigned short target , DicomFileImage& fileInfo )
{
	unsigned long	currentOffset;
	unsigned long	size;
	unsigned short	group;
	unsigned short	element;
	unsigned int	lengthInt;
	char*			value;
	bool			found;
	

	
	try
	{
		currentOffset = offset;
		found = false;
		value = NULL;
		input.seekg(0,ifstream::end);
		size = input.tellg();
		input.seekg(offset,ifstream::beg);
		while( !input.eof()  &&  ( currentOffset = input.tellg() ) < size )
		{
			input.read((char*)&group,2);	// read group code
			input.read((char*)&element,2);	// read element code
			input.read((char*)&lengthInt,4);	// read value length

			// if the transfer syntax is Big Endian perform a byte swap
			if ( bigEndian )
			{
				group = _byteswap_ushort(group);
				element = _byteswap_ushort(element);
				lengthInt = _byteswap_ulong(lengthInt);
			}

			// termination condition update
			if ( group == target  &&  !found )	found = true;
			else if ( group != target  &&  found )	break;


			// if the length is undefined
			if ( lengthInt == 0xFFFFFFFF )
			{
				int	valueSize;



				// read unlimited text 
				value = readUnlimitedText(input,"",true,bigEndian,&valueSize);
				// update DicomFileImage information
				saveInformation(group,element,valueSize,value,fileInfo);
				delete[] value;
				value = NULL;
			}
			else	// if the length is defined
			{
				if ( lengthInt > 0 )
				{
					// read data of size equal to the defined length
					value = new char[lengthInt];
					input.read(value,lengthInt);
					saveInformation(group,element,sizeof(unsigned short),value,fileInfo);
					delete[] value;
					value = NULL;
				}
			}
		}
	}
	catch ( exception &e )
	{
		if ( value != NULL )
			delete[] value;

		throw e;
	}



	return currentOffset;
};