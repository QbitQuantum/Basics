MStatus sgBDataCmd_key::writeData( bool exportByMatrix )
{
	MStatus status;
	
	double dTime  = MAnimControl::currentTime().value();

	if( exportByMatrix )
	{
		for( unsigned int i=0; i<m_pathArrExport.length(); i++ )
		{
			m_objectKeyDatasExport[i].lengthTime++;
			m_objectKeyDatasExport[i].dArrTime.append( dTime );
			MFnDependencyNode fnNode( m_objectKeyDatasExport[i].oTargetNode );

			if( m_objectKeyDatasExport[i].numAttr == 0 )
			{
				continue;
			}
			if( m_objectKeyDatasExport[i].numAttr == 1 )
			{
				MPlug plug = fnNode.findPlug( m_objectKeyDatasExport[i].namesAttribute[0] );
				m_objectKeyDatasExport[i].dArrValuesArray.append( plug.asDouble() );
			}
			else
			{
				if( m_objectKeyDatasExport[i].numAttr == 10 )
				{
					MPlug plug = fnNode.findPlug( m_objectKeyDatasExport[i].namesAttribute[0] );
					m_objectKeyDatasExport[i].dArrValuesArray.append( plug.asDouble() );
				}

				MDagPath dagPath;
				dagPath.getAPathTo( m_objectKeyDatasExport[i].oTargetNode, dagPath );

				MTransformationMatrix trMtx = dagPath.inclusiveMatrix() * dagPath.exclusiveMatrixInverse();
				MVector trans   = trMtx.translation( MSpace::kTransform );
				double rotValues[3] ={0,0,0};
				MTransformationMatrix::RotationOrder order = MTransformationMatrix::kZXY;
				trMtx.getRotation( rotValues, order, MSpace::kTransform );
				double scales[3];
				trMtx.getScale( scales, MSpace::kTransform );

				m_objectKeyDatasExport[i].dArrValuesArray.append( trans.x );
				m_objectKeyDatasExport[i].dArrValuesArray.append( trans.y );
				m_objectKeyDatasExport[i].dArrValuesArray.append( trans.z );
				m_objectKeyDatasExport[i].dArrValuesArray.append( rotValues[0] );
				m_objectKeyDatasExport[i].dArrValuesArray.append( rotValues[1] );
				m_objectKeyDatasExport[i].dArrValuesArray.append( rotValues[2] );
				m_objectKeyDatasExport[i].dArrValuesArray.append( scales[0] );
				m_objectKeyDatasExport[i].dArrValuesArray.append( scales[1] );
				m_objectKeyDatasExport[i].dArrValuesArray.append( scales[2] );
			}
		}
	}
	else
	{
		for( unsigned int i=0; i<m_pathArrExport.length(); i++ )
		{
			m_objectKeyDatasExport[i].lengthTime++;
			m_objectKeyDatasExport[i].dArrTime.append( dTime );
			MFnDependencyNode fnNode( m_objectKeyDatasExport[i].oTargetNode );

			for( unsigned int j=0; j< m_objectKeyDatasExport[i].numAttr; j++ )
			{
				MPlug plug = fnNode.findPlug( m_objectKeyDatasExport[i].namesAttribute[j] );
				m_objectKeyDatasExport[i].dArrValuesArray.append( plug.asDouble() );
			}
		}
	}

	return MS::kSuccess;
}