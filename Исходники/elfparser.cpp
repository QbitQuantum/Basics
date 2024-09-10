bool ElfParser::ParseFileText( const QStringList &strs, const QStringList &sectionStrs, const QStringList &symbolStrs, ElfParser::File &file )
{
	quint32 cnt = strs.size();

	quint32 fOff = 0;
	quint32 fStart = 0;

	QString name;
	QString pattern;
	QList< SymRef > refs;

	//DBG << file.Name() << sectionStrs.size() << symbolStrs.size() << strs.size();
	QMap< QString, QByteArray >sections = ParseSectionText( sectionStrs );
	QList< SymAlias > aliases = ParseSymbolTable( symbolStrs );


	//DBG << file.Name() << sections.size() << aliases.size();

	for( quint32 i = 0; i < cnt; i++ )
	{
		const QString &str = strs.at( i );
		/*if( name == "WII_Initialize" )
  {
   qDebug() << str;
  }*/

		// start a new funciton
		if( IsFunctionStart( str, &fStart ) )
		{
			// add this function to the list
			if( !name.isEmpty() && fOff )
			{
				Function fun( name );
				fun.references = refs;
				fun.pattern = pattern;
				fun.file = &file;
				file.functions << fun;
				//qDebug() << "pattern:" << pattern;
			}
			//qDebug() << GetFunctionName( str );
			name = GetFunctionName( str );
			//DBG << name;
			if( fOff != (quint32)pattern.size() / 2 )
			{
				qDebug() << "size bad";
				exit( 0 );
			}
			fOff = 0;
			pattern.clear();
			refs.clear();

			sections.remove( name );// remove functions from the section list
			continue;
		}
		if( name.isEmpty() )
		{
			continue;
		}
		if( IsBlank( str ) )
		{
			//qDebug() << str << "is blank";
			continue;
		}
		if( IsSymbolLine( str ) )
		{
			//qDebug() << str << "IsSymbolLine";
			continue;
		}
		QString hex;
		QString oper;
		QString symbol;
		quint32 refOff = 0xdeadbeef;

		if( !ParseOpLine( str, hex, oper ) )
		{
			qDebug() << str << strs.at( i - 1 );
			return false;
		}
		/*if( name == "WII_Initialize" )
  {
   qDebug() << "hex" << hex;
  }*/

		if( ( i < cnt - 1 ) && IsSymbolLine( strs.at( i + 1 ) ) )
		{
			SymRef::Type refType;
			symbol = GetNonOperRef( strs.at( i + 1 ), &refOff, &refType );

			if( refOff < fStart )
			{
				WRN << "refOff < fStart" << str;
				return false;
			}
			SymRef ref;
			quint32 deRef;
			ref.name = DeReferenceSymbol( symbol, &deRef );
			ref.symOff = deRef;

			switch( refType )
			{
			case SymRef::R_PPC_ADDR16_HA:
			case SymRef::R_PPC_ADDR16_HI:
			case SymRef::R_PPC_ADDR16_LO:
			{
				hex[ 4 ] = '.';
				hex[ 5 ] = '.';
				hex[ 6 ] = '.';
				hex[ 7 ] = '.';
			}
			break;
			case SymRef::R_PPC_REL24:
			case SymRef::R_PPC_EMB_SDA21:
			{
				hex[ 1 ] = '.';
				hex[ 2 ] = '.';
				hex[ 3 ] = '.';
				hex[ 4 ] = '.';
				hex[ 5 ] = '.';
				hex[ 6 ] = '.';
				hex[ 7 ] = '.';
			}
			break;
			case SymRef::R_PPC_SDAREL16:
			{
				hex = "........";
			}
			break;
			default:
				WRN << "unhandled reference type";
				return false;
				break;
			}

			ref.type = refType;
			ref.off = refOff - fStart;
			refs << ref;
			if( ref.off & 0xff000000 )
			{
				qDebug() << "ref.off is busted 1" << name << str;

				qDebug() << ::hex << refOff << fStart;
				exit( 0 );
			}
		}

		else if( OpNeedsWildCard( oper ) )
		{
			//DBG << "bl called without symbol reference\n" << str;
			hex = "........";
			if( symbol.isEmpty() )
			{
				symbol = GetOpersymRef( str );
			}
			SymRef ref;
			ref.name = symbol;
			ref.off = (quint32)(pattern.size());
			ref.type = SymRef::R_PPC_REL24;
			refs << ref;

			if( ref.off & 0xff000000 )
			{
				DBG << "ref.off is busted 2" << name << str;
				exit( 0 );
			}

		}
		pattern += hex.toUpper();
		/*if( name == "WII_Initialize" )
  {
   qDebug() << "hex" << pattern;
  }*/
		fOff += 4;
	}
	if( !name.isEmpty() )
	{
		Function fun( name );
		fun.references = refs;
		fun.pattern = pattern;
		fun.file = &file;
		file.functions << fun;
	}
	file.sections = sections;
	file.aliases = aliases;
	return true;
}