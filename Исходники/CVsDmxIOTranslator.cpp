MStatus CVsDmxIOTranslator::writer(
	const MFileObject &i_mFileObject,
	const MString &i_optionsString,
	const FileAccessMode i_fileAccessMode )
{
	MString cmd( "vsDmxIO -export" );

	if ( i_optionsString.length() )
	{
		bool useTimeline( true );
		double fs( MAnimControl::minTime().as( MTime::uiUnit() ) );
		double fe( MAnimControl::maxTime().as( MTime::uiUnit() ) );
		double fi( 1.0 );

		MStringArray options;
		if ( !i_optionsString.split( ';', options ) )
		{
			merr << "Can't split " << s_name << " translator arguments" << std::endl;
			return MS::kFailure;
		}

		for ( unsigned int oi( 0 ); oi != options.length(); ++oi )
		{
			MStringArray keyValue;
			if ( options[ oi ].split( '=', keyValue ) && keyValue.length() == 2 )
			{
				const MString &key( keyValue[ 0 ] );
				const MString &val( keyValue[ 1 ] );

				if ( key == "useTimeline" )
				{
					useTimeline = val.asInt() ? true : false;
					continue;
				}

				if ( !useTimeline )
				{
					if ( key == "fs" )
					{
						fs = val.asDouble();
						continue;
					}

					if ( key == "fe" )
					{
						fe = val.asDouble();
						continue;
					}

					if ( key == "fi" )
					{
						fi = val.asDouble();
						continue;
					}
				}
			}	
		}

		if ( !useTimeline )
		{
			if ( fs > fe )
			{
				merr << "Invalid frame start " << fs << " > frame end " << fe << ", ignoring and using timeline" << std::endl;
			}
			else
			{
				cmd += " -time \"";
				cmd += fs;
				cmd += "-";
				cmd += fe;
				if ( fi <= 0 )
				{
					mwarn << "Invalid frame increment " << fi << " specified, using 1" << std::endl;
				}
				else
				{
					cmd += "x";
					cmd += fi;
				}
				cmd += "\"";
			}
		}
	}

	if ( i_fileAccessMode == MPxFileTranslator::kExportActiveAccessMode )
	{
		cmd += " -selection";
	}

	cmd += " -filename \"";
	cmd += i_mFileObject.fullName();
	cmd += "\";";

	return MGlobal::executeCommand( cmd, true, true );
}