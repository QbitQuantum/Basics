bool tdnMesh::LoadTDNM(FILE* file, const char* fileName)
{
	unsigned int vertexSize( sizeof( MESHVERTEX2 ) );

	// 頂点読み込み
	numVertexes = 0;
	fread_s( &numVertexes, sizeof( numVertexes ), sizeof( numVertexes ), 1, file );
	delete[] vertexArray;
	vertexArray = new MESHVERTEX2[numVertexes];
	fread_s( vertexArray, vertexSize * numVertexes, vertexSize * numVertexes, 1, file );

	if ( !CreateVertex( numVertexes, sizeof( MESHVERTEX2 ), vertexArray ) )
		return false;

	// インデックス設定
	DWORD* indexArray = new DWORD[numVertexes];
	for ( unsigned int i = 0; i < numVertexes; i++ )
	{
		indexArray[i] = i;
	}
	CreateIndexes( numVertexes, indexArray );
	delete[]indexArray;

	// 面数
	numFaces = numVertexes / 3;

	// 頂点情報
	D3DVERTEXELEMENT9 declAry[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 }, // 位置
		{ 0, sizeof( float ) * 3, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 }, // 法線
		{ 0, sizeof( float ) * 6, D3DDECLTYPE_UBYTE4N, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 }, // 頂点色
		{ 0, sizeof( float ) * 6 + sizeof( COLOR ), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, // UV座標
		D3DDECL_END()
	};
	CreateDeclaration( sizeof( MESHVERTEX2 ), declAry );

	// テクスチャ読み込み
	std::string workFileName = fileName;
	unsigned int filePathLength = workFileName.find_last_of('/');
	if (filePathLength == std::string::npos)
		filePathLength = workFileName.find_last_of('\\');
	workFileName = workFileName.substr(0, filePathLength + 1);
	size_t textureNameLen( 0 );
	fread_s( &textureNameLen, sizeof( size_t ), sizeof( size_t ), 1, file );
	delete[] textureName;
	textureName = new char[textureNameLen + 1];
	fread_s( textureName, textureNameLen + 1, textureNameLen, 1, file );
	textureName[textureNameLen] = '\0';
	workFileName += textureName;
	texture = tdnTexture::Load(workFileName.c_str());

	return true;
}