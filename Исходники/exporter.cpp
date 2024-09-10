        //-------------------------------------------------------------------------------------------------------
        bool Exporter::prepareVertexStreams()
        {
                auto& textureCoordinates = meshData_->vertices[Mesh::VERTEX_STREAM_TEXTURE_COORDINATES];
                auto& positions          = meshData_->vertices[Mesh::VERTEX_STREAM_POSITIONS];
                auto& tbnBases           = meshData_->vertices[Mesh::VERTEX_STREAM_TBN_BASES];

                auto& boneIndicesAndWeights = meshData_->vertices[Mesh::VERTEX_STREAM_BONE_INDICES_AND_WEIGHTS];

                if(!textureCoordinates.create(numVertices_, sizeof(Vector2d)) ||
                   !positions.create(numVertices_, sizeof(Vector3d))          ||
                   !tbnBases.create(numVertices_, sizeof(Vector3d) + sizeof(Vector4d)))
                        return false;

                if(!rawMesh_->bones_.isEmpty())
                {
                        if(!boneIndicesAndWeights.create(numVertices_, 2 * sizeof(Vector4d)))
                                return false;
                }

                for(uint32_t i = 0; i < faces_.getSize(); ++i)
                {
                        for(uint8_t j = 0; j < 3; ++j)
                        {
                                uint32_t vertexIndex = faces_[i].indices[j];
                                const auto& vertex = vertices_[vertexIndex];

                                uint8_t* stream = &positions[vertexIndex * positions.getStride()];
                                *reinterpret_cast<Vector3d*>(stream) = vertex.pos;

                                stream = &textureCoordinates[vertexIndex * textureCoordinates.getStride()];
                                *reinterpret_cast<Vector2d*>(stream) = Vector2d(vertex.s, vertex.t);

                                stream = &tbnBases[vertexIndex * tbnBases.getStride()];
                                Vector4d& tangent = *(reinterpret_cast<Vector4d*>(stream + sizeof(Vector3d)));
                                Vector3d& normal  = *(reinterpret_cast<Vector3d*>(stream));

                                normal = vertex.normal;
                                normal.normalize();

                                // tangent and binormal

                                Vector3d t = vertex.tangent;
                                Vector3d b = vertex.binormal;

                                t = t - normal.dot(t) * normal;
                                t.normalize();

                                b = b - normal.dot(b) * normal - t.dot(b) * t / t.dot(t);
                                b.normalize();

                                Vector3d crossProduct = normal.cross(t);
                                if(crossProduct == b)
                                        tangent.define(t, 1.0f);
                                else if(crossProduct == -b)
                                        tangent.define(t, -1.0f);
                                else
                                {
                                        std::cout << "warning: vertex " << vertexIndex <<
                                                     " has bad TBN basis" << std::endl;
                                        tangent = Vector4d(t, -1.0f);
                                }

                                if(!rawMesh_->bones_.isEmpty())
                                {
                                        stream = &boneIndicesAndWeights[vertexIndex *
                                                                        boneIndicesAndWeights.getStride()];

                                        Vector4d& boneIndices = *(reinterpret_cast<Vector4d*>(stream));
                                        Vector4d& boneWeights = *(reinterpret_cast<Vector4d*>(stream +
                                                                                              sizeof(Vector4d)));

                                        uint32_t oldVertexIndex = newToOldVertexMapping_[vertexIndex];
                                        boneIndices = boneIndices_[oldVertexIndex];
                                        boneWeights = boneWeights_[oldVertexIndex];

                                        if(std::fabs(boneWeights.x + boneWeights.y +
                                                     boneWeights.z + boneWeights.w - 1.0f) > SELENE_EPSILON)
                                                std::cout << "warning: vertex " << vertexIndex <<
                                                             " has bad bone weights" << std::endl;
                                }
                        }
                }

                return true;
        }