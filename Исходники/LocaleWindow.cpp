LocaleWindow::LocaleWindow()
	:
	BWindow(BRect(0, 0, 0, 0), "Locale", B_TITLED_WINDOW, B_QUIT_ON_WINDOW_CLOSE
		| B_ASYNCHRONOUS_CONTROLS | B_AUTO_UPDATE_SIZE_LIMITS)
{
	BCountry* defaultCountry;
	be_locale_roster->GetDefaultCountry(&defaultCountry);

	SetLayout(new BGroupLayout(B_HORIZONTAL));

	float spacing = be_control_look->DefaultItemSpacing();

	BTabView* tabView = new BTabView("tabview");
	BGroupView* languageTab = new BGroupView(B_TRANSLATE("Language"),
		B_HORIZONTAL, spacing);

	// first list: available languages
	fLanguageListView = new LanguageListView("available",
		B_MULTIPLE_SELECTION_LIST);
	BScrollView* scrollView = new BScrollView("scroller", fLanguageListView,
		B_WILL_DRAW | B_FRAME_EVENTS, false, true);

	fLanguageListView->SetInvocationMessage(new BMessage(kMsgLanguageInvoked));
	fLanguageListView->SetDragMessage(new BMessage(kMsgLanguageDragged));

	// Fill the language list from the LocaleRoster data
	BMessage installedLanguages;
	if (be_locale_roster->GetInstalledLanguages(&installedLanguages) == B_OK) {
		BString currentID;
		LanguageListItem* lastAddedCountryItem = NULL;

		for (int i = 0; installedLanguages.FindString("langs", i, &currentID)
				== B_OK; i++) {
			// Now get an human-readable, localized name for each language
			BLanguage* currentLanguage;
			be_locale_roster->GetLanguage(currentID.String(),
				&currentLanguage);

			BString name;
			currentLanguage->GetName(name);

			// TODO: as long as the app_server doesn't support font overlays,
			// use the translated name if problematic characters are used...
			const char* string = name.String();
			while (uint32 code = BUnicodeChar::FromUTF8(&string)) {
				if (code > 1424) {
					currentLanguage->GetTranslatedName(name);
					break;
				}
			}

			LanguageListItem* item = new LanguageListItem(name,
				currentID.String(), currentLanguage->Code());
			if (currentLanguage->IsCountrySpecific()
				&& lastAddedCountryItem != NULL
				&& lastAddedCountryItem->Code() == item->Code()) {
				fLanguageListView->AddUnder(item, lastAddedCountryItem);
			} else {
				// This is a language variant, add it at top-level
				fLanguageListView->AddItem(item);
				if (!currentLanguage->IsCountrySpecific()) {
					item->SetExpanded(false);
					lastAddedCountryItem = item;
				}
			}

			delete currentLanguage;
		}

		fLanguageListView->FullListSortItems(compare_typed_list_items);
	} else {
		BAlert* alert = new BAlert("Error",
			B_TRANSLATE("Unable to find the available languages! You can't "
				"use this preflet!"),
			B_TRANSLATE("OK"), NULL, NULL,
			B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_STOP_ALERT);
		alert->Go();
	}

	// Second list: active languages
	fPreferredListView = new LanguageListView("preferred",
		B_MULTIPLE_SELECTION_LIST);
	BScrollView* scrollViewEnabled = new BScrollView("scroller",
		fPreferredListView, B_WILL_DRAW | B_FRAME_EVENTS, false, true);

	fPreferredListView->SetInvocationMessage(
		new BMessage(kMsgPreferredLanguageInvoked));
	fPreferredListView->SetDeleteMessage(
		new BMessage(kMsgPreferredLanguageDeleted));
	fPreferredListView->SetDragMessage(
		new BMessage(kMsgPreferredLanguageDragged));

	BLayoutBuilder::Group<>(languageTab)
		.AddGroup(B_VERTICAL, spacing)
			.Add(new BStringView("", B_TRANSLATE("Available languages")))
			.Add(scrollView)
			.End()
		.AddGroup(B_VERTICAL, spacing)
			.Add(new BStringView("", B_TRANSLATE("Preferred languages")))
			.Add(scrollViewEnabled)
			.End()
		.SetInsets(spacing, spacing, spacing, spacing);

	BView* countryTab = new BView(B_TRANSLATE("Country"), B_WILL_DRAW);
	countryTab->SetLayout(new BGroupLayout(B_VERTICAL, 0));

	BListView* listView = new BListView("country", B_SINGLE_SELECTION_LIST);
	scrollView = new BScrollView("scroller", listView,
		B_WILL_DRAW | B_FRAME_EVENTS, false, true);
	listView->SetSelectionMessage(new BMessage(kMsgCountrySelection));

	// get all available countries from ICU
	// Use DateFormat::getAvailableLocale so we get only the one we can
	// use. Maybe check the NumberFormat one and see if there is more.
	int32_t localeCount;
	const Locale* currentLocale = Locale::getAvailableLocales(localeCount);

	for (int index = 0; index < localeCount; index++) {
		UnicodeString countryFullName;
		BString string;
		BStringByteSink sink(&string);
		currentLocale[index].getDisplayName(countryFullName);
		countryFullName.toUTF8(sink);

		LanguageListItem* item
			= new LanguageListItem(string, currentLocale[index].getName(),
				NULL);
		listView->AddItem(item);
		if (!strcmp(currentLocale[index].getName(), defaultCountry->Code()))
			listView->Select(listView->CountItems() - 1);
	}

	// TODO: find a real solution intead of this hack
	listView->SetExplicitMinSize(
		BSize(25 * be_plain_font->Size(), B_SIZE_UNSET));

	fFormatView = new FormatView(defaultCountry);

	countryTab->AddChild(BLayoutBuilder::Group<>(B_HORIZONTAL, spacing)
		.AddGroup(B_VERTICAL, 3)
			.Add(scrollView)
			.End()
		.Add(fFormatView)
		.SetInsets(spacing, spacing, spacing, spacing));

	listView->ScrollToSelection();

	tabView->AddTab(languageTab);
	tabView->AddTab(countryTab);

	BButton* button = new BButton(B_TRANSLATE("Defaults"),
		new BMessage(kMsgDefaults));

	fRevertButton = new BButton(B_TRANSLATE("Revert"),
		new BMessage(kMsgRevert));
	fRevertButton->SetEnabled(false);

	BLayoutBuilder::Group<>(this, B_VERTICAL, spacing)
		.Add(tabView)
		.AddGroup(B_HORIZONTAL, spacing)
			.Add(button)
			.Add(fRevertButton)
			.AddGlue()
			.End()
		.SetInsets(spacing, spacing, spacing, spacing)
		.End();

	_UpdatePreferredFromLocaleRoster();
	SettingsReverted();
	CenterOnScreen();
}