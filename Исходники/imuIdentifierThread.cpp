void imuIdentifierThread::threadRelease()
{
    printMessage(0,"Putting head in home position..\n");
        goHome();

    printMessage(0,"Closing controllers..\n");
        ddH.close();

    printMessage(0,"Closing ports...\n");
        closePort(inIMUPort);
        closePort(outPort);
}