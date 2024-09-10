noesisModel_t *Anim_DS_Load(BYTE *fileBuffer, int bufferLen, int &numMdl, noeRAPI_t *rapi)
{
	//for vanquish, append any matching dtt files (they're just paired dat files)
	char *inFile = rapi->Noesis_GetInputName();
	BYTE *skeletonFile = NULL;
	xmlSkeleton_t xml;
	xmlAnim_t xml_anim;
	bool bparsedXml = false;
	bool bparsedAnim = false;
	if (inFile && inFile[0])
	{
		char fn[MAX_NOESIS_PATH];
		rapi->Noesis_GetExtensionlessName(fn, inFile);
		rapi->Noesis_GetDirForFilePath(fn, inFile);
		strcat_s(fn, MAX_NOESIS_PATH, "Skeleton-out.hkx");

		// parsing xml
		bparsedXml = ParseSkeleton(&xml, fn, rapi);
		bparsedAnim = ParseAnim(&xml_anim, inFile, rapi);
	}

	if (!bparsedXml || !bparsedAnim)
	{
		rapi->LogOutput("An error occured while parsing the skeleton xml file...");
		return NULL;
	}

	modelBone_t * bones = rapi->Noesis_AllocBones(xml.numBones);

	for (int i = 0; i < xml.numBones; i++)
	{
		modelBone_t *bone = bones + i;

		short parent = xml.parentindices[i];
		bone->index = i;
		bone->eData.parent = (parent >= 0) ? bones + parent : NULL;
		sprintf_s(bone->name, xml.names[i].length() + 1, xml.names[i].c_str());

		g_mfn->Math_QuatToMat(xml.quat[i].q, &bone->mat, false, false);

		g_mfn->Math_VecScaleVec(bone->mat.x1, xml.scl[i].v);
		g_mfn->Math_VecScaleVec(bone->mat.x2, xml.scl[i].v);
		g_mfn->Math_VecScaleVec(bone->mat.x3, xml.scl[i].v);
		g_mfn->Math_VecCopy(xml.trn[i].v, bone->mat.o);
	}

	rapi->rpgMultiplyBones(bones, xml.numBones);

	//char* infile = rapi->Noesis_GetInputName();
	char anim_name[MAX_NOESIS_PATH];
	rapi->Noesis_GetLocalFileName(anim_name, inFile);
	std::string anim_name_t;
	anim_name_t.append(anim_name);
	for (int i = 0; i < 10; ++i)
	{
		anim_name_t.pop_back();
	}

	strcpy_s(anim_name, anim_name_t.c_str());

	int FrameNumber = xml_anim.FrameNumber;
	int TrackNumber = xml_anim.TrackNumber;
	int FloatNumber = xml_anim.FloatNumber;

	float AnimDuration = xml_anim.AnimDuration;
	float incrFrame = xml_anim.incFrame;
	int numAnimKeys = xml_anim.numAnimKeys;

	//convert anim keys to matrices
	bool printed = false;
	RichMat43 *mats = (RichMat43 *) rapi->Noesis_UnpooledAlloc(sizeof(RichMat43)*numAnimKeys);
	for (int i = 0; i < numAnimKeys; i++)
	{
		RichQuat q = xml_anim.keys[i].rot;
		modelBone_t *bone = bones + (i % xml.numBones);
		mats[i] = q.ToMat43(true);
		mats[i][3] = xml_anim.keys[i].trn;

		mats[i][1][0] = -mats[i][1][0];
		mats[i][2][0] = -mats[i][2][0];
		mats[i][3][0] = -mats[i][3][0];
		mats[i][0][1] = -mats[i][0][1];
		mats[i][0][2] = -mats[i][0][2];
	}

	int totalFrames = FrameNumber;
	float frameRate = 30;
	noesisAnim_t *na = rapi->rpgAnimFromBonesAndMatsFinish(bones, xml.numBones, (modelMatrix_t *) mats, totalFrames, frameRate);
	rapi->Noesis_UnpooledFree(mats);
	if (na)
	{
		na->aseq = rapi->Noesis_AnimSequencesAlloc(1, totalFrames);
		for (int i = 0; i < 1; i++)
		{ //fill in the sequence info
			noesisASeq_t *seq = na->aseq->s + i;

			seq->name = rapi->Noesis_PooledString(anim_name);
			seq->startFrame = 0;
			seq->endFrame = 0 + FrameNumber - 1;
			seq->frameRate = frameRate;
		}

		numMdl = 1;
	}

	noesisModel_t * my_mdl = rapi->Noesis_AllocModelContainer(NULL, na, 1);

	return my_mdl;
}