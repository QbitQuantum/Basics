ArsCadena TarjetaCAPI::getEtiqueta() const
{
	char  buff[256];
	DWORD len = 256;
	ArsCadena ret;

	if ( isConectado() )
	{
		if ( CryptGetProvParam(getHandle(), PP_NAME, buff, &len, 0) )
			ret = buff;
	}

	return (ret);
}