bool CImporter::Import(const string& filename)
{
	unsigned int flags = aiProcess_JoinIdenticalVertices;
	flags |= aiProcess_FlipUVs;
	flags |= aiProcess_Triangulate;
	flags |= aiProcess_GenSmoothNormals;
	flags |= aiProcess_LimitBoneWeights;
	flags |= aiProcess_ValidateDataStructure;
	flags |= aiProcess_ImproveCacheLocality;
	flags |= aiProcess_RemoveRedundantMaterials;
	flags |= aiProcess_FixInfacingNormals;
	flags |= aiProcess_FindInvalidData;
	flags |= aiProcess_OptimizeMeshes;
	flags |= aiProcess_SplitByBoneCount;
	flags |= aiProcess_TransformUVCoords;
	flags |= aiProcess_SortByPType;
	flags |= aiProcess_RemoveComponent;
	flags |= aiProcess_MakeLeftHanded;
	//flags |= aiProcess_FlipWindingOrder;
	//flags |= aiProcess_OptimizeGraph;

	Importer importer;
	if (!importer.ValidateFlags(flags))
	{
		qCritical("Import flags not supported");
		return false;
	}

	if (!importer.IsExtensionSupported(('.' % GetExtension(filename)).toLocal8Bit().constData()))
	{
		qCritical("This file format isn't supported");
		return false;
	}

	importer.SetPropertyInteger(AI_CONFIG_PP_LBW_MAX_WEIGHTS, 2);
	importer.SetPropertyInteger(AI_CONFIG_PP_SBBC_MAX_BONES, MAX_BONES);
	importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, aiComponent_TANGENTS_AND_BITANGENTS
		| aiComponent_COLORS
		| aiComponent_TEXTURES
		| aiComponent_LIGHTS
		| aiComponent_CAMERAS);

	m_scene = (aiScene*)importer.ReadFile(filename.toLocal8Bit().constData(), flags);
	if (!m_scene)
	{
		qCritical(importer.GetErrorString());
		return false;
	}

	if (!m_scene->HasMeshes() || !m_scene->mRootNode || m_scene->mRootNode->mNumChildren == 0)
	{
		qCritical("No meshes in this scene");
		return false;
	}

	m_obj3D = m_mesh->m_elements[0].obj = new CObject3D(m_mesh->m_device);
	m_obj3D->m_ID = _getNewID();

	const string filenameToLower = QFileInfo(filename).fileName().toLower();

	if (filenameToLower.startsWith("mvr")
		|| filenameToLower.startsWith("part")
		|| filenameToLower.startsWith("item"))
		m_externBones = true;

	_importScene();

	if (!m_obj3D->InitDeviceObjects())
	{
		qCritical(("Can't init object3D device objects '" % filename % "'").toLocal8Bit().data());
		return false;
	}

	importer.FreeScene();
	return true;
}