	std::shared_ptr<ILoadableObject> ObjLoader::load(AssetManager *assetMgr, AssetInfo &asset)
	{
		shared_ptr<Node> node(new Node());

		std::string currentDir = std::string(asset.getFilePath());
		std::string nodeFileName = currentDir.substr(currentDir.find_last_of("\\/")+1);
		nodeFileName = nodeFileName.substr(0, nodeFileName.find_first_of(".")); // trim extension

		node->setName(nodeFileName);

		std::string line;
		while (std::getline(*asset.getStream(), line))
		{
			vector<string> tokens = split(line, ' ');
			tokens = removeEmptyStrings(tokens);

			if (tokens.size() == 0 || strcmp(tokens[0].c_str(), "#") == 0)
			{
			}
			else if (strcmp(tokens[0].c_str(), "v") == 0)
			{
				float x = parse<float>(tokens[1]);
				float y = parse<float>(tokens[2]);
				float z = parse<float>(tokens[3]);
				Vector3f vec(x, y, z);
				positions.push_back(vec);
			}
			else if (strcmp(tokens[0].c_str(), "vn") == 0)
			{
				float x = parse<float>(tokens[1]);
				float y = parse<float>(tokens[2]);
				float z = parse<float>(tokens[3]);
				Vector3f vec(x, y, z);
				normals.push_back(vec);
			}
			else if (strcmp(tokens[0].c_str(), "vt") == 0)
			{
				float x = parse<float>(tokens[1]);
				float y = parse<float>(tokens[2]);
				Vector2f vec(x, y);
				texCoords.push_back(vec);
			}
			else if (strcmp(tokens[0].c_str(), "f") == 0)
			{
				vector<ObjIndex> *c_idx = currentList();
				for (int i = 0; i < tokens.size() - 3; i++)
				{
					c_idx->push_back(parseObjIndex(tokens[1]));
					c_idx->push_back(parseObjIndex(tokens[2 + i]));
					c_idx->push_back(parseObjIndex(tokens[3 + i]));
				}
			}
			else if (strcmp(tokens[0].c_str(), "mtllib") == 0)
			{
				string libLoc = tokens[1];

				std::string currentDir = std::string(asset.getFilePath());
				currentDir = currentDir.substr(0, currentDir.find_last_of("\\/"));

				if (!contains(currentDir, "/") && !contains(currentDir, "\\"))	// the file path is just current file name,															   
				{																// so just make the string empty
					currentDir = "";
				}

				currentDir += "/" + libLoc;

				std::shared_ptr<MaterialList> mtlList = assetMgr->loadAs<MaterialList>(currentDir.c_str());
				this->mtlList = *mtlList.get();
			}
			else if (strcmp(tokens[0].c_str(), "usemtl") == 0)
			{
				string matname = tokens[1];
				newMesh(matname);
			}
		}

		for (int i = 0; i < objIndices.size(); i++)
		{
			vector<ObjIndex> *c_idx = objIndices[i];
			vector<Vertex> vertices;

			for (int j = 0; j < c_idx->size(); j++)
			{
				Vertex vert(positions[(*c_idx)[j].vertex_idx],
						   (hasTexCoords ? texCoords[(*c_idx)[j].texcoord_idx] : Vector2f()),
						   (hasNormals ? normals[(*c_idx)[j].normal_idx] : Vector3f()));

				vertices.push_back(vert);
			}

			shared_ptr<Mesh> mesh(new Mesh());
			mesh->setVertices(vertices);

			if (hasNormals)
				mesh->getAttributes().setAttribute(VertexAttributes::NORMALS);
			if (hasTexCoords)
				mesh->getAttributes().setAttribute(VertexAttributes::TEXCOORDS0);

			shared_ptr<Geometry> geom(new Geometry());
			geom->setName(names[i]);
			geom->setMesh(mesh);
			geom->setMaterial(materialWithName(namesMtl[i]));
			node->add(geom);

			delete c_idx;
		}

		return std::static_pointer_cast<ILoadableObject>(node);
	}