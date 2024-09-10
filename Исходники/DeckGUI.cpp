DeckGUI::DeckGUI()  {
	// Images can only be loaded once the main window has been initialized, so cannot be done as a static
	// constant array. Instead, use the STL transform algorithm to apply the method createPixbuf to every
	// element in the array of image names, starting with first and ending with the last. New elements are
	// added to the back of deck.
	transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)], 
			   std::back_inserter(deck), &createPixbuf );	
	transform( &legal_image_names[0], &legal_image_names[G_N_ELEMENTS(legal_image_names)], 
			   std::back_inserter(legalDeck), &createPixbuf );
} // DeckGUI::DeckGUI