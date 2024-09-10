int __cdecl _tmain (int argc, char** argv)
{

	//------------ I N I C I O   M A I N    D E L   P R O G R A M A   D E L    R O B O T-----------//

	  //inicializaion de variables
	  Aria::init();
	  ArArgumentParser parser(&argc, argv);
	  parser.loadDefaultArguments();
	  ArSimpleConnector simpleConnector(&parser);
	  ArRobot robot;
	  ArSonarDevice sonar;
	  ArAnalogGyro gyro(&robot);
	  robot.addRangeDevice(&sonar);
	  ActionGos go(500, 350);	  
	  robot.addAction(&go, 48);
	  ActionTurns turn(400, 110);
	  robot.addAction(&turn, 49);
	  ActionTurns turn2(400, 110);
	  robot.addAction(&turn2, 49);

	  // presionar tecla escape para salir del programa
	  ArKeyHandler keyHandler;
	  Aria::setKeyHandler(&keyHandler);
	  robot.attachKeyHandler(&keyHandler);
	  printf("Presionar ESC para salir\n");

	  // uso de sonares para evitar colisiones con las paredes u 
	  // obstaculos grandes, mayores a 8cm de alto
	  ArActionLimiterForwards limiterAction("limitador velocidad cerca", 300, 600, 250);
	  ArActionLimiterForwards limiterFarAction("limitador velocidad lejos", 300, 1100, 400);
	  ArActionLimiterTableSensor tableLimiterAction;
	  robot.addAction(&tableLimiterAction, 100);
	  robot.addAction(&limiterAction, 95);
	  robot.addAction(&limiterFarAction, 90);


	  // Inicializon la funcion de goto
	  ArActionGoto gotoPoseAction("goto");
	  robot.addAction(&gotoPoseAction, 50);
	  
	  // Finaliza el goto si es que no hace nada
	  ArActionStop stopAction("stop");
	  robot.addAction(&stopAction, 40);

	  // Parser del CLI
	  if (!Aria::parseArgs() || !parser.checkHelpAndWarnUnparsed())
	  {    
		Aria::logOptions();
		exit(1);
	  }
	  
	  // Conexion del robot
	  if (!simpleConnector.connectRobot(&robot))
	  {
		printf("Could not connect to robot... exiting\n");
		Aria::exit(1);
	  }
	  robot.runAsync(true);

	  // enciende motores, apaga sonidos
	  robot.enableMotors();
	  robot.comInt(ArCommands::SOUNDTOG, 0);

	  // Imprimo algunos datos del robot como posicion velocidad y bateria
		robot.lock();
		ArLog::log(ArLog::Normal, "Posicion=(%.2f,%.2f,%.2f), Trans. Vel=%.2f, Bateria=%.2fV",
			robot.getX(), robot.getY(), robot.getTh(), robot.getVel(), robot.getBatteryVoltage());
		robot.unlock();

	  const int duration = 100000; //msec
	  ArLog::log(ArLog::Normal, "Completados los puntos en %d segundos", duration/1000);

	  // ============================ INICIO CONFIG COM =================================//
	    CSerial serial;
		LONG    lLastError = ERROR_SUCCESS;

		// Trata de abrir el com seleccionado
		lLastError = serial.Open(_T("COM3"),0,0,false);
		if (lLastError != ERROR_SUCCESS)
			return ::ShowError(serial.GetLastError(), _T("Imposible abrir el COM"));

		// Inicia el puerto serial (9600,8N1)
		lLastError = serial.Setup(CSerial::EBaud9600,CSerial::EData8,CSerial::EParNone,CSerial::EStop1);
		if (lLastError != ERROR_SUCCESS)
			return ::ShowError(serial.GetLastError(), _T("Imposible setear la config del COM"));

		// Register only for the receive event
		lLastError = serial.SetMask(CSerial::EEventBreak |
									CSerial::EEventCTS   |
									CSerial::EEventDSR   |
									CSerial::EEventError |
									CSerial::EEventRing  |
									CSerial::EEventRLSD  |
									CSerial::EEventRecv);
		if (lLastError != ERROR_SUCCESS)
			return ::ShowError(serial.GetLastError(), _T("Unable to set COM-port event mask"));

		// Use 'non-blocking' reads, because we don't know how many bytes
		// will be received. This is normally the most convenient mode
		// (and also the default mode for reading data).
		lLastError = serial.SetupReadTimeouts(CSerial::EReadTimeoutNonblocking);
		if (lLastError != ERROR_SUCCESS)
			return ::ShowError(serial.GetLastError(), _T("Unable to set COM-port read timeout."));
		// ============================ FIN CONFIG COM =================================//

	  bool first = true;
	  int goalNum = 0;
	  int color = 3;
	  ArTime start;
	  start.setToNow();
	  while (Aria::getRunning()) 
	  {
		robot.lock();

		// inicia el primer punto 
		if (first || gotoPoseAction.haveAchievedGoal())
		{
		  first = false;
		  
		  goalNum++; //cambia de 0 a 1 el contador
		  printf("El contador esta en: --> %d <---\n",goalNum);
		  if (goalNum > 20)
			goalNum = 1;

		  //comienza la secuencia de puntos
		  if (goalNum == 1)
		  {
			gotoPoseAction.setGoal(ArPose(1150, 0));
			ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
			gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			// Imprimo algunos datos del robot como posicion velocidad y bateria
			robot.lock();
			ArLog::log(ArLog::Normal, "Posicion=(%.2f,%.2f,%.2f), Trans. Vel=%.2f, Bateria=%.2fV",
				robot.getX(), robot.getY(), robot.getTh(), robot.getVel(), robot.getBatteryVoltage());
			robot.unlock();
			// Create the sound queue.
			ArSoundsQueue soundQueue;
			// Run the sound queue in a new thread
			soundQueue.runAsync();
			std::vector<const char*> filenames;
			filenames.push_back("sound-r2a.wav");
			soundQueue.play(filenames[0]);
		  }
		  else if (goalNum == 2)
		  {
			  printf("Gira 90 grados izquierda\n");
			  robot.unlock();
			  turn.myActivate = 1;
			  turn.myDirection = 1;
			  turn.activate();
			  ArUtil::sleep(1000);
			  turn.deactivate();
			  turn.myActivate = 0;
			  turn.myDirection = 0;
			  robot.lock();
		  }
		  else if (goalNum == 3)
		  {
			gotoPoseAction.setGoal(ArPose(1150, 2670));
			ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
			gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			// Imprimo algunos datos del robot como posicion velocidad y bateria
			robot.lock();
			ArLog::log(ArLog::Normal, "Posicion=(%.2f,%.2f,%.2f), Trans. Vel=%.2f, Bateria=%.2fV",
				robot.getX(), robot.getY(), robot.getTh(), robot.getVel(), robot.getBatteryVoltage());
			robot.unlock();
		  }
		  else if (goalNum == 4)
		  {
			  printf("Gira 90 grados izquierda\n");
			  robot.unlock();
			  turn2.myActivate = 1;
			  turn2.myDirection = 1;
			  turn2.activate();
			  ArUtil::sleep(1000);
			  turn2.deactivate();
			  turn2.myActivate = 0;
			  turn2.myDirection = 0;
			  robot.lock();
		  }
		  else if (goalNum == 5)
		  {
			gotoPoseAction.setGoal(ArPose(650, 2670));
			ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
			gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
		  }
		  else if (goalNum == 6)
		  {
			  printf("Gira 90 grados izquierda\n");
			  robot.unlock();
			  turn2.myActivate = 1;
			  turn2.myDirection = 1;
			  turn2.activate();
			  ArUtil::sleep(1000);
			  turn2.deactivate();
			  turn2.myActivate = 0;
			  turn2.myDirection = 0;
			  robot.lock();
		  }
		  else if (goalNum == 7)
		  {
			gotoPoseAction.setGoal(ArPose(650, 0));
			ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
			gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
		  }
		  else if (goalNum == 8)
		  {
			gotoPoseAction.setGoal(ArPose(1800,1199));
			ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
			gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
		  }
		  else if (goalNum == 9)
		  {
			gotoPoseAction.setGoal(ArPose(2600, 1199));
			ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
			gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
		  }
		  else if (goalNum == 10)
		  {
			  if (color == 1)
			  {
				gotoPoseAction.setGoal(ArPose(2800, 850));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
			  if (color == 2)
			  {
				gotoPoseAction.setGoal(ArPose(3500, 1199));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY()); 
			  }
			  if (color == 3)
			  {
				gotoPoseAction.setGoal(ArPose(2800, 1550));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
		  }
		  else if (goalNum == 11)
		  {
			  if (color == 1)
			  {
				gotoPoseAction.setGoal(ArPose(2800, 613));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
			  if (color == 2)
			  {
				  printf("Gira 180 grados derecha\n");
				  robot.unlock();
				  turn2.myActivate = 1;
				  turn2.myDirection = 2;
				  turn2.activate();
				  ArUtil::sleep(2000);
				  turn2.deactivate();
				  turn2.myActivate = 0;
				  turn2.myDirection = 0;
				  robot.lock();
				  goalNum = 19;
			  }
			  if (color == 3)
			  {
				gotoPoseAction.setGoal(ArPose(2800, 1785));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
		  }
		  else if (goalNum == 12)
		  {
			  if (color == 1)
			  {
				gotoPoseAction.setGoal(ArPose(3300, 413));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
			  if (color == 3)
			  {
				gotoPoseAction.setGoal(ArPose(3300, 1985));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
		  }
		  else if (goalNum == 13)
		  {
			  if (color == 1)
			  {
				gotoPoseAction.setGoal(ArPose(3500, 413));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
			  if (color == 3)
			  {
				gotoPoseAction.setGoal(ArPose(3500, 1985));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
		  }
		  else if (goalNum == 14)
		  {
			  robot.unlock();
			  //Valor para el while
			  bool fContinue = true;
				// <<<<<<------------- 1 Parte Secuencia: BAJA BRAZO ------------->>>>>> //
				lLastError = serial.Write("b");
				if (lLastError != ERROR_SUCCESS)
					return ::ShowError(serial.GetLastError(), _T("Unable to send data"));

				//-------------------------E S C U C H A   C O M ----------------------------//
				do
				{
					// Wait for an event
					lLastError = serial.WaitEvent();
					if (lLastError != ERROR_SUCCESS)
						return ::ShowError(serial.GetLastError(), _T("Unable to wait for a COM-port event."));

					// Save event
					const CSerial::EEvent eEvent = serial.GetEventType();

					// Handle break event
					if (eEvent & CSerial::EEventBreak)
					{
						printf("\n### BREAK received ###\n");
					}

					// Handle CTS event
					if (eEvent & CSerial::EEventCTS)
					{
						printf("\n### Clear to send %s ###\n", serial.GetCTS()?"on":"off");
					}

					// Handle DSR event
					if (eEvent & CSerial::EEventDSR)
					{
						printf("\n### Data set ready %s ###\n", serial.GetDSR()?"on":"off");
					}

					// Handle error event
					if (eEvent & CSerial::EEventError)
					{
						printf("\n### ERROR: ");
						switch (serial.GetError())
						{
						case CSerial::EErrorBreak:		printf("Break condition");			break;
						case CSerial::EErrorFrame:		printf("Framing error");			break;
						case CSerial::EErrorIOE:		printf("IO device error");			break;
						case CSerial::EErrorMode:		printf("Unsupported mode");			break;
						case CSerial::EErrorOverrun:	printf("Buffer overrun");			break;
						case CSerial::EErrorRxOver:		printf("Input buffer overflow");	break;
						case CSerial::EErrorParity:		printf("Input parity error");		break;
						case CSerial::EErrorTxFull:		printf("Output buffer full");		break;
						default:						printf("Unknown");					break;
						}
						printf(" ###\n");
					}

					// Handle ring event
					if (eEvent & CSerial::EEventRing)
					{
						printf("\n### RING ###\n");
					}

					// Handle RLSD/CD event
					if (eEvent & CSerial::EEventRLSD)
					{
						printf("\n### RLSD/CD %s ###\n", serial.GetRLSD()?"on":"off");
					}

					// Handle data receive event
					if (eEvent & CSerial::EEventRecv)
					{
						// Read data, until there is nothing left
						DWORD dwBytesRead = 0;
						char szBuffer[101];
						do
						{
							// Lee datos del Puerto COM
							lLastError = serial.Read(szBuffer,sizeof(szBuffer)-1,&dwBytesRead);
							if (lLastError != ERROR_SUCCESS)
								return ::ShowError(serial.GetLastError(), _T("Unable to read from COM-port."));

							if (dwBytesRead > 0)
							{
								//Preseteo color
								int color = 0;
								// Finaliza el dato, asi que sea una string valida
								szBuffer[dwBytesRead] = '\0';
								// Display the data
								printf("%s", szBuffer);

								// <<<<<<----------- 2 Parte Secuencia: CIERRA GRIPPER ----------->>>>>> //
								if (strchr(szBuffer,76))
								{
									lLastError = serial.Write("c");
									if (lLastError != ERROR_SUCCESS)
										return ::ShowError(serial.GetLastError(), _T("Unable to send data"));
								}
								
								// <<<<<<------------- 3 Parte Secuencia: SUBE BRAZO ------------->>>>>> //
								if (strchr(szBuffer,117))
								{
									lLastError = serial.Write("s");
									if (lLastError != ERROR_SUCCESS)
										return ::ShowError(serial.GetLastError(), _T("Unable to send data"));
								}

								// <<<<<<------------- 4 Parte Secuencia: COLOR ------------->>>>>> //
								if (strchr(szBuffer,72))
								{
									lLastError = serial.Write("C");
									if (lLastError != ERROR_SUCCESS)
										return ::ShowError(serial.GetLastError(), _T("Unable to send data"));
								}

								// <<<<<<---------- 5.1 Parte Secuencia: COLOR ROJO---------->>>>>> //
								if (strchr(szBuffer,82))
								{
									color = 1;
									//salir del bucle
									fContinue = false;
								}

								// <<<<<<---------- 5.2 Parte Secuencia: COLOR AZUL ---------->>>>>> //
								if (strchr(szBuffer,66))
								{
									color = 2;
									//salir del bucle
									fContinue = false;
								}

								// <<<<<<---------- 5.3 Parte Secuencia: COLOR VERDE ---------->>>>>> //
								if (strchr(szBuffer,71))
								{
									color = 3;
									//salir del bucle
									fContinue = false;
								}
							}
						}
						while (dwBytesRead == sizeof(szBuffer)-1);
					}
				}
				while (fContinue);
				// Close the port again
				serial.Close();
				robot.lock();
		  }
		  else if (goalNum == 15)
		  {
			  printf("Gira 180 grados derecha\n");
			  robot.unlock();
			  turn2.myActivate = 1;
			  turn2.myDirection = 2;
			  turn2.activate();
			  ArUtil::sleep(2000);
			  turn2.deactivate();
			  turn2.myActivate = 0;
			  turn2.myDirection = 0;
			  robot.lock();
		  }
		  else if (goalNum == 16)
		  {
			  if (color == 1)
			  {
				gotoPoseAction.setGoal(ArPose(3300, 413));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
			  if (color == 3)
			  {
				gotoPoseAction.setGoal(ArPose(3300, 1985));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
		  }
		  else if (goalNum == 17)
		  {
			  if (color == 1)
			  {
				gotoPoseAction.setGoal(ArPose(2800, 603));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
			  if (color == 3)
			  {
				gotoPoseAction.setGoal(ArPose(2800, 1795));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
		  }
		  else if (goalNum == 18)
		  {
			  if (color == 1)
			  {
				gotoPoseAction.setGoal(ArPose(2800, 860));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
			  if (color == 3)
			  {
				gotoPoseAction.setGoal(ArPose(2800, 1540));
				ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
				gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
			  }
		  }
		  else if (goalNum == 19)
		  {
			gotoPoseAction.setGoal(ArPose(2600, 1199));
			ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
			gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
		  }
		  else if (goalNum == 20)
		  {
			gotoPoseAction.setGoal(ArPose(1800, 1199));
			ArLog::log(ArLog::Normal, "Siguiente punto en %.0f %.0f", 
			gotoPoseAction.getGoal().getX(), gotoPoseAction.getGoal().getY());
		  }
		}

		if(start.mSecSince() >= duration) {
		  ArLog::log(ArLog::Normal, "No puede llegar al punto, y la aplicacion saldra en %d", duration/1000);
		  gotoPoseAction.cancelGoal();
		  robot.unlock();
		  ArUtil::sleep(3000);
		  break;
		}
	    
		robot.unlock();
		ArUtil::sleep(10);
	  }

	  // Robot desconectado al terminal el sleep
	  Aria::shutdown();

	//------------ F I N   M A I N    D E L   P R O G R A M A   D E L    R O B O T-----------//
    
    return 0;
}