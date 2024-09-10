void updateDisplay(void)
{
  // Updates to the temperature can come at any time, only update 
  // if we're in a state that displays them
  state_t state = Menus.getState();
  if (!isMenuHomeState())
    return;

  char buffer[17];
  unsigned char probeIdxLow, probeIdxHigh;

  // Fixed pit area
  lcd.setCursor(0, 0);
  if (state == ST_HOME_ALARM)
  {
    toneEnable(true);
    if (ALARM_ID_TO_IDX(g_AlarmId) == ALARM_IDX_LOW)
      lcdprint_P(PSTR("** ALARM LOW  **"), false);
    else
      lcdprint_P(PSTR("** ALARM HIGH **"), false);

    probeIdxLow = probeIdxHigh = ALARM_ID_TO_PROBE(g_AlarmId);
  }  /* if ST_HOME_ALARM */
  else
  {
    toneEnable(false);

    /* Big Number probes overwrite the whole display if it has a temperature */
    if (g_HomeDisplayMode >= TEMP_PIT && g_HomeDisplayMode <= TEMP_AMB)
    {
      TempProbe *probe = pid.Probes[g_HomeDisplayMode];
      if (probe->hasTemperature())
      {
        lcdPrintBigNum(probe->Temperature);
        return;
      }
    }

    /* Default Pit / Fan Speed first line */
    int pitTemp;
    if (pid.Probes[TEMP_CTRL]->hasTemperature())
      pitTemp = pid.Probes[TEMP_CTRL]->Temperature;
    else
      pitTemp = 0;
    if (!pid.getManualOutputMode() && !pid.Probes[TEMP_CTRL]->hasTemperature())
      memcpy_P(buffer, LCD_LINE1_UNPLUGGED, sizeof(LCD_LINE1_UNPLUGGED));
    else if (pid.LidOpenResumeCountdown > 0)
      snprintf_P(buffer, sizeof(buffer), PSTR("Pit:%3d"DEGREE"%c Lid%3u"),
        pitTemp, pid.getUnits(), pid.LidOpenResumeCountdown);
    else
    {
      char c1,c2;
      if (pid.getManualOutputMode())
      {
        c1 = '^';  // LCD_ARROWUP
        c2 = '^';  // LCD_ARROWDN
      }
      else
      {
        c1 = '[';
        c2 = ']';
      }
      snprintf_P(buffer, sizeof(buffer), PSTR("Pit:%3d"DEGREE"%c %c%3u%%%c"),
        pitTemp, pid.getUnits(), c1, pid.getPidOutput(), c2);
    }

    lcd.print(buffer);
    // Display mode 0xff is 2-line, which only has space for 1 non-pit value
    if (g_HomeDisplayMode == 0xff)
      probeIdxLow = probeIdxHigh = state - ST_HOME_FOOD1 + TEMP_FOOD1;
    else
    {
      // Display mode 0xfe is 4 line home, display 3 other temps there
      probeIdxLow = TEMP_FOOD1;
      probeIdxHigh = TEMP_AMB;
    }
  } /* if !ST_HOME_ALARM */

  // Rotating probe display
  for (unsigned char probeIndex=probeIdxLow; probeIndex<=probeIdxHigh; ++probeIndex)
  {
    if (probeIndex < TEMP_COUNT && pid.Probes[probeIndex]->hasTemperature())
    {
      loadProbeName(probeIndex);
      snprintf_P(buffer, sizeof(buffer), PSTR("%-12s%3d"DEGREE), editString,
        (int)pid.Probes[probeIndex]->Temperature);
    }
    else
    {
      // If probeIndex is outside the range (in the case of ST_HOME_NOPROBES)
      // just fill the bottom line with spaces
      memset(buffer, ' ', sizeof(buffer));
      buffer[sizeof(buffer) - 1] = '\0';
    }

    lcd.setCursor(0, probeIndex - probeIdxLow + 1);
    lcd.print(buffer);
  }
}