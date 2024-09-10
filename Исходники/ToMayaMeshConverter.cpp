void ToMayaMeshConverter::addUVSet( MFnMesh &fnMesh, const MIntArray &polygonCounts, IECore::ConstMeshPrimitivePtr mesh, const std::string &sPrimVarName, const std::string &tPrimVarName, const std::string &stIdPrimVarName, MString *uvSetName ) const
{
	IECore::PrimitiveVariableMap::const_iterator sIt = mesh->variables.find( sPrimVarName );
	bool haveS = sIt != mesh->variables.end();
	IECore::PrimitiveVariableMap::const_iterator tIt = mesh->variables.find( tPrimVarName );
	bool haveT = tIt != mesh->variables.end();
	IECore::PrimitiveVariableMap::const_iterator stIdIt = mesh->variables.find( stIdPrimVarName );
	bool haveSTId = stIdIt != mesh->variables.end();

	if ( haveS && haveT )
	{
		if ( sIt->second.interpolation != IECore::PrimitiveVariable::FaceVarying )
		{
			IECore::msg( IECore::Msg::Warning,"ToMayaMeshConverter::doConversion",  boost::format(  "PrimitiveVariable \"%s\" has unsupported interpolation (expected FaceVarying).") % sPrimVarName );
			return;
		}

		if ( tIt->second.interpolation != IECore::PrimitiveVariable::FaceVarying )
		{
			IECore::msg( IECore::Msg::Warning, "ToMayaMeshConverter::doConversion", boost::format( "PrimitiveVariable \"%s\" has unsupported interpolation (expected FaceVarying).") % tPrimVarName);
			return;
		}

		if ( !sIt->second.data )
		{
			IECore::msg( IECore::Msg::Warning, "ToMayaMeshConverter::doConversion", boost::format( "PrimitiveVariable \"%s\" has no data." ) % sPrimVarName );
		}

		if ( !tIt->second.data )
		{
			IECore::msg( IECore::Msg::Warning, "ToMayaMeshConverter::doConversion", boost::format( "PrimitiveVariable \"%s\" has no data." ) % tPrimVarName );
		}

		/// \todo Employ some M*Array converters to simplify this
		int numUVs = mesh->variableSize( IECore::PrimitiveVariable::FaceVarying );

		IECore::ConstFloatVectorDataPtr u = IECore::runTimeCast<const IECore::FloatVectorData>(sIt->second.data);

		if ( !u )
		{
			IECore::msg( IECore::Msg::Warning, "ToMayaMeshConverter::doConversion", boost::format( "PrimitiveVariable \"%s\" has unsupported type \"%s\"." ) % sPrimVarName % sIt->second.data->typeName() );
			return;
		}

		assert( (int)u->readable().size() == numUVs );
		
		IECore::ConstFloatVectorDataPtr v = IECore::runTimeCast<const IECore::FloatVectorData>(tIt->second.data);
		if ( !v )
		{
			IECore::msg( IECore::Msg::Warning, "ToMayaMeshConverter::doConversion", boost::format( "PrimitiveVariable \"%s\" has unsupported type \"%s\"." ) % tPrimVarName % tIt->second.data->typeName() );
			return;
		}

		assert( (int)v->readable().size() == numUVs );
		
		const std::vector<float> &uAll = u->readable();
		const std::vector<float> &vAll = v->readable();

		if ( uvSetName )
		{
			bool setExists = false;
			MStringArray existingSets;
			fnMesh.getUVSetNames( existingSets );
			for ( unsigned i=0; i < existingSets.length(); ++i )
			{
				if ( *uvSetName == existingSets[i] )
				{
					fnMesh.clearUVs( uvSetName );
					setExists = true;
					break;
				}
			}
			
			if ( !setExists )
			{
				MDagPath dag;
				MStatus s = fnMesh.getPath( dag );
				if ( s )
				{
					fnMesh.createUVSetWithName( *uvSetName );
				}
				else
				{
					fnMesh.createUVSetDataMeshWithName( *uvSetName );
				}
			}
		}
		
		MIntArray uvIds;
		uvIds.setLength( numUVs );
		MFloatArray uArray;
		MFloatArray vArray;
		
		if( haveSTId )
		{
			// Get compressed uv values by matching them with their uvId.
			IECore::ConstIntVectorDataPtr uvId = IECore::runTimeCast<const IECore::IntVectorData>(stIdIt->second.data);
			if ( !uvId )
			{
				IECore::msg( IECore::Msg::Warning, "ToMayaMeshConverter::doConversion", boost::format( "PrimitiveVariable \"%s\" has unsupported type \"%s\"." ) % stIdPrimVarName % stIdIt->second.data->typeName() );
				return;
			}
			
			const std::vector<int> &uvIdData = uvId->readable();
	
			assert( (int)uvIdData.size() == numUVs );
			
			int highestId = 0;
			for ( int i = 0; i < numUVs; i++)
			{
				uvIds[i] = uvIdData[i];
				if( uvIdData[i] > highestId )
				{
					highestId = uvIdData[i];
				}
			}
			
			// u and v arrays need only be as long as the number of unique uvIds
			uArray.setLength( highestId + 1 );
			vArray.setLength( highestId + 1 );
			
			for ( int i = 0; i < numUVs; i++ )
			{
				uArray[ uvIds[i] ] = uAll[i];
				// FromMayaMeshConverter does the opposite of this
				vArray[ uvIds[i] ] = 1 - vAll[i];
			}
		}
		else
		{
			// If for some reason we cannot find the uv indices, set the UVs using the old way
			// the performances in maya won't be good (for weigth painting in particular)
			uArray.setLength( numUVs );
			vArray.setLength( numUVs );

			for ( int i = 0; i < numUVs; i++)
			{
				uArray[i] = u->readable()[i];
				// FromMayaMeshConverter does the opposite of this
				vArray[i] = 1 - v->readable()[i];
			}
			
			for ( int i = 0; i < numUVs; i++)
			{
				uvIds[i] = i;
			}
		}
		
		MStatus s = fnMesh.setUVs( uArray, vArray, uvSetName );
		if ( !s )
		{
			IECore::msg( IECore::Msg::Warning, "ToMayaMeshConverter::doConversion", "Failed to set UVs." );
			return;
		}

		s = fnMesh.assignUVs( polygonCounts, uvIds, uvSetName );
		if ( !s )
		{
			IECore::msg( IECore::Msg::Warning, "ToMayaMeshConverter::doConversion", "Failed to assign UVs." );
			return;
		}

	}
	else if ( haveS )
	{
		IECore::msg( IECore::Msg::Warning, "ToMayaMeshConverter::doConversion", boost::format( "Primitive variable \"%s\" found, but not \"%s\"." ) % sPrimVarName % tPrimVarName );
	}
	else if ( haveT )
	{
		IECore::msg( IECore::Msg::Warning, "ToMayaMeshConverter::doConversion", boost::format( "Primitive variable \"%s\" found, but not \"%s\"." ) % tPrimVarName % sPrimVarName );
	}
	else
	{
		assert( !uvSetName );
	}
}