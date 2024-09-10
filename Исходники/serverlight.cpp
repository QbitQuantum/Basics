void ServerLight::readyRead() {
    BL_FUNC_DEBUG
    static QByteArray array = "";
    QByteArray lectura = "";
    QTcpSocket *socket = (QTcpSocket *) sender();
    lectura = socket->readAll();
    g_buffers[socket]  += lectura;
    array += lectura;
    QString mensaje = _("Mensaje desde: ")+ socket->peerAddress().toString() + "\n";
    
    QString texto(g_buffers[socket]);

    fprintf(stderr, "\nPaquete recibido:\n");
    fprintf(stderr, array);
    fprintf(stderr, "\nPaquete finalizado :\n");
    fprintf(stderr, QString::number(array.size()).toAscii());
    fprintf(stderr, "\nFin Paquete recibido :\n");
    
    /// Si se detecta el final de la transmision se procesa la informacion.
    if (texto.contains("</DOCUMENT>", Qt::CaseInsensitive)) {
    
	if (texto.contains("<GETCOMMAND>categoria_articulo</GETCOMMAND>", Qt::CaseInsensitive)) {
	    fprintf(stderr, categoryArticleXML().toAscii() );
	    socket->write(categoryArticleXML().toAscii());
	    /// Hay que cerrar el socket despues del envio.
	    g_buffers[socket] = "";
	    g_buffers.remove(socket);
	    socket->close();
	
        } else if (texto.contains("<PUTCOMMAND>ticket_data</PUTCOMMAND>", Qt::CaseInsensitive)) {
	    /// Nos han mandado la informacion de un ticket.
	    processTicketDataXML(texto);
	    g_buffers[socket] = "";
	    g_buffers.remove(socket);
	    socket->close();
        } else {
	    //fprintf(stderr, "--NO ENTIENDO--");
	} // end if

	/// Como se ha completado la recepcion de datos y se han procesado, se resetea el buffer de entrada.
	array = "";

    } // end if

    
}