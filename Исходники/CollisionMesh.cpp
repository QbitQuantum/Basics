bool CollisionMesh::CheckCollisionsCustom(CollisionMesh &otherMesh)
{
  bool collision = false;
  std::vector<XMFLOAT3> convexHull;

  std::vector<VPCNTDesc> vertices = GetVertices();
  std::vector<VPCNTDesc> otherVertices = otherMesh.GetVertices();
  XMMATRIX otherWorld = otherMesh.GetWorldTransform();
  XMMATRIX world = GetWorldTransform();
  XMFLOAT3 origin = XMFLOAT3(0.0f, 0.0f, 0.0f);

  // Create a vector to ease the inversion calculation (we want the opposite direction for the translation vector).
  XMVECTOR inverse = XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f);
  
  XMVECTOR ourOriginDisplacement = XMVector3Transform(XMVectorSet(origin.x, origin.y, origin.z, 0.0f), world);
  XMMATRIX ourOriginTransform = XMMatrixTranslationFromVector(XMVectorMultiply(ourOriginDisplacement, inverse));

  // This is used for the purposes of moving the normals of the other object back to around (0, 0, 0).
  XMVECTOR theirOriginDisplacement = XMVector3Transform(XMVectorSet(origin.x, origin.y, origin.z, 0.0f), otherWorld);
  XMMATRIX theirOriginTransform = XMMatrixTranslationFromVector(XMVectorMultiply(theirOriginDisplacement, inverse));

  XMMATRIX ourOriginTranslatedWorld = world * ourOriginTransform;
  XMMATRIX theirOriginTranslatedWorld = otherWorld * ourOriginTransform;
  XMMATRIX theirOriginTranslatedWorldNormalAdjustment = theirOriginTransform * otherWorld;

  // Pre-multiply the model's vertices so as to avoid transforming them during comparison.
  for (int vertIndex = 0; vertIndex < vertices.size(); vertIndex++)
  {
    XMStoreFloat3(&vertices[vertIndex].Position, XMVector3Transform(XMLoadFloat3(&vertices[vertIndex].Position), ourOriginTranslatedWorld));
    XMStoreFloat3(&vertices[vertIndex].Normal, XMVector3Transform(XMLoadFloat3(&vertices[vertIndex].Normal), ourOriginTranslatedWorld));
  }

  for (int otherVertIndex = 0; otherVertIndex < otherVertices.size(); otherVertIndex++)
  {
    XMStoreFloat3(&otherVertices[otherVertIndex].Position, XMVector3Transform(XMLoadFloat3(&otherVertices[otherVertIndex].Position), theirOriginTranslatedWorld));
    XMStoreFloat3(&otherVertices[otherVertIndex].Normal, XMVector3Transform(XMLoadFloat3(&otherVertices[otherVertIndex].Normal), theirOriginTranslatedWorldNormalAdjustment));
  }

  int potentialCollisions = 0;
  std::vector<XMFLOAT3> positions;

  // Now that the pre-multiplication is done, time to do our first-case checking: are we inside of it?
  for (int vertIndex = 0; vertIndex < vertices.size(); vertIndex++)
  {
    bool localCollision = true;
    XMVECTOR ourVertex = XMLoadFloat3(&vertices[vertIndex].Position);
    XMVECTOR ourNormal = XMLoadFloat3(&vertices[vertIndex].Normal);

    // For each vertex in our mesh, we'll check to see if it resides inside our other mesh.
    for (int otherVertIndex = 0; otherVertIndex < otherVertices.size(); otherVertIndex++)
    {
      XMVECTOR otherVertex = XMLoadFloat3(&otherVertices[otherVertIndex].Position);
      XMVECTOR otherNormal = XMLoadFloat3(&otherVertices[otherVertIndex].Normal);

      XMVECTOR difference = XMVectorSubtract(ourVertex, otherVertex);
      XMFLOAT3 differenceDotValue, normalDotValue;
      XMVECTOR diffLength = XMVector3Length(difference);
      XMVECTOR normLength = XMVector3Length(otherNormal);
      XMVECTOR magnitude = XMVectorMultiply(diffLength, normLength);

      XMStoreFloat3(&differenceDotValue, XMVectorDivide(XMVector3Dot(difference, otherNormal), magnitude));
      // At this point, we should have the cosine of the angle.
      float angleInRads = acosf(differenceDotValue.x);
      float angleInDegs = XMConvertToDegrees(angleInRads);

      XMStoreFloat3(&normalDotValue, XMVector3Dot(ourNormal, otherNormal));

      if (angleInDegs < 90.0f)
      {
        localCollision = false;
      }
    }

    if (localCollision)
    {
      positions.push_back(vertices[vertIndex].Position);
    }
  }

  if (positions.empty())
  {
    // Time to do our second-case checking: is it inside of us?
    for (int otherVertIndex = 0; otherVertIndex < otherVertices.size(); otherVertIndex++)
    {
      bool localCollision = true;
      XMVECTOR otherVertex = XMLoadFloat3(&otherVertices[otherVertIndex].Position);
      XMVECTOR otherNormal = XMVector3Normalize(XMLoadFloat3(&otherVertices[otherVertIndex].Normal));

      // For each vertex in our mesh, we'll check to see if it resides inside our other mesh.
      for (int vertIndex = 0; vertIndex < vertices.size(); vertIndex++)
      {
        XMVECTOR ourVertex = XMLoadFloat3(&vertices[vertIndex].Position);
        XMVECTOR ourNormal = XMVector3Normalize(XMLoadFloat3(&vertices[vertIndex].Normal));

        XMVECTOR difference = XMVectorSubtract(otherVertex, ourVertex);
        XMFLOAT3 differenceDotValue, normalDotValue;
        XMVECTOR diffLength = XMVector3Length(difference);
        XMVECTOR normLength = XMVector3Length(ourNormal);
        XMVECTOR magnitude = XMVectorMultiply(diffLength, normLength);

        XMStoreFloat3(&differenceDotValue, XMVectorDivide(XMVector3Dot(difference, ourNormal), magnitude));
        // At this point, we should have the cosine of the angle.
        float angleInRads = acosf(differenceDotValue.x);
        float angleInDegs = XMConvertToDegrees(angleInRads);

        XMStoreFloat3(&normalDotValue, XMVector3Dot(ourNormal, otherNormal));

        if (angleInDegs < 90.0f)
        {
          localCollision = false;
        }
      }

      if (localCollision)
      {
        positions.push_back(otherVertices[otherVertIndex].Position);
      }
    }
  }

  if(positions.size())
  {
    mDelegate->CollisionOccurred(otherMesh.mDelegate);
    otherMesh.mDelegate->CollisionOccurred(mDelegate);
  }
  return positions.size();
}