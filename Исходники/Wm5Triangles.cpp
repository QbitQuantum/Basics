//----------------------------------------------------------------------------
void Triangles::UpdateModelTangentsUseGeometry (VertexBufferAccessor& vba)
{
    // Compute the matrix of normal derivatives.
    const int numVertices = vba.GetNumVertices();
    HMatrix* dNormal = new1<HMatrix>(numVertices);
    HMatrix* wwTrn = new1<HMatrix>(numVertices);
    HMatrix* dwTrn = new1<HMatrix>(numVertices);
    memset(wwTrn, 0, numVertices*sizeof(HMatrix));
    memset(dwTrn, 0, numVertices*sizeof(HMatrix));

    const int numTriangles = GetNumTriangles();
    int i, row, col;
    for (i = 0; i < numTriangles; ++i)
    {
        // Get the vertex indices for the triangle.
        int v[3];
        if (!GetTriangle(i, v[0], v[1], v[2]))
        {
            continue;
        }

        for (int j = 0; j < 3; j++)
        {
            // Get the vertex positions and normals.
            int v0 = v[j];
            int v1 = v[(j + 1) % 3];
            int v2 = v[(j + 2) % 3];
            APoint pos0 = vba.Position<Float3>(v0);
            APoint pos1 = vba.Position<Float3>(v1);
            APoint pos2 = vba.Position<Float3>(v2);
            AVector nor0 = vba.Normal<Float3>(v0);
            AVector nor1 = vba.Normal<Float3>(v1);
            AVector nor2 = vba.Normal<Float3>(v2);

            // Compute the edge from pos0 to pos1, project it to the tangent
            // plane of the vertex, and compute the difference of adjacent
            // normals.
            AVector edge = pos1 - pos0;
            AVector proj = edge - edge.Dot(nor0)*nor0;
            AVector diff = nor1 - nor0;
            for (row = 0; row < 3; ++row)
            {
                for (col = 0; col < 3; ++col)
                {
                    wwTrn[v0][row][col] += proj[row]*proj[col];
                    dwTrn[v0][row][col] += diff[row]*proj[col];
                }
            }

            // Compute the edge from pos0 to pos2, project it to the tangent
            // plane of the vertex, and compute the difference of adjacent
            // normals.
            edge = pos2 - pos0;
            proj = edge - edge.Dot(nor0)*nor0;
            diff = nor2 - nor0;
            for (row = 0; row < 3; ++row)
            {
                for (col = 0; col < 3; ++col)
                {
                    wwTrn[v0][row][col] += proj[row]*proj[col];
                    dwTrn[v0][row][col] += diff[row]*proj[col];
                }
            }
        }
    }

    // Add N*N^T to W*W^T for numerical stability.  In theory 0*0^T is added
    // to D*W^T, but of course no update is needed in the implementation.
    // Compute the matrix of normal derivatives.
    for (i = 0; i < numVertices; ++i)
    {
        AVector nor = vba.Normal<Float3>(i);
        for (row = 0; row < 3; ++row)
        {
            for (col = 0; col < 3; ++col)
            {
                wwTrn[i][row][col] =
                    0.5f*wwTrn[i][row][col] + nor[row]*nor[col];
                dwTrn[i][row][col] *= 0.5f;
            }
        }

        wwTrn[i].SetColumn(3, APoint::ORIGIN);
        dNormal[i] = dwTrn[i]*wwTrn[i].Inverse();
    }

    delete1(wwTrn);
    delete1(dwTrn);

    // If N is a unit-length normal at a vertex, let U and V be unit-length
    // tangents so that {U, V, N} is an orthonormal set.  Define the matrix
    // J = [U | V], a 3-by-2 matrix whose columns are U and V.  Define J^T
    // to be the transpose of J, a 2-by-3 matrix.  Let dN/dX denote the
    // matrix of first-order derivatives of the normal vector field.  The
    // shape matrix is
    //   S = (J^T * J)^{-1} * J^T * dN/dX * J = J^T * dN/dX * J
    // where the superscript of -1 denotes the inverse.  (The formula allows
    // for J built from non-perpendicular vectors.) The matrix S is 2-by-2.
    // The principal curvatures are the eigenvalues of S.  If k is a principal
    // curvature and W is the 2-by-1 eigenvector corresponding to it, then
    // S*W = k*W (by definition).  The corresponding 3-by-1 tangent vector at
    // the vertex is called the principal direction for k, and is J*W.  The
    // principal direction for the minimum principal curvature is stored as
    // the mesh tangent.  The principal direction for the maximum principal
    // curvature is stored as the mesh bitangent.
    for (i = 0; i < numVertices; ++i)
    {
        // Compute U and V given N.
        AVector norvec = vba.Normal<Float3>(i);
        AVector uvec, vvec;
        AVector::GenerateComplementBasis(uvec, vvec, norvec);

        // Compute S = J^T * dN/dX * J.  In theory S is symmetric, but
        // because we have estimated dN/dX, we must slightly adjust our
        // calculations to make sure S is symmetric.
        float s01 = uvec.Dot(dNormal[i]*vvec);
        float s10 = vvec.Dot(dNormal[i]*uvec);
        float sAvr = 0.5f*(s01 + s10);
        float smat[2][2] =
        {
            { uvec.Dot(dNormal[i]*uvec), sAvr },
            { sAvr, vvec.Dot(dNormal[i]*vvec) }
        };

        // Compute the eigenvalues of S (min and max curvatures).
        float trace = smat[0][0] + smat[1][1];
        float det = smat[0][0]*smat[1][1] - smat[0][1]*smat[1][0];
        float discr = trace*trace - 4.0f*det;
        float rootDiscr = Mathf::Sqrt(Mathf::FAbs(discr));
        float minCurvature = 0.5f*(trace - rootDiscr);
        // float maxCurvature = 0.5f*(trace + rootDiscr);

        // Compute the eigenvectors of S.
        AVector evec0(smat[0][1], minCurvature - smat[0][0], 0.0f);
        AVector evec1(minCurvature - smat[1][1], smat[1][0], 0.0f);
        AVector tanvec, binvec;
        if (evec0.SquaredLength() >= evec1.SquaredLength())
        {
            evec0.Normalize();
            tanvec = evec0.X()*uvec + evec0.Y()*vvec;
            binvec = norvec.Cross(tanvec);
        }
        else
        {
            evec1.Normalize();
            tanvec = evec1.X()*uvec + evec1.Y()*vvec;
            binvec = norvec.Cross(tanvec);
        }

        if (vba.HasTangent())
        {
            vba.Tangent<Float3>(i) = tanvec;
        }

        if (vba.HasBinormal())
        {
            vba.Binormal<Float3>(i) = binvec;
        }
    }

    delete1(dNormal);
}