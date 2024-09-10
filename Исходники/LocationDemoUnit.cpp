void __fastcall TForm2::LocationSensor1LocationChanged(TObject *Sender, const TLocationCoord2D &OldLocation,
          const TLocationCoord2D &NewLocation)
{
	WideChar LDecSeparator = FormatSettings.DecimalSeparator;
	TFormatSettings LSettings = FormatSettings;
	FormatSettings.DecimalSeparator = '.';
	// Show current location
	ListBoxItemLatitude->ItemData->Detail =
		ListBoxItemLatitude->ItemData->Detail.sprintf(L"%2.6f", NewLocation.Latitude);
	ListBoxItemLongitude->ItemData->Detail =
		ListBoxItemLongitude->ItemData->Detail.sprintf(L"%2.6f", NewLocation.Longitude);
	// Show Map using Google Maps
	auto LLongitude = FloatToStr(NewLocation.Longitude, LSettings);
	String URLString = "";
	URLString = URLString.sprintf(L"https://maps.google.com/maps?q=%2.6f,%2.6f&output=embed",
		NewLocation.Latitude, NewLocation.Longitude);

	FormatSettings.DecimalSeparator = LDecSeparator;
	WebBrowser1->Navigate(URLString);

	// Setup an instance of TGeocoder
	if (FGeocoder == NULL) {
		if (TGeocoder::Current != NULL) {
			FGeocoder = (TGeocoder*)new TGeocoderClass(TGeocoder::Current);
		}
		if (FGeocoder != NULL) {
			FGeocoder->OnGeocodeReverse = OnGeocodeReverseEvent;
		}
	}
	// Translate location to address
	if ((FGeocoder != NULL) && (FGeocoder->Geocoding)) {
		FGeocoder->GeocodeReverse(NewLocation);
	}
}