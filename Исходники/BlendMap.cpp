XMFLOAT4 BlendMap::GetBlendData(float x, float z)
{
	if (x < 0 || z < 0 ) 
		return XMFLOAT4(0,0,0,0);

	int maxWidth  = (m_Width  - 1);
	int maxHeight = (m_Height - 1);

	float X = x * maxWidth;
	float Z = z * maxHeight;

	if ( X > maxWidth || Z > maxHeight )
		return XMFLOAT4(0,0,0,0);

	if ( X == maxWidth || Z == maxHeight )
		return m_Map[(int)Z][(int)X];

	//hämtar blenddata för hörnen i den rektangel man står i
	XMVECTOR a = XMLoadFloat4(&m_Map[(int)Z+1][(int)X]);
	XMVECTOR b = XMLoadFloat4(&m_Map[(int)Z+1][(int)X+1]);
	XMVECTOR c = XMLoadFloat4(&m_Map[(int)Z][(int)X]);
	XMVECTOR d = XMLoadFloat4(&m_Map[(int)Z][(int)X+1]);

	float s = X - (int)X;
	float t = 1 - (Z - (int)Z);

	XMFLOAT4 result;

	//kollar vilken triangel man står i och räknar ut blenddata därefter.
	if (s + t <= 1)					//abc-triangel
	{
		XMVECTOR uy = b - a;
		XMVECTOR vy = c - a;
		XMStoreFloat4(&result, a + s * uy + t * vy);
	}

	else							//bcd-triangel
	{
		XMVECTOR uy = c - d;
		XMVECTOR vy = b - d;
		XMStoreFloat4(&result, d + (1.0f - s) * uy + (1.0f - t) * vy);
	}

	return result;
}