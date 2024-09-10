//---------------------------------------------------------------------------
void __fastcall TForm6::OnGeocodeEvent(System::DynamicArray<TLocationCoord2D> Coords)
{
	if (Coords[0].Latitude!= 0 && Coords[0].Longitude != 0) {
		FoundLatitude = Coords[0].Latitude;
		FoundLongitude = Coords[0].Longitude;
		FoundAddrLatLong = true;
		LatLongLabel->Text =
		  FloatToStr(Coords[0].Latitude)
		  + ","
		  + FloatToStr(Coords[0].Longitude);
    	#if defined(TARGET_OS_IPHONE)
		FormatSettings.DecimalSeparator = '.';
		String URLString = "";
		URLString = URLString.sprintf(
			L"https://maps.google.com/maps?q=%2.6f,%2.6f",
			Coords[0].Latitude, Coords[0].Longitude);
		// FormatSettings.DecimalSeparator = LDecSeparator;
		WebBrowser1->Navigate(URLString);
		#endif
		RefreshButton->Visible = true;
	}
	else {
		FoundAddrLatLong = false;
		LatLongLabel->Text = "Address not Found!";
	}
}