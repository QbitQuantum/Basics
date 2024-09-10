int main(int argc, char* argv[])
{
	using namespace std;
	using namespace Assimp;
	using namespace DirectX;


#pragma region Exporter
	Importer importer;
	unsigned int flags = 
		aiProcess_GenSmoothNormals |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_FlipWindingOrder;
	const aiScene* scene = importer.ReadFile(argv[1], flags);
	string modelFileName;
	for (size_t i = 0; argv[1][i] != '.'; i++)
	{
		modelFileName.push_back(argv[1][i]);
	}
	modelFileName.append(".mesh");
	ofstream bout(modelFileName.c_str(), ios_base::binary);
	if (bout.is_open() && scene)
	{
		if (scene->HasMeshes())
		{
			//Flag Header
			char headerString[] = { 'F','U', 'L', 'L', 'S', 'A', 'I', 'L' };
			bout.write(headerString, sizeof headerString / sizeof(char));

			//File Name
			uint8_t modelNameLength = static_cast<uint8_t>(modelFileName.size());
			bout.write(reinterpret_cast<char*>(&modelNameLength), sizeof modelNameLength);
			bout.write(modelFileName.c_str(), modelNameLength);

			//Number of Meshes
			uint8_t numOfMeshes = static_cast<uint8_t>(scene->mNumMeshes);
			bout.write(reinterpret_cast<char*>(&numOfMeshes), sizeof numOfMeshes);
			for (size_t meshIndex = 0; meshIndex < numOfMeshes; meshIndex++)
			{
				auto currentMesh = scene->mMeshes[meshIndex];

				//Pos
				uint32_t numOfVertices = currentMesh->mNumVertices;
				bout.write(reinterpret_cast<char*>(&numOfVertices), sizeof numOfVertices);
				bout.write(reinterpret_cast<char*>(currentMesh->mVertices), numOfVertices * sizeof(aiVector3D));

				//Normal
				bout.write(reinterpret_cast<char*>(currentMesh->mNormals), numOfVertices * sizeof(aiVector3D));

				//UV
				bout.write(reinterpret_cast<char*>(currentMesh->mTextureCoords[0]), numOfVertices * sizeof(aiVector3D));

				//Indices
				uint32_t numOfIndices = currentMesh->mNumFaces * 3;
				bout.write(reinterpret_cast<char*>(&numOfIndices), sizeof numOfIndices);
				for (size_t eachFace = 0; eachFace < currentMesh->mNumFaces; eachFace++)
				{
					for (size_t i = 0; i < 3; i++)
					{
						bout.write(reinterpret_cast<char*>(&currentMesh->mFaces[eachFace].mIndices[i]), sizeof(unsigned int));
					}
					
				}
				
			}
		}
	}
#pragma endregion

#pragma region Importer
	ifstream bin(modelFileName, ios_base::binary);
	ofstream text("log.txt");
	if (bin.is_open())
	{
		char header[8];
		bin.read(header, 8);
		if (strcmp(header,"FULLSAIL"))
		{
			uint8_t modelNameLength = 0;
			bin.read(reinterpret_cast<char*>(&modelNameLength), sizeof modelNameLength);
			text << "Model Name Length: " << (int)modelNameLength << "\n";

			string modelName;
			modelName.resize(modelNameLength);
			bin.read(&modelName[0],  modelNameLength * sizeof (char));
			text << "Model Name: "<< modelName << endl;

			uint8_t numOfMeshes = 0;
			bin.read(reinterpret_cast<char*>(&numOfMeshes), sizeof numOfMeshes);
			text << "Number of meshes: " << (int)numOfMeshes << "\n";


			for (size_t eachMesh = 0; eachMesh < numOfMeshes; eachMesh++)
			{
				uint32_t numOfVertices = 0;
				bin.read(reinterpret_cast<char*>(&numOfVertices), sizeof numOfVertices);
				text << "Number of Vertices for " << eachMesh << ": " << (int)numOfVertices << "\n";
				vector<XMFLOAT3> pos;
				vector<XMFLOAT3> nor;
				vector<XMFLOAT3> uvs;
				pos.resize(numOfVertices);
				nor.resize(numOfVertices);
				uvs.resize(numOfVertices);

				bin.read(reinterpret_cast<char*>(pos.data()), sizeof (XMFLOAT3) *  numOfVertices);
				bin.read(reinterpret_cast<char*>(nor.data()), sizeof(XMFLOAT3) *  numOfVertices);
				bin.read(reinterpret_cast<char*>(uvs.data()), sizeof(XMFLOAT3) *  numOfVertices);


				for (size_t eachVertex = 0; eachVertex < numOfVertices; eachVertex++)
				{
					text << "Pos: " << pos[eachVertex].x << " " << pos[eachVertex].y << " " << pos[eachVertex].z << "\t";
					text << "Nor: " << nor[eachVertex].x << " " << nor[eachVertex].y << " " << nor[eachVertex].z << "\t";
					text << "UVs: " << uvs[eachVertex].x << " " << uvs[eachVertex].y << " " << uvs[eachVertex].z << "\n";
				}
				

				vector<unsigned int> indices;
				uint32_t numOfIndices = 0;
				bin.read(reinterpret_cast<char*>(&numOfIndices), sizeof numOfIndices);
				text << "Number of Indices for " << eachMesh << ": " << (int)numOfIndices << "\n";
				indices.resize(numOfIndices);
				bin.read(reinterpret_cast<char*>(indices.data()), sizeof(unsigned int) *  numOfIndices);
				for (size_t eachIndex = 0; eachIndex < numOfIndices; eachIndex++)
				{
					text << indices[eachIndex] << " ";
				}
				text << "\n";

			}
		}
	}
#pragma endregion


	
	return 0;
}