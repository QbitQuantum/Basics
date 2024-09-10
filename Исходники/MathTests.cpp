        bool AdvancedMatrixTests()
        {
            Matrix m(1, 0, 0, 0,
                     0, 2, 0, 0,
                     0, 0, 3, 0,
                     0, 0, 0, 4);

            float trace = m.Trace();
            float expectedTrace = 1 + 2 + 3 + 4;

            if (trace != expectedTrace)
            {
                wprintf(L"trace didn't match! %f\n", trace);
                return false;
            }

            float det = m.Determinant();
            // that's a non-reflective, scaling matrix with a scale > 1, so we should have a pos det > 1
            if (det <= 1)
            {
                wprintf(L"determinant wasn't > 1! %f\n", det);
                return false;
            }

            Matrix invM;
            // we only don't have an inverse if det(M) == 0
            if (m.Inverse(&invM) != (det != 0))
            {
                wprintf(L"inverse existence didn't match determinant! %f\n", det);
                return false;
            }

            // if we had an inverse, let's verify it
            if (det != 0)
            {
                // first, m * invM == I
                Matrix testForIdentity = m * invM;
                // quick test for identiy is trace == 4 && det = 1. Not perfect, but good enough
                if (testForIdentity.Trace() != 4 || testForIdentity.Determinant() != 1)
                {
                    wprintf(L"M * invM != I!\n");
                    return false;
                }

                // second, inverting the inverse should give us the original matrix
                Matrix testM;
                if (!invM.Inverse(&testM))
                {
                    return false;
                }

                if (testM.Trace() != trace || testM.Determinant() != det)
                {
                    wprintf(L"inverting the inverse didn't appear to give the original matrix!\n");
                    return false;
                }
            }

            // inverse of an orthonormal matrix (any rotation matrix) is equivelant to it's transpose
            Matrix m2(Matrix::CreateFromAxisAngle(Vector3(0.707f, 0.707f, 0.0f), 1.234f));
            Matrix invM2;
            if (!m2.Inverse(&invM2))
            {
                return false;
            }

            Matrix transM2 = m2.Transpose();
            if (invM2.Trace() != transM2.Trace() || invM2.Determinant() != transM2.Determinant())
            {
                return false;
            }

            // another inverse test
            Matrix m3(1, 2, 0, 0,
                      4, 0, 4, 0,
                      0, 8, 8, 0,
                      1, 0, 2, 1);
            Matrix invM3;
            if (!m3.Inverse(&invM3))
            {
                return false;
            }

            DirectX::XMMATRIX xm = m3;
            DirectX::XMVECTOR xdet;
            DirectX::XMMATRIX invXM = DirectX::XMMatrixInverse(&xdet, xm);

            DirectX::XMFLOAT4X4 invXMF;
            DirectX::XMStoreFloat4x4(&invXMF, invXM);

            return true;
        }