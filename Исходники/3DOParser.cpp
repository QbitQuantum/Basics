void C3DOParser::GetPrimitives(S3DOPiece* obj, int pos, int num, int excludePrim)
{
	map<int,int> prevHashes;

	for(int a=0;a<num;a++){
		if(excludePrim==a){
			continue;
		}
		curOffset=pos+a*sizeof(_Primitive);
		_Primitive p;

		READ_PRIMITIVE(p);
		S3DOPrimitive sp;
		sp.numVertex=p.NumberOfVertexIndexes;

		if(sp.numVertex<3)
			continue;

		sp.vertices.reserve(sp.numVertex);
		sp.vnormals.reserve(sp.numVertex);

		curOffset=p.OffsetToVertexIndexArray;
		boost::uint16_t w;

		list<int> orderVert;
		for(int b=0;b<sp.numVertex;b++){
			SimStreamRead(&w,2);
			swabWordInPlace(w);
			sp.vertices.push_back(w);
			orderVert.push_back(w);
		}
		orderVert.sort();
		int vertHash=0;

		for(list<int>::iterator vi=orderVert.begin();vi!=orderVert.end();++vi)
			vertHash=(vertHash+(*vi))*(*vi);


		std::string texName;

		if (p.OffsetToTextureName != 0) {
			texName = StringToLower(GetText(p.OffsetToTextureName));

			if (teamtex.find(texName) == teamtex.end()) {
				texName += "00";
			}
		} else {
			texName = "ta_color" + IntToString(p.PaletteEntry, "%i");
		}

		if ((sp.texture = texturehandler3DO->Get3DOTexture(texName)) == NULL) {
			LOG_L(L_WARNING, "[%s] unknown 3DO texture \"%s\" for piece \"%s\"",
					__FUNCTION__, texName.c_str(), obj->name.c_str());

			// assign a dummy texture (the entire atlas)
			sp.texture = texturehandler3DO->Get3DOTexture("___dummy___");
		}


		const float3 v0v1 = (obj->vertices[sp.vertices[1]].pos - obj->vertices[sp.vertices[0]].pos);
		const float3 v0v2 = (obj->vertices[sp.vertices[2]].pos - obj->vertices[sp.vertices[0]].pos);

		float3 n = (-v0v1.cross(v0v2)).SafeNormalize();

		// set the primitive-normal and copy it <numVertex>
		// times (vnormals get overwritten by CalcNormals())
		sp.primNormal = n;
		sp.vnormals.insert(sp.vnormals.begin(), sp.numVertex, n);

		// sometimes there are more than one selection primitive (??)
		if (n.dot(DownVector) > 0.99f) {
			bool ignore=true;

			if(sp.numVertex!=4) {
				ignore=false;
			} else {
				const float3 s1 = obj->vertices[sp.vertices[0]].pos - obj->vertices[sp.vertices[1]].pos;
				const float3 s2 = obj->vertices[sp.vertices[1]].pos - obj->vertices[sp.vertices[2]].pos;

				if(s1.SqLength()<900 || s2.SqLength()<900)
					ignore=false;

				if (ignore) {
					for(int a=0;a<sp.numVertex;++a) {
						if(obj->vertices[sp.vertices[a]].pos.y>0) {
							ignore=false;
							break;
						}
					}
				}
			}

			if(ignore)
				continue;
		}

		map<int,int>::iterator phi;
		if((phi=prevHashes.find(vertHash))!=prevHashes.end()){
			if(n.y>0)
				obj->prims[phi->second]=sp;
			continue;
		} else {
			prevHashes[vertHash]=obj->prims.size();
			obj->prims.push_back(sp);
			obj->isEmpty = false;
		}
		curOffset = p.OffsetToVertexIndexArray;

		for (int b = 0; b < sp.numVertex; b++) {
			SimStreamRead(&w, 2);
			swabWordInPlace(w);
			obj->vertices[w].prims.push_back(obj->prims.size() - 1);
		}
	}
}