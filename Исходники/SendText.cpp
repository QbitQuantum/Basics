double RobotController::onAction(ActionEvent &evt)
{

#if 1
	sendText(evt.time(), "Robot2", "hello!");
#else

	double distance = 10.0;
	sendText(evt.time(), NULL, "hello!", distance);
#endif
	return 3.0;
}