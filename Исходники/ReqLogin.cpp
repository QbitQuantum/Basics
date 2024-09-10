void ReqLogin::ChooseMode()
{
  TheResearchCalendar::Instance()->Clear();

  GameMode gm = AMJU_MODE_NO_GAME;
  bool doCogTests = false;

  PXml research = m_xml.getChildNode(5);
  if (SafeStrCmp(research.getName(), "research"))
  {
    // Schedule - for calendar
    PXml p = research.getChildNode(4);
    if (SafeStrCmp(p.getName(), "dates"))
    {
      Time today(Time::Now());
      today.RoundDown(TimePeriod(ONE_DAY_IN_SECONDS));

      // Bunch of dates - add to TheResearchCal
      int numDates = p.nChildNode();
      for (int i = 0; i < numDates; i++)
      {
        PXml date = p.getChildNode(i);
        if (SafeStrCmp(date.getName(), "date"))
        {
          if (SafeStrCmp(date.getChildNode(0).getName(), "timestamp") &&
              SafeStrCmp(date.getChildNode(1).getName(), "cogtest") &&
              SafeStrCmp(date.getChildNode(2).getName(), "play"))
          {
            std::string dateStr = date.getChildNode(0).getText();
            bool cogtest = SafeStrCmp(date.getChildNode(1).getText(), "1"); 
            bool play = SafeStrCmp(date.getChildNode(2).getText(), "1"); 

            Time t(dateStr);
            t.RoundDown(TimePeriod(ONE_DAY_IN_SECONDS));
            if (t == today)
            {
              // Cog tests already done today ?
              Results results = TheCogTestResults::Instance()->GetResultsForDate(Time::Now());
              if (results.empty())
              {
                doCogTests = cogtest;
              }
              else
              {
                doCogTests = false;
                std::cout << "Test results for today are here already.\n";
              }

              if (play)
              { 
                gm = AMJU_MODE_MULTI;
              }
              if (doCogTests && !play)
              {
                // Create dummy target for heart count, etc
                CreateDummyLocalPlayer();
              }
            }
            TheResearchCalendar::Instance()->AddResearchDate(ResearchDate(Time(dateStr), cogtest, play));   
          }
          else
          {
            std::cout << "Login: unexpected format for session dates.\n";
            Assert(0);
          }
        }
      }
    }
    else
    {
      std::cout << "Login: found research element but no schedule.\n";
    }
  }
  else
  {
    std::cout << "No research element in login.pl response?!?\n";
    Assert(0);
  }

  // Now we can look up today on the calendar to get game mode flags.

  ResetLocalPlayerFuelCount();

  SetGameMode(gm); // TODO handle edit mode - send extra flag to login.pl ??

  SetDoCogTests(doCogTests); // mode, in GameMode

  TheGSCalendar::Instance()->SetPrevState(TheGSToday::Instance());
  TheGSThanks::Instance()->SetPrevState(TheGSToday::Instance());
  TheGame::Instance()->SetCurrentState(TheGSThanks::Instance());
  TheGSMain::Instance()->ResetHud();
}