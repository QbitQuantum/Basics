TEST(IsNamespaceRoot, Root)
{
	LPITEMIDLIST pidl = NULL;
	HRESULT hr = SHGetFolderLocation(NULL, CSIDL_DESKTOP, NULL, 0, &pidl);
	ASSERT_TRUE(SUCCEEDED(hr));

	BOOL bRet = IsNamespaceRoot(pidl);
	EXPECT_EQ(TRUE, bRet);

	CoTaskMemFree(pidl);
}