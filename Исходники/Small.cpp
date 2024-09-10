void Small::Separation(float weight)
{
	XMMATRIX rotationmatrix;
	XMVECTOR closestflockmatedifference = {-1000.0f, -1000.0f, 0, 0};

	bool isalone = true;

	for (int i = 0; i < SmallVector->size(); i++)
	{
		if (SmallVector->at(i)->ID != this->ID)
		{
			if (SmallVector->at(i)->Chasing)
			{
				if (Target->ID == SmallVector->at(i)->Target->ID)
				{
					XMVECTOR tempvector = {XMVectorGetX(SmallVector->at(i)->Location), XMVectorGetY(SmallVector->at(i)->Location), 0, 0};
					XMVECTOR tempdifference = Location - tempvector;

					if (XMVectorGetX(XMVector2Length(tempdifference)) < XMVectorGetX(XMVector2Length(closestflockmatedifference)))
					{
						closestflockmatedifference = tempdifference;
						isalone = false;
					}
				}
			}
		}
	}

	if (!isalone)
	{
		XMVECTOR leftvector = {0, 0, 0, 0};
		XMVECTOR rightvector = {0, 0, 0, 0};

		XMMATRIX rotationmatrixleft = XMMatrixRotationZ(float(M_PI)/2.0f);
		XMMATRIX rotationmatrixright = XMMatrixRotationZ(float(M_PI)/-2.0f);

		leftvector = XMVector3Transform(Direction, rotationmatrixleft);
		rightvector = XMVector3Transform(Direction, rotationmatrixright);

		Direction = XMVector2Normalize(Direction);

		XMVECTOR differencevector = closestflockmatedifference;

		differencevector = XMVector2Normalize(differencevector);

		float radiandifference = XMVectorGetX(XMVector2AngleBetweenNormals(leftvector, differencevector));
		float epsilon = XMVectorGetX(XMVector2AngleBetweenNormals(Direction, differencevector));

		if (radiandifference <= float(M_PI/2.0f)) 
		{
			rotationmatrix = XMMatrixRotationZ(weight);

			if (epsilon <= (1.25f * weight))
			{
				Direction = differencevector;
				Direction = XMVector2Normalize(Direction);

			}
			else
			{
				Direction = XMVector3Transform(Direction, rotationmatrix);
				Direction = XMVector2Normalize(Direction);
			}
		}
		else if (radiandifference > float(M_PI/2.0f)) 
		{
			rotationmatrix = XMMatrixRotationZ(-weight);

			if (epsilon <= (1.25f * weight))
			{
				Direction = differencevector;
				Direction = XMVector2Normalize(Direction);

			}
			else
			{
				Direction = XMVector3Transform(Direction, rotationmatrix);
				Direction = XMVector2Normalize(Direction);
			}
		}
	}
}