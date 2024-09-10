void gazeEvaluatorThread::threadRelease()
{
    printMessage(0,"Closing ports...\n");
        closePort(inPort);
        closePort(outPort);
        closePort(imgPortOutMod);
        closePort(portOutModAvg);
}