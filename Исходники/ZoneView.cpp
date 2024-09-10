void
TimeZoneView::_BuildZoneMenu()
{
	BTimeZone defaultTimeZone;
	BLocaleRoster::Default()->GetDefaultTimeZone(&defaultTimeZone);

	BLanguage language;
	BLocale::Default()->GetLanguage(&language);

	/*
	 * Group timezones by regions, but filter out unwanted (duplicate) regions
	 * and add an additional region with generic GMT-offset timezones at the end
	 */
	typedef	std::map<BString, TimeZoneListItem*, TimeZoneItemLess> ZoneItemMap;
	ZoneItemMap zoneItemMap;
	const char* kOtherRegion = B_TRANSLATE_MARK("<Other>");
	const char* kSupportedRegions[] = {
		B_TRANSLATE_MARK("Africa"),		B_TRANSLATE_MARK("America"),
		B_TRANSLATE_MARK("Antarctica"),	B_TRANSLATE_MARK("Arctic"),
		B_TRANSLATE_MARK("Asia"),		B_TRANSLATE_MARK("Atlantic"),
		B_TRANSLATE_MARK("Australia"),	B_TRANSLATE_MARK("Europe"),
		B_TRANSLATE_MARK("Indian"),		B_TRANSLATE_MARK("Pacific"),
		kOtherRegion,
		NULL
	};
	// Since the zone-map contains translated country-names (we get those from
	// ICU), we need to use translated region names in the zone-map, too:
	typedef	std::map<BString, BString> TranslatedRegionMap;
	TranslatedRegionMap regionMap;
	for (const char** region = kSupportedRegions; *region != NULL; ++region) {
		BString translatedRegion = B_TRANSLATE_NOCOLLECT(*region);
		regionMap[*region] = translatedRegion;

		TimeZoneListItem* regionItem
			= new TimeZoneListItem(translatedRegion, NULL, NULL);
		regionItem->SetOutlineLevel(0);
		zoneItemMap[translatedRegion] = regionItem;
	}

	// Get all time zones
	BMessage zoneList;
	BLocaleRoster::Default()->GetAvailableTimeZonesWithRegionInfo(&zoneList);

	typedef std::map<BString, std::vector<const char*> > ZonesByCountyMap;
	ZonesByCountyMap zonesByCountryMap;
	const char *zoneID;
	BString countryCode;
	for (int tz = 0; zoneList.FindString("timeZone", tz, &zoneID) == B_OK
			&& zoneList.FindString("region", tz, &countryCode) == B_OK; tz++) {
		// From the global ("001") timezones, we only accept the generic GMT
		// timezones, as all the other world-zones are duplicates of others.
		if (countryCode == "001" && strncmp(zoneID, "Etc/GMT", 7) != 0)
			continue;
		zonesByCountryMap[countryCode].push_back(zoneID);
	}

	ZonesByCountyMap::const_iterator countryIter = zonesByCountryMap.begin();
	for (; countryIter != zonesByCountryMap.end(); ++countryIter) {
		BCountry country(countryIter->first.String());
		BString countryName;
		country.GetName(countryName);

		size_t zoneCountInCountry = countryIter->second.size();
		for (size_t tz = 0; tz < zoneCountInCountry; tz++) {
			BString zoneID(countryIter->second[tz]);
			int32 slashPos = zoneID.FindFirst('/');

			BString region(zoneID, slashPos);
			if (region == "Etc")
				region = kOtherRegion;

			// just accept timezones from our supported regions, others are
			// aliases and would just make the list even longer
			TranslatedRegionMap::iterator regionIter = regionMap.find(region);
			if (regionIter == regionMap.end())
				continue;

			BString fullCountryID = regionIter->second;
			bool countryIsRegion
				= countryName == regionIter->second || region == kOtherRegion;
			if (!countryIsRegion)
				fullCountryID << "/" << countryName;

			BTimeZone* timeZone = new BTimeZone(zoneID, &language);
			BString tzName;
			BString fullZoneID = fullCountryID;
			if (zoneCountInCountry > 1)
			{
				// we can't use the country name as timezone name, since there
				// are more than one timezones in this country - fetch the
				// localized name of the timezone and use that
				tzName = timeZone->Name();
				int32 openParenthesisPos = tzName.FindFirst('(');
				if (openParenthesisPos >= 0) {
					tzName.Remove(0, openParenthesisPos + 1);
					int32 closeParenthesisPos = tzName.FindLast(')');
					if (closeParenthesisPos >= 0)
						tzName.Truncate(closeParenthesisPos);
				}
				fullZoneID << "/" << tzName;
			} else {
				tzName = countryName;
				fullZoneID << "/" << zoneID;
			}

			// skip duplicates
			ZoneItemMap::iterator zoneIter = zoneItemMap.find(fullZoneID);
			if (zoneIter != zoneItemMap.end()) {
				delete timeZone;
				continue;
			}

			TimeZoneListItem* countryItem = NULL;
			TimeZoneListItem* zoneItem = NULL;
			if (zoneCountInCountry > 1) {
				ZoneItemMap::iterator countryIter
					= zoneItemMap.find(fullCountryID);
				if (countryIter == zoneItemMap.end()) {
					countryItem = new TimeZoneListItem(countryName, NULL, NULL);
					countryItem->SetOutlineLevel(1);
					zoneItemMap[fullCountryID] = countryItem;
				} else
					countryItem = countryIter->second;

				zoneItem = new TimeZoneListItem(tzName, NULL, timeZone);
				zoneItem->SetOutlineLevel(countryIsRegion ? 1 : 2);
			} else {
				zoneItem = new TimeZoneListItem(tzName, NULL, timeZone);
				zoneItem->SetOutlineLevel(1);
			}
			zoneItemMap[fullZoneID] = zoneItem;

			if (timeZone->ID() == defaultTimeZone.ID()) {
				fCurrentZoneItem = zoneItem;
				if (countryItem != NULL)
					countryItem->SetExpanded(true);
				ZoneItemMap::iterator regionItemIter
					= zoneItemMap.find(regionIter->second);
				if (regionItemIter != zoneItemMap.end())
					regionItemIter->second->SetExpanded(true);
			}
		}
	}

	fOldZoneItem = fCurrentZoneItem;

	ZoneItemMap::iterator zoneIter;
	bool lastWasCountryItem = false;
	TimeZoneListItem* currentCountryItem = NULL;
	for (zoneIter = zoneItemMap.begin(); zoneIter != zoneItemMap.end();
		++zoneIter) {
		if (zoneIter->second->OutlineLevel() == 2 && lastWasCountryItem) {
			/* Some countries (e.g. Spain and Chile) have their timezones
			 * spread across different regions. As a result, there might still
			 * be country items with only one timezone below them. We manually
			 * filter those country items here.
			 */
			ZoneItemMap::iterator next = zoneIter;
			++next;
			if (next != zoneItemMap.end()
				&& next->second->OutlineLevel() != 2) {
				fZoneList->RemoveItem(currentCountryItem);
				zoneIter->second->SetText(currentCountryItem->Text());
				zoneIter->second->SetOutlineLevel(1);
				delete currentCountryItem;
			}
		}

		fZoneList->AddItem(zoneIter->second);
		if (zoneIter->second->OutlineLevel() == 1) {
			lastWasCountryItem = true;
			currentCountryItem = zoneIter->second;
		} else
			lastWasCountryItem = false;
	}
}