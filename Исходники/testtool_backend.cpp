/**
 * @brief Easily allows to generate regression tests for keysets.
 *
 * @param tocheck the keyset to check (name + string)
 * @param name the name of the keyset
 */
void outputGTest(kdb::KeySet tocheck, std::string name)
{
	std::cout << name << ".rewind();" << std::endl;
	tocheck.rewind();
	while(tocheck.next())
	{
		std::cout << name << ".next();" << std::endl;
		std::cout << "EXPECT_TRUE(" << name
			<< ".current().getName() == \""
			<< tocheck.current().getName()
			<< "\") << \"name of element in keyset wrong\";"
			<< std::endl;
		std::cout << "EXPECT_TRUE(" << name
			<< ".current().getString() == \""
			<< tocheck.current().getString()
			<< "\") << \"string of element in keyset wrong\";"
			<< std::endl;
	}
}