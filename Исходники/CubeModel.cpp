void CubeModel::Update(float time)
{
  mAngle += 90.0f * time;
  
  XMVECTOR rotationAxis = XMVectorSet(1, 0, 1, 0);
  mWorldPos.world = XMMatrixRotationAxis(rotationAxis, XMConvertToRadians(mAngle));
  
  mVertexShader->UpdateWorldMatrix(mWorldPos);
}