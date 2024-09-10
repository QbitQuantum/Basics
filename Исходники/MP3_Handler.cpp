void MP3_MetaHandler::CacheFileData()
{

    //*** abort procedures
    this->containsXMP = false;		//assume no XMP for now

    XMP_IO* file = this->parent->ioRef;
    XMP_PacketInfo &packetInfo = this->packetInfo;

    file->Rewind();

    this->hasID3Tag = this->id3Header.read( file );
    this->majorVersion = this->id3Header.fields[ID3Header::o_vMajor];
    this->minorVersion = this->id3Header.fields[ID3Header::o_vMinor];
    this->hasExtHeader = (0 != ( 0x40 & this->id3Header.fields[ID3Header::o_flags])); //'naturally' false if no ID3Tag
    this->hasFooter = ( 0 != ( 0x10 & this->id3Header.fields[ID3Header::o_flags])); //'naturally' false if no ID3Tag

    // stored size is w/o initial header (thus adding 10)
    // + but extended header (if existing)
    // + padding + frames after unsynchronisation (?)
    // (if no ID3 tag existing, constructed default correctly sets size to 10.)
    this->oldTagSize = ID3Header::kID3_TagHeaderSize + synchToInt32(GetUns32BE( &id3Header.fields[ID3Header::o_size] ));

    if ( ! hasExtHeader ) {

        this->extHeaderSize = 0; // := there is no such header.

    } else {

        this->extHeaderSize = synchToInt32( XIO::ReadInt32_BE( file));
        XMP_Uns8 extHeaderNumFlagBytes = XIO::ReadUns8( file );

        // v2.3 doesn't include the size, while v2.4 does
        if ( this->majorVersion < 4 ) this->extHeaderSize += 4;
        XMP_Validate( this->extHeaderSize >= 6, "extHeader size too small", kXMPErr_BadFileFormat );

        file->Seek ( this->extHeaderSize - 6, kXMP_SeekFromCurrent );

    }

    this->framesVector.clear(); //mac precaution
    ID3v2Frame* curFrame = 0; // reusable

    ////////////////////////////////////////////////////
    // read frames

    XMP_Uns32 xmpID = XMP_V23_ID;
    if ( this->majorVersion == 2 ) xmpID = XMP_V22_ID;

    while ( file->Offset() < this->oldTagSize ) {

        curFrame = new ID3v2Frame();

        try {
            XMP_Int64 frameSize = curFrame->read ( file, this->majorVersion );
            if ( frameSize == 0 ) {
                delete curFrame; // ..since not becoming part of vector for latter delete.
                break;			 // not a throw. There's nothing wrong with padding.
            }
            this->containsXMP = true;
        } catch ( ... ) {
            delete curFrame;
            throw;
        }

        // these are both pointer assignments, no (copy) construction
        // (MemLeak Note: for all things pushed, memory cleanup is taken care of in destructor.)
        this->framesVector.push_back ( curFrame );

        //remember XMP-Frame, if it occurs:
        if ( (curFrame->id ==xmpID) &&
                (curFrame->contentSize > 8) && CheckBytes ( &curFrame->content[0], "XMP\0", 4 ) ) {

            // be sure that this is the first packet (all else would be illegal format)
            XMP_Validate ( this->framesMap[xmpID] == 0, "two XMP packets in one file", kXMPErr_BadFileFormat );
            //add this to map, needed on reconciliation
            this->framesMap[xmpID] = curFrame;

            this->packetInfo.length = curFrame->contentSize - 4; // content minus "XMP\0"
            this->packetInfo.offset = ( file->Offset() - this->packetInfo.length );

            this->xmpPacket.erase(); //safety
            this->xmpPacket.assign( &curFrame->content[4], curFrame->contentSize - 4 );
            this->containsXMP = true; // do this last, after all possible failure

        }

        // No space for another frame? => assume into ID3v2.4 padding.
        XMP_Int64 newPos = file->Offset();
        XMP_Int64 spaceLeft = this->oldTagSize - newPos;	// Depends on first check below!
        if ( (newPos > this->oldTagSize) || (spaceLeft < (XMP_Int64)ID3Header::kID3_TagHeaderSize) ) break;

    }

    ////////////////////////////////////////////////////
    // padding

    this->oldPadding = this->oldTagSize - file->Offset();
    this->oldFramesSize = this->oldTagSize - ID3Header::kID3_TagHeaderSize - this->oldPadding;

    XMP_Validate ( (this->oldPadding >= 0), "illegal oldTagSize or padding value", kXMPErr_BadFileFormat );

    for ( XMP_Int64 i = this->oldPadding; i > 0; ) {
        if ( i >= 8 ) {
            if ( XIO::ReadInt64_BE(file) != 0 ) XMP_Throw ( "padding not nulled out", kXMPErr_BadFileFormat );
            i -= 8;
            continue;
        }
        if ( XIO::ReadUns8(file) != 0) XMP_Throw ( "padding(2) not nulled out", kXMPErr_BadFileFormat );
        i--;
    }

    //// read ID3v1 tag
    if ( ! this->containsXMP ) this->containsXMP = id3v1Tag.read ( file, &this->xmpObj );

}	// MP3_MetaHandler::CacheFileData