void
KPaletteTable::readNamedColor( void )
{
  if( mNamedColorList->count() != 0 )
  {
    return; // Strings already present
  }

  TDEGlobal::locale()->insertCatalogue("tdelibs_colors");

  //
  // Code somewhat inspired by KPalette.
  //

  const char * const *path = namedColorFilePath();
  for( int i=0; path[i]; ++i )
  {
    TQFile paletteFile( path[i] );
    if( !paletteFile.open( IO_ReadOnly ) )
    {
      continue;
    }

    TQString line;
    TQStringList list;
    while( paletteFile.readLine( line, 100 ) != -1 )
    {
      int red, green, blue;
      int pos = 0;

      if( sscanf(line.ascii(), "%d %d %d%n", &red, &green, &blue, &pos ) == 3 )
      {
	//
	// Remove duplicates. Every name with a space and every name
	// that start with "gray".
	//
	TQString name = line.mid(pos).stripWhiteSpace();
	if( name.isNull() || name.find(' ') != -1 ||
	    name.find( "gray" ) != -1 ||  name.find( "grey" ) != -1 )
	{
	  continue;
	}

        const TQColor color ( red, green, blue );
        if ( color.isValid() )
        {
            const TQString colorName( i18n("color", name.latin1() ) );
            list.append( colorName );
            d->m_namedColorMap[ colorName ] = color;
        }
      }
    }

    list.sort();
    mNamedColorList->insertStringList( list );
    break;
  }

  if( mNamedColorList->count() == 0 )
  {
    //
    // Give the error dialog box a chance to center above the
    // widget (or dialog). If we had displayed it now we could get a
    // situation where the (modal) error dialog box pops up first
    // preventing the real dialog to become visible until the
    // error dialog box is removed (== bad UI).
    //
    TQTimer::singleShot( 10, this, TQT_SLOT(slotShowNamedColorReadError()) );
  }
}