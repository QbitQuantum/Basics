///////////////////
// Change a part
void Gar_ChangePart(void)
{
	mouse_t *mouse = System_GetMouse();


    // Process an escape
    /*if( System_GetKeyboard()->KeyUp[SDLK_ESCAPE] ) {
        // Go up a level
		if(tGarage->iState == GAR_ENGINEPART) {
			Gar_Part2Engine();
		}
		if(tGarage->iState == GAR_RUNGPART) {
			tGarage->iState = GAR_RUNNINGG;
			Gar_Part2RunningG();
		}
        return;
    }*/

    // Draw the part information
    cGarLocation->drawPartInfo(tPartChange.cPart, 1);


    // Process the change part dialog box
    cPartDlg.Draw();
    gui_event_t *ev = cPartDlg.Process();
    if( ev ) {
        switch(ev->iControlID) {

            // Add all / Remove all
            case 1:
                if( ev->iEventMsg == BUT_CLICKED ) {

                    if( tPartChange.iNutsGoingon ) {
                        // Put all the nuts on
                        tPartChange.cPart->putNutsOn();
                        Gar_FinishAddPart();
                    } else {

                        // Remove all the nuts
                        Gar_RemovePart();
                    }

                    cPartDlg.Shutdown();
                    return;

                }
                break;

            // Repair
            case 2:
                if( ev->iEventMsg == BUT_CLICKED ) {

                    // Parts with more then 50% damage cannot be repaired
                    if( tPartChange.cPart->getDamage() >= 50 ) {
                        Gar_InitSpeechBubble("The part is too damaged to be repaired");
                        return;
                    }

                    // Can we afford to repair the part?
                    if( !cMainGuy->canBuy( tPartChange.cPart->repairCost() ) ) {
                        Gar_InitSpeechBubble("You ain't got enough cash buddy");
                        return;
                    }

                    // Repair the part
                    int cost = tPartChange.cPart->repair();
                    cMainGuy->makePurchase(cost);
                }
                break;

            // Forget it
            case 3:
                if( ev->iEventMsg == BUT_CLICKED ) {

                    // If this part is coming off but was cancelled; put all the nuts back on
                    if( !tPartChange.iNutsGoingon )
                        tPartChange.cPart->putNutsOn();
                    else {
                        // Remove the part
                        Gar_RemovePart();
                    }


                    // Go up a level
		            if(tGarage->iState == GAR_ENGINEPART) {
			            Gar_Part2Engine();
		            }
		            if(tGarage->iState == GAR_RUNGPART) {
			            tGarage->iState = GAR_RUNNINGG;
			            Gar_Part2RunningG();
		            }

                    cPartDlg.Shutdown();
                    return;
                }
                break;
        }

    }


	CVec dir = tGarage->mousePoint - cGarLocation->getCamPos();
	VectorNormalize(&dir);

	// Check if any of the nuts are highlighted
	int n = tPartChange.cPart->LineIntersectNut(cGarLocation->getCamPos(),dir);

	if(n == -1)
		return;
	CNut *nut = tPartChange.cPart->getNut(n);

	// Left clicking does the work
	if(mouse->Up & SDL_BUTTON(1)) {

        // If the nuts are going on, left clicking on a nut puts the nut in
        if( tPartChange.iNutsGoingon ) {

            // Do ratchet noise
            if( !nut->getIn() )
		        BASS_SamplePlay(sfxParts.smpRatchet);

            nut->setIn(true);

            // If the nuts are all on the part, then we finish adding the part
            if( tPartChange.cPart->AllNutsOn() )
                Gar_FinishAddPart();
        } else {

            // If the nuts are coming off, left clicking on a nut removes it

            // Do ratchet noise
            if( nut->getIn() )
		        BASS_SamplePlay(sfxParts.smpRatchet);

            nut->setIn(false);

            // If all the nuts are gone, remove the part from the car
            // and put it into the player's spare parts
            if( tPartChange.cPart->AllNutsGone() )
                Gar_RemovePart();
        }
    }

    // Highlight the nut
	nut->setHighlight(true);
	cGarLocation->setStatusText((char *)(nut->getIn() ? "Undo nut" : "Put nut"));
}