void testEncryptor()
{
	char plainText[] = "Hello! How are you.";
	vector<char> data(plainText, plainText + 20);
	Encryptor<char> enc;
	SecByteBlock key;
	SecByteBlock iv;

	auto cdata = enc.encrypt(data, key, iv);
	auto databack = enc.decrypt(cdata, key, iv);
	assert(data == databack);

	cout << cdata.data() << endl;
	cout << databack.data() << endl;
}