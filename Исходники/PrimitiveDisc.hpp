    inline void GenerateTriangles(unsigned int segments)
    {
        vertices.clear();
        normals.clear();
        indicies.clear();
        texCoords.clear();

        float thetaStep = static_cast<float>(PI2) / static_cast<float>(segments);

        int numVerts = (segments) * 3; // Edge points + center + return to start
        int numTexCoords = (numVerts / 3) * 2;

        vertices.reserve(numVerts);
        normals.reserve(numVerts);
        texCoords.reserve(numVerts);

        float theta1 = 0.0f, theta2 = thetaStep;
        for (unsigned int i = 0; i < segments + 1; i++)
        {
            // Find the two points for this segment
            Vector3 xyz1, xyz2;
            xyz1 = Vector3(sinf(theta1), 0.0f, cosf(theta1));
            xyz2 = Vector3(sinf(theta2), 0.0f, cosf(theta2));

            Vector2 uv1, uv2;
            uv1 = Vector2((xyz1.x * 0.5f) + 0.5f, (xyz1.z * 0.5f) + 0.5f);
            uv2 = Vector2((xyz2.x * 0.5f) + 0.5f, (xyz2.z * 0.5f) + 0.5f);

            // Push the vertices, normals and texture coordinates
            // Center of disc
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);

            vertices.push_back(xyz1.x);
            vertices.push_back(0.0f);
            vertices.push_back(xyz1.z);

            vertices.push_back(xyz2.x);
            vertices.push_back(0.0f);
            vertices.push_back(xyz2.z);

            for (int i = 0; i < 3; i++)
            {
                normals.push_back(0.0f);
                normals.push_back(1.0f);
                normals.push_back(0.0f);
            }

            texCoords.push_back(0.5f);
            texCoords.push_back(0.5f);

            texCoords.push_back(uv1.x);
            texCoords.push_back(uv1.y);
            
            texCoords.push_back(uv2.x);
            texCoords.push_back(uv2.y);

            if (i < segments)
            {
                theta1 += thetaStep;
                theta2 += thetaStep;
            }
            else
            {
                theta1 += thetaStep;
                theta2 = 0.0f; // Clamp back to the beginning
            }
        }
    }