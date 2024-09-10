void CMarshalErrorInfo::GenerateErrorInfo(REFGUID rGUID, 
										  _bstr_t source, _bstr_t message)
{
	ICreateErrorInfo* pCreateInfo		= NULL;
	IErrorInfo* pErrorInfo				= NULL;
	// 创建ICreateErrorInfo对象
	CreateErrorInfo(&pCreateInfo);

	// 设置属性值
	pCreateInfo->SetGUID(rGUID);
	pCreateInfo->SetSource(source);
	pCreateInfo->SetDescription(message);

	// 获得pCreateInfo的IErrorInfo接口引用
	pCreateInfo->QueryInterface(IID_IErrorInfo, (void**)&pErrorInfo);

	// 设置IErrorInfo
	SetErrorInfo(0,pErrorInfo);

	// 释放对象
	pErrorInfo->Release();
	pCreateInfo->Release();
}