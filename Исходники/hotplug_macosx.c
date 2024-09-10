/*
 * Creates a vector of driver bundle info structures from the hot-plug driver
 * directory.
 *
 * Returns NULL on error and a pointer to an allocated HPDriver vector on
 * success.  The caller must free the HPDriver with a call to
 * HPDriversRelease().
 */
static HPDriverVector HPDriversGetFromDirectory(const char *driverBundlePath)
{
#ifdef DEBUG_HOTPLUG
	Log2(PCSC_LOG_DEBUG, "Entering HPDriversGetFromDirectory: %s",
		driverBundlePath);
#endif

	int readersNumber = 0;
	HPDriverVector bundleVector = NULL;
	CFArrayRef bundleArray;
	CFStringRef driverBundlePathString =
		CFStringCreateWithCString(kCFAllocatorDefault,
		driverBundlePath,
		kCFStringEncodingMacRoman);
	CFURLRef pluginUrl = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
		driverBundlePathString,
		kCFURLPOSIXPathStyle, TRUE);

	CFRelease(driverBundlePathString);
	if (!pluginUrl)
	{
		Log1(PCSC_LOG_ERROR, "error getting plugin directory URL");
		return NULL;
	}
	bundleArray = CFBundleCreateBundlesFromDirectory(kCFAllocatorDefault,
		pluginUrl, NULL);
	if (!bundleArray)
	{
		Log1(PCSC_LOG_ERROR, "error getting plugin directory bundles");
		return NULL;
	}
	CFRelease(pluginUrl);

	size_t bundleArraySize = CFArrayGetCount(bundleArray);
	size_t i;

	/* get the number of readers (including aliases) */
	for (i = 0; i < bundleArraySize; i++)
	{
		CFBundleRef currBundle =
			(CFBundleRef) CFArrayGetValueAtIndex(bundleArray, i);
		CFDictionaryRef dict = CFBundleGetInfoDictionary(currBundle);

		const void * blobValue = CFDictionaryGetValue(dict,
			CFSTR(PCSCLITE_HP_MANUKEY_NAME));

		if (!blobValue)
		{
			Log1(PCSC_LOG_ERROR, "error getting vendor ID from bundle");
			return NULL;
		}

		if (CFGetTypeID(blobValue) == CFArrayGetTypeID())
		{
			/* alias found, each reader count as 1 */
			CFArrayRef propertyArray = blobValue;
			readersNumber += CFArrayGetCount(propertyArray);
		}
		else
			/* No alias, only one reader supported */
			readersNumber++;
	}
#ifdef DEBUG_HOTPLUG
	Log2(PCSC_LOG_DEBUG, "Total of %d readers supported", readersNumber);
