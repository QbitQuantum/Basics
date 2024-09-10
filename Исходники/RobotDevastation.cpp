bool rd::RobotDevastation::onKeyDown(rd::RdKey k)
{
    if ( k.isControlKey() )
    {
        RD_SUCCESS( "Control key with code %d pressed!\n", k.getValue() );

        if ( k.getValue() == RdKey::KEY_SPACE)
        {
            //-- Do things to shoot
            mentalMap->shoot();
            RD_SUCCESS("Shoot!\n");
        }
        else if ( k.getValue() == RdKey::KEY_ESCAPE)
        {
            RD_SUCCESS("Exit!\n");
            this->interruptModule();
        }
    }
    else if (k.isPrintable() )
    {
        RD_SUCCESS( "Key \"%c\" was pressed!\n", k.getChar() );

        if ( k.getChar() == 'r')
        {
            RD_SUCCESS("Reload!\n");
            mentalMap->reload();
        }
        else if ( k.getChar() == 'q')
        {
            RD_SUCCESS("Exit!\n");
            this->interruptModule();
        }
        else if ( k.getChar() == 'w')
        {
            robotManager->moveForward();
        }
        else if ( k.getChar() == 'a')
        {
            robotManager->turnLeft();
        }
        else if ( k.getChar() == 'd')
        {
            robotManager->turnRight();
        }
        else if ( k.getChar() == 's')
        {
            robotManager->moveBackwards();
        }
    }
	return true;
}