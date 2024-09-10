ModelLightingClass::ModelLightingClass(string barName, bool p_quad, const XMFLOAT3 & postion):Entity(),
	Position(postion), Rotation(0.0f, 0.0f, 0.0f), Scale(1.0f, 1.0f, 1.0f), Quaternion(XMQuaternionIdentity())
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_model = 0;


	m_bar = TwNewBar(barName.c_str());

	string define = barName + " iconified=true  alpha=200";
	string group = barName + "/Rotation opened = false";
	TwDefine(define.c_str());

	TwAddVarRW(m_bar, "XRotation", TW_TYPE_FLOAT, &Rotation.x, " step=0.01 group=Rotation");
	TwAddVarRW(m_bar, "YRotation", TW_TYPE_FLOAT, &Rotation.y, " step=0.01 group=Rotation");
	TwAddVarRW(m_bar, "ZRotation", TW_TYPE_FLOAT, &Rotation.z, "min=0 max=6.28 step=0.01 group=Rotation");
	TwDefine(group.c_str());

	TwAddVarRW(m_bar, "XPosition", TW_TYPE_FLOAT, &Position.x, "  step=0.1 group=Position");
	TwAddVarRW(m_bar, "YPosition", TW_TYPE_FLOAT, &Position.y, "  step=0.1 group=Position");
	TwAddVarRW(m_bar, "ZPosition", TW_TYPE_FLOAT, &Position.z, "  step=0.1 group=Position");
	group = barName + "/Position opened = false";
	TwDefine(group.c_str());

	TwAddVarRW(m_bar, "XScale", TW_TYPE_FLOAT, &Scale.x, "  step=0.01 group=Scale");
	TwAddVarRW(m_bar, "YScale", TW_TYPE_FLOAT, &Scale.y, "  step=0.01 group=Scale");
	TwAddVarRW(m_bar, "ZScale", TW_TYPE_FLOAT, &Scale.z, "  step=0.01 group=Scale");
	group = barName + "/Scale opened = false";
	TwDefine(group.c_str());
}