void keyMouse::applyKeys(){
	INPUT eventPress = {0};
	INPUT eventRelease = {0};
	bool send = false;

	//Check if there is anything new to press
	for(std::vector<std::string>::size_type i = 0; i != buttons.size(); i++) {
		//if in buttons and not in buttonsOld press it
		if(!(std::find(buttonsOld.begin(), buttonsOld.end(), buttons[i]) != buttonsOld.end())){
			// buttonsOld does not contain buttons[i] so press the button
			if(buttons[i].find("KEY") != std::string::npos){
				pressKey(eventPress, bmap[buttons[i]]);
				send = true;
			}else if(buttons[i].find("MOUSE") != std::string::npos){
				pressMouse(eventPress, bmap[buttons[i]]);
				send = true;
			}else if(buttons[i].find("MOTION") != std::string::npos){
				send = false;
				processMotionPress(buttons[i]);
			}
			if(send == true){
				SendInput( 1, &eventPress, sizeof( eventPress ) );
			}
		}
	}

	//Check if anything that was pressed last time is now unpressed
	for(std::vector<std::string>::size_type i = 0; i != buttonsOld.size(); i++) {
		//if in buttonsOld and not in buttons release it
		if( !(std::find(buttons.begin(), buttons.end(), buttonsOld[i]) != buttons.end())) {
			// buttons does not contain buttonsOld[i] so release the button press
			if(buttonsOld[i].find("KEY") != std::string::npos){
				releaseKey(eventRelease, bmap[buttonsOld[i]]);
				send = true;
			//	std::cout << " ReleaseKey: " << buttonsOld[i] << "\n";
			}else if(buttonsOld[i].find("MOUSE") != std::string::npos){
				releaseMouse(eventRelease, bmap[buttonsOld[i]]);
				send = true;
				//std::cout << " ReleaseMouse: " << buttonsOld[i] << "\n";
			}else if(buttonsOld[i].find("MOTION") != std::string::npos){
				send = false;
				processMotionRelease(buttonsOld[i]);
			}
			if(send == true){
				SendInput( 1, &eventRelease, sizeof( eventRelease ) );
			}
		}
	}
	buttonsOld = buttons;
	//clear the vector
	buttons.clear();
}