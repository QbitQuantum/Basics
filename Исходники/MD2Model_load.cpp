void MD2Model::Part::load(const std::string& filename, float resize) {

    resize *= 0.55f;

    // If models are being reloaded it is dangerous to trust the interpolation cache.
    interpolatedModel = NULL;

    alwaysAssertM(FileSystem::exists(filename), std::string("Can't find \"") + filename + "\"");

    setNormalTable();

    // Clear out
    reset();

    BinaryInput b(filename, G3D_LITTLE_ENDIAN);

    MD2ModelHeader header;

    header.deserialize(b);
    debugAssert(header.version == 8);
    debugAssert(header.numVertices <= 4096);

    keyFrame.resize(header.numFrames);
    Array<Vector3> frameMin;
    frameMin.resize(header.numFrames); 
    Array<Vector3> frameMax;
    frameMax.resize(header.numFrames);
    Array<double>  frameRad;
    frameRad.resize(header.numFrames);

    texCoordScale.x = 1.0f / header.skinWidth;
    texCoordScale.y = 1.0f / header.skinHeight;

    Vector3 min  = Vector3::inf();
    Vector3 max  = -Vector3::inf();
    double  rad  = 0;

    if (header.numVertices < 3) {
        Log::common()->printf("\n*****************\nWarning: \"%s\" is corrupted and is not being loaded.\n", filename.c_str());
        return;
    }

    loadTextureFilenames(b, header.numSkins, header.offsetSkins);

    for (int f = 0; f < keyFrame.size(); ++f) {
        MD2Frame md2Frame;

        b.setPosition(header.offsetFrames + f * header.frameSize);
        md2Frame.deserialize(b);

        // Read the vertices for the frame
        keyFrame[f].vertexArray.resize(header.numVertices);
        keyFrame[f].normalArray.resize(header.numVertices);

        // Per-pose bounds
        Vector3 min_1  = Vector3::inf();
        Vector3 max_1  = -Vector3::inf();
        double  rad_1  = 0;

        // Quake's axes are permuted and scaled
        double scale[3]   = {-.07, .07, -.07};
        int    permute[3] = {2, 0, 1};
        int v, i;
        for (v = 0; v < header.numVertices; ++v) {

            Vector3& vertex = keyFrame[f].vertexArray[v];
            for (i = 0; i < 3; ++i) {
                vertex[permute[i]] = (b.readUInt8() * md2Frame.scale[i] + md2Frame.translate[i]) * float(scale[permute[i]]);
            }

            vertex *= resize;

            uint8 normalIndex = b.readUInt8();
            debugAssertM(normalIndex < 162, "Illegal canonical normal index in file");
            keyFrame[f].normalArray[v] = iClamp(normalIndex, 0, 161);

            min_1 = min_1.min(vertex);
            max_1 = max_1.max(vertex);

            if (vertex.squaredMagnitude() > rad_1) {
                rad_1 = vertex.squaredMagnitude();
            }
        }

        frameMin[f] = min_1;
        frameMax[f] = max_1;
        frameRad[f] = sqrt(rad_1);

        min = min.min(min_1);
        max = max.max(max_1);

        if (rad_1 > rad) {
            rad = rad_1;
        }
    }

    // Compute per-animation bounds based on frame bounds
    for (int a = 0; a < JUMP; ++a) {
        const int first = animationTable[a].first;
        const int last  = animationTable[a].last;

        if ((first < header.numFrames) && (last < header.numFrames)) {
            Vector3 min = frameMin[first];
            Vector3 max = frameMax[first];
            double rad  = frameRad[first];

            for (int i = first + 1; i <= last; ++i) {
                min = min.min(frameMin[i]);
                max = max.max(frameMax[i]);
                rad = G3D::max(rad, frameRad[i]);
            }

            animationBoundingBox[a]    = AABox(min, max);

            // Sometimes the sphere bounding the box is tighter than the one we calculated.
            const float boxRadSq = (max-min).squaredMagnitude() * 0.25f;

            if (boxRadSq >= square(rad)) {
                animationBoundingSphere[a] = Sphere(Vector3::zero(), (float)rad);
            } else {
                animationBoundingSphere[a] = Sphere((max + min) * 0.5f, sqrt(boxRadSq));
            }

        } else {
            // This animation is not supported by this model
            animationBoundingBox[a]    = AABox(Vector3::zero(), Vector3::zero());
            animationBoundingSphere[a] = Sphere(Vector3::zero(), 0);
        }
    }

    animationBoundingBox[JUMP] = animationBoundingBox[JUMP_DOWN];
    animationBoundingSphere[JUMP] = animationBoundingSphere[JUMP_DOWN];

    boundingBox    = AABox(min, max);
    boundingSphere = Sphere(Vector3::zero(), (float)sqrt(rad));

    // Load the texture coords
    Array<Vector2int16> fileTexCoords;
    fileTexCoords.resize(header.numTexCoords);
    b.setPosition(header.offsetTexCoords);
    for (int t = 0; t < fileTexCoords.size(); ++t) {
        fileTexCoords[t].x = b.readUInt16();
        fileTexCoords[t].y = b.readUInt16();
    }

    // The indices for the texture coords (which don't match the
    // vertex indices originally).
    indexArray.resize(header.numTriangles * 3);
    Array<Vector2int16> index_texCoordArray;
    index_texCoordArray.resize(indexArray.size());

    // Read the triangles, reversing them to get triangle list order
    b.setPosition(header.offsetTriangles);
    for (int t = header.numTriangles - 1; t >= 0; --t) {

        for (int i = 2; i >= 0; --i) {
            indexArray[t * 3 + i] = b.readUInt16();
        }

        for (int i = 2; i >= 0; --i) {
            index_texCoordArray[t * 3 + i] = fileTexCoords[b.readUInt16()];
        }
    }

    computeTexCoords(index_texCoordArray);

    // Read the primitives
    {
        primitiveArray.clear();
        b.setPosition(header.offsetGlCommands);
        
        int n = b.readInt32();

        while (n != 0) {
            Primitive& primitive = primitiveArray.next();

            if (n > 0) {
                primitive.type = PrimitiveType::TRIANGLE_STRIP;
            } else {
                primitive.type = PrimitiveType::TRIANGLE_FAN;
                n = -n;
            }

            primitive.pvertexArray.resize(n);

            Array<Primitive::PVertex>&  pvertex = primitive.pvertexArray;

            for (int i = 0; i < pvertex.size(); ++i) {
                pvertex[i].texCoord.x = b.readFloat32();
                pvertex[i].texCoord.y = b.readFloat32();
                pvertex[i].index      = b.readInt32();
            }

            n = b.readInt32();
        }
    }


    MeshAlg::computeAdjacency(keyFrame[0].vertexArray, indexArray, faceArray, edgeArray, vertexArray);
    weldedFaceArray = faceArray;
    weldedEdgeArray = edgeArray;
    weldedVertexArray = vertexArray;
    MeshAlg::weldAdjacency(keyFrame[0].vertexArray, weldedFaceArray, weldedEdgeArray, weldedVertexArray);

    numBoundaryEdges = MeshAlg::countBoundaryEdges(edgeArray);
    numWeldedBoundaryEdges = MeshAlg::countBoundaryEdges(weldedEdgeArray);

    shared_ptr<VertexBuffer> indexBuffer = 
        VertexBuffer::create(indexArray.size() * sizeof(int), VertexBuffer::WRITE_ONCE);
    indexVAR = IndexStream(indexArray, indexBuffer);
}