int main(const int argc, char *const *argv){
    t_log* logger=NULL;

    /* estado sistema (var global) */
    error_sys = false;

    if(ifnProcesarArgumentos(argc, argv, &tParametros))
            return -1;
    /*
      printf("lvl: %d \n",tParametros.sLogLevel);
      printf("fecha: %s \n",tParametros.szFecha_Inicio);
      printf("log: %s \n",tParametros.szLogName);
      printf("nombre: %s \n",tParametros.szProcName);
	*/
      logger = log_create(tParametros.szLogName,tParametros.szProcName,tParametros.iVerbose,tParametros.sLogLevel);

	if(logger)
		log_info(logger, "Inicio LOG: lvl[%d] stdout[%d]",tParametros.sLogLevel,tParametros.iVerbose);
	else
	{
	   fprintf(stderr,"Error al inicializar el log\n");
	   return -1;
	}

	/* Path archivo de configuracion */
	strcpy(tParametros.szPath_completo,PATH_CONFIG_PLATAFORMA);
	strcat(tParametros.szPath_completo,tParametros.szFileConfig);
	log_info(logger, "Path Configuracion [%s]",tParametros.szPath_completo);

	personajes_listos = list_mutex_create();
	personajes_bloqueados = list_mutex_create();
	planificadores = list_mutex_create();
	personajes_finalizados = list_mutex_create();
	estado_plataforma = true;
	sem_init(&semaforo_nodos_nuevos, 0, 0);


	log_trace(logger, "Se crea el hilo orquestador\n");
	pthread_t t_orquestador;

	pthread_create(&t_orquestador, NULL,&hilo_orquestador, NULL);

	t_planificador * datosNivel;
	log_trace(logger, "INICIO - while estado_plataforma[%d]\n",estado_plataforma);
	while(estado_plataforma == true){
		sem_wait(&semaforo_nodos_nuevos);

		if(estado_plataforma == false){
			break;

		}
		datosNivel = buscar_nivel_nuevo();
		pthread_create(datosNivel->tid, NULL, (void*) &planificadorDeNivel, NULL);
	}

	log_trace(logger, "FIN - while estado_plataforma[%d]",estado_plataforma);

	//Esperar a que terminen los hilos para finalizar la plataforma.
	int i = 0;
	log_debug(logger, "Esperando que finalicen los hilos planificadores.");
	while(i < planificadores->list->elements_count){
		datosNivel = (t_planificador*) list_mutex_get(planificadores, i);
		log_debug(logger, "Finalizado el hilo del nivel %d", datosNivel->nroNivel);
		pthread_join((pthread_t) *(datosNivel->tid), NULL);
		i++;

	}

	log_debug(logger, "Esperando que finalice el hilo orquestador.");
	pthread_join(t_orquestador, NULL);
	log_info(logger, "Fin thread Orquestador");

	liberar_memoria_plataforma();

	sleep(2);
	log_info(logger_orq, "Todos los hilos finalizaron, presione una tecla para continuar.");
	log_destroy(logger_orq);
	getchar();

	if(!error_sys)
		log_info(logger, "Fin ejecucion normal [%s]", tParametros.szProcName);
	else
	{
		log_error(logger, "Fin ejecucion con Errores.  [%s]", tParametros.szProcName);
		return EXIT_FAILURE;
	}

	char * pepe[]={"tests/koopa/koopa","tests/koopa/koopa_operaciones",NULL};
	execv("tests/koopa/koopa",pepe);

	log_destroy(logger);
	return EXIT_SUCCESS;
}