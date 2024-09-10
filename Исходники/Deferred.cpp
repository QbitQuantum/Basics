//**************************************************
//				Lighting
//**************************************************
// 平行光
void Deferred::DirLight(const Vector3 dir, const Vector3 color)
{
	Matrix matV = matView;

	Vector3 LightDir;
	// ワールドの平行光を渡す
	Vector3 wLightDir = dir;
	wLightDir.Normalize();
	//shader->SetValue("wLightVec", wLightDir);

	//ビュー座標系に変換
	LightDir.x = dir.x * matV._11 + dir.y * matV._21 + dir.z * matV._31;
	LightDir.y = dir.x * matV._12 + dir.y * matV._22 + dir.z * matV._32;
	LightDir.z = dir.x * matV._13 + dir.y * matV._23 + dir.z * matV._33;


	LightDir.Normalize();

	//	シェーダー設定 shaderに送る
	shader->SetValue("ViewLightVec", LightDir);
	shader->SetValue("LightColor", (Vector3)color);

	//現在のレンダーターゲットを一時的に確保
	Surface* now = nullptr;
	tdnSystem::GetDevice()->GetRenderTarget(0, &now);

	//レンダーターゲットの切替え
	m_sLight->RenderTarget();
	m_sSpecular->RenderTarget(1);

	//	レンダリング
	m_mNormal->Render(0,0,shader, "DirLight");

	//レンダーターゲットの復元
	tdnSystem::GetDevice()->SetRenderTarget(0, now);
	tdnSystem::GetDevice()->SetRenderTarget(1, nullptr);
}