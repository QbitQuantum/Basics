XmlFixture::~XmlFixture()
{
	root->Release();
	doc->Release();

	OleUninitialize();
}