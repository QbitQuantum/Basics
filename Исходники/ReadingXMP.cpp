/**
*	Initializes the toolkit and attempts to open a file for reading metadata.  Initially
* an attempt to open the file is done with a handler, if this fails then the file is opened with
* packet scanning. Once the file is open several properties are read and displayed in the console.  
* The XMP object is then dumped to a text file and the resource file is closed.
*/
int main ( int argc, const char * argv[] )
{
	if ( argc != 2 ) // 2 := command and 1 parameter
	{
		cout << "usage: ReadingXMP (filename)" << endl;
		return 0;
	}
	
	string filename = string( argv[1] );

	if(!SXMPMeta::Initialize())
	{
		cout << "Could not initialize toolkit!";
		return -1;
	}
	
	// Must initialize SXMPFiles before we use it
	if ( ! SXMPFiles::Initialize() )
	{
		cout << "Could not initialize SXMPFiles.";
		return -1;
	}
	
	try
	{
		// Options to open the file with - read only and use a file handler
		XMP_OptionBits opts = kXMPFiles_OpenForRead | kXMPFiles_OpenUseSmartHandler;

		bool ok;
		SXMPFiles myFile;			
		std::string status = "";

		// First we try and open the file
		ok = myFile.OpenFile(filename, kXMP_UnknownFile, opts);
		if( ! ok )
		{
			status += "No smart handler available for " + filename + "\n";
			status += "Trying packet scanning.\n";

			// Now try using packet scanning
			opts = kXMPFiles_OpenForUpdate | kXMPFiles_OpenUsePacketScanning;
			ok = myFile.OpenFile(filename, kXMP_UnknownFile, opts);
		}


		// If the file is open then read the metadata
		if(ok)
		{
			cout << status << endl;
			cout << filename << " is opened successfully" << endl;
			// Create the xmp object and get the xmp data
			SXMPMeta meta;
			myFile.GetXMP(&meta);

			bool exists;

			// Read a simple property
			string simpleValue;  //Stores the value for the property
			exists = meta.GetProperty(kXMP_NS_XMP, "CreatorTool", &simpleValue, NULL);
			if(exists)
				cout << "CreatorTool = " << simpleValue << endl;
			else
				simpleValue.clear();

			// Get the first element in the dc:creator array
			string elementValue;
			exists = meta.GetArrayItem(kXMP_NS_DC, "creator", 1, &elementValue, NULL);
			if(exists)
				cout << "dc:creator = " << elementValue << endl;
			else
				elementValue.clear();

			// Get the the entire dc:subject array 
			string propValue;
			int arrSize = meta.CountArrayItems(kXMP_NS_DC, "subject");
			for(int i = 1; i <= arrSize;i++)
			{
				meta.GetArrayItem(kXMP_NS_DC, "subject", i, &propValue, 0);
				cout << "dc:subject[" << i << "] = " << propValue << endl;
			}

			// Get the dc:title for English and French
			string itemValue;
			string actualLang;
			meta.GetLocalizedText(kXMP_NS_DC, "title", "en", "en-US", NULL, &itemValue, NULL);
			cout << "dc:title in English = " << itemValue << endl;

			meta.GetLocalizedText(kXMP_NS_DC, "title", "fr", "fr-FR", NULL, &itemValue, NULL);
			cout << "dc:title in French = " << itemValue << endl;

			// Get dc:MetadataDate
			XMP_DateTime myDate;
			if(meta.GetProperty_Date(kXMP_NS_XMP, "MetadataDate", &myDate, NULL))
			{
				// Convert the date struct into a convenient string and display it
				string myDateStr;
				SXMPUtils::ConvertFromDate(myDate, &myDateStr);
				cout << "meta:MetadataDate = " << myDateStr << endl;						 
			}

			// See if the flash struct exists and see if it was used
			string path, value;
			exists = meta.DoesStructFieldExist(kXMP_NS_EXIF, "Flash", kXMP_NS_EXIF,"Fired");
			if(exists)
			{
				bool flashFired;
				SXMPUtils::ComposeStructFieldPath(kXMP_NS_EXIF, "Flash", kXMP_NS_EXIF, "Fired", &path);
				meta.GetProperty_Bool(kXMP_NS_EXIF, path.c_str(), &flashFired, NULL);
				string flash = (flashFired) ? "True" : "False";

				cout << "Flash Used = " << flash << endl;
			}

			// Dump the current xmp object to a file
			ofstream dumpFile;
			dumpFile.open("XMPDump.txt", ios::out);
			meta.DumpObject(DumpXMPToFile, &dumpFile);
			dumpFile.close();
			cout << endl << "XMP dumped to XMPDump.txt" << endl;

			// Close the SXMPFile.  The resource file is already closed if it was
			// opened as read only but this call must still be made.
			myFile.CloseFile();
		}
		else
		{
			cout << "Unable to open " << filename << endl;
		}
	}
	catch(XMP_Error & e)
	{
		cout << "ERROR: " << e.GetErrMsg() << endl;
	}

	// Terminate the toolkit
	SXMPFiles::Terminate();
	SXMPMeta::Terminate();

	return 0;
}