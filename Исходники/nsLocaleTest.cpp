void
win32_test_special_locales(void)
{
	nsresult			result;
	nsCOMPtr<nsIWin32Locale>	win32Locale;
	nsCOMPtr<nsILocaleFactory>	xp_locale_factory;
	nsCOMPtr<nsILocale>	xp_locale;
	nsString*			locale, *result_locale, *category;
	LCID				sys_lcid, user_lcid;
	PRUnichar *lc_name_unichar;

  win32Locale = do_CreateInstance(kWin32LocaleFactoryCID, &result);
	NS_ASSERTION(NS_SUCCEEDED(result),"nsLocaleTest: factory_create_interface failed");

  xp_locale_factory = do_GetClassObject(kLocaleFactoryCID, &result);
	NS_ASSERTION(NS_SUCCEEDED(result),"nsLocaleTest: factory_create_interface failed");

	category = new nsString(localeCategoryList[0]);

	//
	// derive a system locale
	//
	result  = xp_locale_factory->GetSystemLocale(getter_AddRefs(xp_locale));
	NS_ASSERTION(NS_SUCCEEDED(result),"nsLocaleTest: factory_create_interface failed");

	sys_lcid = GetSystemDefaultLCID();
	locale = new nsString();
	result_locale = new nsString();

	result = win32Locale->GetXPLocale(sys_lcid,locale);
	NS_ASSERTION(NS_SUCCEEDED(result),"nsLocaleTest: factory_create_interface failed");
	result = xp_locale->GetCategory(category, &lc_name_unichar);
	NS_ASSERTION(NS_SUCCEEDED(result),"nsLocaleTest: factory_create_interface failed");

  result_locale->SetString(lc_name_unichar);
	delete result_locale;

	//
	// derive a system locale
	//
	result  = xp_locale_factory->GetApplicationLocale(getter_AddRefs(xp_locale));
	NS_ASSERTION(NS_SUCCEEDED(result),"nsLocaleTest: factory_create_interface failed");

	user_lcid = GetUserDefaultLCID();
	locale = new nsString();
	result_locale = new nsString();

	result = win32Locale->GetXPLocale(user_lcid,locale);
	NS_ASSERTION(NS_SUCCEEDED(result),"nsLocaleTest: factory_create_interface failed");
	result = xp_locale->GetCategory(category, &lc_name_unichar);
	NS_ASSERTION(NS_SUCCEEDED(result),"nsLocaleTest: factory_create_interface failed");

 result_locale->SetString(lc_name_unichar);
	delete result_locale;

	delete category;

}