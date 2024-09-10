void LightSample::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
	switch (evt)
	{
	case Touch::TOUCH_PRESS:
		{
			_touched = true;
			_touchX = x;
			_touchY = y;
			
			Ray pickRay;
			_scene->getActiveCamera()->pickRay(getViewport(), _touchX, _touchY, &pickRay);

			if (_directional->isSelected() && pickRay.intersects(_directionalLightQuadModel->getMesh()->getBoundingBox()))
			{
				_usedForMoving = _directionalLightNode;
			}
			else if (_spot->isSelected() && pickRay.intersects(_spotLightQuadModel->getMesh()->getBoundingBox()))
			{
				_usedForMoving = _spotLightNode;
			}
			else if (_point->isSelected() && pickRay.intersects(_pointLightQuadModel->getMesh()->getBoundingBox()))
			{
				_usedForMoving = _pointLightNode;
			}
			else
			{
				_usedForMoving = NULL;
			}
		}
		break;

	case Touch::TOUCH_RELEASE:
		{
			_touched = false;
			_touchX = 0;
			_touchY = 0;
			_usedForMoving = NULL;
		}
		break;

	case Touch::TOUCH_MOVE:
		{
			int deltaX = x - _touchX;
			_touchX = x;

			int deltaY = y - _touchY;
			_touchY = y;

			Matrix m;
			_modelNode->getWorldMatrix().transpose(&m);

			// Yaw in world frame
			Vector3 yaw;
			m.getUpVector(&yaw);
			_modelNode->rotate(yaw, MATH_DEG_TO_RAD(deltaX * 0.5f));

			// Roll in world frame
			Vector3 pitch;
			m.getRightVector(&pitch);
			_modelNode->rotate(pitch, MATH_DEG_TO_RAD(deltaY * 0.5f));
		}
		break;

	default:
		break;
	};
}