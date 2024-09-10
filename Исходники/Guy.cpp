void Guy::Update(float time, float seconds)
{
//	if (Input::GetKey(KeyCode_T))
		//d += seconds;
	//if (Input::GetKey(KeyCode_G))
//		d -= seconds;

//	d = MathUtils::Clamp(d, 0.0f, 1.0f);

	if (m_meshRibbon != NULL)
	{
		float d = 0;
		if (m_meshRibbon->m_ribbon != NULL && m_meshRibbon->m_ribbon->m_ribbonWeightCurve != NULL)
			d = m_meshRibbon->m_ribbon->m_ribbonWeightCurve->Evaluate(time);

		d = MathUtils::Clamp(d, 0.0f, 1.0f);

		shader->UseProgram();
		shader->SetParameter("u_ribbonWeight", d);

		m_meshRibbon->Update(time, seconds);
	}

	if (time < m_positionCurve->GetStartTime() ||
		time > m_positionCurve->GetEndTime())
	{
		for (uint32_t i = 0; i < m_renderables.size(); i++)
			m_renderables[i]->SetActive(false);
	}
	else
	{
		for (uint32_t i = 0; i < m_renderables.size(); i++)
			m_renderables[i]->SetActive(true);
	}

	sm::Vec3 position = m_positionCurve->Evaluate(time);
	sm::Vec3 nextPosition = m_positionCurve->Evaluate(time + 0.05f);

	sm::Vec3 direction(0, 0, 1);

	if (position != nextPosition)
		direction = (nextPosition - position).GetNormalized();

	sm::Matrix baseTransform =
		sm::Matrix::TranslateMatrix(position) *
		sm::Matrix::CreateLookAt(direction.GetReversed(), sm::Vec3(0, 1, 0)) *
		sm::Matrix::ScaleMatrix(0.02f, 0.02f, 0.02f);

	//sm::Matrix baseTransform = sm::Matrix::Identity;

	int animationIndex = 0;

	float animLength = m_animations[animationIndex]->GetAnimLength();

	//m_animations[animationIndex]->Update(time, m_mesh->m_meshData->m_worldMatrix, seconds);
	m_animations[animationIndex]->Update(fmodf(time * 1.0f, animLength), baseTransform, seconds);
	//m_animations[animationIndex]->Update(animLength * 0.8f, baseTransform, seconds);

	//DrawSegment2(m_animations[0]);

	/*for (uint32_t i = 0; i < m_renderables.size(); i++)
		m_renderables[i]->SetActive(false);*/
}