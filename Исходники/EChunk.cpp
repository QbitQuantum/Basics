/*
====================
Find
====================
*/
U32 EChunk::Find(const CHAR* name, const Vector2& st)
{
	GUARD(EChunk::Find);	

	CHECK(name);
	
	// searche the layer table
	for(U32 i = 0; i < mLayers.size(); i++)
	{
		if(mLayers[i].name == name && mLayers[i].st == st) return i;
	}

	// create the new layer
	Layer layer;
	layer.name = name;
	layer.st = st;
	layer.alpha.resize(U2P(ALPHA_STRIDE)*U2P(ALPHA_STRIDE), 0);
	layer.total = 0;

	// create the new primitive
	layer.primitive = GNEW(Primitive); CHECK(layer.primitive);
	layer.primitive->SetType(Primitive::PT_TRIANGLES);
	layer.primitive->SetVertexBuffer(mVBPtr.Ptr());
	layer.primitive->SetIndexBuffer(mIBPtr.Ptr());	
	layer.primitive->SetConstant("gWVP",GNEW(Constant(Matrix())));

	// get the color texture
	KeyPtr texture_key_ptr = Key::Find(name);
	if(texture_key_ptr == NULL)
	{
		const Image* image = Image::Load(GLoad(name)); CHECK(image);
		BaseTexture* base_texture = GNEW(Texture); CHECK(base_texture);
		base_texture->Load(image);
		texture_key_ptr = GNEW(Key(name, base_texture)); CHECK(texture_key_ptr);
	}
	mKeys.push_back(texture_key_ptr);
	layer.primitive->SetConstant("gColorTex",GNEW(Constant((BaseTexture*)texture_key_ptr->Ptr())));

	// set the scale st	
	layer.primitive->SetConstant("gScaleST",GNEW(Constant(Vector4(st[0],st[1],0,0))));	

	// set the alpha
	U32 width = U2P(ALPHA_STRIDE);
	U32 height = U2P(ALPHA_STRIDE);
	Image* image = GNEW(Image); CHECK(image);
	image->Width(width);
	image->Height(height);
	image->PixelFormat(PF_ALPHA);
	image->DataType(DT_UNSIGNED_BYTE);
	image->MipmapCount(1);
	image->Mipmap(0,&layer.alpha[0],width*height*sizeof(U8));		
	BaseTexture *alpha_texture = GNEW(Texture); CHECK(alpha_texture);
	alpha_texture->Load(image);
	layer.primitive->SetConstant("gAlphaTex",GNEW(Constant(alpha_texture)));
	layer.texture = alpha_texture;

	// load the shader
	layer.primitive->SetShader(dynamic_cast<Shader*>(mShaderKey->Ptr()), "layer");
	
	// add the layer to the table
	mLayers.push_back(layer);
	return mLayers.size() - 1;

	UNGUARD;
}