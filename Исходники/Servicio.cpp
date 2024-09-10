/*
 * Agrega el mensaje que envió el cliente a la conversacion correspondiente y luego la almacena en
 * la Base de Datos.
 *
 */
void Servicio::almacenarConversacion() {

	string idEmisor = this->getParametro(keyIdUsuarioEmisor, keyDefault);
	string idReceptor = this->getParametro(keyIdUsuarioReceptor, keyDefault);

	//chequeo que los usuarios existan:
	Usuario *emisor = Usuario::obtenerPorTelefono(idEmisor);
	Usuario *receptor = Usuario::obtenerPorTelefono(idReceptor);

	string token = this->getParametro(keyTokenSesion, keyDefault);

	if (emisor->getId() == keyIdUsuarioNoEncontrado
			|| receptor->getId() == keyIdUsuarioNoEncontrado) {
		string msj_warning = "No se pudo almacenar la conversacion porque: ";
		if (emisor->getId() == keyIdUsuarioNoEncontrado)
			msj_warning.append("el emisor no existe.");
		if (receptor->getId() == keyIdUsuarioNoEncontrado)
			msj_warning.append(" el receptor no existe.");
		this->responder(msj_warning, false);
		Loger::getLoger()->warn(msj_warning);
		Loger::getLoger()->guardarEstado();

	} else {
		if (emisor->getToken() == token) {
			//Obtengo el mensaje:
			string cuerpo = this->getParametro(keyCuerpo, keyDefault);
			string fecha = this->getParametro(keyFecha, keyDefault);
			Mensaje* mensaje = new Mensaje(cuerpo, emisor->getId(), fecha);

			//almaceno la conversacion (si no existe la creo):
			Conversacion *conversacion = Conversacion::obtener(
					emisor->getId() + "-" + receptor->getId());
			if (conversacion->getId() != keyIdConversacionNoEncontrada) {
				conversacion->agregarMensaje(mensaje);
				conversacion->persistir();
				delete conversacion;
			} else {
				Conversacion *conversacion = Conversacion::obtener(
						receptor->getId() + "-" + emisor->getId());
				if (conversacion->getId() != keyIdConversacionNoEncontrada) {
					conversacion->agregarMensaje(mensaje);
					conversacion->persistir();
					delete conversacion;
				} else {
					vector<Usuario*> usuarios;
					usuarios.push_back(emisor);
					usuarios.push_back(receptor);
					vector<Mensaje*> mensajes;
					mensajes.push_back(mensaje);
					Conversacion *nuevaConversacion = new Conversacion(usuarios,
							mensajes);
					nuevaConversacion->persistir();
					delete nuevaConversacion;
				}
			}

			this->responder(mensaje->getId(), true);
			delete mensaje;
		} else {
			string msj = "El usuario " + emisor->getNombre()
					+ " no posee un token de session correcto";
			Loger::getLoger()->warn(msj);
			this->responder(msj, false);
		}
	}

}