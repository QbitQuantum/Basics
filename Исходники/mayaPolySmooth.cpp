//! Caller is expected to delete the returned value
static OpenSubdiv::Far::TopologyRefiner *
gatherTopology( MFnMesh & inMeshFn,
                MItMeshPolygon & inMeshItPolygon,
                OpenSubdiv::Sdc::SchemeType type,
                OpenSubdiv::Sdc::Options options,
                bool * hasUVs, bool * hasColors,
                std::vector<MFloatArray> & uvSet_uCoords,
                std::vector<MFloatArray> & uvSet_vCoords,
                std::vector<MColorArray> & colorSet_colors,
                float * maxCreaseSharpness=0 ) {

    MStatus returnStatus;

    // Gather FVarData
    MStringArray uvSetNames;
    MStringArray colorSetNames;
    std::vector<int> colorSetChannels;
    std::vector<MFnMesh::MColorRepresentation> colorSetReps;
    int totalColorSetChannels = 0;
    returnStatus = getMayaFvarFieldParams(inMeshFn, uvSetNames, colorSetNames, 
                        colorSetChannels, colorSetReps, totalColorSetChannels);
    MWARNERR(returnStatus, "Failed to retrieve Maya face-varying parameters");

    // Storage for UVs and ColorSets for face-vertex
    MIntArray fvArray; // face vertex array
    uvSet_uCoords.clear();  uvSet_uCoords.resize(uvSetNames.length());
    uvSet_vCoords.clear();  uvSet_vCoords.resize(uvSetNames.length());
    colorSet_colors.clear();colorSet_colors.resize(colorSetNames.length());

    // Put the data in the format needed for OSD
    Descriptor desc;
    
    int numFaceVertices = inMeshFn.numFaceVertices();

    desc.numVertices = inMeshFn.numVertices();
    desc.numFaces = inMeshItPolygon.count();

    int * vertsPerFace = new int[desc.numFaces],
        * vertIndices = new int[numFaceVertices];

    desc.numVertsPerFace = vertsPerFace;
    desc.vertIndicesPerFace = vertIndices;

    // Create Topology
    for (inMeshItPolygon.reset(); !inMeshItPolygon.isDone(); inMeshItPolygon.next()) {

        inMeshItPolygon.getVertices(fvArray);
        int nverts = fvArray.length();

        vertsPerFace[inMeshItPolygon.index()] = nverts;

        for (int i=0; i<nverts; ++i) {
            *vertIndices++ = fvArray[i];
        }
    }

    // Add Face-Varying data to the descriptor
    Descriptor::FVarChannel * channels = NULL;
    *hasUVs = uvSet_uCoords.size() > 0 && uvSet_vCoords.size() > 0;
    *hasColors = colorSet_colors.size() > 0;

    // Note : Only supports 1 channel of UVs and 1 channel of color
    if (*hasUVs || *hasColors) {

        // Create 2 face-varying channel descriptor that will hold UVs and color
        desc.numFVarChannels = 2;
        channels = new Descriptor::FVarChannel[desc.numFVarChannels];
        desc.fvarChannels = channels;

        int * uvIndices = new int[numFaceVertices];
        channels[CHANNELUV].valueIndices = uvIndices;
        channels[CHANNELUV].numValues = 0;

        int * colorIndices = new int[numFaceVertices];
        channels[CHANNELCOLOR].valueIndices = colorIndices;
        channels[CHANNELCOLOR].numValues = 0;

        // Obtain UV information
        if (*hasUVs) {
            inMeshFn.getUVs(uvSet_uCoords[0], uvSet_vCoords[0], &uvSetNames[0]);
            assert( uvSet_uCoords[0].length() == uvSet_vCoords[0].length() );

            int uvId = 0, nUVs = 0;
            for (int faceIndex = 0; faceIndex < inMeshFn.numPolygons(); ++faceIndex)
            {
                int numVertices = inMeshFn.polygonVertexCount(faceIndex);
                for (int v = 0; v < numVertices; v++)
                {
                    inMeshFn.getPolygonUVid(faceIndex, v, uvId, &uvSetNames[0]);
                    uvIndices[nUVs++] = uvId;
                }
            }

            channels[CHANNELUV].numValues = uvSet_uCoords[0].length();
        }

        // Obtain color information
        if (*hasColors) {  
            inMeshFn.getColors(colorSet_colors[0], &colorSetNames[0]);

            int colorId = 0, nColors = 0;
            bool addDefaultColor = true;
            for (int faceIndex = 0; faceIndex < inMeshFn.numPolygons(); ++faceIndex)
            {
                int numVertices = inMeshFn.polygonVertexCount(faceIndex);
                for ( int v = 0 ; v < numVertices; v++ )
                {
                    inMeshFn.getColorIndex(faceIndex, v, colorId, &colorSetNames[0]);
                    if (colorId == -1)
                    {
                        if (addDefaultColor)
                        {
                            addDefaultColor = false;
                            colorSet_colors[0].append(MColor(1.0, 1.0, 1.0, 1.0));
                        }
                        colorId = colorSet_colors[0].length() - 1;
                    }
                    colorIndices[nColors ++] = colorId;
                }
            }
            
            channels[CHANNELCOLOR].numValues = colorSet_colors[0].length();
        }
    }

    // Apply Creases
    float maxEdgeCrease = getCreaseEdges( inMeshFn, desc );
    float maxVertexCrease = getCreaseVertices( inMeshFn, desc );

    OpenSubdiv::Far::TopologyRefiner * refiner =
        OpenSubdiv::Far::TopologyRefinerFactory<Descriptor>::Create(desc,
            OpenSubdiv::Far::TopologyRefinerFactory<Descriptor>::Options(type, options));

    delete [] desc.numVertsPerFace;
    delete [] desc.vertIndicesPerFace;
    delete [] desc.creaseVertexIndexPairs;
    delete [] desc.creaseWeights;
    delete [] desc.cornerVertexIndices;
    delete [] desc.cornerWeights;

    if (*hasUVs || *hasColors) {
        for(int i = 0 ; i < desc.numFVarChannels ; i ++) {
            delete [] channels[i].valueIndices;
        }
        delete [] channels;
    }

    if (maxCreaseSharpness) {
        *maxCreaseSharpness = std::max(maxEdgeCrease, maxVertexCrease);
    }

    return refiner;
}