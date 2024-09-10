int main(int argc, char* argv[])
{
	AutoSeededRandomPool prng;

	byte key[AES::DEFAULT_KEYLENGTH] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
	//prng.GenerateBlock(key, sizeof(key));  /* For pseudo random key generation */

	byte plain[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
	string cipher, encoded, recovered;

	/**************************************************************************************
	NOTE:
	***************************************************************************************
	-- plaintext can also be changed to type string of 16 bytes i.e. 16 characters
	-- Only Decryption can also be performed on the same basis
	****************************************************************************************/

	if(sizeof(key) != BLOCK_SIZE_BYTES || sizeof(plain) != BLOCK_SIZE_BYTES)
	{
		cerr << "Either plainText or Key has improper block size" << endl;
		exit(1);
	}

	/*********************************\
	\*********************************/

	// print key
	encoded.clear();
	StringSource(key, sizeof(key), true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "key: " << encoded << endl;

	/*********************************\
	\*********************************/

	try
	{
		cout << "plain text: " << plain << endl;

		ECB_Mode< AES >::Encryption e;
		e.SetKey(key, sizeof(key));

		StringSource ss(plain, sizeof(plain), true, 
			new StreamTransformationFilter(e,
				new StringSink(cipher)//,
					//BlockPaddingScheme::NO_PADDING
			) // StreamTransformationFilter      
		); // StringSource
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	/*********************************\
	\*********************************/

	// print Cipher Text
	encoded.clear();
	StringSource(cipher, true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	encoded.resize(16*2);
	cout << "cipher text: " << encoded << endl;

	/*********************************\
	\*********************************/

	try
	{
		ECB_Mode< AES >::Decryption d;
		d.SetKey(key, sizeof(key));

		StringSource s(cipher, true, 
			new StreamTransformationFilter(d,
				new StringSink(recovered)
			) // StreamTransformationFilter
		); // StringSource

		cout << "recovered text: " << recovered << endl;
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	/*********************************\
	\*********************************/

	return 0;
}