	msiPack(std::wstring file) : hProduct(NULL),m_msiFile(file) {
		MsiOpenPackage(m_msiFile.c_str(),&hProduct);
		DWORD sz = sizeof(prodCode);
		MsiGetProductProperty(hProduct,L"ProductCode",prodCode,&sz);
		MsiCloseHandle(hProduct);
		hProduct = NULL;
		}