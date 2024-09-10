void mnRegressionTest()
{
	Menu M;
	sf::Context C; C.setActive(1);
	SharedResources SR;
	shInit(&SR, NULL, NULL);
	
	shLoadAudio(&SR);
	//shLoadTextures(&SR); //Il faut un contexte valid d'OpenGL
	shLoadFonts(&SR);
	
	printf("=== mnRegressionTest Begin ===\n");
	mnInit(&M, &SR);
	
	mnAddMenu(&M, "Menu", 2);
	mnAddMenu(&M, "menu2", 2);
	
	mnAddItemMenuSwitcher(&M, 0, "texte", 1);
	mnAddItem(&M, 0, "teee", ITEM_LABEL, NULL, NULL);
	
	mnAddItem(&M, 1, "teeee", ITEM_LABEL, NULL, NULL);
	mnAddItemMenuSwitcher(&M, 1, "move", 0);
	
	assert(mnGetCurrentMenuID(&M) == 0);
	
	mnGoToMenu(&M, 1);
	
	for (int i=0; i<1000; i++)
		mnUpdate(&M, vec2(0.f, 0.f), vec2(0.f, 0.f));
	
	assert(mnGetCurrentMenuID(&M) == 1);
	
	mnGoToMenu(&M, 0);
	
	for (int i=0; i<1000; i++)
		mnUpdate(&M, vec2(0.f, 0.f), vec2(0.f, 0.f));
	
	assert(mnGetCurrentMenuID(&M) == 0);
	
	mnFree(&M);
	printf("=== mnRegressionTest End =====\n");
	shFree(&SR);
	
	//Il y a des leaks à cause des sons, problème de SFML, impossible de le contourner...
}