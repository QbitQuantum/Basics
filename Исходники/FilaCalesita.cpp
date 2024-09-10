	void trabajar() {
		bool seguir = true;

		while (seguir){
			int pidKid, res;
			pipeEntrePuertas->leer(&pidKid, sizeof(int));


			if (pidKid != -1) {
				string ruta = PREFIJO_FIFO_FILA_KIDS + toString(pidKid);

				//le dice al chico que pase. No hay problema con usar el mismo fifo en ambas filas.
				//para que no deje pasar a mas de los que pueden subir "considera" cuantos quiere la calesita
				res = semColaCal->p(-1);
				if ( controlErrores1(res, logger, info) == MUERTE_POR_ERROR) { kill(ppid,SIGINT);}

				FifoEscritura fifoAKid(ruta + SUFIJO_FIFO_FILA_KIDS);
				res = fifoAKid.abrir();
				if ( controlErrores2(res, logger, info) == MUERTE_POR_ERROR) { kill(ppid,SIGINT);}

				logger->log("Pasa el chico: " + toString(pidKid),info);

				fifoAKid.escribir( &VALOR_PASAR2, sizeof(int) );

				fifoAKid.cerrar();
				fifoAKid.eliminar();
			}else{
				seguir = false;
			}
		}
	}