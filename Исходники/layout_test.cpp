void MyFrame::Test_GridBagLayout_2( wxCommandEvent& event )
{
	RemoveAll(); SetTestName( "GridBagLayout-2" );

	parent = new Container( this );
	SetCurrentContainer( parent );

	parent->setLayout( new GridBagLayout() );

	GridBagConstraints c;
	c.fill = GridBagConstraints::BOTH;
	c.weightx = 1.0;
	c.weighty = 1.0;
	c.gridwidth = GridBagConstraints::REMAINDER;

	parent->add( MakeButton( "Hi" ), &c );

	Container* panel = new Container();

	c.weighty = 0.0;
	parent->add( panel, &c );

	panel->setLayout( new FlowLayout() );

	for( int i = 0;i != 5; ++i )

		panel->add( MakeButton( "Button" + IntToStr(i) ) );

	if ( mCfg.mAutoPack ) parent->pack();
				     else parent->doLayout();
}