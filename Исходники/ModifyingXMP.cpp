/**
* Initializes the toolkit and attempts to open a file for updating its metadata. Initially
* an attempt to open the file is done with a handler, if this fails then the file is opened with
* packet scanning. Once the file is open several properties are read and displayed in the console.
*
* Several properties are then modified, first by checking for their existence and then, if they 
* exist, by updating their values. The updated properties are then displayed again in the console. 
*
* Next a new XMP object is created from an RDF stream, the properties from the new XMP object are
* appended to the original XMP object and the updated properties are displayed in the console for
* last time.
*
* The updated XMP object is then serialized in different formats and written to text files.  Lastly,
* the modified XMP is written back to the resource file.
*/
int main ( int argc, const char * argv[] )
{
	if ( argc != 2 ) // 2 := command and 1 parameter
	{
		cout << "usage: ModifyingXMP (filename)" << endl;
		return 0;
	}

	string filename = string( argv[1] );

	if(!SXMPMeta::Initialize())
	{
		cout << "Could not initialize toolkit!";
		return -1;
	}
	
	XMP_OptionBits options = 0;
	#if UNIX_ENV
		options |= kXMPFiles_ServerMode;
	#endif
		
	// Must initialize SXMPFiles before we use it
	if(SXMPFiles::Initialize(options))
	{
		try
		{
			// Options to open the file with - open for editing and use a smart handler
			XMP_OptionBits opts = kXMPFiles_OpenForUpdate | kXMPFiles_OpenUseSmartHandler;

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

			// If the file is open then read get the XMP data
			if(ok)
			{
				cout << status << endl;
				cout << filename << " is opened successfully" << endl;
				// Create the XMP object and get the XMP data
				SXMPMeta meta;
				myFile.GetXMP(&meta);

				// Display some properties in the console
				displayPropertyValues(&meta);
				
				///////////////////////////////////////////////////
				// Now modify the XMP
				if(meta.DoesPropertyExist(kXMP_NS_XMP, "CreatorTool"))
				{
					// Update xap:CreatorTool - we don't need to set any option bits
					meta.SetProperty(kXMP_NS_XMP, "CreatorTool", "Updated By XMP SDK", 0);
				}

				// Update the Metadata Date
				XMP_DateTime updatedTime;
				// Get the current time.  This is a UTC time automatically 
				// adjusted for the local time
				SXMPUtils::CurrentDateTime(&updatedTime);
				if(meta.DoesPropertyExist(kXMP_NS_XMP, "MetadataDate"))
				{
					meta.SetProperty_Date(kXMP_NS_XMP, "MetadataDate", updatedTime, 0);
				}
				
				// Add an item onto the dc:creator array
				// Note the options used, kXMP_PropArrayIsOrdered, if the array does not exist it will be created
				meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author Name", 0);
				meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Another Author Name", 0);

				// Now update alt-text properties
				meta.SetLocalizedText(kXMP_NS_DC, "title", "en", "en-US", "An English title");
				meta.SetLocalizedText(kXMP_NS_DC, "title", "fr", "fr-FR", "Un titre Francais");
				
				// Display the properties again to show changes
				cout << "After update:" << endl;
				displayPropertyValues(&meta);

				// Create a new XMP object from an RDF string
				SXMPMeta rdfMeta = createXMPFromRDF();

				// Append the newly created properties onto the original XMP object
				// This will:
				// a) Add ANY new TOP LEVEL properties in the source (rdfMeta) to the destination (meta)
				// b) Replace any top level properties in the source with the matching properties from the destination
				SXMPUtils::ApplyTemplate(&meta, rdfMeta, kXMPTemplate_AddNewProperties | kXMPTemplate_ReplaceExistingProperties | kXMPTemplate_IncludeInternalProperties);

				// Display the properties again to show changes
				cout << "After Appending Properties:" << endl;
				displayPropertyValues(&meta);

				// Serialize the packet and write the buffer to a file
				// Let the padding be computed and use the default linefeed and indents without limits
				string metaBuffer;
				meta.SerializeToBuffer(&metaBuffer, 0, 0, "", "", 0);

				// Write the packet to a file as RDF
				writeRDFToFile(&metaBuffer, filename+"_XMP_RDF.txt");
								
				// Write the packet to a file but this time as compact RDF
				XMP_OptionBits outOpts = kXMP_OmitPacketWrapper | kXMP_UseCompactFormat;
				meta.SerializeToBuffer(&metaBuffer, outOpts);
				writeRDFToFile(&metaBuffer, filename+"_XMP_RDF_Compact.txt");

				// Check we can put the XMP packet back into the file
				if(myFile.CanPutXMP(meta))
				{
					// If so then update the file with the modified XMP
					myFile.PutXMP(meta);
				}
			
				// Close the SXMPFile.  This *must* be called.  The XMP is not
				// actually written and the disk file is not closed until this call is made.
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

	}
	else
	{
		cout << "Could not initialize SXMPFiles.";
		return -1;
	}
	
	return 0;
}