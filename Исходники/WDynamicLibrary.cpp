void			WDynamicLibrary<IMonster *>::freeLibrary(void) {
	FreeLibrary(this->hinstLib);
}