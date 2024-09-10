void EditorLoader::AddTrigger()
{
	Trigger* pTrigger(new Trigger());

	pTrigger->Init(m_pPhysXEngine, Vector3(2,2,2));

	Vector3 look = m_pRenderContext->GetCamera()->GetLook();
	look.Normalize();

	pTrigger->SetPosition(m_pRenderContext->GetCamera()->GetPosition() + look * 2);

	m_pLevel->AddLevelObject(pTrigger);
}