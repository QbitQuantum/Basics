//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CField::Exec()
{
	//::D3DXVec3TransformCoord(&vAxisX, &vAxisX, &m_matRotate);
	//::D3DXVec3TransformCoord(&vAxisZ, &vAxisZ, &m_matRotate);
	
	//if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_LEFT) )
	//{
	//	m_vPos -= vAxisX*0.1f;
	//	//m_Anim += 1.0f;
	//}
	//
	//if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_RIGHT) )
	//{
	//	m_vPos += vAxisX*0.1f;
	//	//m_Anim += 1.0f;
	//}	
	//
	//if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_UP) )
	//{
	//	m_vPos -= vAxisZ * 0.1f;
	//	//m_vPos.z -= 0.1f;
	//	//m_Anim += 1.0f;
	//}
	//
	//if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_DOWN) )
	//{
	//	m_vPos += vAxisZ * 0.1f;
	//	//m_vPos.z += 0.1f;
	//	//m_Anim += 1.0f;
	//}
	
	
	//if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_BUTTON_02) )
	//{
	//	m_vRot.x += 0.1f;
	//}
	
//	Update(0.000f);
	
	Translation(m_vPos.x, m_vPos.y, m_vPos.z);
	
	Scaling(m_vScale.x, m_vScale.y, m_vScale.z);
	
	Heading(m_vRot.x);
	
	Pitching(m_vRot.x);
	
	Rolling(m_vRot.x);
	
	Render(Joker::GetDevice());
	
	SetWorldMatrix();
}