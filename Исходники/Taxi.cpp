void Taxi::Update(float time, float seconds)
{
	//m_position.y = sinf(time * (((m_speed + 1) / 13.0f) * 1.0f)) * 0.5f + 0.5f;
	//m_position.y *= 0.5f;

	sm::Vec3 oldPos = m_position;

	if (IsOccupied())
	{
		m_timeLeft -= seconds;
		if (m_timeLeft < 0.0f)
			m_timeLeft = 0.0f;
	}

	sm::Vec3 turnPivot;
	sm::Matrix turnMatrix;
	float pivotDistance = 0.0f;

	m_speed += m_acc * 5.0f * seconds;

	static float maxSpeed = 14.0f;

	if (m_acc == 0.0f)
	{
		m_speed -= MathUtils::Min(MathUtils::Abs(m_speed), 8.0f * seconds) * MathUtils::Sign(m_speed);
	}

	if (m_speed > 0.0f && m_acc == -1.0f)
	{
		m_speed -= MathUtils::Min(MathUtils::Abs(m_speed), 12.0f * seconds) * MathUtils::Sign(m_speed);
	}

	m_speed = MathUtils::Clamp(m_speed, -maxSpeed / 4, maxSpeed);

	SoundManager::GetInstance()->SetEnginePitch((MathUtils::Abs(m_speed) / maxSpeed) * 1.0f + 1.0f);

	m_wheelsAngle += 2.0f * m_turnValue * seconds;

	m_wheelsAngle = MathUtils::Clamp(m_wheelsAngle, -MathUtils::PI4, MathUtils::PI4);

	if (m_wheelsAngle != 0.0f)
	{
		if (m_wheelsAngle < 0.0)
		{
			pivotDistance = m_backFrontWheelsDistance / tanf(fabs(m_wheelsAngle));
			turnPivot = sm::Vec3(m_baseBackRightWheelPosition.x + pivotDistance, 0, m_baseBackRightWheelPosition.z);
		}
		else
		{
			pivotDistance = m_backFrontWheelsDistance / tanf(fabs(m_wheelsAngle));
			turnPivot = sm::Vec3(m_baseBackLeftWheelPosition.x - pivotDistance, 0, m_baseBackLeftWheelPosition.z);
		}

		float angleSpeed = m_speed / (2.0f * MathUtils::PI * MathUtils::Abs(turnPivot.x));

		sm::Matrix turnMatrixNormal =
			sm::Matrix::RotateAxisMatrix(
				angleSpeed * (MathUtils::PI * 2.0f) * seconds * MathUtils::Sign(m_wheelsAngle),
				0, 1, 0);

		turnPivot = m_worldMatrix * turnPivot;
		turnPivot.y = 0.0f;

		turnMatrix =
			sm::Matrix::TranslateMatrix(turnPivot) *
			turnMatrixNormal *
			sm::Matrix::TranslateMatrix(turnPivot.GetReversed());

		sm::Vec3 prevCarDirection = m_carDirection;
		m_carDirection = turnMatrixNormal * m_carDirection;
		m_carDirection.Normalize();

	
		float angleDiff = sm::Vec3::GetAngle(prevCarDirection, m_carDirection);
		m_wheelsAngle -= angleDiff * MathUtils::Sign(m_wheelsAngle);

		m_position = turnMatrix * m_position;
	}
	else
		m_position += m_carDirection * m_speed * seconds;

	sm::Matrix newWorldMatrix =
		sm::Matrix::TranslateMatrix(m_position) *
		sm::Matrix::CreateLookAt(m_carDirection.GetReversed(), sm::Vec3(0, 1, 0));

	sm::Vec3 boundsTopLeftWorldOld = m_worldMatrix * m_boundsTopLeft;
	sm::Vec3 boundsBottomLeftWorldOld = m_worldMatrix * m_boundsBottomLeft;
	sm::Vec3 boundsTopRightWorldOld = m_worldMatrix * m_boundsTopRight;
	sm::Vec3 boundsBottomRightWorldOld = m_worldMatrix * m_boundsBottomRight;

	sm::Vec3 boundsTopLeftWorldNew = newWorldMatrix * m_boundsTopLeft;
	sm::Vec3 boundsBottomLeftWorldNew = newWorldMatrix * m_boundsBottomLeft;
	sm::Vec3 boundsTopRightWorldNew = newWorldMatrix * m_boundsTopRight;
	sm::Vec3 boundsBottomRightWorldNew = newWorldMatrix * m_boundsBottomRight;

	sm::Vec3 collisionNormal;
	sm::Vec3 collisionPoint;

	if (Street::Instance->GetCollistion(boundsTopLeftWorldOld, boundsTopLeftWorldNew, collisionPoint, collisionNormal))
	{
		if (m_speed > 4.0f)
		{
			static Randomizer random;

			SoundManager::GetInstance()->PlaySound((SoundManager::Sound)random.GetInt(0, 2));
		}

		float dot = sm::Vec3::Dot(collisionNormal, m_carDirection.GetReversed());
		if (dot > 0.8 && m_speed > 3.0f)
			m_speed = -3.0f;
		else
			m_speed *= 1.0f - sm::Vec3::Dot(collisionNormal, m_carDirection.GetReversed());

		collisionPoint += collisionNormal * 0.01f;

		sm::Vec3 toCollisionTarget = collisionPoint - boundsTopLeftWorldOld;
		sm::Vec3 fromCollisionTarget = sm::Vec3::Reflect(collisionNormal, toCollisionTarget);
		sm::Vec3 correntPosition = boundsTopLeftWorldOld + toCollisionTarget + fromCollisionTarget;
		sm::Vec3 deltaMove = collisionPoint - boundsTopLeftWorldOld;

		m_carDirection = (collisionPoint - boundsBottomLeftWorldOld).GetNormalized();

		m_position = oldPos + deltaMove;

		m_worldMatrix =
			sm::Matrix::TranslateMatrix(m_position) *
			sm::Matrix::CreateLookAt(m_carDirection.GetReversed(), sm::Vec3(0, 1, 0));
	}
	else if (Street::Instance->GetCollistion(boundsTopRightWorldOld, boundsTopRightWorldNew, collisionPoint, collisionNormal))
	{
		if (m_speed > 4.0f)
		{
			static Randomizer random;

			SoundManager::GetInstance()->PlaySound((SoundManager::Sound)random.GetInt(0, 2));
		}

		float dot = sm::Vec3::Dot(collisionNormal, m_carDirection.GetReversed());
		if (dot > 0.8 && m_speed > 3.0f)
			m_speed = -3.0f;
		else
			m_speed *= 1.0f - sm::Vec3::Dot(collisionNormal, m_carDirection.GetReversed());

		collisionPoint += collisionNormal * 0.01f;

		sm::Vec3 toCollisionTarget = collisionPoint - boundsTopRightWorldOld;
		sm::Vec3 fromCollisionTarget = sm::Vec3::Reflect(collisionNormal, toCollisionTarget);
		sm::Vec3 correntPosition = boundsTopRightWorldOld + toCollisionTarget + fromCollisionTarget;
		sm::Vec3 deltaMove = collisionPoint - boundsTopRightWorldOld;

		m_carDirection = (collisionPoint - boundsBottomRightWorldOld).GetNormalized();

		m_position = oldPos + deltaMove;

		m_worldMatrix =
			sm::Matrix::TranslateMatrix(m_position) *
			sm::Matrix::CreateLookAt(m_carDirection.GetReversed(), sm::Vec3(0, 1, 0));
	}
	/*else if (Street::Instance->GetCollistion(boundsBottomRightWorldOld, boundsBottomRightWorldNew, collisionPoint, collisionNormal))
	{
		if (m_speed > 4.0f)
		{
			static Randomizer random;

			SoundManager::GetInstance()->PlaySound((SoundManager::Sound)random.GetInt(0, 2));
		}

		float dot = sm::Vec3::Dot(collisionNormal, m_carDirection.GetReversed());
		if (dot > 0.8 && m_speed > 3.0f)
			m_speed = -3.0f;
		else
			m_speed *= 1.0f - sm::Vec3::Dot(collisionNormal, m_carDirection.GetReversed());

		collisionPoint += collisionNormal * 0.01f;

		sm::Vec3 toCollisionTarget = collisionPoint - boundsBottomRightWorldOld;
		sm::Vec3 fromCollisionTarget = sm::Vec3::Reflect(collisionNormal, toCollisionTarget);
		sm::Vec3 correntPosition = boundsBottomRightWorldOld + toCollisionTarget + fromCollisionTarget;
		sm::Vec3 deltaMove = collisionPoint - boundsBottomRightWorldOld;

		m_carDirection = (boundsTopRightWorldOld - collisionPoint).GetNormalized();

		m_position = oldPos + deltaMove;

		m_worldMatrix =
			sm::Matrix::TranslateMatrix(m_position) *
			sm::Matrix::CreateLookAt(m_carDirection.GetReversed(), sm::Vec3(0, 1, 0));
	}*/
	else if (Street::Instance->GetCollistion(boundsBottomRightWorldOld, boundsBottomRightWorldNew, collisionPoint, collisionNormal))
	{
		if (m_speed > 4.0f)
		{
			static Randomizer random;

			SoundManager::GetInstance()->PlaySound((SoundManager::Sound)random.GetInt(0, 2));
		}

		m_position = oldPos + collisionNormal * 0.1f;
		m_speed = 0.0f;

		m_worldMatrix =
			sm::Matrix::TranslateMatrix(m_position) *
			sm::Matrix::CreateLookAt(m_carDirection.GetReversed(), sm::Vec3(0, 1, 0));
	}
	else if (Street::Instance->GetCollistion(boundsBottomLeftWorldOld, boundsBottomLeftWorldNew, collisionPoint, collisionNormal))
	{
		if (m_speed > 4.0f)
		{
			static Randomizer random;

			SoundManager::GetInstance()->PlaySound((SoundManager::Sound)random.GetInt(0, 2));
		}

		m_position = oldPos + collisionNormal * 0.1f;
		m_speed = 0.0f;

		m_worldMatrix =
			sm::Matrix::TranslateMatrix(m_position) *
			sm::Matrix::CreateLookAt(m_carDirection.GetReversed(), sm::Vec3(0, 1, 0));
	}
	else
		m_worldMatrix = newWorldMatrix;

	m_frontRightWheel->Transform() =
		m_frontRightWheel->m_worldMatrix *
		sm::Matrix::RotateAxisMatrix(m_wheelsAngle, 0, 1, 0) *
		m_frontRightWheel->m_worldInverseMatrix;

	m_frontLeftWheel->Transform() =
		m_frontLeftWheel->m_worldMatrix *
		sm::Matrix::RotateAxisMatrix(m_wheelsAngle, 0, 1, 0) *
		m_frontLeftWheel->m_worldInverseMatrix;
}