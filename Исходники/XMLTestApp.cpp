void XMLTestApp::setup()
{
	XmlTree doc( loadFile( getAssetPath( "library.xml" ) ) );
	XmlTree musicLibrary( doc.getChild( "library" ) );
	for( XmlTree::ConstIter item = doc.begin("library/album"); item != doc.end(); ++item ) {
		console() << "Node: " << item->getTag() << " Value: " << item->getValue() << endl;
	}

	for( XmlTree::ConstIter track = doc.begin("library/album/track"); track != doc.end(); ++track )
		console() << track->getValue() << endl;

	assert( (musicLibrary / "album")["musician"] == "John Coltrane" );

	// test that /one/two is equivalent to one/two
	vector<string> noLeadingSeparator, leadingSeparator;
	for( XmlTree::ConstIter track = doc.begin("library/album/track"); track != doc.end(); ++track )
		noLeadingSeparator.push_back( track->getValue() );
	for( XmlTree::ConstIter track = doc.begin("/library/album/track"); track != doc.end(); ++track )
		leadingSeparator.push_back( track->getValue() );
	assert( noLeadingSeparator == leadingSeparator );

	XmlTree firstAlbum = doc.getChild( "library/album" );
	for( XmlTree::Iter child = firstAlbum.begin(); child != firstAlbum.end(); ++child ) {
		console() << "Tag: " << child->getTag() << "  Value: " << child->getValue() << endl;
	}
	console() << doc.getChild( "library/owner/city" );
	XmlTree ownerCity = doc.getChild( "///library/////owner/city" );
	console() << "Path: " << ownerCity.getPath() << "  Value: " << ownerCity.getValue() << std::endl;
	console() << doc;
	
	console() << findTrackNamed( doc.getChild( "library" ), "Wolf" );
	
	// Whoops - assignment by value doesn't modifying the original XmlTree
	XmlTree firstTrackCopy = doc.getChild( "/library/album/track" );
	firstTrackCopy.setValue( "Replacement name" );
	console() << doc.getChild( "/library/album/track" ) << std::endl;

	XmlTree &firstTrackRef = doc.getChild( "/library/album/track" );
	firstTrackRef.setValue( "Replacement name" );
	console() << doc.getChild( "/library/album/track" ) << std::endl;

	XmlTree albumCopy = copyFirstAlbum( doc / "library" );
	console() << ( albumCopy / "track" ).getPath() << std::endl; // should print 'newRoot/track'

	// This code only works in VC2010
/*	std::for_each( doc.begin( "library/album" ), doc.end(), []( const XmlTree &child ) {
		app::console() << child.getChild( "title" ).getValue() << std::endl;
	} );*/
}