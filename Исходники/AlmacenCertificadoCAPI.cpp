DWORD AlmacenCertificadoCAPI::eliminarCRL(const ArsCadena &emisor)
{
	DWORD 	ret;
	PCCRL_CONTEXT crl;
	LPBYTE	bytesEmisor, emisorActual;
	DWORD	lenBytesEmisor, lenEmisorActual;
	bool	error, terminado, esEmisorBuscado;

	if (handle != NULL && emisor != "")
	{
		// convierto el emisor
		lenBytesEmisor = emisor.longitud() / 2;
		bytesEmisor = new BYTE[lenBytesEmisor];
		ConversorDatos::StrToByte(emisor, bytesEmisor, lenBytesEmisor);

		// cargar y recorrer las CRLs disponibles dentro del almacén
		crl = NULL;
		ret = 0;
		error = false;
		do
		{
			crl = CertEnumCRLsInStore(handle, crl);
			terminado = (crl == NULL);

			if (!terminado)
			{
				emisorActual = crl->pCrlInfo->Issuer.pbData;
				lenEmisorActual = crl->pCrlInfo->Issuer.cbData;

				esEmisorBuscado  = lenEmisorActual == lenBytesEmisor;
				esEmisorBuscado &=  (0 == memcmp(emisorActual, bytesEmisor, lenBytesEmisor));

				if (esEmisorBuscado)
				{
					if (CertDeleteCRLFromStore(crl))
					{
						ret++;
						// para reiniciar la búsqueda.
						crl = NULL;
					}
					else
					{
						error = true;
						terminado = true;
					}
				}
			}
		}
		while (!terminado);

		if (error)
			ret = (DWORD) -2;

		delete [] bytesEmisor;
	}
	else
		ret = (DWORD) -1;

	return (ret);
}