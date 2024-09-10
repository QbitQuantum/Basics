SAssPiece* CAssParser::LoadPiece(SAssModel* model, aiNode* node, const LuaTable& metaTable)
{
	//! Create new piece
	++model->numPieces;
	SAssPiece* piece = new SAssPiece;
	piece->type = MODELTYPE_OTHER;
	piece->node = node;
	piece->model = model;
	piece->isEmpty = (node->mNumMeshes == 0);

	if (node->mParent) {
		piece->name = std::string(node->mName.data);
	} else {
		//FIXME is this really smart?
		piece->name = "root"; //! The real model root
	}

	//! find a new name if none given or if a piece with the same name already exists
	if (piece->name.empty()) {
		piece->name = "piece";
	}
	ModelPieceMap::const_iterator it = model->pieces.find(piece->name);
	if (it != model->pieces.end()) {
		char buf[64];
		int i = 0;
		while (it != model->pieces.end()) {
			SNPRINTF(buf, 64, "%s%02i", piece->name.c_str(), i++);
			it = model->pieces.find(buf);
		}
		piece->name = buf;
	}
	LOG_S(LOG_SECTION_PIECE, "Converting node '%s' to piece '%s' (%d meshes).",
			node->mName.data, piece->name.c_str(), node->mNumMeshes);

	//! Load additional piece properties from metadata
	const LuaTable& pieceTable = metaTable.SubTable("pieces").SubTable(piece->name);
	if (pieceTable.IsValid()) {
		LOG_S(LOG_SECTION_PIECE, "Found metadata for piece '%s'",
				piece->name.c_str());
	}

	//! Load transforms
	LoadPieceTransformations(piece, pieceTable);

	//! Update piece min/max extents
	for (unsigned meshListIndex = 0; meshListIndex < node->mNumMeshes; meshListIndex++) {
		unsigned int meshIndex = node->mMeshes[meshListIndex];
		SAssModel::MinMax& minmax = model->mesh_minmax[meshIndex];
		piece->mins.x = std::min(piece->mins.x, minmax.mins.x);
		piece->mins.y = std::min(piece->mins.y, minmax.mins.y);
		piece->mins.z = std::min(piece->mins.z, minmax.mins.z);
		piece->maxs.x = std::max(piece->maxs.x, minmax.maxs.x);
		piece->maxs.y = std::max(piece->maxs.y, minmax.maxs.y);
		piece->maxs.z = std::max(piece->maxs.z, minmax.maxs.z);
	}


	//! Check if piece is special (ie, used to set Spring model properties)
	if (strcmp(node->mName.data, "SpringHeight") == 0) {
		//! Set the model height to this nodes Z value
		if (!metaTable.KeyExists("height")) {
			model->height = piece->offset.z;
			LOG_S(LOG_SECTION_MODEL,
					"Model height of %f set by special node 'SpringHeight'",
					model->height);
		}
		--model->numPieces;
		delete piece;
		return NULL;
	}
	if (strcmp(node->mName.data, "SpringRadius") == 0) {
		if (!metaTable.KeyExists("midpos")) {
			model->relMidPos = float3(piece->offset.x, piece->offset.z, piece->offset.y); //! Y and Z are swapped because this piece isn't rotated
			LOG_S(LOG_SECTION_MODEL,
					"Model midpos of (%f,%f,%f) set by special node 'SpringRadius'",
					model->relMidPos.x, model->relMidPos.y, model->relMidPos.z);
		}
		if (!metaTable.KeyExists("radius")) {
			if (piece->maxs.x <= 0.00001f) {
				model->radius = piece->scale.x; //! the blender import script only sets the scale property
			} else {
				model->radius = piece->maxs.x; //! use the transformed mesh extents
			}
			LOG_S(LOG_SECTION_MODEL,
					"Model radius of %f set by special node 'SpringRadius'",
					model->radius);
		}
		--model->numPieces;
		delete piece;
		return NULL;
	}


	//! Get vertex data from node meshes
	for (unsigned meshListIndex = 0; meshListIndex < node->mNumMeshes; ++meshListIndex) {
		unsigned int meshIndex = node->mMeshes[meshListIndex];
		LOG_SL(LOG_SECTION_PIECE, L_DEBUG, "Fetching mesh %d from scene",
				meshIndex);
		aiMesh* mesh = model->scene->mMeshes[meshIndex];
		std::vector<unsigned> mesh_vertex_mapping;
		//! extract vertex data
		LOG_SL(LOG_SECTION_PIECE, L_DEBUG,
				"Processing vertices for mesh %d (%d vertices)",
				meshIndex, mesh->mNumVertices);
		LOG_SL(LOG_SECTION_PIECE, L_DEBUG,
				"Normals: %s Tangents/Bitangents: %s TexCoords: %s",
				(mesh->HasNormals() ? "Y" : "N"),
				(mesh->HasTangentsAndBitangents() ? "Y" : "N"),
				(mesh->HasTextureCoords(0) ? "Y" : "N"));

		// FIXME add piece->vertices.reserve()
		for (unsigned vertexIndex= 0; vertexIndex < mesh->mNumVertices; ++vertexIndex) {
			SAssVertex vertex;

			//! vertex coordinates
			//LOG_SL(LOG_SECTION_PIECE, L_DEBUG, "Fetching vertex %d from mesh", vertexIndex);
			const aiVector3D& aiVertex = mesh->mVertices[vertexIndex];
			vertex.pos.x = aiVertex.x;
			vertex.pos.y = aiVertex.y;
			vertex.pos.z = aiVertex.z;

			//LOG_SL(LOG_SECTION_PIECE, L_DEBUG, "vertex position %d: %f %f %f", vertexIndex, vertex.pos.x, vertex.pos.y, vertex.pos.z);

			//! vertex normal
			LOG_SL(LOG_SECTION_PIECE, L_DEBUG, "Fetching normal for vertex %d",
					vertexIndex);
			const aiVector3D& aiNormal = mesh->mNormals[vertexIndex];
			vertex.hasNormal = !IS_QNAN(aiNormal);
			if (vertex.hasNormal) {
				vertex.normal.x = aiNormal.x;
				vertex.normal.y = aiNormal.y;
				vertex.normal.z = aiNormal.z;
				//LOG_SL(LOG_SECTION_PIECE, L_DEBUG, "vertex normal %d: %f %f %f",vertexIndex, vertex.normal.x, vertex.normal.y,vertex.normal.z);
			}

			//! vertex tangent, x is positive in texture axis
			if (mesh->HasTangentsAndBitangents()) {
				LOG_SL(LOG_SECTION_PIECE, L_DEBUG,
						"Fetching tangent for vertex %d", vertexIndex );
				const aiVector3D& aiTangent = mesh->mTangents[vertexIndex];
				const aiVector3D& aiBitangent = mesh->mBitangents[vertexIndex];
				vertex.hasTangent = !IS_QNAN(aiBitangent) && !IS_QNAN(aiTangent);

				const float3 tangent(aiTangent.x, aiTangent.y, aiTangent.z);
				//LOG_SL(LOG_SECTION_PIECE, L_DEBUG, "vertex tangent %d: %f %f %f",vertexIndex, tangent.x, tangent.y,tangent.z);
				piece->sTangents.push_back(tangent);

				const float3 bitangent(aiBitangent.x, aiBitangent.y, aiBitangent.z);
				//LOG_SL(LOG_SECTION_PIECE, L_DEBUG, "vertex bitangent %d: %f %f %f",vertexIndex, bitangent.x, bitangent.y,bitangent.z);
				piece->tTangents.push_back(bitangent);
			}

			//! vertex texcoords
			if (mesh->HasTextureCoords(0)) {
				vertex.textureX = mesh->mTextureCoords[0][vertexIndex].x;
				vertex.textureY = mesh->mTextureCoords[0][vertexIndex].y;
				//LOG_SL(LOG_SECTION_PIECE, L_DEBUG, "vertex texcoords %d: %f %f", vertexIndex, vertex.textureX, vertex.textureY);
			}

			mesh_vertex_mapping.push_back(piece->vertices.size());
			piece->vertices.push_back(vertex);
		}

		//! extract face data
		// FIXME add piece->vertexDrawOrder.reserve()
		LOG_SL(LOG_SECTION_PIECE, L_DEBUG,
				"Processing faces for mesh %d (%d faces)",
				meshIndex, mesh->mNumFaces);
		for (unsigned faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
			const aiFace& face = mesh->mFaces[faceIndex];
			//! get the vertex belonging to the mesh
			for (unsigned vertexListID = 0; vertexListID < face.mNumIndices; ++vertexListID) {
				unsigned int vertexID = mesh_vertex_mapping[face.mIndices[vertexListID]];
				//LOG_SL(LOG_SECTION_PIECE, L_DEBUG, "face %d vertex %d", faceIndex, vertexID);
				piece->vertexDrawOrder.push_back(vertexID);
			}
		}
	}

	//! collision volume for piece (not sure about these coords)
	// FIXME add metatable tags for this!!!!
	const float3 cvScales = piece->maxs - piece->mins;
	const float3 cvOffset = (piece->maxs - piece->offset) + (piece->mins - piece->offset);
	//const float3 cvOffset(piece->offset.x, piece->offset.y, piece->offset.z);
	piece->colvol = new CollisionVolume("box", cvScales, cvOffset, CollisionVolume::COLVOL_HITTEST_CONT);

	//! Get parent name from metadata or model
	if (pieceTable.KeyExists("parent")) {
		piece->parentName = pieceTable.GetString("parent", "");
	} else if (node->mParent) {
		if (node->mParent->mParent) {
			piece->parentName = std::string(node->mParent->mName.data);
		} else { //! my parent is the root, which gets renamed
			piece->parentName = "root";
		}
	} else {
		piece->parentName = "";
	}

	LOG_S(LOG_SECTION_PIECE, "Loaded model piece: %s with %d meshes",
			piece->name.c_str(), node->mNumMeshes);

	//! Verbose logging of piece properties
	LOG_S(LOG_SECTION_PIECE, "piece->name: %s", piece->name.c_str());
	LOG_S(LOG_SECTION_PIECE, "piece->parent: %s", piece->parentName.c_str());

	//! Recursively process all child pieces
	for (unsigned int i = 0; i < node->mNumChildren; ++i) {
		LoadPiece(model, node->mChildren[i], metaTable);
	}

	model->pieces[piece->name] = piece;
	return piece;
}