	void GOAPapp::loadMaps()//for drawing
	{
		//load public shader
		m_shaderID = shaderMgr->loadShader(TEXT("Shader\\GOAP"), "PT");



		//load all the txt map

		char* mapsname[TotalMaps] = { "simulation.txt" };

		for (int i = 0; i < TotalMaps; ++i)
		{
			std::ifstream* ifs = new std::ifstream("tests\\" + std::string(mapsname[i]));
			char buffer[Map_MaxWidth];
			ifs->getline(buffer, Map_MaxWidth);
			uint w = strlen(buffer);// n
			uint h = 0;
			AstarMap* oneMap = new AstarMap(std::string(mapsname[i]));

			for (;; ++h, ifs->getline(buffer, Map_MaxWidth))
			{
				for (uint j = 0; j < w; ++j)
				{
					/*
					Start (1 NPC each)
					Money
					Wolf
					Oven
					Table (eat)
					Fur Trader
					General Store
					Pizza Hut
					*/
					vec2f texCoordInCombinedTex;
					switch (buffer[j])
					{
					case 'S'://start
						oneMap->nodesList.push_back(AstarMapNode(START, j, h, w*h + j));
						oneMap->startNode.push_back(oneMap->nodesList.size() - 1);
						botVec.push_back(new AIbot(oneMap->nodesList.size() - 1));
						botVec.back()->display = NPC1 + botVec.size() - 1;
						break;
					case 'E'://end
						ADDNODE(END)
							//oneMap->endNode = oneMap->nodesList.size()-1;
							break;
					case '.'://empty
						ADDNODE(EMPTY)
							break;
					case '/'://water
						ADDNODE(SEMIBLOCKER)
							break;
					case '#'://stone
						ADDNODE(BLOCKER)
							break;
					case 'M'://money
						ADDNODE(MONEY)
							oneMap->resource[MONEY]->push_back(Res(w*h + j, true));
						break;
					case 'W'://wolf
						ADDNODE(WOLF)
							oneMap->resource[WOLF]->push_back(Res(w*h + j, true));
						break;
					case 'O'://Oven
						ADDNODE(OVEN)
							oneMap->resource[OVEN]->push_back(Res(w*h + j));
						break;
					case 'T'://table , means eat
						ADDNODE(TABLE)
							oneMap->resource[TABLE]->push_back(Res(w*h + j));
						break;
					case 'F'://Fur Trader
						ADDNODE(FURTRADER)
							oneMap->resource[FURTRADER]->push_back(Res(w*h + j));
						break;
					case 'G'://	General Store
						ADDNODE(GENERALSTORE)
							oneMap->resource[GENERALSTORE]->push_back(Res(w*h + j));
						break;
					case 'B':
						ADDNODE(BANK)
							oneMap->resource[BANK]->push_back(Res(w*h + j));
						break;
					case 'P'://	Pizza Hut						
						ADDNODE(PIZZAHUT)
							oneMap->resource[PIZZAHUT]->push_back(Res(w*h + j));
						break;
					default:
						errorMsg("Map error: can't recognize the character or this line doesn't match the width", "error!");
						break;
					}

					texCoordInCombinedTex = oneMap->getTexCoord(oneMap->nodesList.back().nodeType);

					oneMap->vertices.push_back(PT_Vertex(j, h, texCoordInCombinedTex));
					oneMap->vertices.push_back(PT_Vertex(j + 1, h, texCoordInCombinedTex + vec2f(1, 0)));
					oneMap->vertices.push_back(PT_Vertex(j + 1, h - 1, texCoordInCombinedTex + vec2f(1, 1 / TEXCOUNT)));
					oneMap->vertices.push_back(PT_Vertex(j, h - 1, texCoordInCombinedTex + vec2f(0, 1 / TEXCOUNT)));
				}

				if (ifs->eof())
				{
					ifs->close();
					delete ifs;
					break;
				}

			}



			oneMap->width = w;
			oneMap->height = h + 1;



			oneMap->renderObj.reset(new RenderObject(std::string(mapsname[i])));
			oneMap->renderObj->vbo = new PT_Vertex[oneMap->vertices.size()];
			oneMap->renderObj->VertexNum = oneMap->vertices.size();
			memcpy_s(oneMap->renderObj->vbo, oneMap->renderObj->VertexNum * sizeof(PT_Vertex), &oneMap->vertices.front(), oneMap->renderObj->VertexNum * sizeof(PT_Vertex));



			//vbo,ibo

			for (unsigned int row = 0; row < h + 1; ++row)
			{
				for (unsigned int col = 0; col < w; ++col)
				{
					unsigned int idx = 4 * (row * w + col);
					oneMap->renderObj->ibo.push_back(idx);
					oneMap->renderObj->ibo.push_back(idx + 1);
					oneMap->renderObj->ibo.push_back(idx + 2);

					oneMap->renderObj->ibo.push_back(idx);
					oneMap->renderObj->ibo.push_back(idx + 2);
					oneMap->renderObj->ibo.push_back(idx + 3);
				}
			}

			oneMap->renderObj->IndexNum = oneMap->renderObj->ibo.size();

			oneMap->renderObj.get()->vbo_id = m_pRenderer->createVBO(oneMap->renderObj->vbo, sizeof(PT_Vertex), oneMap->renderObj.get()->VertexNum, m_shaderID, "PT");
			oneMap->renderObj.get()->ibo_id = m_pRenderer->createIBO(oneMap->renderObj->ibo.data(),oneMap->renderObj->IndexNum);


			m_maps.push_back(oneMap);
		}

		initBots(m_maps[currentMapIdx]);

	}