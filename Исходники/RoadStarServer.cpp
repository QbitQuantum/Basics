int main() {
	////////////////////////init current state////////////////
	currentState.connected = false;
	currentState.autonomous = false;
	currentState.cruise = false;
	currentState.leftTurn = false;
	currentState.rightTurn = false;
	currentState.turnPeaked = false;
	currentState.signalOn = false;
	currentState.obsticle = false;
	currentState.servoInt = 0;
	currentState.motorInt = 0;
	currentState.speed = 0;
	currentState.lastMessageTime = 0;
	currentState.distanceTraveled = 0;
	currentState.lastRequestedMotorInt = 0;
	currentState.sonarRange = 200;
	currentState.cameraAngle = 0;

	////////////////////////GPIO setup////////////////////////
	int GPIOstatus;
	int GPIOfrequencySteering;
	int GPIOfrequencyMotor;
	GPIOstatus = gpioInitialise();				//required for GPIO to function

	if (GPIOstatus < 0)							//did we succeed
			{
		fprintf(stderr, "pigpio initialisation failed.\n");
		return 1;
	}

	//steering
	gpioSetPWMrange(GPIO_STEERING_CONTROL, 255);
	gpioSetPWMfrequency(GPIO_STEERING_CONTROL, 0);
	GPIOfrequencySteering = gpioGetPWMfrequency(GPIO_STEERING_CONTROL);
	int GPIOrangeSteering = gpioGetPWMrange(GPIO_MOTOR_CONTROL);
	//motor
	gpioSetPWMrange(GPIO_MOTOR_CONTROL, 255);
	gpioSetPWMfrequency(GPIO_MOTOR_CONTROL, 250);
	int GPIOrangeMotor = gpioGetPWMrange(GPIO_MOTOR_CONTROL);
	GPIOfrequencyMotor = gpioGetPWMfrequency(GPIO_MOTOR_CONTROL);
	cout << "FREQ: Using " << GPIOfrequencySteering << " for steering and "
			<< GPIOfrequencyMotor << " for motor." << endl;
	cout << "RANGE: Using " << GPIOrangeSteering << " for steering and "
			<< GPIOrangeMotor << "for motor." << endl;
	//gpioSetAlertFunc(GPIOsteeringControl, GPIOcallBack);
	gpioServo(GPIO_STEERING_CONTROL, SERVO_CENTER);	//set steering to straight
	//set mode of turn signals to output
	gpioSetMode(GPIO_RIGHT_TURN_SIGNAL, PI_OUTPUT);
	gpioSetMode(GPIO_LEFT_TURN_SIGNAL, PI_OUTPUT);

	/////////////////////////threads////////////////////////////
	pthread_create(&watchDog_th, NULL, watchDog, NULL);
	pthread_create(&turnSignal_th, NULL, turnSignal, NULL);
	//pthread_create(&sonar_th, NULL, sonar, NULL);
	pthread_create(&speedometer_th, NULL, speedometer, NULL);
	pthread_create(&laneDetect_th, NULL, laneDetect, NULL);
	pthread_create(&motorControl_th, NULL, motorControl, NULL);

	////////////////////////Websocket Server setup////////////////////////
	//what function should be called on a new message
	websocket_server.set_message_handler(&on_message);//what function should be called on a new message
	websocket_server.set_open_handler(&on_open);
	websocket_server.set_close_handler(&on_close);
	websocket_server.init_asio();
	//What ip version and port should we listen on
	websocket_server.listen(boost::asio::ip::tcp::v4(), 8080);
	websocket_server.start_accept();
	//Way to much log
	websocket_server.clear_access_channels(websocketpp::log::alevel::all);
	cout << "Starting RoadStar server" << endl;
	websocket_server.run();									//start the server

	gpioTerminate();

	return 0;
}