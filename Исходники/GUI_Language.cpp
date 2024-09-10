void LanguageOnSelect( VariantList *pVList )
{
	Entity *pEntClicked = pVList->m_variant[1].GetEntity();

	Config* config = Config::GetInstance();

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_LANGUAGE_BACK_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		OptionsCreate( pEntClicked->GetParent()->GetParent() );
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_FLAG_EN_BUTTON )
	{
		GetApp()->buttonClickSound();
		config->setLang( convertCodeToId( LANG_NAMES[ LANG_EN ] ) );
		config->Save();
		config->ReloadLang( LANG_EN );
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		OptionsCreate( pEntClicked->GetParent()->GetParent() );
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_FLAG_RU_BUTTON )
	{
		GetApp()->buttonClickSound();
		config->setLang( convertCodeToId( LANG_NAMES[ LANG_RU ] ) );
		config->Save();
		config->ReloadLang( LANG_RU );
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		OptionsCreate( pEntClicked->GetParent()->GetParent() );
	}

	config->FreeInstance();
}