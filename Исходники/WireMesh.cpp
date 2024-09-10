//----------------------------------------------------------------------------
void Mesh::GenerateNormals(Bool ignoreHardEdges)
{
	VertexBuffer* pPositions = GetPositionBuffer();
	if (!pPositions)
	{
		return;
	}

	VertexBuffer* pNormals = GetNormalBuffer();
	if (!pNormals)
	{
		return;
	}

	UShort* const pIndices = mspIndexBuffer->GetData();

	// collect the triangles each vertex is part of
	TArray<TArray<UInt> > buckets(pPositions->GetQuantity());
	buckets.SetQuantity(pPositions->GetQuantity());

	UInt triIndex = 0;
	for (UInt i = 0; i < mspIndexBuffer->GetQuantity(); i += 3)
	{
		buckets[pIndices[i]].Append(triIndex);
		buckets[pIndices[i+1]].Append(triIndex);
		buckets[pIndices[i+2]].Append(triIndex);
		triIndex++;
	}

	if (ignoreHardEdges)
	{
		for (UInt j = 0; j < pPositions->GetQuantity(); j++)
		{
			const Vector3F& vertex = pPositions->Position3(j);
			for (UInt i = j+1; i < pPositions->GetQuantity(); i++)
			{
				if (vertex == pPositions->Position3(i))
				{
					UInt origCount = buckets[j].GetQuantity();
					for (UInt k = 0; k < buckets[i].GetQuantity(); k++)
					{
						buckets[j].Append(buckets[i][k]);
					}

					for (UInt k = 0; k < origCount; k++)
					{
						buckets[i].Append(buckets[j][k]);
					}
				}
			}
		}
	}

	// calculate the normals of the individual triangles
	TArray<Vector3F> faceNormals(mspIndexBuffer->GetQuantity()/3);
	for (UInt i = 0; i < mspIndexBuffer->GetQuantity(); i +=3)
	{
		Vector3F v1 = pPositions->Position3(pIndices[i+1]) - pPositions->
			Position3(pIndices[i]);
		Vector3F v2 = pPositions->Position3(pIndices[i+2]) - pPositions->
			Position3(pIndices[i+1]);

		Vector3F normal = v2.Cross(v1);
		normal.Normalize();
		faceNormals.Append(normal);
	}

	// calculate the normal of the vertex from the normals of its faces
	for (UInt i = 0; i < buckets.GetQuantity(); i++)
	{
		Vector3F normal(Vector3F::ZERO);
		for (UInt j = 0; j < buckets[i].GetQuantity(); j++)
		{
			normal += faceNormals[buckets[i][j]];
		}

		if (buckets[i].GetQuantity() > 0)
		{
			normal /= static_cast<Float>(buckets[i].GetQuantity());
			normal.Normalize();
		}
		else
		{
			// vertex not used in mesh, use a default normal
			normal = Vector3F::UNIT_X;
		}

		pNormals->Normal3(i) = normal;
	}
}