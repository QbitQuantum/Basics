void Willard_HW02_Linked_ListApp::keyDown(KeyEvent event)
{

	if(event.getCode() == KeyEvent::KEY_r){
		reverseList(sentinel);
	}

	char yup = event.getChar();
	if(yup == '/' || yup == '?')
	{
	if(showMenu){
		showMenu = false;
	} else{
		showMenu = true;
		}
	}

	if(event.getCode() == KeyEvent::KEY_SPACE){
		reverseList(sentinel);
	}

	if(event.getCode() == KeyEvent::KEY_UP){
		toTop();
	}
}