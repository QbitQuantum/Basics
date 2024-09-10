static void ParseList(DynamicVectorClass<T> &List, CCINIClass * pINI, const char *section, const char *key) {
	if(pINI->ReadString(section, key, Ares::readDefval, Ares::readBuffer)) {
		List.Clear();

		char* context = nullptr;
		for(char *cur = strtok_s(Ares::readBuffer, Ares::readDelims, &context); cur; cur = strtok_s(nullptr, Ares::readDelims, &context)) {
			T buffer = T();
			if(Parser<T>::TryParse(cur, &buffer)) {
				List.AddItem(buffer);
			} else if(!std::is_pointer<T>() || !INIClass::IsBlank(cur)) {
				Debug::INIParseFailed(section, key, cur);
			}
		}
	}
};