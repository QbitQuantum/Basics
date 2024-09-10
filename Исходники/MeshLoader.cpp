Mesh MeshLoader::uploadMesh(const aiMesh *mesh) {
  Mesh model;

  // Generate vertex array object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create vertex indices VBO
  {
    // Store face indices in an array
    std::unique_ptr<unsigned int[]> faceArray(new unsigned int[mesh->mNumFaces * 3]);
    for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
      const aiFace &face = mesh->mFaces[f];
      std::memcpy(&faceArray[f * 3], face.mIndices, 3 * sizeof(face.mIndices[0]));
    }
    // Prepare vertex indices VBO
    createVBO(GL_ELEMENT_ARRAY_BUFFER,
              sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray.get());
  }

  // Cache vertex attributes existence to avoid dereferencing and calling every
  // time
  bool hasPositions = mesh->HasPositions(),
       hasTexCoords = mesh->HasTextureCoords(0),
       hasNormals = mesh->HasNormals(),
       hasTangents = mesh->HasTangentsAndBitangents();

  // Use them to determine the vertex definition size
  unsigned int vtxSize = +(hasPositions ? sizeof(float) * 3 : 0) +
                          (hasTexCoords ? sizeof(float) * 2 : 0) +
                          (hasNormals ? sizeof(float) * 3 : 0) +
                          (hasTangents ? sizeof(float) * 3 : 0);

  // Create a buffer to store vertex data, with determined size since we now
  // know it
  TightDataPacker data(mesh->mNumVertices * vtxSize);

  if (hasPositions) {
    // Since we keep the vertices in the model, better determine the storage
    // size once and for all
    model.vertices.resize(mesh->mNumVertices);
  }

  // Process each vertex and store its data
  for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
    if (hasPositions) {
      const aiVector3D &v = mesh->mVertices[i];
      model.vertices[i] = Vector3f(v.x, v.y, v.z);
      data << v.x << v.y << v.z;
    }

    if (hasTexCoords) {
      const aiVector3D &t = mesh->mTextureCoords[0][i];
      data << t.x
           << 1.f - t.y; // Y must be flipped due to OpenGL's coordinate system
    }

    if (hasNormals) {
      const aiVector3D &n = mesh->mNormals[i];
      data << n.x << n.y << n.z;
    }

    if (hasTangents) {
      const aiVector3D &t = mesh->mTangents[i];
      data << t.x << t.y << t.z;
    }
  }

  // Describe the vertex format we have
  {
    intptr_t offset = 0;
    specVector vertexAttrib;
    if (hasPositions) {
          vertexAttrib.push_back({0, 3, GL_FLOAT, reinterpret_cast<GLvoid*>(offset)});
          offset += sizeof(float) * 3;
    }
    if (hasTexCoords) {
          vertexAttrib.push_back({1, 2, GL_FLOAT, reinterpret_cast<GLvoid*>(offset)});
          offset += sizeof(float) * 2;
    }
    if (hasNormals) {
        vertexAttrib.push_back({2, 3, GL_FLOAT, reinterpret_cast<GLvoid*>(offset)});
        offset += sizeof(float) * 3;
    }
    if (hasTangents) {
        vertexAttrib.push_back({3, 3, GL_FLOAT, reinterpret_cast<GLvoid*>(offset)});
    }
    createVBO(GL_ARRAY_BUFFER, data.getSize(), data.getDataPtr(),
                         static_cast<int>(vtxSize), vertexAttrib);
  }
  glBindVertexArray(0);

  // Store relevant data in the new mesh
  model.handle = static_cast<int>(vao);
  model.numFaces = static_cast<int>(mesh->mNumFaces);

  return model;
}