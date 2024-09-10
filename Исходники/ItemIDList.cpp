ItemIDList ItemIDList::FromPath(const wchar_t* path)
{
	ItemIDList result;

	if (FAILED(SHILCreateFromPath(path, &result, NULL)))
		throw std::invalid_argument("Failed to convert the specified path");

	return result;
}