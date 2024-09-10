/*!
	@function	IndexedLineSetV1ToObject
	
	@abstract	Attempt to convert a VRML 1 IndexedLineSet node to a Quesa object.
	
	@param		ioNode			Node to convert.
	@param		inReader		The reader object.
	
	@result		An object reference, or NULL on failure.
*/
CQ3ObjectRef	IndexedLineSetV1ToObject( PolyValue& ioNode, CVRMLReader& inReader )
{
	CQ3ObjectRef	theObject( Q3DisplayGroup_New() );
	ThrowIfNullQuesaOb_( theObject );
	PolyValue::Dictionary&	theDict( ioNode.GetDictionary() );
	int	polylineNum = 0;
	
	// I am not going to bother with normals, so it is better not to use lighting.
	CQ3ObjectRef	theShader( Q3NULLIllumination_New() );
	ThrowIfNullQuesaOb_( theShader );
	Q3Group_AddObject( theObject.get(), theShader.get() );
	
	// Gather data
	PolyValue::IntVec		pointIndices;
	PolyValue::IntVec		colorIndices;
	GetIntVecFromField( theDict, "coordIndex", pointIndices );
	GetIntVecFromField( theDict, "materialIndex", colorIndices );
	StandardizeIndexVector( pointIndices );
	StandardizeIndexVector( colorIndices );
	const SVRML1State&	theState( inReader.GetVRML1State() );
	const std::vector<TQ3Point3D>&	thePoints( theState.coordinate3 );
	const std::vector<TQ3ColorRGB>&	theColors( theState.diffuseColor );
	bool isColorPerVertex( (theState.materialBinding == eVRML1Value_PER_VERTEX) or
		(theState.materialBinding == eVRML1Value_PER_VERTEX_INDEXED) );
	// Note: the VRML 1 spec, unlike the VRML 2 spec, indicates that colors
	// can be per segment rather than per polyline.  Currently I will not
	// support that.
	bool isColorPerPolyline( (theState.materialBinding == eVRML1Value_PER_PART) or
		(theState.materialBinding == eVRML1Value_PER_PART_INDEXED) or
		(theState.materialBinding == eVRML1Value_PER_FACE) or
		(theState.materialBinding == eVRML1Value_PER_FACE_INDEXED) );
	

	// Start building polylines
	std::vector<TQ3Vertex3D>	vertices;
	std::vector<CQ3ObjectRef>	vertAttSets;
	
	for (unsigned int i = 0; i < pointIndices.size(); ++i)
	{
		if (pointIndices[i] < 0)
		{
			// FInish a PolyLine
			TQ3PolyLineData	polyData;
			polyData.numVertices = vertices.size();
			polyData.vertices = &vertices[0];
			polyData.segmentAttributeSet = NULL;
			CQ3ObjectRef	polyAtts;
			if (not theColors.empty())
			{
				polyAtts = GetIndexedMaterial( inReader, 0 );
				
				if (isColorPerPolyline)
				{
					TQ3ColorRGB	polyColor;
					if (colorIndices.empty())
					{
						polyColor = theColors[ polylineNum ];
					}
					else
					{
						polyColor = theColors[ colorIndices[polylineNum] ];
					}
					Q3AttributeSet_Add( polyAtts.get(), kQ3AttributeTypeDiffuseColor,
						&polyColor );
				}

				polyData.polyLineAttributeSet = polyAtts.get();
			}
			else
			{
				polyData.polyLineAttributeSet = NULL;
			}
			CQ3ObjectRef	polyLine( Q3PolyLine_New( &polyData ) );
			ThrowIfNullQuesaOb_( polyLine );
			Q3Group_AddObject( theObject.get(), polyLine.get() );
			vertices.clear();
			vertAttSets.clear();
			polylineNum += 1;
		}
		else
		{
			TQ3Vertex3D	aVertex;
			aVertex.point = thePoints[ pointIndices[i] ];
			if (isColorPerVertex and (not theColors.empty()))
			{
				TQ3ColorRGB	vertColor;
				if (colorIndices.empty())
				{
					vertColor = theColors[ pointIndices[i] ];
				}
				else
				{
					vertColor = theColors[ colorIndices[i] ];
				}
				CQ3ObjectRef	vertAtts( Q3AttributeSet_New() );
				ThrowIfNullQuesaOb_( vertAtts );
				Q3AttributeSet_Add( vertAtts.get(), kQ3AttributeTypeDiffuseColor,
					&vertColor );
				vertAttSets.push_back( vertAtts );
				aVertex.attributeSet = vertAtts.get();
			}
			else
			{
				aVertex.attributeSet = NULL;
			}
			vertices.push_back( aVertex );
		}
	}

	if (polylineNum == 0)
	{
		// no sense returning an empty display group
		theObject = CQ3ObjectRef();
	}
	
	return theObject;
}