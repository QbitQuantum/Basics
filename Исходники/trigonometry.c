trigonometry (){
	char selectora;
	char selectorb;
	puts ("do you have lines and angles, just angles or just lines? \nIf you have both angles and lines please enter \"al\"\nIf you only have lines please enter \"ll\"\nOr for the main menu please enter \"m\"");
	scanf ("%c%c", &selectora, &selectorb);
	flushall ();
	selectora = toupper (selectora);
	selectorb = toupper (selectorb);
	
	if (selectora == 'L' && selectorb == 'L'){
		lineline();
	}else if (selectora == 'A' && selectorb == 'L'){
		angleline();
	}else if (selectora == 'L' && selectorb == 'A'){
		angleline();
	}else if (selectora == 'M' || selectorb == 'M'){
		main();
	}else {
		trigonometry();
	}
}