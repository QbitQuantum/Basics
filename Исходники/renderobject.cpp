bool renderObject::loadOBJ(std::string path, std::string & mtlFileName, 
	std::vector < objBuffer > & out_objVec, std::vector <GLuint> & out_indexes)
{
	std::vector < myVec3 > vertices;
	std::vector < myVec2 > uvs;
	std::vector < myVec3 > normals;

	FILE * file;
	fopen_s(&file, path.data(), "r");

	fprintf(stdout, "Reading file\n");

	GLuint index = 0;
	while (1){
		char lineHeader[128];

		// load a row into char array
		char res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));

		// Check for End of file
		if (res == EOF) break;
		
		
		if (strcmp(lineHeader, "mtllib") == 0)
		{
			char mtlName[100];
			fscanf_s(file, "%s", mtlName, sizeof(mtlName));
			
			mtlFileName = std::string(mtlName);
		}
		else if (strcmp(lineHeader, "v") == 0)
		{
			// Push vertices into vector < myVec3 >

			myVec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.pos[0], &vertex.pos[1], &vertex.pos[2]);
			vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			// Push uvs into vector < myVec2 >

			myVec2 uv;
			fscanf_s(file, "%f %f\n", &uv.pos[0], &uv.pos[1]);
			uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			// Push normals into vector < myVec3 >

			myVec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.pos[0], &normal.pos[1], &normal.pos[2]);
			normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			struct face
			{
				GLuint v[3];
				GLuint uv[3];
				GLuint vn[3];
			};

			face faceL;
			fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &faceL.v[0], &faceL.uv[0], &faceL.vn[0], &faceL.v[1], &faceL.uv[1], &faceL.vn[1], &faceL.v[2], &faceL.uv[2], &faceL.vn[2]);

			for (GLuint i = 0; i < 3; i++)
			{
				faceL.v[i] --;
				faceL.uv[i] --;
				faceL.vn[i] --;
			}

			// Put the v/vt/vn into the right order and push into vector<objBuffer> 
			for (size_t j = 0; j < 3; j++)
			{
				objBuffer temp;

				// Copying vertices
				temp.vertices[0] = vertices[faceL.v[j]].pos[0];
				temp.vertices[1] = vertices[faceL.v[j]].pos[1];
				temp.vertices[2] = vertices[faceL.v[j]].pos[2];

				// Copying texture normals
				temp.uvs[0] = uvs[faceL.uv[j]].pos[0];
				temp.uvs[1] = uvs[faceL.uv[j]].pos[1];

				// Copying vertex normals
				temp.vns[0] = normals[faceL.vn[j]].pos[0];
				temp.vns[1] = normals[faceL.vn[j]].pos[1];
				temp.vns[2] = normals[faceL.vn[j]].pos[2];

				out_objVec.push_back(temp);

				// push indexes into index buffer :-)
				out_indexes.push_back(index++);
			}
		}
	}

	fprintf(stdout, "Generating vertices\n");

	//Succes!
	fclose(file);
	return true;
}