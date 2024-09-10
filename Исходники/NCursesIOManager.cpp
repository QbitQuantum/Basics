void NCursesIOManager::removeCharFromOrder(std::string & input)
{
	input.resize(input.length() == 0 ? 0 : input.length() - 1);
}