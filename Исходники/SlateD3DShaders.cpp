void FSlateD3DVS::Create( const FString& Filename, const FString& EntryPoint, const FString& ShaderModel, D3D11_INPUT_ELEMENT_DESC* VertexLayout, uint32 VertexLayoutCount )
{
	TRefCountPtr<ID3DBlob> Blob;
	CompileShader( Filename, EntryPoint, ShaderModel, Blob);

	HRESULT Hr = GD3DDevice->CreateVertexShader( Blob->GetBufferPointer(), Blob->GetBufferSize(), NULL, VertexShader.GetInitReference() );
	check( SUCCEEDED(Hr) );

	Hr = GD3DDevice->CreateInputLayout( VertexLayout, VertexLayoutCount, Blob->GetBufferPointer(), Blob->GetBufferSize(), InputLayout.GetInitReference() );
	check( SUCCEEDED(Hr) );

	TRefCountPtr<ID3D11ShaderReflection> Reflector;
	Hr = D3DReflect( Blob->GetBufferPointer(), Blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)Reflector.GetInitReference() );
	check( SUCCEEDED(Hr) );

	GetShaderBindings( Reflector, ShaderBindings );
}