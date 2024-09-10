void ExportMd5Anim(const CAnimSet *Anim)
{
	guard(ExportMd5Anim);

	int numBones = Anim->TrackBoneNames.Num();
	UObject *OriginalAnim = Anim->OriginalAnim;

	for (int AnimIndex = 0; AnimIndex < Anim->Sequences.Num(); AnimIndex++)
	{
		int i;
		const CAnimSequence &S = Anim->Sequences[AnimIndex];

		FArchive *Ar = CreateExportArchive(OriginalAnim, "%s/%s.md5anim", OriginalAnim->Name, *S.Name);
		if (!Ar) continue;

		Ar->Printf(
			"MD5Version 10\n"
			"commandline \"Created with UE Viewer\"\n"
			"\n"
			"numFrames %d\n"
			"numJoints %d\n"
			"frameRate %g\n"
			"numAnimatedComponents %d\n"
			"\n",
			S.NumFrames,
			numBones,
			S.Rate,
			numBones * 6
		);

		// skeleton
		Ar->Printf("hierarchy {\n");
		for (i = 0; i < numBones; i++)
		{
			Ar->Printf("\t\"%s\" %d %d %d\n", *Anim->TrackBoneNames[i], (i == 0) ? -1 : 0, 63, i * 6);
				// ParentIndex is unknown for UAnimSet, so always write "0"
				// here: 6 is number of components per frame, 63 = (1<<6)-1 -- flags "all components are used"
		}

		// bounds
		Ar->Printf("}\n\nbounds {\n");
		for (i = 0; i < S.NumFrames; i++)
			Ar->Printf("\t( -100 -100 -100 ) ( 100 100 100 )\n");	//!! dummy
		Ar->Printf("}\n\n");

		// baseframe and frames
		for (int Frame = -1; Frame < S.NumFrames; Frame++)
		{
			int t = Frame;
			if (Frame == -1)
			{
				Ar->Printf("baseframe {\n");
				t = 0;
			}
			else
				Ar->Printf("frame %d {\n", Frame);

			for (int b = 0; b < numBones; b++)
			{
				CVec3 BP;
				CQuat BO;
				S.Tracks[b].GetBonePosition(t, S.NumFrames, false, BP, BO);
				if (!b) BO.Conjugate();			// root bone
#if MIRROR_MESH
				BO.y  *= -1;
				BO.w  *= -1;
				BP[1] *= -1;					// y
#endif
				if (BO.w < 0) BO.Negate();		// W-component of quaternion will be removed ...
				if (Frame < 0)
					Ar->Printf("\t( %f %f %f ) ( %.10f %.10f %.10f )\n", VECTOR_ARG(BP), BO.x, BO.y, BO.z);
				else
					Ar->Printf("\t%f %f %f %.10f %.10f %.10f\n", VECTOR_ARG(BP), BO.x, BO.y, BO.z);
			}
			Ar->Printf("}\n\n");
		}

		delete Ar;
	}

	unguard;
}