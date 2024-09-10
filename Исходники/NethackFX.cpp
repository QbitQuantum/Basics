void NethackFX::updateLogic(TelnetWindow *theWindow)
{
    MainWindow *mainWindow = whiteBoard->getMainWindow();
    string oldFirstLine;//checks if the contents of the first line changed

    if (theWindow->getDisplayChanged())
    {
        oldFirstLine.append(firstLine);

        //### Read the top line(s) of the telnet window ###
        firstLine.clear();
        for (int yPos = 0; yPos < FIRST_FX_ROW; yPos++)
        {
            for (unsigned int xPos = 0; xPos < theWindow->getWidth(); xPos++)
                firstLine.push_back(theWindow->getByte(xPos, yPos));
        }//for yPos

        //### Check the graphics rules for the first line of text ###
        if (oldFirstLine != firstLine)
        {
            if (ruleHandler->checkActions(firstLine, lineRuleFX))
            {
                //We found a rule to enable graphics, this should only happen at the welcome
                //message. Switch userFX to true. We've previously been blocking FX for the
                //login screen, now we'll enable them for the game.
                if (lineRuleFX)
                    mainWindow->setGraphicsMode(true);//sets userFX and toggles the checkbox
            }//if ruleHandler

            //If no rule is found, we default to true
            else
                lineRuleFX = true;

            setGraphicsMode();
        }//if oldFirstLine

        handleExtendedMore(theWindow);
        handleGravestone(theWindow);

        //### Add the first line to the user's history ###
        userHistory->updateLogic(firstLine, showGraphics);
        if (showGraphics)
            userHistory->show();
        else
            userHistory->hide();
    }//if getDisplayChanged
}//updateLogic