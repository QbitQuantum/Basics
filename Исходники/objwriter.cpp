    std::shared_ptr<gameplay::Model> OBJWriter::readModel(const boost::filesystem::path& path, const std::shared_ptr<gameplay::ShaderProgram>& shaderProgram, const glm::vec3& ambientColor) const
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile((m_basePath / path).string(), aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_ValidateDataStructure | aiProcess_FlipUVs);
        BOOST_ASSERT(scene != nullptr);

        auto renderModel = std::make_shared<gameplay::Model>();

        for( unsigned int mi = 0; mi < scene->mNumMeshes; ++mi )
        {
            BOOST_LOG_TRIVIAL(info) << "Converting mesh " << mi + 1 << " of " << scene->mNumMeshes << " from " << m_basePath / path;

            const aiMesh* mesh = scene->mMeshes[mi];
            if( mesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE )
            BOOST_THROW_EXCEPTION(std::runtime_error("Mesh does not consist of triangles only"));
            if( !mesh->HasTextureCoords(0) )
            BOOST_THROW_EXCEPTION(std::runtime_error("Mesh does not have UV coordinates"));
            if( mesh->mNumUVComponents[0] != 2 )
            BOOST_THROW_EXCEPTION(std::runtime_error("Mesh does not have a 2D UV channel"));
            if( !mesh->HasFaces() )
            BOOST_THROW_EXCEPTION(std::runtime_error("Mesh does not have faces"));
            if( !mesh->HasPositions() )
            BOOST_THROW_EXCEPTION(std::runtime_error("Mesh does not have positions"));

            std::shared_ptr<gameplay::Mesh> renderMesh;

            if( mesh->HasNormals() )
            {
                std::vector<VDataNormal> vbuf(mesh->mNumVertices);
                for( unsigned int i = 0; i < mesh->mNumVertices; ++i )
                {
                    vbuf[i].position = glm::vec3{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z} * static_cast<float>(SectorSize);
                    vbuf[i].normal = glm::vec3{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
                    vbuf[i].uv = glm::vec2{mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
                    if( mesh->HasVertexColors(0) )
                        vbuf[i].color = glm::vec4(mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b, mesh->mColors[0][i].a);
                    else
                        vbuf[i].color = glm::vec4(ambientColor, 1);
                }

                renderMesh = std::make_shared<gameplay::Mesh>(VDataNormal::getFormat(), mesh->mNumVertices, false);
                renderMesh->rebuild(reinterpret_cast<const float*>(vbuf.data()), mesh->mNumVertices);
            }
            else
            {
                std::vector<VData> vbuf(mesh->mNumVertices);
                for( unsigned int i = 0; i < mesh->mNumVertices; ++i )
                {
                    vbuf[i].position = glm::vec3{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z} * static_cast<float>(SectorSize);
                    vbuf[i].uv = glm::vec2{mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
                    if( mesh->HasVertexColors(0) )
                        vbuf[i].color = glm::vec4(mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b, mesh->mColors[0][i].a);
                    else
                        vbuf[i].color = glm::vec4(ambientColor, 1);
                }

                renderMesh = std::make_shared<gameplay::Mesh>(VData::getFormat(), mesh->mNumVertices, false);
                renderMesh->rebuild(reinterpret_cast<const float*>(vbuf.data()), mesh->mNumVertices);
            }

            std::vector<uint32_t> faces;
            for( const aiFace& face : gsl::span<aiFace>(mesh->mFaces, mesh->mNumFaces) )
            {
                BOOST_ASSERT(face.mNumIndices == 3);
                faces.push_back(face.mIndices[0]);
                faces.push_back(face.mIndices[1]);
                faces.push_back(face.mIndices[2]);
            }

            auto part = renderMesh->addPart(gameplay::Mesh::TRIANGLES, gameplay::Mesh::INDEX32, mesh->mNumFaces * 3, false);
            part->setIndexData(faces.data(), 0, faces.size());

            const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            aiString textureName;
            if( material->GetTexture(aiTextureType_DIFFUSE, 0, &textureName) != aiReturn_SUCCESS )
            BOOST_THROW_EXCEPTION(std::runtime_error("Failed to get diffuse texture path from mesh"));

            part->setMaterial(readMaterial(textureName.C_Str(), shaderProgram));

            renderModel->addMesh(renderMesh);
        }

        return renderModel;
    }