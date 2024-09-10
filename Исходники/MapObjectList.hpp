	T* findOrAllocate(const std::string& name)
	{
		int ret1 = _strcmpi("", name.c_str());
		int ret2 = _strcmpi("none", name.c_str());
		int ret3 = _strcmpi("<none>", name.c_str());

		if (ret1 == 0 || ret2 == 0 || ret3 == 0)
			return nullptr;

		if (auto ptr = find(name))
			return ptr;

		objectList.push_back(std::make_unique<T>(name));
		return objectList.back().get();
	}