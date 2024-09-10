void setupShaders(ID3D11Device* device, ID3D11DeviceContext* context)
{
	// load and compile the two shaders
	const char* shaders =
	    "#define ATTRIBUTES 5\n"
	    "struct Foo { float4 v[ATTRIBUTES]; };"
	    "float4 VS(uint index: SV_VertexId, out Foo foo: FOO): SV_Position { uint i = index % 3; [unroll] for (int j = 0; j < ATTRIBUTES; j++) foo.v[j] = j; return float4(i != 0, i != 2, 0, 1); }"
	    "float4 PS(Foo foo: FOO): SV_Target { float4 result = 0; [unroll] for (int j = 0; j < ATTRIBUTES; j++) result += foo.v[j]; return result; }";

	ID3DBlob* vsblob = 0;
	ID3DBlob* psblob = 0;
	D3DCompile(shaders, strlen(shaders), 0, 0, 0, "VS", "vs_5_0", 0, 0, &vsblob, 0);
	D3DCompile(shaders, strlen(shaders), 0, 0, 0, "PS", "ps_5_0", 0, 0, &psblob, 0);

	ID3D11VertexShader* vs = 0;
	ID3D11PixelShader* ps = 0;
	device->CreateVertexShader(vsblob->GetBufferPointer(), vsblob->GetBufferSize(), 0, &vs);
	device->CreatePixelShader(psblob->GetBufferPointer(), psblob->GetBufferSize(), 0, &ps);

	context->VSSetShader(vs, 0, 0);
	context->PSSetShader(ps, 0, 0);
}