/**
* Reads some metadata from a file and appends some custom XMP to it.  Then does several 
* iterations, using various iterators.  Each iteration is displayed in the console window.
*/
int main()
{
	if(SXMPMeta::Initialize())
	{
		XMP_OptionBits options = 0;
		#if UNIX_ENV
			options |= kXMPFiles_ServerMode;
		#endif
		if ( SXMPFiles::Initialize ( options ) ) {
			bool ok;
			SXMPFiles myFile;

			XMP_OptionBits opts = kXMPFiles_OpenForRead | kXMPFiles_OpenUseSmartHandler;
			ok = myFile.OpenFile("../../../testfiles/Image1.jpg", kXMP_UnknownFile, opts);
			if(ok)
			{
				SXMPMeta xmp;
				myFile.GetXMP(&xmp);

				// Add some custom metadata to the XMP object
				SXMPMeta custXMP(rdf, (XMP_StringLen) strlen(rdf));
				SXMPUtils::ApplyTemplate(&xmp, custXMP, kXMPTemplate_AddNewProperties);

				// Store any details from the iter.Next() call
				string schemaNS, propPath, propVal;

				// Only visit the immediate children that are leaf properties of the Dublin Core schema
				SXMPIterator dcLeafIter(xmp, kXMP_NS_DC, (kXMP_IterJustChildren | kXMP_IterJustLeafNodes));
				while(dcLeafIter.Next(&schemaNS, &propPath, &propVal))
				{
					cout << schemaNS << "  " << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Visit one property from the XMP Basic schema
				SXMPIterator xmpKeywordsIter(xmp, kXMP_NS_XMP, "Keywords", kXMP_IterJustLeafNodes);
				while(xmpKeywordsIter.Next(&schemaNS, &propPath, &propVal))
				{
					cout << schemaNS << "  " << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Visit the Dublin Core schema, omit any quailifiers and only
				// show the leaf properties
				SXMPIterator dcIter(xmp, kXMP_NS_DC, (kXMP_IterOmitQualifiers | kXMP_IterJustLeafNodes));
				while(dcIter.Next(&schemaNS, &propPath, &propVal))
				{
					cout << schemaNS << "  " << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Visit the Dublin Core schema, omit any quailifiers, 
				// show the leaf properties but only return the leaf name and not the full path
				SXMPIterator dcIter2(xmp, kXMP_NS_DC, (kXMP_IterOmitQualifiers | kXMP_IterJustLeafNodes | kXMP_IterJustLeafName));
				while(dcIter2.Next(&schemaNS, &propPath, &propVal))
				{
					cout << schemaNS << "  " << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Iterate over a single namespace.  Show all properties within
				// the Photoshop schema
				SXMPIterator exifIter(xmp, kXMP_NS_Photoshop);
				while(exifIter.Next(&schemaNS, &propPath, &propVal))
				{
					cout << schemaNS << "  " << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Just visit the leaf nodes of EXIF properties. That is just 
				// properties that may have values.
				SXMPIterator exifLeafIter(xmp, kXMP_NS_EXIF, kXMP_IterJustLeafNodes);
				while(exifLeafIter.Next(&schemaNS, &propPath, &propVal))
				{
					cout << schemaNS << "  " << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Iterate over all properties but skip the EXIF schema and skip the custom schema
				// and continue visiting nodes
				SXMPIterator skipExifIter (xmp);
				while(skipExifIter.Next(&schemaNS, &propPath, &propVal))
				{
					if(schemaNS == kXMP_NS_EXIF || schemaNS == kXMP_NS_SDK)
					{
						skipExifIter.Skip(kXMP_IterSkipSubtree);
					}
					else
					{ 
						cout << schemaNS << "  " << propPath << " = " << propVal << endl;
					}
				}

				cout << "----------------------------------" << endl;

				// Iterate over all properties but skip the EXIF schema
				// and any remaining siblings of the current node.
				SXMPIterator stopAfterExifIter ( xmp );
				while(stopAfterExifIter.Next(&schemaNS, &propPath, &propVal))
				{
					if(schemaNS == kXMP_NS_EXIF || schemaNS == kXMP_NS_SDK)
					{
						stopAfterExifIter.Skip(kXMP_IterSkipSiblings);
					}
					else
					{
						cout << schemaNS << "  " << propPath << " = " << propVal << endl;
					}
				}

				cout << "----------------------------------" << endl;

				//////////////////////////////////////////////////////////////////////////////////////

				// Iterate over the custom XMP

				// Visit the immediate children of this node. 
				// No qualifiers are visisted as they are below the property being visisted.
				SXMPIterator justChildrenIter(xmp, kXMP_NS_SDK, kXMP_IterJustChildren);
				while(justChildrenIter.Next(&schemaNS, &propPath, &propVal))
				{
					cout << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Visit the immediate children of this node but only those that may have values.
				// No qualifiers are visisted as they are below the property being visisted.
				SXMPIterator justChildrenAndLeafIter(xmp, kXMP_NS_SDK, (kXMP_IterJustChildren | kXMP_IterJustLeafNodes));
				while(justChildrenAndLeafIter.Next(&schemaNS, &propPath, &propVal))
				{
					cout << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Visit the leaf nodes of TopStructProperty
				SXMPIterator myTopStructIter(xmp, kXMP_NS_SDK, "MyTopStruct", kXMP_IterJustLeafNodes);
				while(myTopStructIter.Next(&schemaNS, &propPath, &propVal))
				{
					cout << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Visit the leaf nodes of the TopStructProperty but only return the names for 
				// the leaf components and not the full path
				SXMPIterator xmyTopStructIterShortNames(xmp, kXMP_NS_SDK, "MyTopStruct", (kXMP_IterJustLeafNodes | kXMP_IterJustLeafName));
				while(xmyTopStructIterShortNames.Next(&schemaNS, &propPath, &propVal))
				{
					cout << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Visit a property and all of the qualifiers
				SXMPIterator iterArrayProp (xmp, kXMP_NS_SDK, "ArrayWithStructures", kXMP_IterJustLeafNodes );
				while(iterArrayProp.Next(&schemaNS, &propPath, &propVal))
				{
					cout << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Visit a property and omit all of the qualifiers
				SXMPIterator iterArrayPropNoQual (xmp, kXMP_NS_SDK, "ArrayWithStructures", (kXMP_IterJustLeafNodes | kXMP_IterOmitQualifiers));
				while(iterArrayPropNoQual.Next(&schemaNS, &propPath, &propVal))
				{
					cout << propPath << " = " << propVal << endl;
				}

				cout << "----------------------------------" << endl;

				// Skip a subtree and continue onwards.  Once 'Item 4' is found then the we can skip all of the
				// siblings of the current node.  If the the current node were a top level node the iteration 
				// would be complete as all siblings would be skipped.  However, when 'Item 4' is found the current 
				// node is not at the top level so there are other nodes further up the tree that still need to be
				// visited.
				SXMPIterator skipIter (xmp, kXMP_NS_SDK, (kXMP_IterJustLeafNodes | kXMP_IterOmitQualifiers | kXMP_IterJustLeafName));
				while(skipIter.Next(&schemaNS, &propPath, &propVal))
				{
					if(propVal == "Item 4")
					{
						skipIter.Skip(kXMP_IterSkipSiblings);
					}
					else
					{
						cout << schemaNS << "  " << propPath << " = " << propVal << endl;
					}
				}

				/*
				// Visit all properties and qualifiers
				SXMPIterator allPropsIter(xmp);
				while(allPropsIter.Next(&schemaNS, &propPath, &propVal))
				{
					cout << schemaNS << "  " << propPath << " = " << propVal << endl;
				}
				*/
			}
		}
	}
	
	SXMPFiles::Terminate();
	SXMPMeta::Terminate();

	return 0;
}