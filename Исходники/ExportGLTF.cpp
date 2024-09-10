static void ExportSkinData(ExportContext& Context, const CSkelMeshLod& Lod, FArchive& Ar)
{
	guard(ExportSkinData);

	int numBones = Context.SkelMesh->RefSkeleton.Num();

	int MatrixBufIndex = Context.Data.AddZeroed();
	BufferData& MatrixBuf = Context.Data[MatrixBufIndex];
	MatrixBuf.Setup(numBones, "MAT4", BufferData::FLOAT, sizeof(CMat4));

	Ar.Printf(
		"  \"nodes\" : [\n"
		"    {\n"
		"      \"name\" : \"%s\",\n"
		"      \"mesh\" : 0,\n"
		"      \"skin\" : 0,\n"
		"      \"children\" : [ 1 ]\n"
		"    },\n",
		Context.MeshName);

	TArray<CCoords> BoneCoords;
	BoneCoords.AddZeroed(numBones);

	for (int boneIndex = 0; boneIndex < numBones; boneIndex++)
	{
		const CSkelMeshBone& B = Context.SkelMesh->RefSkeleton[boneIndex];

		// Find all children
		TStaticArray<int, 32> children;
		for (int j = 0; j < numBones; j++)
		{
			if (boneIndex == j) continue;
			const CSkelMeshBone& B2 = Context.SkelMesh->RefSkeleton[j];
			if (B2.ParentIndex == boneIndex)
			{
				children.Add(j);
			}
		}

		Ar.Printf(
			"    {\n"
			"      \"name\" : \"%s\",\n",
			*B.Name
		);

		// Write children
		if (children.Num())
		{
			Ar.Printf("      \"children\" : [ %d", children[0]+FIRST_BONE_NODE);
			for (int j = 1; j < children.Num(); j++)
			{
				Ar.Printf(", %d", children[j]+FIRST_BONE_NODE);
			}
			Ar.Printf(" ],\n");
		}

		// Bone transform
		CVec3 bonePos = B.Position;
		CQuat boneRot = B.Orientation;
		if (boneIndex == 0)
		{
			boneRot.Conjugate();
		}

		TransformPosition(bonePos);
		TransformRotation(boneRot);

		Ar.Printf(
			"      \"translation\" : [ %g, %g, %g ],\n"
			"      \"rotation\" : [ %g, %g, %g, %g ]\n",
			bonePos[0], bonePos[1], bonePos[2],
			boneRot.x, boneRot.y, boneRot.z, boneRot.w
		);

		boneRot.w *= -1;

		CCoords& BC = BoneCoords[boneIndex];
		BC.origin = bonePos;
		boneRot.ToAxis(BC.axis);
		if (boneIndex)
		{
			// World coordinate
			BoneCoords[B.ParentIndex].UnTransformCoords(BC, BC);
		}
		CCoords InvCoords;
		InvertCoords(BC, InvCoords);

		CMat4 BC4x4(InvCoords);
		MatrixBuf.Put(BC4x4);

		// Closing brace
		Ar.Printf(
			"    }%s\n",
			boneIndex == (numBones-1) ? "" : ","
		);
	}

	// Close "nodes" array
	Ar.Printf("  ],\n");

	// Make "skins"
	Ar.Printf(
		"  \"skins\" : [\n"
		"    {\n"
		"      \"inverseBindMatrices\" : %d,\n"
		"      \"skeleton\" : 1,\n"
		"      \"joints\" : [",
		MatrixBufIndex
	);
	for (int i = 0; i < numBones; i++)
	{
		if ((i & 31) == 0) Ar.Printf("\n        ");
		Ar.Printf("%d%s", i+FIRST_BONE_NODE, (i == numBones-1) ? "" : ",");
	}
	Ar.Printf(
		"\n"
		"      ]\n"
		"    }\n"
		"  ],\n"
	);

	unguard;
}