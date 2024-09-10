	void EntityComposite::render()
	{
		//get view and projection matrices
		XMMATRIX viewMatrix, projectionMatrix;
		GRAPHICS->getCamera()->GetViewMatrix(viewMatrix);
		GRAPHICS->getDirectXWrapper()->getProjectionMatrix(projectionMatrix);

		//compute position and orientation of the actor
		vector<snICollider*> colliders = m_actor->getColliders();
		for (vector<snICollider*>::const_iterator i = colliders.cbegin(); i != colliders.cend(); ++i)
		{
			snMatrix44f temp = (*i)->getTransform().getLocalToWorld();

			snMatrix44f scale;
			IGfxEntity* gfx = 0;
			switch ((*i)->getTypeOfCollider())
			{
				case snEColliderType::snEColliderBox:
				{
					snOBB* box = static_cast<snOBB*>((*i));
					scale.createScale(box->getExtends() * 2);
					gfx = GRAPHICS->getBox();
				}
				break;

				case snEColliderType::snEColliderSphere:
				{
					snSphere* sphere = static_cast<snSphere*>((*i));
					scale.createScale(sphere->getRadius() * 2);
					gfx = GRAPHICS->getSphere();
				}
				break;

				case snEColliderType::snEColliderCapsule:
				{
					snCapsule* capsule = static_cast<snCapsule*>((*i));
					float diameter = capsule->getRadius() * 2;

					//draw the first sphere
					scale.createScale(diameter);
					snMatrix44f translate;
					translate.createTranslation(capsule->getFirstEndPoint());

					snMatrix44f worldTransform;
					snMatrixMultiply4(scale, translate, worldTransform);
					XMMATRIX dxWorldMatrix;
					dxWorldMatrix.r[0] = worldTransform.m_r[0];
					dxWorldMatrix.r[1] = worldTransform.m_r[1];
					dxWorldMatrix.r[2] = worldTransform.m_r[2];
					dxWorldMatrix.r[3] = worldTransform.m_r[3];

					gfx = GRAPHICS->getSphere();
					gfx->render(dxWorldMatrix, viewMatrix, projectionMatrix, m_color, m_texture, m_wireframe);

					//draw the second sphere
					translate.createTranslation(capsule->getSecondEndPoint());
					snMatrixMultiply4(scale, translate, worldTransform);
					dxWorldMatrix.r[0] = worldTransform.m_r[0];
					dxWorldMatrix.r[1] = worldTransform.m_r[1];
					dxWorldMatrix.r[2] = worldTransform.m_r[2];
					dxWorldMatrix.r[3] = worldTransform.m_r[3];
					gfx->render(dxWorldMatrix, viewMatrix, projectionMatrix, m_color, m_texture, m_wireframe);

					//prepare the capsule
					float length = Supernova::Vector::snVec3Norme(capsule->getFirstEndPoint() - capsule->getSecondEndPoint());
					scale.createScale(Supernova::Vector::snVec4Set(capsule->getRadius(), length, capsule->getRadius(), 1));
					gfx = GRAPHICS->getCylinder();
				}
				break;

				default:
					continue;
			}

			snMatrix44f worldTransform;
			snMatrixMultiply4(scale, temp, worldTransform);
			XMMATRIX dxWorldMatrix;
			dxWorldMatrix.r[0] = worldTransform.m_r[0];
			dxWorldMatrix.r[1] = worldTransform.m_r[1];
			dxWorldMatrix.r[2] = worldTransform.m_r[2];
			dxWorldMatrix.r[3] = worldTransform.m_r[3];
			gfx->render(dxWorldMatrix, viewMatrix, projectionMatrix, m_color, m_texture, m_wireframe);
		}

		//render the center of mass
		XMMATRIX centerOfMassPosition = XMMatrixIdentity();
		centerOfMassPosition.r[3] = m_actor->getWorldCenterOfMass();
		m_gfxCenterOfMass->render(centerOfMassPosition, viewMatrix, projectionMatrix, Colors::Green, m_texture, m_wireframe);
	}