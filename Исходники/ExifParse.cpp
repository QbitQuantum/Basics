//--------------------------------------------------------------------------
// Process one of the nested EXIF directories.
//--------------------------------------------------------------------------
void CExifParse::ProcessDir(const unsigned char* const DirStart,
                            const unsigned char* const OffsetBase,
                            const unsigned ExifLength,
                            int NestingLevel)
{
  if (NestingLevel > 4)
  {
    ErrNonfatal("Maximum directory nesting exceeded (corrupt exif header)", 0,0);
    return;
  }

  char IndentString[25];
  memset(IndentString, ' ', 25);
  IndentString[NestingLevel * 4] = '\0';


  int NumDirEntries = Get16((void*)DirStart, m_MotorolaOrder);

  const unsigned char* const DirEnd = DIR_ENTRY_ADDR(DirStart, NumDirEntries);
  if (DirEnd+4 > (OffsetBase+ExifLength))
  {
    if (DirEnd+2 == OffsetBase+ExifLength || DirEnd == OffsetBase+ExifLength)
    {
      // Version 1.3 of jhead would truncate a bit too much.
      // This also caught later on as well.
    }
    else
    {
      ErrNonfatal("Illegally sized directory", 0,0);
      return;
    }
  }

  for (int de=0;de<NumDirEntries;de++)
  {
    int Tag, Format, Components;
    unsigned char* ValuePtr;
    int ByteCount;
    const unsigned char* const DirEntry = DIR_ENTRY_ADDR(DirStart, de);

    Tag = Get16(DirEntry, m_MotorolaOrder);
    Format = Get16(DirEntry+2, m_MotorolaOrder);
    Components = Get32(DirEntry+4, m_MotorolaOrder);

    if (Format <= 0 || Format > NUM_FORMATS)
    {
      ErrNonfatal("Illegal number format %d for tag %04x", Format, Tag);
      continue;
    }

    if ((unsigned)Components > 0x10000)
    {
      ErrNonfatal("Illegal number of components %d for tag %04x", Components, Tag);
      continue;
    }

    ByteCount = Components * BytesPerFormat[Format - 1];

    if (ByteCount > 4)
    {
      unsigned OffsetVal;
      OffsetVal = (unsigned)Get32(DirEntry+8, m_MotorolaOrder);
      // If its bigger than 4 bytes, the dir entry contains an offset.
      if (OffsetVal+ByteCount > ExifLength)
      {
        // Bogus pointer offset and / or bytecount value
        ErrNonfatal("Illegal value pointer for tag %04x", Tag,0);
        continue;
      }
      ValuePtr = (unsigned char*)(OffsetBase+OffsetVal);

      if (OffsetVal > m_LargestExifOffset)
      {
        m_LargestExifOffset = OffsetVal;
      }

    }
    else {
      // 4 bytes or less and value is in the dir entry itself
      ValuePtr = (unsigned char*)(DirEntry+8);
    }


    // Extract useful components of tag
    switch(Tag)
    {
      case TAG_DESCRIPTION:
      {
        int length = max(ByteCount, 0);
        length = min(length, MAX_COMMENT);
        strncpy(m_ExifInfo->Description, (char *)ValuePtr, length);
        m_ExifInfo->Description[length] = '\0';
        break;
      }
      case TAG_MAKE:
      {
        int space = sizeof(m_ExifInfo->CameraMake);
        if (space > 0)
        {
          strncpy(m_ExifInfo->CameraMake, (char *)ValuePtr, space - 1);
          m_ExifInfo->CameraMake[space - 1] = '\0';
        }
        break;
      }
      case TAG_MODEL:
      {
        int space = sizeof(m_ExifInfo->CameraModel);
        if (space > 0)
        {
          strncpy(m_ExifInfo->CameraModel, (char *)ValuePtr, space - 1);
          m_ExifInfo->CameraModel[space - 1] = '\0';
        }
        break;
      }
//      case TAG_SOFTWARE:          strncpy(m_ExifInfo->Software, ValuePtr, 5);    break;
      case TAG_FOCALPLANEXRES:    m_FocalPlaneXRes  = ConvertAnyFormat(ValuePtr, Format);               break;
      case TAG_THUMBNAIL_OFFSET:  m_ExifInfo->ThumbnailOffset = (unsigned)ConvertAnyFormat(ValuePtr, Format);     break;
      case TAG_THUMBNAIL_LENGTH:  m_ExifInfo->ThumbnailSize   = (unsigned)ConvertAnyFormat(ValuePtr, Format);     break;

      case TAG_MAKER_NOTE:
        continue;
      break;

      case TAG_DATETIME_ORIGINAL:
      {

        int space = sizeof(m_ExifInfo->DateTime);
        if (space > 0)
        {
          strncpy(m_ExifInfo->DateTime, (char *)ValuePtr, space - 1);
          m_ExifInfo->DateTime[space - 1] = '\0';
          // If we get a DATETIME_ORIGINAL, we use that one.
          m_DateFound = true;
        }
        break;
      }
      case TAG_DATETIME_DIGITIZED:
      case TAG_DATETIME:
      {
        if (m_DateFound == false)
        {
          // If we don't already have a DATETIME_ORIGINAL, use whatever
          // time fields we may have.
          int space = sizeof(m_ExifInfo->DateTime);
          if (space > 0)
          {
            strncpy(m_ExifInfo->DateTime, (char *)ValuePtr, space - 1);
            m_ExifInfo->DateTime[space - 1] = '\0';
          }
        }
        break;
      }
      case TAG_USERCOMMENT:
      {
        // The UserComment allows comments without the charset limitations of ImageDescription.
        // Therefore the UserComment field is prefixed by a CharacterCode field (8 Byte):
        //  - ASCII:         'ASCII\0\0\0'
        //  - Unicode:       'UNICODE\0'
        //  - JIS X208-1990: 'JIS\0\0\0\0\0'
        //  - Unknown:       '\0\0\0\0\0\0\0\0' (application specific)

        m_ExifInfo->CommentsCharset = EXIF_COMMENT_CHARSET_UNKNOWN;

        const int EXIF_COMMENT_CHARSET_LENGTH = 8;
        if (ByteCount >= EXIF_COMMENT_CHARSET_LENGTH)
        {
          // As some implementations use spaces instead of \0 for the padding,
          // we're not so strict and check only the prefix.
          if (memcmp(ValuePtr, "ASCII", 5) == 0)
            m_ExifInfo->CommentsCharset = EXIF_COMMENT_CHARSET_ASCII;
          else if (memcmp(ValuePtr, "UNICODE", 7) == 0)
            m_ExifInfo->CommentsCharset = EXIF_COMMENT_CHARSET_UNICODE;
          else if (memcmp(ValuePtr, "JIS", 3) == 0)
            m_ExifInfo->CommentsCharset = EXIF_COMMENT_CHARSET_JIS;

          int length = ByteCount - EXIF_COMMENT_CHARSET_LENGTH;
          length = min(length, MAX_COMMENT);
          memcpy(m_ExifInfo->Comments, ValuePtr + EXIF_COMMENT_CHARSET_LENGTH, length);
          m_ExifInfo->Comments[length] = '\0';
//          FixComment(comment);                          // Ensure comment is printable
        }
      }
      break;

      case TAG_XP_COMMENT:
      {
        // The XP user comment field is always unicode (UCS-2) encoded
        m_ExifInfo->XPCommentsCharset = EXIF_COMMENT_CHARSET_UNICODE;
        size_t length = min(ByteCount, MAX_COMMENT);
        memcpy(m_ExifInfo->XPComment, ValuePtr, length);
        m_ExifInfo->XPComment[length] = '\0';
      }
      break;

      case TAG_FNUMBER:
        // Simplest way of expressing aperture, so I trust it the most.
        // (overwrite previously computd value if there is one)
        m_ExifInfo->ApertureFNumber = (float)ConvertAnyFormat(ValuePtr, Format);
      break;

      case TAG_APERTURE:
      case TAG_MAXAPERTURE:
        // More relevant info always comes earlier, so only use this field if we don't
        // have appropriate aperture information yet.
        if (m_ExifInfo->ApertureFNumber == 0)
        {
          m_ExifInfo->ApertureFNumber = (float)exp(ConvertAnyFormat(ValuePtr, Format)*log(2.0)*0.5);
        }
      break;

      case TAG_FOCALLENGTH:
        // Nice digital cameras actually save the focal length as a function
        // of how far they are zoomed in.
        m_ExifInfo->FocalLength = (float)ConvertAnyFormat(ValuePtr, Format);
      break;

      case TAG_SUBJECT_DISTANCE:
        // Inidcates the distacne the autofocus camera is focused to.
        // Tends to be less accurate as distance increases.
        {
          float distance = (float)ConvertAnyFormat(ValuePtr, Format);
          m_ExifInfo->Distance = distance;
        }
      break;

      case TAG_EXPOSURETIME:
        {
        // Simplest way of expressing exposure time, so I trust it most.
        // (overwrite previously computd value if there is one)
        float expTime = (float)ConvertAnyFormat(ValuePtr, Format);
        if (expTime)
          m_ExifInfo->ExposureTime = expTime;
        }
      break;

      case TAG_SHUTTERSPEED:
        // More complicated way of expressing exposure time, so only use
        // this value if we don't already have it from somewhere else.
        if (m_ExifInfo->ExposureTime == 0)
        {
          m_ExifInfo->ExposureTime = (float)(1/exp(ConvertAnyFormat(ValuePtr, Format)*log(2.0)));
        }
      break;

      case TAG_FLASH:
        m_ExifInfo->FlashUsed = (int)ConvertAnyFormat(ValuePtr, Format);
      break;

      case TAG_ORIENTATION:
        m_ExifInfo->Orientation = (int)ConvertAnyFormat(ValuePtr, Format);
        if (m_ExifInfo->Orientation < 0 || m_ExifInfo->Orientation > 8)
        {
          ErrNonfatal("Undefined rotation value %d", m_ExifInfo->Orientation, 0);
          m_ExifInfo->Orientation = 0;
        }
      break;

      case TAG_EXIF_IMAGELENGTH:
      case TAG_EXIF_IMAGEWIDTH:
        // Use largest of height and width to deal with images that have been
        // rotated to portrait format.
        {
          int a = (int)ConvertAnyFormat(ValuePtr, Format);
          if (m_ExifImageWidth < a) m_ExifImageWidth = a;
        }
      break;

      case TAG_FOCALPLANEUNITS:
        switch((int)ConvertAnyFormat(ValuePtr, Format))
        {
          // According to the information I was using, 2 means meters.
          // But looking at the Cannon powershot's files, inches is the only
          // sensible value.
          case 1: m_FocalPlaneUnits = 25.4; break;  // inch
          case 2: m_FocalPlaneUnits = 25.4; break;
          case 3: m_FocalPlaneUnits = 10;   break;  // centimeter
          case 4: m_FocalPlaneUnits = 1;    break;  // millimeter
          case 5: m_FocalPlaneUnits = .001; break;  // micrometer
        }
      break;

      case TAG_EXPOSURE_BIAS:
        m_ExifInfo->ExposureBias = (float)ConvertAnyFormat(ValuePtr, Format);
      break;

      case TAG_WHITEBALANCE:
        m_ExifInfo->Whitebalance = (int)ConvertAnyFormat(ValuePtr, Format);
      break;

      case TAG_LIGHT_SOURCE:
        //Quercus: 17-1-2004 Added LightSource, some cams return this, whitebalance or both
        m_ExifInfo->LightSource = (int)ConvertAnyFormat(ValuePtr, Format);
      break;

      case TAG_METERING_MODE:
        m_ExifInfo->MeteringMode = (int)ConvertAnyFormat(ValuePtr, Format);
      break;

      case TAG_EXPOSURE_PROGRAM:
        m_ExifInfo->ExposureProgram = (int)ConvertAnyFormat(ValuePtr, Format);
      break;

      case TAG_EXPOSURE_INDEX:
        if (m_ExifInfo->ISOequivalent == 0)
        {
          // Exposure index and ISO equivalent are often used interchangeably,
          // so we will do the same.
          // http://photography.about.com/library/glossary/bldef_ei.htm
          m_ExifInfo->ISOequivalent = (int)ConvertAnyFormat(ValuePtr, Format);
        }
      break;

      case TAG_ISO_EQUIVALENT:
        m_ExifInfo->ISOequivalent = (int)ConvertAnyFormat(ValuePtr, Format);
        if (m_ExifInfo->ISOequivalent < 50)
          m_ExifInfo->ISOequivalent *= 200;          // Fixes strange encoding on some older digicams.
      break;

      case TAG_EXPOSURE_MODE:
        m_ExifInfo->ExposureMode = (int)ConvertAnyFormat(ValuePtr, Format);
      break;

      case TAG_DIGITALZOOMRATIO:
        m_ExifInfo->DigitalZoomRatio = (float)ConvertAnyFormat(ValuePtr, Format);
      break;

      case TAG_EXIF_OFFSET:
      case TAG_INTEROP_OFFSET:
      {
        const unsigned char* const SubdirStart = OffsetBase + (unsigned)Get32(ValuePtr, m_MotorolaOrder);
        if (SubdirStart < OffsetBase || SubdirStart > OffsetBase+ExifLength)
        {
          ErrNonfatal("Illegal exif or interop ofset directory link",0,0);
        }
        else
        {
          ProcessDir(SubdirStart, OffsetBase, ExifLength, NestingLevel+1);
        }
        continue;
      }
      break;

      case TAG_GPSINFO:
      {
        const unsigned char* const SubdirStart = OffsetBase + (unsigned)Get32(ValuePtr, m_MotorolaOrder);
        if (SubdirStart < OffsetBase || SubdirStart > OffsetBase+ExifLength)
        {
          ErrNonfatal("Illegal GPS directory link",0,0);
        }
        else
        {
          ProcessGpsInfo(SubdirStart, ByteCount, OffsetBase, ExifLength);
        }
        continue;
      }
      break;

      case TAG_FOCALLENGTH_35MM:
        // The focal length equivalent 35 mm is a 2.2 tag (defined as of April 2002)
        // if its present, use it to compute equivalent focal length instead of
        // computing it from sensor geometry and actual focal length.
        m_ExifInfo->FocalLength35mmEquiv = (unsigned)ConvertAnyFormat(ValuePtr, Format);
      break;
    }
  }


  // In addition to linking to subdirectories via exif tags,
  // there's also a potential link to another directory at the end of each
  // directory.  this has got to be the result of a committee!
  unsigned Offset;

  if (DIR_ENTRY_ADDR(DirStart, NumDirEntries) + 4 <= OffsetBase+ExifLength)
  {
    Offset = (unsigned)Get32(DirStart+2+12*NumDirEntries, m_MotorolaOrder);
    if (Offset)
    {
      const unsigned char* const SubdirStart = OffsetBase + Offset;
      if (SubdirStart > OffsetBase+ExifLength || SubdirStart < OffsetBase)
      {
        if (SubdirStart > OffsetBase && SubdirStart < OffsetBase+ExifLength+20)
        {
          // Jhead 1.3 or earlier would crop the whole directory!
          // As Jhead produces this form of format incorrectness,
          // I'll just let it pass silently
        }
        else
        {
          ErrNonfatal("Illegal subdirectory link",0,0);
        }
      }
      else
      {
        if (SubdirStart <= OffsetBase+ExifLength)
        {
          ProcessDir(SubdirStart, OffsetBase, ExifLength, NestingLevel+1);
        }
      }
      if (Offset > m_LargestExifOffset)
      {
        m_LargestExifOffset = Offset;
      }
    }
  }
  else
  {
    // The exif header ends before the last next directory pointer.
  }

  if (m_ExifInfo->ThumbnailOffset)
  {
    m_ExifInfo->ThumbnailAtEnd = false;

    if (m_ExifInfo->ThumbnailOffset <= ExifLength)
    {
      if (m_ExifInfo->ThumbnailSize > ExifLength - m_ExifInfo->ThumbnailOffset)
      {
        // If thumbnail extends past exif header, only save the part that
        // actually exists.  Canon's EOS viewer utility will do this - the
        // thumbnail extracts ok with this hack.
        m_ExifInfo->ThumbnailSize = ExifLength - m_ExifInfo->ThumbnailOffset;
      }
    }
  }
}