bool MyRender::Draw()
{
  static float dfi = 0.02f;
  static float fi = 0.0f;
  static float radius = 30.0f;
  
  float dz = radius * (cos(fi + dfi) - cos(fi));
  float dx = radius * (sin(fi + dfi) - sin(fi));
  m_car->RotateY(dfi);
  m_car->Translate(dx, 0, dz);
  fi += dfi;
  if (fi > XM_2PI)
    fi -= XM_2PI;

  ConstantBuffer cb;

  m_camera->Update();
  XMMATRIX view = XMLoadFloat4x4(&(m_camera->GetViewMatrix()));

  // add all projectors info to constant buffer
  for (size_t i = 0, lightIndex = 0; i < m_scene->GetObjectsNumber(); i++)
  {
    MyObject *object = m_scene->GetObjectAt(i);
    for (size_t j = 0; j < object->GetProjectorLightsNumber(); j++, lightIndex++)
    {
      ProjectorLight *projector = object->GetProjectorAt(j);
      XMMATRIX projectorWorldMatrix = (XMLoadFloat4x4(&(object->GetWorldMatrix())));
      XMMATRIX projectorRotationMatrix = (XMLoadFloat4x4(&(object->GetRotationMatrix())));
      XMVECTOR tempPos = XMLoadFloat4(&(XMFLOAT4(projector->Pos.x, projector->Pos.y, projector->Pos.z, 1)));
      XMVECTOR tempDir = XMLoadFloat4(&(XMFLOAT4(projector->Direction.x, projector->Direction.y, projector->Direction.z, 1)));

      XMVECTOR projectorPos = XMVector4Transform(tempPos, projectorWorldMatrix);
      XMVECTOR projectorDir = XMVector4Transform(tempDir, projectorRotationMatrix);

      XMStoreFloat4(cb.vLightPos + lightIndex, projectorPos);
      XMStoreFloat4(cb.vLightDir + lightIndex, projectorDir);
	    cb.vLightColor[lightIndex] = projector->Color;
    }
  }
  // add all point lights info to constant buffer
  for (size_t i = 0, lightIndex = 0; i < m_scene->GetObjectsNumber(); i++)
  {
    MyObject *object = m_scene->GetObjectAt(i);
    for (size_t j = 0; j < object->GetPointLightsNumber(); j++, lightIndex++)
    {
      SimpleLight *bulb = object->GetPointLightAt(j);
      XMMATRIX bulbWorldMatrix = (XMLoadFloat4x4(&(object->GetWorldMatrix())));
      XMVECTOR tempPos = XMLoadFloat4(&(XMFLOAT4(bulb->Pos.x, bulb->Pos.y, bulb->Pos.z, 1)));

      XMVECTOR bulbPos = XMVector4Transform(tempPos, bulbWorldMatrix);

      XMStoreFloat4(cb.vBulbLightPos + lightIndex, bulbPos);
	    cb.vBulbLightColor[lightIndex] = bulb->Color;
    }
  }

  // add all directed lights info to constant buffer
  for (size_t i = 0, lightIndex = 0; i < m_scene->GetObjectsNumber(); i++)
  {
    MyObject *object = m_scene->GetObjectAt(i);
    for (size_t j = 0; j < object->GetDirectedLightsNumber(); j++, lightIndex++)
    {
      DirectedLight *dirLight = object->GetDirectedLightAt(j);
      XMMATRIX dirRotationMatrix = (XMLoadFloat4x4(&(object->GetRotationMatrix())));
      XMVECTOR tempDir = XMLoadFloat4(&(XMFLOAT4(dirLight->Dir.x, dirLight->Dir.y, dirLight->Dir.z, 1)));

      XMVECTOR bulbPos = XMVector4Transform(tempDir, dirRotationMatrix);

      XMStoreFloat4(cb.vDirectedLightDir + lightIndex, bulbPos);
	    cb.vDirectedLightColor[lightIndex] = dirLight->Color;
    }
  }

  cb.isLightEnabled[0] = m_enableProjectorLight;
  cb.isLightEnabled[1] = m_enablePointLight;
  cb.isLightEnabled[2] = m_enableDirectedLight;
  cb.isLightEnabled[3] = 0;

  for (size_t idx = 0; idx < m_scene->GetObjectsNumber(); idx++)
  {
    MyObject *object = m_scene->GetObjectAt(idx);

    /****************************************************/

    D3D11_BUFFER_DESC bd;
    RtlZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * object->GetVerticesNumber();
	  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	  bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA data;
    RtlZeroMemory(&data, sizeof(data));
    data.pSysMem = object->GetVertices();

    HRESULT hr = m_pd3dDevice->CreateBuffer(&bd, &data, &m_pVertexBuffer);
    if (FAILED(hr))
    {
      Log::Get()->Err("CreateBuffer error for vertex buffer.");
      return false;
    }
    UINT stride = sizeof(SimpleVertex);
	  UINT offset = 0;

    m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
  
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(UINT) * object->GetIndicesNumber();
	  bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	  bd.CPUAccessFlags = 0;
	  data.pSysMem = object->GetIndices();
	  hr = m_pd3dDevice->CreateBuffer(&bd, &data, &m_pIndexBuffer);
	  if(FAILED(hr))
    {
      Log::Get()->Err("CreateBuffer error for torus.");
		  return false;
    }
    m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    /****************************************************/
    XMMATRIX world = XMLoadFloat4x4(&(object->GetWorldMatrix()));

    cb.mWorld = XMMatrixTranspose(world);
    cb.mView = XMMatrixTranspose(view);
	  cb.mProjection = XMMatrixTranspose(m_Projection);
    cb.vOutputColor = XMFLOAT4(0, 0, 0, 0);
	  m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);
  
	  m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
	  m_pImmediateContext->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer);
    if (object == m_sun) // absolutely black body
	    m_pImmediateContext->PSSetShader(m_pPixelShaderSolid, NULL, 0);
    else
      m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);
	  m_pImmediateContext->PSSetConstantBuffers( 0, 1, &m_pConstantBuffer);
    m_pImmediateContext->DrawIndexed(object->GetIndicesNumber(), 0, 0);

    _RELEASE(m_pVertexBuffer);
    _RELEASE(m_pIndexBuffer);
  }
	return true;
}