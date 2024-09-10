int UtcDaliTextInputSetMaxCharacterLength(void)
{
  ToolkitTestApplication application;

  tet_infoline("Testing Setting of max characters");

  const int maxChars = 4;
  const char* testChar  = "v";

  TextInput textInput = TextInput::New();  // create empty TextInput
  Stage::GetCurrent().Add(textInput);
  application.SendNotification();
  application.Render();

  textInput.SetMaxCharacterLength(maxChars);

  Integration::KeyEvent event(testChar, testChar, 0, 0, 0, Integration::KeyEvent::Down );

  std::string testString = "";

  tet_infoline("Starting editmode");
  textInput.SetEditable( true );

  tet_infoline("Sending Key Events");
  // Send max number of characters
  for (int i=0; i < maxChars; i++)
    {
      application.ProcessEvent(event);
      testString.append(testChar);
    }

  tet_printf( "Get text result : %s\n", textInput.GetText().c_str());

  DALI_TEST_EQUALS(testString, textInput.GetText(), TEST_LOCATION);

  tet_infoline("Sending Key Event which exceeds max characters");

  application.ProcessEvent(event); // try to append additional character

  DALI_TEST_EQUALS(testString,textInput.GetText(), TEST_LOCATION);

  tet_infoline("Increase max characters limit");

  textInput.SetMaxCharacterLength(maxChars+1); // increment max characters by 1

  tet_infoline("Send character again which should now fit");
  application.ProcessEvent(event); // append additional character
  testString.append(testChar);

  DALI_TEST_EQUALS(testString,textInput.GetText(), TEST_LOCATION);
  END_TEST;
}