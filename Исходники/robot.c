ExtFunc void InitRobot(char *robotProg)
{
	int to[2], from[2];
	int status;
	MyEvent event;

	signal(SIGPIPE, CatchPipe);
	AtExit(CloseRobot);
	if (pipe(to) || pipe(from))
		die("pipe");
	robotProcess = fork();
	if (robotProcess < 0)
		die("fork");
	if (robotProcess == 0) {
		dup2(to[0], STDIN_FILENO);
		dup2(from[1], STDOUT_FILENO);
		close(to[0]);
		close(to[1]);
		close(from[0]);
		close(from[1]);
		execl("/bin/sh", "sh", "-c", robotProg, NULL);
		die("execl failed");
	}
	close(to[0]);
	close(from[1]);
	toRobotFd = to[1];
	robotGen.fd = fromRobotFd = from[0];
	if (!(toRobot = fdopen(toRobotFd, "w")))
		die("fdopen");
	if ((status = fcntl(fromRobotFd, F_GETFL, 0)) < 0)
		die("fcntl/F_GETFL");
	status |= O_NONBLOCK;
	if (fcntl(fromRobotFd, F_SETFL, status) < 0)
		die("fcntl/F_SETFL");
	AddEventGen(&robotGen);
	RobotCmd(1, "Version %d\n", ROBOT_VERSION);
	if (WaitMyEvent(&event, EM_robot) != E_robot)
		fatal("Robot didn't start successfully");
	if (1 > sscanf(event.u.robot.data, "Version %d", &robotVersion)
			|| robotVersion < 1)
		fatal("Invalid Version line from robot");
	if (robotVersion > ROBOT_VERSION)
		robotVersion = ROBOT_VERSION;
}