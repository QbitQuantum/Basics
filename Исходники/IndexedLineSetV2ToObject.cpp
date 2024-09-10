/*!
	@function	IndexedLineSetV2ToObject
	
	@abstract	Attempt to convert a VRML 2 IndexedLineSet node to a Quesa object.
	
	@param		ioNode			Node to convert.
	@param		inReader		The reader object.
	
	@result		An object reference, or NULL on failure.
*/
CQ3ObjectRef	IndexedLineSetV2ToObject( PolyValue& ioNode )
{
	CQ3ObjectRef	theObject( Q3DisplayGroup_New() );
	ThrowIfNullQuesaOb_( theObject );
	
	// The VRML 2 spec says that lines are not lit.
	CQ3ObjectRef	theShader( Q3NULLIllumination_New() );
	ThrowIfNullQuesaOb_( theShader );
	Q3Group_AddObject( theObject.get(), theShader.get() );
	
	PolyValue::Dictionary&	theDict( ioNode.GetDictionary() );
	
	// Gather data from fields
	std::vector<TQ3Point3D>	thePoints;
	std::vector<TQ3ColorRGB>	theColors;
	PolyValue::IntVec		pointIndices;
	PolyValue::IntVec		colorIndices;
	
	GetNodeArray( theDict, "coord", "Coordinate", "point", thePoints );
	GetNodeArray( theDict, "color", "Color", "color", theColors );
	
	GetIntVecFromField( theDict, "coordIndex", pointIndices );
	GetIntVecFromField( theDict, "colorIndex", colorIndices );
	StandardizeIndexVector( pointIndices );
	StandardizeIndexVector( colorIndices );
	
	bool	isColorPerVertex = true;
	if (IsKeyPresent( theDict, "colorPerVertex" ))
	{
		PolyValue&	theNode( theDict[ "colorPerVertex" ] );
		if (theNode.GetType() == PolyValue::kDataTypeBool)
		{
			isColorPerVertex = theNode.GetBool();
		}
	}
	
	// Start building polylines
	std::vector<TQ3Vertex3D>	vertices;
	std::vector<CQ3ObjectRef>	vertAttSets;
	int	polylineNum = 0;
	
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
			if ((not isColorPerVertex) and (not theColors.empty()))
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
				polyAtts = CQ3ObjectRef( Q3AttributeSet_New() );
				ThrowIfNullQuesaOb_( polyAtts );
				Q3AttributeSet_Add( polyAtts.get(), kQ3AttributeTypeDiffuseColor,
					&polyColor );
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