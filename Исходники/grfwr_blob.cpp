void Blob::Load(std::wstring path)
{
	Graphouny::Framework::ThrowOnFailed(
		D3DReadFileToBlob(path.c_str(), &m_pBlob), 
		L"Failed to load blob '" + path + L"'");
}