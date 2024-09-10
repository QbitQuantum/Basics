void avanzar(int *posicion, int *carril, int color)
{
	int valor_devuelto, tpos = 0, tcarril = 0;
	int apos = *posicion;
	int acarril = *carril;
	HANDLE posiciones[3]; //Vamos a añadir los dif. eventos por los que esperaremos

						  //EVENTOS A ESPERAR: EVENTO_ACABAR, MUTEX_POSICION_ADELANTE, MUTEX_POSICION_CAMBIO_DE_CARRIL

						  //Añadimos el evento acabar para detenernos y no avanzar mas*/
	posiciones[0] = IPC.evento_acabar;

	/*Vemos si estamos en alguna de las 4 posiciones especiales para compartir los mutex*/
	if (apos + 1 != traductor(apos + 1, acarril))
		posiciones[1] = IPC.posiciones[traductor(apos + 1, acarril)];
	else if (apos != 136) //Si no estamos en la posicion 136 solicitamos el mutex de la posicion siguiente
		posiciones[1] = IPC.posiciones[apos + acarril * 137 + 1];
	else
		posiciones[1] = IPC.posiciones[acarril * 137]; //Si estamos en la posicion 136 solicitamos el mutex de la primera posicion

													   //Añadimos el evento cambio de carril si procede
	if (cambio(apos, acarril, &tpos, &tcarril))
	{
		posiciones[2] = IPC.posiciones[tpos + tcarril * 137];
		valor_devuelto = WaitForMultipleObjectsEx(3, posiciones, FALSE, INFINITE, TRUE);
	}
	else
		valor_devuelto = WaitForMultipleObjectsEx(2, posiciones, FALSE, INFINITE, TRUE);

	switch (valor_devuelto)
	{
	case WAIT_OBJECT_0 + 0:
		ExitThread(7);
		break;
	case WAIT_OBJECT_0 + 1:
		DLL.avanza_coche(carril, posicion, color);
		break;
	case WAIT_OBJECT_0 + 2:
		DLL.cambio_carril(carril, posicion, color);
		break;
	}

	/*Si estamos en alguna posicion con mutex compartido lo liberamos llamando a traductor*/
	if (traductor(apos, acarril) != apos)
		ReleaseMutex(IPC.posiciones[traductor(apos, acarril)]);
	else
		ReleaseMutex(IPC.posiciones[apos + acarril * 137]);
}