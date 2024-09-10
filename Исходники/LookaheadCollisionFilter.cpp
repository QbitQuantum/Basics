//
// Now that have the spaces in the Broad Collision Zone,
//	determine which of those are within the Lookahead Zone.
//
void LookaheadCollisionFilter::Filter(
	list<Space *> * pFiltered,	// in, out
	list<Space *> * pCollided,
	float2 fScreenDimensions,
	list<float2> * fCollisionZonePixels,
	ActionParameter * pActionParameter)
{
	float2 vertices[5];
	vertices[LEFT_TOP] = *(fCollisionZonePixels->begin());
	vertices[RIGHT_TOP] = *(next(fCollisionZonePixels->begin()));
	vertices[RIGHT_BOTTOM] = *(next(next(fCollisionZonePixels->begin())));
	vertices[LEFT_BOTTOM] = *(next(next(next(fCollisionZonePixels->begin()))));
	vertices[4] = *(next(next(next(next(fCollisionZonePixels->begin())))));

	// These never change and don't need to be inside the loops.
	XMVECTOR vecCollidedVertices[4];

	vecCollidedVertices[LEFT_TOP] =
		XMVectorSet(
			GRID->GetColumnWidth() / -2.0f,
			GRID->GetRowHeight() / -2.0f,
			0.0f,
			0.0f);

	vecCollidedVertices[RIGHT_TOP] =
		XMVectorSet(
			GRID->GetColumnWidth() / 2.0f,
			GRID->GetRowHeight() / -2.0f,
			0.0f,
			0.0f);

	vecCollidedVertices[RIGHT_BOTTOM] =
		XMVectorSet(
			(GRID->GetColumnWidth() / 2.0f),
			GRID->GetRowHeight() / 2.0f,
			0.0f,
			0.0f);

	vecCollidedVertices[LEFT_BOTTOM] =
		XMVectorSet(
			GRID->GetColumnWidth() / -2.0f,
			GRID->GetRowHeight() / 2.0f,
			0.0f,
			0.0f);

	// For each line segment of the lookahead zone...
	for (int i = 0; i < 4; i++)
	{
		// Need to determine the line equations 
		//	that make up each side of the lookahead zone.
		//	Need to consider rotation when determining
		//	how to calculate slope of each line.

		// Check which vertex is on the left.
		float2 fPt1 = vertices[i % 4];
		float2 fPt2 = vertices[(i + 1) % 4];

		LineSegment * currentLookaheadZoneLineSegment = 
			new LineSegment(fPt1, fPt2);

		list<Space *>::const_iterator iteratorSpaces;

		// For each of the Spaces in the broad zone,
		//	determine their vertices.
		for (iteratorSpaces = pCollided->begin();
			iteratorSpaces != pCollided->end();
			iteratorSpaces++)
		{
			float2 fCollidedCenter = (*iteratorSpaces)->GetLocationRatio();

			float fCollidedRotation = 
				FLOAT((*iteratorSpaces)->GetAttributes()->LookupValue(A_ROTATION));

			XMMATRIX translationMatrix =
				XMMatrixTransformation2D(
					XMVectorSet(
						fCollidedCenter.x * fScreenDimensions.x,
						fCollidedCenter.y * fScreenDimensions.y,
						0.0f,
						0.0f),
					1.0f,
					XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f),
					XMVectorSet(
						fCollidedCenter.x * fScreenDimensions.x,
						fCollidedCenter.y * fScreenDimensions.y,
						0.0f,
						0.0f),
					0.0f,
					XMVectorSet(
						fCollidedCenter.x * fScreenDimensions.x,
						fCollidedCenter.y * fScreenDimensions.y,
						0.0f,
						0.0f));


			XMMATRIX rotationMatrix =
				XMMatrixTransformation2D(
					XMVectorSet(
						fCollidedCenter.x * fScreenDimensions.x,
						fCollidedCenter.y * fScreenDimensions.y,
						0.0f,
						0.0f),
					1.0f,
					XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f),
					XMVectorSet(
						fCollidedCenter.x * fScreenDimensions.x,
						fCollidedCenter.y * fScreenDimensions.y,
						0.0f,
						0.0f),
					XMConvertToRadians(360.0f - fCollidedRotation),
					XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));

			XMVECTOR vecTransform[4];

			for (int i = LEFT_TOP; i <= LEFT_BOTTOM; i++)
			{
				vecTransform[i] = XMVector3Transform(vecCollidedVertices[i], translationMatrix * rotationMatrix);
			}

			LineSegment lineSegments[4];

			// Locations (i.e. LEFT_TOP, etc) are relative due east (0 degrees).
			lineSegments[0] = 
				LineSegment
				{
					float2 { XMVectorGetX(vecTransform[LEFT_TOP]), XMVectorGetY(vecTransform[LEFT_TOP]) },
					float2 { XMVectorGetX(vecTransform[RIGHT_TOP]), XMVectorGetY(vecTransform[RIGHT_TOP]) }
				};

			lineSegments[1] =
				LineSegment
				{
					float2{ XMVectorGetX(vecTransform[RIGHT_TOP]), XMVectorGetY(vecTransform[RIGHT_TOP]) },
					float2{ XMVectorGetX(vecTransform[RIGHT_BOTTOM]), XMVectorGetY(vecTransform[RIGHT_BOTTOM]) }
				};

			lineSegments[2] =
				LineSegment
				{
					float2{ XMVectorGetX(vecTransform[RIGHT_BOTTOM]), XMVectorGetY(vecTransform[RIGHT_BOTTOM]) },
					float2{ XMVectorGetX(vecTransform[LEFT_BOTTOM]), XMVectorGetY(vecTransform[LEFT_BOTTOM]) }
				};

			lineSegments[3] =
				LineSegment
				{
					float2{ XMVectorGetX(vecTransform[LEFT_BOTTOM]), XMVectorGetY(vecTransform[LEFT_BOTTOM]) },
					float2{ XMVectorGetX(vecTransform[LEFT_TOP]), XMVectorGetY(vecTransform[LEFT_TOP]) }
				};

			for (int i = 0; i <= 3; i++)
			{
				float fIntersectionX = 0.0f;
				float fIntersectionY = 0.0f;

				if (Utils::DoLinesIntersect(
					*currentLookaheadZoneLineSegment,
					lineSegments[i],
					&fIntersectionX,
					&fIntersectionY))
				{
					pFiltered->push_back(*iteratorSpaces);
				}
			}	
		}

		delete currentLookaheadZoneLineSegment;
	}
}