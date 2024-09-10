void initPatchSection( )
{
    patchSection.bankLed = new JunoAlphaLed( "bank" );
    patchSection.patchLed = new JunoAlphaLed( "patch" );
    for( int i = 0; i < 10; i++)
    {
	String tmp;
	tmp.sprintf( "patch_%d", i );

	patchSection.patchButtons[i] = new JunoButton( GTK_JUNO_BUTTON_CREAM, 
						       (const char *)tmp, false );
	gtk_signal_connect( GTK_OBJECT( patchSection.patchButtons[i]->widget ),
			    "pressed",
			    GTK_SIGNAL_FUNC( buttonPressed ), 
			    patchSection.patchButtons[i] );
    }

    patchSection.usedLed = gtk_juno_led_new();
    gtk_widget_show( patchSection.usedLed );

    patchSection.saveButton = new JunoButton( GTK_JUNO_BUTTON_YELLOW, "patch_save", false );
    patchSection.loadButton = new JunoButton( GTK_JUNO_BUTTON_ORANGE, "patch_load", false );

    gtk_signal_connect( GTK_OBJECT( patchSection.bankLed->widget ),
			"value_changed",
			GTK_SIGNAL_FUNC( patchChanged ), NULL );

    gtk_signal_connect( GTK_OBJECT( patchSection.patchLed->widget ),
			"value_changed",
			GTK_SIGNAL_FUNC( patchChanged ), NULL );

    gtk_signal_connect( GTK_OBJECT( patchSection.saveButton->widget ),
			"pressed",
			GTK_SIGNAL_FUNC( buttonPressed ), 
			patchSection.saveButton );


    gtk_signal_connect( GTK_OBJECT( patchSection.loadButton->widget ),
			"pressed",
			GTK_SIGNAL_FUNC( buttonPressed ), 
			patchSection.loadButton );
}