/**
poistaa rekisteristä arvon
*/
void MyRegistryClass::MyRegistryClass::deleteValue(std::string subkey)
{
	int n = RegDeleteValueA(key, (LPCSTR)(subkey.data()));
	if (n == ERROR_SUCCESS)
	{
		std::cout << "subkey \"" << subkey << "\" deleted successfully." << std::endl;
	}
	else
	{
		/* ERROR: 2 == subkey not found  */
		std::cout << "ERROR: " << n << std::endl;
		std::cout << "unable to delete subkey \"" << subkey << "\"." << std::endl;
	}

}