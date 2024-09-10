//----------------------------------------------------------------------------
void SimpleBumpMapEffect::ComputeLightVectors (Triangles* mesh,
    const AVector& worldLightDirection)
{
    // The tangent-space coordinates for the light direction vector at each
    // vertex is stored in the color0 channel.  The computations use the
    // vertex normals and the texture coordinates for the base mesh, which
    // are stored in the tcoord0 channel.  Thus, the mesh must have positions,
    // normals, colors (unit 0), and texture coordinates (unit 0).

    // The light direction D is in world-space coordinates.  Negate it,
    // transform it to model-space coordinates, and then normalize it.  The
    // world-space direction is unit-length, but the geometric primitive
    // might have non-unit scaling in its model-to-world transformation, in
    // which case the normalization is necessary.
    AVector modelLightDirection =
        -mesh->WorldTransform.Inverse()*worldLightDirection;

    // Set the light vectors to (0,0,0) as a flag that the quantity has not
    // yet been computed.  The probability that a light vector is actually
    // (0,0,0) should be small, so the flag system should save computation
    // time overall.
    VertexBufferAccessor vba(mesh);
    Float3 black(0.0f, 0.0f, 0.0f);
    int i;
    for (i = 0; i < vba.GetNumVertices(); ++i)
    {
        vba.Color<Float3>(0, i) = black;
    }

    int numTriangles = mesh->GetNumTriangles();
    for (int t = 0; t < numTriangles; ++t)
    {
        // Get the triangle vertices and attributes.
        int v0, v1, v2;
        if (!mesh->GetTriangle(t, v0, v1, v2))
        {
            continue;
        }

        APoint position[3] =
        {
            vba.Position<Float3>(v0),
            vba.Position<Float3>(v1),
            vba.Position<Float3>(v2)
        };

        AVector normal[3] =
        {
            vba.Normal<Float3>(v0),
            vba.Normal<Float3>(v1),
            vba.Normal<Float3>(v2)
        };

        Float3* color[3] =
        {
            &vba.Color<Float3>(0, v0),
            &vba.Color<Float3>(0, v1),
            &vba.Color<Float3>(0, v2)
        };

        Float2 tcoord[3] =
        {
            vba.TCoord<Float2>(0, v0),
            vba.TCoord<Float2>(0, v1),
            vba.TCoord<Float2>(0, v2)
        };

        for (i = 0; i < 3; ++i)
        {
            Float3& colorref = *color[i];
            if (colorref != black)
            {
                continue;
            }

            int iP = (i == 0) ? 2 : i - 1;
            int iN = (i + 1) % 3;

            AVector tangent;
            if (!ComputeTangent(position[i], tcoord[i], position[iN],
                tcoord[iN], position[iP], tcoord[iP], tangent))
            {
                // The texture coordinate mapping is not properly defined for
                // this.  Just say that the tangent space light vector points
                // in the same direction as the surface normal.
                colorref[0] = normal[i][0];
                colorref[1] = normal[i][1];
                colorref[2] = normal[i][2];
                continue;
            }

            // Project T into the tangent plane by projecting out the surface
            // normal N, and then make it unit length.
            tangent -= normal[i].Dot(tangent)*(normal[i]);
            tangent.Normalize();

            // Compute the bitangent B, another tangent perpendicular to T.
            AVector bitangent = normal[i].UnitCross(tangent);

            // The set {T,B,N} is a right-handed orthonormal set.  The
            // negated light direction U = -D is represented in this
            // coordinate system as
            //   U = Dot(U,T)*T + Dot(U,B)*B + Dot(U,N)*N
            float dotUT = modelLightDirection.Dot(tangent);
            float dotUB = modelLightDirection.Dot(bitangent);
            float dotUN = modelLightDirection.Dot(normal[i]);

            // Transform the light vector into [0,1]^3 to make it a valid
            // Float3 object.
            colorref[0] = 0.5f*(dotUT + 1.0f);
            colorref[1] = 0.5f*(dotUB + 1.0f);
            colorref[2] = 0.5f*(dotUN + 1.0f);
        }
    }
}