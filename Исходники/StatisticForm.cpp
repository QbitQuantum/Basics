// Only include non-filter mapper statistics
static bool IncludeName(const CComBSTR& name)
{
	static const OLECHAR build_mapper[] = L"Build Mapper Cache";
	static const OLECHAR category[] = L"Process Category";
	static const int category_length = (sizeof(category) / sizeof(category[0])) - 1;

	return name != build_mapper && 
			0 != _wcsnicmp(name, category, min(category_length, name.Length()));
}