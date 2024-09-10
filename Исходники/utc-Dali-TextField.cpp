int utcDaliTextFieldEvent01(void)
{
  ToolkitTestApplication application;
  tet_infoline(" utcDaliTextFieldEvent01");

  // Creates a tap event. After creating a tap event the text field should
  // have the focus and add text with key events should be possible.

  TextField field = TextField::New();
  DALI_TEST_CHECK( field );

  Stage::GetCurrent().Add( field );

  field.SetSize( 300.f, 50.f );
  field.SetParentOrigin( ParentOrigin::TOP_LEFT );
  field.SetAnchorPoint( AnchorPoint::TOP_LEFT );

  // Avoid a crash when core load gl resources.
  application.GetGlAbstraction().SetCheckFramebufferStatusResult( GL_FRAMEBUFFER_COMPLETE );

  // Render and notify
  application.SendNotification();
  application.Render();

  // Add a key event but as the text field has not the focus it should do nothing.
  application.ProcessEvent( GenerateKey( "a", "a", 0, 0, 0, Integration::KeyEvent::Down ) );

  // Render and notify
  application.SendNotification();
  application.Render();

  DALI_TEST_EQUALS( field.GetProperty<std::string>( TextField::Property::TEXT ), std::string(""), TEST_LOCATION );

  // Create a tap event to touch the text field.
  application.ProcessEvent( GenerateTap( Gesture::Possible, 1u, 1u, Vector2( 150.0f, 25.0f ) ) );
  application.ProcessEvent( GenerateTap( Gesture::Started, 1u, 1u, Vector2( 150.0f, 25.0f ) ) );

  // Render and notify
  application.SendNotification();
  application.Render();

  // Now the text field has the focus, so it can handle the key events.
  application.ProcessEvent( GenerateKey( "a", "a", 0, 0, 0, Integration::KeyEvent::Down ) );
  application.ProcessEvent( GenerateKey( "a", "a", 0, 0, 0, Integration::KeyEvent::Down ) );

  // Render and notify
  application.SendNotification();
  application.Render();

  DALI_TEST_EQUALS( field.GetProperty<std::string>( TextField::Property::TEXT ), std::string("aa"), TEST_LOCATION );

  // Create a second text field and send key events to it.
  TextField field2 = TextField::New();

  field2.SetParentOrigin( ParentOrigin::TOP_LEFT );
  field2.SetAnchorPoint( AnchorPoint::TOP_LEFT );
  field2.SetSize( 100.f, 100.f );
  field2.SetPosition( 100.f, 100.f );

  Stage::GetCurrent().Add( field2 );

  // Render and notify
  application.SendNotification();
  application.Render();

  // Create a tap event on the second text field.
  application.ProcessEvent( GenerateTap( Gesture::Possible, 1u, 1u, Vector2( 150.0f, 125.0f ) ) );
  application.ProcessEvent( GenerateTap( Gesture::Started, 1u, 1u, Vector2( 150.0f, 125.0f ) ) );

  // Render and notify
  application.SendNotification();
  application.Render();

  // The second text field has the focus. It should handle the key events.
  application.ProcessEvent( GenerateKey( "a", "a", 0, 0, 0, Integration::KeyEvent::Down ) );
  application.ProcessEvent( GenerateKey( "a", "a", 0, 0, 0, Integration::KeyEvent::Down ) );

  // Render and notify
  application.SendNotification();
  application.Render();

  // Check the text has been added to the second text field.
  DALI_TEST_EQUALS( field2.GetProperty<std::string>( TextField::Property::TEXT ), std::string("aa"), TEST_LOCATION );

  END_TEST;
}