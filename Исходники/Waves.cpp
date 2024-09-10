//jingz //todo
void Waves::Update(float dt)
{
	static float t = 0.0f;

	// Accumulate time
	t += dt;

	if ( t>= m_fTimeStep)
	{
		for (UINT i = 1; i < m_uRows - 1;++i)
		{
			for (UINT j = 1; j < m_uCols - 1;++j)
			{
				// After this update we will be discarding the old previous
				// buffer, so overwrite that buffer with the new update.
				// Note how we can do this inplace (read/write to same element) 
				// because we won't need prev_ij again and the assignment happens last.

				// Note j indexes x and i indexes z: h(x_j, z_i, t_k)
				// Moreover, our +z axis goes "down"; this is just to 
				// keep consistent with our row indices going down.

				m_pPreSolution[i*m_uCols + j].y =
					m_fK1 * m_pPreSolution[i*m_uCols + j].y +
					m_fK2 * m_pCurSolution[i*m_uCols + j].y +
					m_fK3 * (
					m_pCurSolution[(i + 1)*m_uCols + j].y +
					m_pCurSolution[(i - 1)*m_uCols + j].y +
					m_pCurSolution[i*m_uCols + j + 1].y + 
					m_pCurSolution[i*m_uCols + j - 1].y
					);
			}
		}

		std::swap(m_pCurSolution, m_pPreSolution);

		//t -= m_fTimeStep;
		t = 0.0f;
		
		//jingz 感觉原作者的代码不是给人看的,有种行列故意倒换的感觉
		//
		// Compute normals using finite difference scheme.
		//
		for (UINT i = 1; i < m_uRows - 1;++i)
		{
			for (UINT j = 1; j < m_uCols - 1;++j)
			{
				float left = m_pCurSolution[i*m_uCols + j - 1].y;
				float right = m_pCurSolution[i*m_uCols + j + 1].y;
				float top = m_pCurSolution[(i-1)*m_uCols + j].y;
				float bottom = m_pCurSolution[(i+1)*m_uCols + j].y;

				m_pNormals[i*m_uCols + j].x = -right + left;
				m_pNormals[i*m_uCols + j].y = 2.0f*m_fSpatialStep;
				m_pNormals[i*m_uCols + j].z = bottom - top;

				XMVECTOR n = XMVector3Normalize(XMLoadFloat3((&m_pNormals[i*m_uCols + j])));
				XMStoreFloat3(&m_pNormals[i*m_uCols + j], n);

				m_pTangents[i*m_uCols + j] = XMFLOAT3(2.0f*m_fSpatialStep, right - left, 0.0f);
				XMVECTOR t = XMVector3Normalize(XMLoadFloat3(&m_pTangents[i*m_uCols + j]));
				XMStoreFloat3(&m_pTangents[i*m_uCols + j], t);
			}
		}

	}
}