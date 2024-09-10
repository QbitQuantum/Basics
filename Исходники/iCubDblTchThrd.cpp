void doubleTouchThread::threadRelease()
{
    printMessage(0,"Returning to position mode..\n");
        if (!dontgoback)
        {
            steerArmsHome();
            imodeL -> setInteractionMode(2,VOCAB_IM_STIFF);
            imodeL -> setInteractionMode(3,VOCAB_IM_STIFF);
            imodeR -> setInteractionMode(2,VOCAB_IM_STIFF);
            imodeR -> setInteractionMode(3,VOCAB_IM_STIFF);
            steerArmsHome();
        }

        delete encsR; encsR = NULL;
        delete  armR;  armR = NULL;

        delete encsL; encsL = NULL;
        delete  armL;  armL = NULL;

    printMessage(0,"Closing ports..\n");
        closePort(skinPort);
        printMessage(1,"skin port successfully closed!\n");
        closePort(outPort);
        printMessage(1,"output port successfully closed!\n");

    printMessage(0,"Closing controllers..\n");
        ddR.close();
        ddL.close();

    printMessage(0,"Closing solver..\n");
        clearTask();
}