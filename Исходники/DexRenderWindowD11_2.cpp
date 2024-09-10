	void RenderWindowD11_2::RenderOneComponent(RenderComponentD11_2* component)
	{
		if (!component) {
			return;
		}

		auto sceneObject = component->GetSceneObject();

		_point aspectRatio = (_point)m_nWidth / m_nHeight;
		_point fovAngleY = 70.0f * MDEX_PI / 180.0f;

		if (aspectRatio < 1.0f)
		{
			fovAngleY *= 2.0f;
		}

		XMMATRIX xmpr = XMMatrixPerspectiveFovRH(
			fovAngleY,
			aspectRatio,
			0.01f,
			100.0f
		);

		/*_4matrix pr = MatrixPerspectiveFovRH(
			fovAngleY,
			aspectRatio,
			0.01f,
			100.0f
		);*/

		//pr = MatrixTranspose(MatrixMultiply(pr, _4matrix::identity()));

		

		//DrawLine(StringConverter::toString(pr));

		stringstream str;
		str << xmpr.r[0].m128_f32[0] << " " << xmpr.r[0].m128_f32[1] << " " << xmpr.r[0].m128_f32[2] << " " << xmpr.r[0].m128_f32[3] << endl;
		str << xmpr.r[1].m128_f32[0] << " " << xmpr.r[1].m128_f32[1] << " " << xmpr.r[1].m128_f32[2] << " " << xmpr.r[1].m128_f32[3] << endl;
		str << xmpr.r[2].m128_f32[0] << " " << xmpr.r[2].m128_f32[1] << " " << xmpr.r[2].m128_f32[2] << " " << xmpr.r[2].m128_f32[3] << endl;
		str << xmpr.r[3].m128_f32[0] << " " << xmpr.r[3].m128_f32[1] << " " << xmpr.r[3].m128_f32[2] << " " << xmpr.r[3].m128_f32[3] << endl;
		str << endl;
		DrawLine(str.str());

		_4matrix view = m_pCamera->GetMatrixView();

		//component->SetViewMatrix(view, pr);

		//auto constantBuffer = component->GetConstantBufferStruct();

		if (!sceneObject->IsCalculateMatrix()) {
			//DirectX::D3DXMATRIX buffer;
			//D3DXMatrixIdentity(&m_WorldMatrixD3D9);

			//// Rotation X
			//D3DXMatrixIdentity(&buffer);
			//D3DXMatrixRotationX(&buffer, D3DXToRadian(rotation.x));
			//D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

			//// Rotation Y
			//D3DXMatrixIdentity(&buffer);
			//D3DXMatrixRotationY(&buffer, D3DXToRadian(rotation.y));
			//D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

			//// Rotation Z
			//D3DXMatrixIdentity(&buffer);
			//D3DXMatrixRotationZ(&buffer, D3DXToRadian(rotation.z));
			//D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

			//// Scaling
			//D3DXMatrixIdentity(&buffer);
			//D3DXMatrixScaling(&buffer, scale.x, scale.y, scale.z);
			//D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

			//// Translation
			//D3DXMatrixIdentity(&buffer);
			//D3DXMatrixTranslation(&buffer, position.x, position.y, position.z);
			//D3DXMatrixMultiply(&m_WorldMatrixD3D9, &buffer, &m_WorldMatrixD3D9);

			//constantBuffer.model = buffer;
		}

		component->Render(m_pRSystem->GetD3DDeviceContext());
	}