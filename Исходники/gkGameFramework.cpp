bool gkGameFramework::OnInputEvent( const SInputEvent &event )
{
 	if (m_pGame)
 	{
 		return false;
 	}

	if (gEnv->pSystem->IsEditor())
	{
		return false;
	}

	float fFrameTime = gEnv->pTimer->GetFrameTime();
	static float speed = 5.0f;

	switch ( event.deviceId )
	{
	case eDI_Mouse:
		{
			static bool holding = false;
			if (event.keyId == eKI_Mouse2)
			{
				if (event.state == eIS_Down)
				{
					holding = true;
				}
				else
				{
					holding = false;
				}
			}

			else if (event.keyId == eKI_MouseX && holding)
			{
				Quat qBefore = gEnv->p3DEngine->getMainCamera()->getDerivedOrientation();
				Ang3 aRot(qBefore);

				aRot.z -= event.value * 0.002f;
				//aRot.x -= vMouseDelta.y * 0.002f;

				Quat qRot = Quat::CreateRotationXYZ(aRot);
				qRot.Normalize();
				gEnv->p3DEngine->getMainCamera()->setOrientation(qRot);				
			}
			else if (event.keyId == eKI_MouseY && holding)
			{
				Quat qBefore = gEnv->p3DEngine->getMainCamera()->getDerivedOrientation();
				Ang3 aRot(qBefore);

				aRot.x -= event.value * 0.002f;
				//aRot.x -= vMouseDelta.y * 0.002f;

				Quat qRot = Quat::CreateRotationXYZ(aRot);
				qRot.Normalize();
				gEnv->p3DEngine->getMainCamera()->setOrientation(qRot);				
			}
			break;
		}
	case eDI_Keyboard:
		{
			if (event.keyId == eKI_LShift && event.state == eIS_Down)
			{
				speed = 50.0f;
			}
			else if (event.keyId == eKI_LShift && event.state == eIS_Released)
			{
				speed = 5.0f;
			}
			else if (event.keyId == eKI_W)
			{
				gEnv->p3DEngine->getMainCamera()->moveLocal( Vec3(0, fFrameTime * speed, 0) );
			}
			else if (event.keyId == eKI_S)
			{
				gEnv->p3DEngine->getMainCamera()->moveLocal( Vec3(0, -fFrameTime * speed, 0 ) );
			}
			else if (event.keyId == eKI_A)
			{
				gEnv->p3DEngine->getMainCamera()->moveLocal( Vec3(-fFrameTime * speed, 0, 0) );
			}
			else if (event.keyId == eKI_D)
			{
				gEnv->p3DEngine->getMainCamera()->moveLocal( Vec3(fFrameTime * speed, 0, 0 ) );
			}
			break;
		}
	case eDI_XBox:
		{
			if (event.keyId == eKI_Xbox_TriggerL && event.state == eIS_Changed)
			{
				speed = (event.value) * 45.0 + 15;
				return false;
			}

			if (event.keyId == eKI_Xbox_ThumbLY && event.state == eIS_Changed)
			{
				float thumbspeed = (event.value) * speed;
				gEnv->p3DEngine->getMainCamera()->moveLocal( Vec3(0, fFrameTime * thumbspeed, 0) );
				return false;
			}

			if (event.keyId == eKI_Xbox_ThumbLX && event.state == eIS_Changed)
			{
				float thumbspeed = (event.value) * speed;
				gEnv->p3DEngine->getMainCamera()->moveLocal( Vec3(fFrameTime * thumbspeed, 0, 0) );
				return false;
			}

			if (event.keyId == eKI_Xbox_ThumbRX && event.state == eIS_Changed)
			{
				Quat qBefore = gEnv->p3DEngine->getMainCamera()->getDerivedOrientation();
				Ang3 aRot(qBefore);

				aRot.z -= event.value * 0.015f;
				//aRot.x -= vMouseDelta.y * 0.002f;

				Quat qRot = Quat::CreateRotationXYZ(aRot);
				qRot.Normalize();
				gEnv->p3DEngine->getMainCamera()->setOrientation(qRot);			
				return false;
			}

			if (event.keyId == eKI_Xbox_ThumbRY && event.state == eIS_Changed)
			{
				Quat qBefore = gEnv->p3DEngine->getMainCamera()->getDerivedOrientation();
				Ang3 aRot(qBefore);

				aRot.x += event.value * 0.015f;
				//aRot.x -= vMouseDelta.y * 0.002f;

				Quat qRot = Quat::CreateRotationXYZ(aRot);
				qRot.Normalize();
				gEnv->p3DEngine->getMainCamera()->setOrientation(qRot);		
				return false;
			}
			break;
		}
	case eDI_Android:
    case eDI_IOS:
	{
		return AndroidFreeModeControl( event );

		break;
	}
        default:
            break;
            
            
	}
	return false;
}