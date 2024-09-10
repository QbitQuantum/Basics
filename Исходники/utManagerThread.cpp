void utManagerThread::threadRelease()
{
    yDebug("Deleting target from the iCubGui..\n");
        deleteGuiTarget();

    yDebug("Closing ports..\n");
        closePort(motionCUTBlobs);
        printMessage(1,"    motionCUTBlobs successfully closed!\n");
}