HRESULT WINAPI GameEnv::OpenEnv(const tstring whichPath)
{
	if (NULL != pInstance) //检查是否已经初始化
	{
		mainEnv = pInstance;
		return E_HANDLE;
	}
	if (_T('\\') == whichPath[whichPath.length() - 1]) //检查结尾反斜杠符
	{
		ErrorHandler(ERROR_RES_Unknown, _T(__FUNCTION__));
		return E_FAIL;
	}
	if (!IsFolderExist(whichPath)) //检查路径是否存在
	{
		ErrorHandler(ERROR_RES_MissingPath, _T(__FUNCTION__));
		return E_FAIL;
	}
	PGameRes pRes = OpenResFiles(whichPath);
	if (NULL != pRes) //检查资源文件完整性
	{
		pInstance = new GameEnv(pRes);
		mainEnv = pInstance;
		return S_OK;
	}
	return E_FAIL;
}