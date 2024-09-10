// 系统基本参数
int ParamGetBaseInfo(PARAM_CONFIG_BASE_INFO *pParam)
{
	int ret;

	ret = GetParamConfig(INDEX_PARAM_CONFIG_BASE_INFO, pParam, sizeof(*pParam), 0);
	Strcpy( pParam->softwareVersion, DEV_SOFTWARE_VERSION );
	Strcpy( pParam->hardwareVersion, DEV_HARDWARE_VERSION );
	Strcpy( pParam->configureVersion, DEV_CONFIG_VERSION );
	Strcpy( pParam->serialNo, DEV_SERIAL_NUM );

	return ret;
}