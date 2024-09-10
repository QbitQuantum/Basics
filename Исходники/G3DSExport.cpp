/*
====================
GatherSkin
====================
*/
void G3DSExport::GatherSkin(INode* i_node)
{
	SKIN skin;

	// get the name of the node
	skin.name = i_node->GetName();

	// get the skin interface
	Modifier *modifier = GetModifier(i_node,SKIN_CLASSID);
	ISkin* i_skin = (ISkin*)modifier->GetInterface(I_SKIN);
	MAX_CHECK(i_skin);

	// convert to the triangle type
	Mesh* i_mesh = NULL;
	Object* obj = i_node->EvalWorldState(mTime).obj;
	if(obj && ( obj->SuperClassID() == GEOMOBJECT_CLASS_ID ))
	{
		if(obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0))) 
		{ 
			TriObject *tri_obj = (TriObject*)obj->ConvertToType(mTime, Class_ID(TRIOBJ_CLASS_ID, 0)); MAX_CHECK(tri_obj);
			i_mesh = &tri_obj->mesh;
		}
	}
	MAX_CHECK(i_mesh&&i_mesh->getNumFaces()&&i_mesh->getNumVerts());

	// get the material
	skin.texture = "textures/default.tga";
	Mtl* mtl = i_node->GetMtl();
	if(mtl && (mtl->ClassID()==Class_ID(DMTL_CLASS_ID, 0)) && ((StdMat*)mtl)->MapEnabled(ID_DI)) 
	{
		Texmap *texmap = mtl->GetSubTexmap(ID_DI);
		if(texmap && texmap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0x00))
		{
			skin.texture = UnifySlashes(((BitmapTex *)texmap)->GetMapName());
			if( !strstr( skin.texture.c_str(), mPath.c_str() ) )
			{
				G3DAssert("The material(%s) is error : the texture path(%s) is illegal!",mtl->GetName(), skin.texture.c_str());
			}
			else
			{
				skin.texture = strstr(skin.texture.c_str(),mPath.c_str()) + strlen(mPath.c_str());
			}
		}
	}

	// if it has uvs
	int map_count = i_mesh->getNumMaps();
	bool has_uvs = i_mesh->getNumTVerts() && i_mesh->tvFace;
	if(!(has_uvs&&map_count)) { G3DAssert("The skin(%s) has not the uv coordinates.",skin.name.c_str()); return; }

	// get the transform
	Matrix3 mesh_matrix = i_node->GetObjectTM(mTime);
	Matrix3 node_matrix = i_node->GetNodeTM(mTime);
	Matrix3 transform = mesh_matrix * Inverse(node_matrix);

	// get the points
	skin.points.assign(i_mesh->verts, i_mesh->verts+i_mesh->getNumVerts());

	// get the triangles
	for(int i = 0; i < i_mesh->getNumFaces(); i++)
	{
		Face& face = i_mesh->faces[i];

		TRIANGLE tri;		
		tri.smoothing = face.smGroup;
		for(int j = 0; j < 3; j++)
		{
			VPTNIS v;
			v.pos = transform * i_mesh->verts[face.v[j]];

			// get the uv
			UVVert * map_verts = i_mesh->mapVerts(1);
			TVFace * map_faces = i_mesh->mapFaces(1);
			v.uv = reinterpret_cast<Point2&>(map_verts[map_faces[i].t[j]]);
			v.uv.y = 1 - v.uv.y;

			// initialize the normal
			v.normal = Point3::Origin;

			// get the vertex index
			v.index = face.v[j];

			// get the smoothing group
			v.smoothing = face.smGroup;			

			// set the index for the triangle
			tri.index0[j] = v.index;

			// reassemble the vertex list
			tri.index1[j] = AddVertex(skin, v);
		}

		// add the triangle to the table
		skin.triangles.push_back(tri);
	}

	// build the index map
	for( int i = 0; i < skin.vertexes.size(); i++ )
	{
		skin.vertex_index_map[skin.vertexes[i].index].push_back(i);
	}

	// get the skin context data
	ISkinContextData* i_skin_context_data = i_skin->GetContextInterface(i_node);
	if(i_skin_context_data == NULL) { G3DAssert("The skin(%s) has not the weight.",skin.name.c_str()); return; }

	// gets the initial matrix of the skinned object 
	Matrix3 initial_object_transform;
	i_skin->GetSkinInitTM(i_node, initial_object_transform, true);

	// process the points
	int num_points = i_skin_context_data->GetNumPoints();
	for(int i = 0; i < num_points; i++)
	{
		MAX_CHECK(i < skin.points.size());

		VPIW viw;

		// get the initial point				
		viw.pos = initial_object_transform * skin.points[i];

		// process the weights		
		std::multimap< float, int > weights;

		// get the number of bones that control this vertex
		int num_bones = i_skin_context_data->GetNumAssignedBones(i);
		if(num_bones>0)
		{
			for (int j = 0; j < num_bones; j++)
			{
				Matrix3 transform;

				// get the assigned bone of the point 
				INode* i_bone_node = i_skin->GetBone(i_skin_context_data->GetAssignedBone(i, j));
				MAX_CHECK(i_bone_node != NULL);

				// get the weight of the bone
				float weight = i_skin_context_data->GetBoneWeight(i, j);

				// add the weight to the table
				weights.insert(std::make_pair(weight, AddBone(skin,i_bone_node)));
			}
		}
		else
		{
			// add the weight to the table
			weights.insert(std::make_pair(1.f, AddBone(skin,i_node)));
		}

		// recalculate the weights
		float weight0 = 0.f, weight1 = 0.f, weight2 = 0.f;
		int index0 = 0, index1 = 0, index2 = 0;
		std::multimap< float, int >::iterator it = weights.end();
		it--;
		weight0 = it->first;
		index0 = it->second;
		if(it != weights.begin())
		{
			it--;
			weight1 = it->first;
			index1 = it->second;
			if(it != weights.begin())
			{
				it--;
				weight2 = it->first;
				index2 = it->second;
			}
		}		
		float sum_weights = weight0 + weight1 + weight2;

		// store the skin weights	
		viw.weight[0]	= weight0/sum_weights;
		viw.index[0]	= index0;
		viw.weight[1]	= weight1/sum_weights;
		viw.index[1]	= index1;
		viw.weight[2]	= weight2/sum_weights;
		viw.index[2]	= index2;
		skin.weights.push_back(viw);
	}

	// get the initial transforms
	skin.transforms.resize(skin.bones.size());
	for(int i = 0; i < skin.bones.size(); i++)
	{
		INode* node = skin.bones[i];
		Matrix3 mat;
		if (SKIN_INVALID_NODE_PTR == i_skin->GetBoneInitTM( node, mat ))
		{
			if (SKIN_INVALID_NODE_PTR == i_skin->GetSkinInitTM( node, mat ))
			{
				mat.IdentityMatrix();
			}
		}
		skin.transforms[i] = Inverse(mat);
	}

	// there is a 75 bone limit for each skinned object.
	if(skin.bones.size()>75)
	{
		G3DAssert("There are more %d bones in the skin(%s).",skin.bones.size(), i_node->GetName());
		return;
	}

	// reset the skin vertex position
	for(int i = 0; i < skin.vertexes.size(); i++)
	{
		VPTNIS& v0 = skin.vertexes[i];
		VPIW& v1 = skin.weights[v0.index];
		v0.pos = v1.pos;
	}

	// build the normal space
	BuildNormal(skin);

	// calculate the bounding box	
	skin.box.Init();
	for(int i = 0; i < skin.vertexes.size(); i++)
	{
		Point3 pt = node_matrix * skin.vertexes[i].pos;
		skin.box += pt;
	}

	// add the skin to the table
	mSkins.push_back(skin);
}