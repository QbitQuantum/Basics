//----------------------------------------------------------------------------------
bool Helper_ProcessFace(IGameMesh * gM,
                        unsigned int Index,
                        const AffineParts & PRS,
                        const Matrix3 & world_to_obj,
                        MatFaceMapType & matface_map,
                        TriMapType     & tri_map,
                        unsigned int & MaxFaceIdx)
{
    FaceEx *pFace		= gM->GetFace(Index);
    IGameMaterial *pIGMat = gM->GetMaterialFromFace(Index);
    bool HasTexVerts	= gM->GetNumberOfTexVerts() ? true : false;
    bool HasCVerts		= gM->GetNumberOfColorVerts() ? true : false;
    unsigned int smg_id = pFace->smGrp; // smooth group
    unsigned int mat_id = ExporterMAX::GetExporter()->FindMaterialIdx(pIGMat);
    IGameSkin *skin = NULL;

    const int numMod = gM->GetNumModifiers();

    if (numMod > 0)
    {
        for (int i = 0; i < numMod; i++)     // check for skin modifier
        {
            IGameModifier *pM = gM->GetIGameModifier(i);
            if (pM->IsSkin()) {
                skin = (IGameSkin*)pM; // skin modifier
            }
        }
    }

    mesh_opt * m_opt = NULL;

    // lets sort by material and find the corresponding mesh_opt
    MatFaceMapIt it_matfacemap = matface_map.find(mat_id);

    if (it_matfacemap == matface_map.end()) // no corresponding mesh, allocate new face holder
    {
        m_opt = new mesh_opt();
        matface_map.insert(MatFaceMapPair(mat_id, m_opt));
    }
    else
    {
        m_opt = (*it_matfacemap).second;
    }

    for (int j = 0; j < 3; ++j) // build the face
    {
        vert_opt face;
        unsigned int idx;
        unsigned int ori_face_idx = pFace->vert[j]; // get index into the vertex array
        unsigned int face_idx = ori_face_idx;

        bool create_face = false;

        // build the face as expected
        face.smg_id = smg_id; // smooth group

        if (HasTexVerts)
        {
            idx = pFace->texCoord[j]; // get index into the standard mapping channel

            if (idx != BAD_IDX)
            {
                face.t.x = gM->GetTexVertex(idx).x;
                face.t.y = gM->GetTexVertex(idx).y;
            }
        }

        if (HasCVerts)
        {
            idx = pFace->color[j];
            face.c.x = gM->GetColorVertex(idx).x;  // get vertex color
            face.c.y = gM->GetColorVertex(idx).y;
            face.c.z = gM->GetColorVertex(idx).z;
            face.c.w = 1.f;

        } else {
            face.c = Vector4f(1.f, 1.f, 1.f, 1.f);
        }

        Tab<int> mapNums = gM->GetActiveMapChannelNum();
        face.num_tmaps = mapNums.Count();

        if (face.num_tmaps)
        {
            face.tmaps = new Vector[face.num_tmaps];
            for (size_t k = 0; k < face.num_tmaps; ++k)
            {
                unsigned long mapfaceidx[3];
                gM->GetMapFaceIndex(mapNums[k], Index, &mapfaceidx[0]);
                idx = mapfaceidx[j];
                face.tmaps[k].x = gM->GetMapVertex(mapNums[k], idx).x;
                face.tmaps[k].y = gM->GetMapVertex(mapNums[k], idx).y;
                face.tmaps[k].z = gM->GetMapVertex(mapNums[k], idx).z;
            }
        }

        // try to find in origin array
        FaceMapIt it_face_map = m_opt->face_map.find(face_idx);  // get face map iter

        if (it_face_map == m_opt->face_map.end()) // if not find such create anyway
        {
            create_face = true;
        }
        else
        {
            if (is_matching((*it_face_map).second, face) == false) // check find vertex not matching
            {
                bool found = false;

                // process vertex multi map
                std::pair<FaceMMapIt,FaceMMapIt> pair_mmap = m_opt->face_mmap.equal_range(ori_face_idx);

                FaceMMapIt it_face_mmap = pair_mmap.first;

                while (it_face_mmap != pair_mmap.second && found == false)
                {
                    idxvert_opt & idxface = (*it_face_mmap).second;

                    if (is_matching(idxface.face, face))
                    {
                        face_idx = idxface.new_idx;
                        found = true;
                    }
                    ++it_face_mmap;
                }

                if (found == false)
                {
                    create_face = true;
                    ++MaxFaceIdx;			// increment max index and
                    face_idx = MaxFaceIdx;	// set index is out of bounds of origin 3DMax's index range
                }
            }
        }

        if (create_face)
        {
            if (skin)
            {
                std::vector<w_offset>   w_offsets;
                for (int k = 0; k < skin->GetNumberOfBones(ori_face_idx); ++k)
                {
                    /*	if (skin->GetWeight(ori_face_idx, k) > m_eps)
                    	{
                    		w_offset w;
                    		w.weight = skin->GetWeight(ori_face_idx, k);

                    		_BoneObject * Bone = ExporterMAX::GetExporter()->Skeleton.AddMaxBone(skin->GetIGameBone(ori_face_idx, k), skin->GetIGameBone(ori_face_idx, k)->GetNodeID());
                    		assert(Bone != NULL);

                    		w.bone_id = Bone->GetID();
                    		w_offsets.push_back(w);
                    	}*/
                }

//				std::sort(w_offsets.begin(), w_offsets.end(), heavier);

                int ILeft = 0;
                for (size_t l = 0; l < w_offsets.size() && l < 4; ++l, ++ILeft)
                {
                    w_offset & w = w_offsets[l];
                    face.weights[l] = w.weight;
                    face.bones[l] = w.bone_id;
                }

                for (; ILeft < 4; ++ILeft)
                {
                    face.weights[ILeft] = 0.f;
                    face.bones[ILeft] = BAD_IDX;
                }

                // check for valid weights...
                float w_sum = 0.f;

                for (int l = 0; l < 4; ++l) {
                    w_sum += face.weights[l];
                }

                if ((w_sum < m_one - m_eps) || (w_sum > m_one + m_eps))
                {
                    for (int l = 0; l < 4; ++l) // renormalizing...
                        face.weights[l] /= w_sum;
                }
            }

            Point3 v_world = gM->GetVertex(ori_face_idx);
            Point3 v_obj = v_world; // * world_to_obj;

            face.v.x = v_obj.x; // * PRS.k.x * PRS.f;
            face.v.y = v_obj.z; // * PRS.k.z * PRS.f;
            face.v.z = v_obj.y; // * PRS.k.y * PRS.f;

            // add the vertex and store its new idx
            face.face_idx = m_opt->count;

            m_opt->face_map.insert(FaceMapPair(face_idx, face));

            if (ori_face_idx != face_idx)  // store the newly created and duplicated independently
            {
                idxvert_opt idxface(face_idx, face);// store new face
                m_opt->face_mmap.insert(FaceMMapPair(ori_face_idx, idxface)); // but store key as a original
            }
            m_opt->count++;
        }

        // add the face indices...
        TriMapIt it = tri_map.find(mat_id);
        if (it != tri_map.end())
        {
            (*it).second->push_back(face_idx);
        }
        else
        {
            IdxType * idx_type = new IdxType;
            idx_type->push_back(face_idx);
            tri_map.insert(TriMapPair(mat_id, idx_type));
        }
    }
    return true;
}