#endif

	/* The last entry is an end marker (m_vendorId = 0)
	 * see checks in HPDriversMatchUSBDevices:503
	 *  and HPDriverVectorRelease:376 */
	readersNumber++;

	bundleVector = calloc(readersNumber, sizeof(HPDriver));
	if (!bundleVector)
	{
		Log1(PCSC_LOG_ERROR, "memory allocation failure");
		return NULL;
	}

	HPDriver *driverBundle = bundleVector;
	for (i = 0; i < bundleArraySize; i++)
	{
		CFBundleRef currBundle =
			(CFBundleRef) CFArrayGetValueAtIndex(bundleArray, i);
		CFDictionaryRef dict = CFBundleGetInfoDictionary(currBundle);

		CFURLRef bundleUrl = CFBundleCopyBundleURL(currBundle);
		CFStringRef bundlePath = CFURLCopyPath(bundleUrl);

		driverBundle->m_libPath = strdup(CFStringGetCStringPtr(bundlePath,
				CFStringGetSystemEncoding()));

		const void * blobValue = CFDictionaryGetValue(dict,
			CFSTR(PCSCLITE_HP_MANUKEY_NAME));

		if (!blobValue)
		{
			Log1(PCSC_LOG_ERROR, "error getting vendor ID from bundle");
			return bundleVector;
		}

		if (CFGetTypeID(blobValue) == CFArrayGetTypeID())
		{
			CFArrayRef vendorArray = blobValue;
			CFArrayRef productArray;
			CFArrayRef friendlyNameArray;
			char *libPath = driverBundle->m_libPath;

#ifdef DEBUG_HOTPLUG
			Log2(PCSC_LOG_DEBUG, "Driver with aliases: %s", libPath);
#endif
			/* get list of ProductID */
			productArray = CFDictionaryGetValue(dict,
				 CFSTR(PCSCLITE_HP_PRODKEY_NAME));
			if (!productArray)
			{
				Log1(PCSC_LOG_ERROR, "error getting product ID from bundle");
				return bundleVector;
			}

			/* get list of FriendlyName */
			friendlyNameArray = CFDictionaryGetValue(dict,
				 CFSTR(PCSCLITE_HP_NAMEKEY_NAME));
			if (!friendlyNameArray)
			{
				Log1(PCSC_LOG_ERROR, "error getting product ID from bundle");
				return bundleVector;
			}

			int reader_nb = CFArrayGetCount(vendorArray);

			if (reader_nb != CFArrayGetCount(productArray))
			{
				Log3(PCSC_LOG_ERROR,
					"Malformed Info.plist: %d vendors and %ld products",
					reader_nb, CFArrayGetCount(productArray));
				return bundleVector;
			}

			if (reader_nb != CFArrayGetCount(friendlyNameArray))
			{
				Log3(PCSC_LOG_ERROR,
					"Malformed Info.plist: %d vendors and %ld friendlynames",
					reader_nb, CFArrayGetCount(friendlyNameArray));
				return bundleVector;
			}

			int j;
			for (j=0; j<reader_nb; j++)
			{
				CFStringRef strValue = CFArrayGetValueAtIndex(vendorArray, j);

				driverBundle->m_vendorId = strtoul(CFStringGetCStringPtr(strValue,
					CFStringGetSystemEncoding()), NULL, 16);

				strValue = CFArrayGetValueAtIndex(productArray, j);
				driverBundle->m_productId = strtoul(CFStringGetCStringPtr(strValue,
					CFStringGetSystemEncoding()), NULL, 16);

				strValue = CFArrayGetValueAtIndex(friendlyNameArray, j);
				const char *cstr = CFStringGetCStringPtr(strValue,
					CFStringGetSystemEncoding());

				driverBundle->m_friendlyName = strdup(cstr);
				if (!driverBundle->m_libPath)
					driverBundle->m_libPath = strdup(libPath);

#ifdef DEBUG_HOTPLUG
				Log2(PCSC_LOG_DEBUG, "VendorID: 0x%04X",
					driverBundle->m_vendorId);
				Log2(PCSC_LOG_DEBUG, "ProductID: 0x%04X",
					driverBundle->m_productId);
				Log2(PCSC_LOG_DEBUG, "Friendly name: %s",
					driverBundle->m_friendlyName);
				Log2(PCSC_LOG_DEBUG, "Driver: %s", driverBundle->m_libPath);
#endif

				/* go to next bundle in the vector */
				driverBundle++;
			}
		}
		else
		{
			CFStringRef strValue = blobValue;

#ifdef DEBUG_HOTPLUG
			Log3(PCSC_LOG_DEBUG, "Driver without alias: %s %s",
				driverBundle->m_friendlyName, driverBundle->m_libPath);
#endif

			driverBundle->m_vendorId = strtoul(CFStringGetCStringPtr(strValue,
					CFStringGetSystemEncoding()), NULL, 16);

			strValue = (CFStringRef) CFDictionaryGetValue(dict,
				CFSTR(PCSCLITE_HP_PRODKEY_NAME));
			if (!strValue)
			{
				Log1(PCSC_LOG_ERROR, "error getting product ID from bundle");
				return bundleVector;
			}
			driverBundle->m_productId = strtoul(CFStringGetCStringPtr(strValue,
				CFStringGetSystemEncoding()), NULL, 16);

			strValue = (CFStringRef) CFDictionaryGetValue(dict,
				CFSTR(PCSCLITE_HP_NAMEKEY_NAME));
			if (!strValue)
			{
				Log1(PCSC_LOG_ERROR, "error getting product friendly name from bundle");
				driverBundle->m_friendlyName = strdup("unnamed device");
			}
			else
			{
				const char *cstr = CFStringGetCStringPtr(strValue,
					CFStringGetSystemEncoding());

				driverBundle->m_friendlyName = strdup(cstr);
			}
#ifdef DEBUG_HOTPLUG
			Log2(PCSC_LOG_DEBUG, "VendorID: 0x%04X", driverBundle->m_vendorId);
			Log2(PCSC_LOG_DEBUG, "ProductID: 0x%04X", driverBundle->m_productId);
			Log2(PCSC_LOG_DEBUG, "Friendly name: %s", driverBundle->m_friendlyName);
			Log2(PCSC_LOG_DEBUG, "Driver: %s", driverBundle->m_libPath);
#endif

			/* go to next bundle in the vector */
			driverBundle++;
		}
	}
	CFRelease(bundleArray);
	return bundleVector;
}