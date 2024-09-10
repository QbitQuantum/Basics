uint32_t CButtonTranslator::TranslateGamepadString(const char *szButton)
{
  if (!szButton) 
    return 0;
  uint32_t buttonCode = 0;
  CStdString strButton = szButton;
  strButton.ToLower();
  if (strButton.Equals("a")) buttonCode = KEY_BUTTON_A;
  else if (strButton.Equals("b")) buttonCode = KEY_BUTTON_B;
  else if (strButton.Equals("x")) buttonCode = KEY_BUTTON_X;
  else if (strButton.Equals("y")) buttonCode = KEY_BUTTON_Y;
  else if (strButton.Equals("white")) buttonCode = KEY_BUTTON_WHITE;
  else if (strButton.Equals("black")) buttonCode = KEY_BUTTON_BLACK;
  else if (strButton.Equals("start")) buttonCode = KEY_BUTTON_START;
  else if (strButton.Equals("back")) buttonCode = KEY_BUTTON_BACK;
  else if (strButton.Equals("leftthumbbutton")) buttonCode = KEY_BUTTON_LEFT_THUMB_BUTTON;
  else if (strButton.Equals("rightthumbbutton")) buttonCode = KEY_BUTTON_RIGHT_THUMB_BUTTON;
  else if (strButton.Equals("leftthumbstick")) buttonCode = KEY_BUTTON_LEFT_THUMB_STICK;
  else if (strButton.Equals("leftthumbstickup")) buttonCode = KEY_BUTTON_LEFT_THUMB_STICK_UP;
  else if (strButton.Equals("leftthumbstickdown")) buttonCode = KEY_BUTTON_LEFT_THUMB_STICK_DOWN;
  else if (strButton.Equals("leftthumbstickleft")) buttonCode = KEY_BUTTON_LEFT_THUMB_STICK_LEFT;
  else if (strButton.Equals("leftthumbstickright")) buttonCode = KEY_BUTTON_LEFT_THUMB_STICK_RIGHT;
  else if (strButton.Equals("rightthumbstick")) buttonCode = KEY_BUTTON_RIGHT_THUMB_STICK;
  else if (strButton.Equals("rightthumbstickup")) buttonCode = KEY_BUTTON_RIGHT_THUMB_STICK_UP;
  else if (strButton.Equals("rightthumbstickdown")) buttonCode = KEY_BUTTON_RIGHT_THUMB_STICK_DOWN;
  else if (strButton.Equals("rightthumbstickleft")) buttonCode = KEY_BUTTON_RIGHT_THUMB_STICK_LEFT;
  else if (strButton.Equals("rightthumbstickright")) buttonCode = KEY_BUTTON_RIGHT_THUMB_STICK_RIGHT;
  else if (strButton.Equals("lefttrigger")) buttonCode = KEY_BUTTON_LEFT_TRIGGER;
  else if (strButton.Equals("righttrigger")) buttonCode = KEY_BUTTON_RIGHT_TRIGGER;
  else if (strButton.Equals("leftanalogtrigger")) buttonCode = KEY_BUTTON_LEFT_ANALOG_TRIGGER;
  else if (strButton.Equals("rightanalogtrigger")) buttonCode = KEY_BUTTON_RIGHT_ANALOG_TRIGGER;
  else if (strButton.Equals("dpadleft")) buttonCode = KEY_BUTTON_DPAD_LEFT;
  else if (strButton.Equals("dpadright")) buttonCode = KEY_BUTTON_DPAD_RIGHT;
  else if (strButton.Equals("dpadup")) buttonCode = KEY_BUTTON_DPAD_UP;
  else if (strButton.Equals("dpaddown")) buttonCode = KEY_BUTTON_DPAD_DOWN;
  else CLog::Log(LOGERROR, "Gamepad Translator: Can't find button %s", strButton.c_str());
  return buttonCode;
}