CREATE_TEST(CaesarCipher, StressTest)
{
	const int trials = 900;
	const int strSize = 40;
	std::string availLetters = "abcdefghijklmnopqrstuvwxyz";
	MonoAlphabeticCipher::CaesarEncrypter encrypter;
	size_t numLetters = availLetters.length();

	for (int i = 0; i < trials; ++i)
	{
		std::stringstream builder;
		for(int j = 0; j < strSize; ++j){
			char c = availLetters[rand() % numLetters];
			builder << c;
		}
		std::string test = builder.str();
		ASSERT_EQUALS_EVAL(test, encrypter.Decrypt(encrypter.Encrypt(test)));
	}
}