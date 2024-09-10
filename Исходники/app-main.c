NXCTRL_VOID
NXCTRLAPP_run (LPNXCTRLAPP pApp) {
  updateMenuButtonState(pApp);
  updateExecButtonState(pApp);

  if (!IN_MENU)
    displayInfo(pApp);

  if (MENU_U_BUTTON_STATE != NXCTRL_HIGH && MENU_D_BUTTON_STATE != NXCTRL_HIGH &&
      EXEC_BUTTON_STATE != NXCTRL_HIGH) {
    DPY_IDLE_COUNT++;
    if (DPY_IDLE_COUNT > DPY_IDLE_COUNT_MAX) {
      pApp->nCmd = 2;
      return;
    }
    return;
  }

  if (MENU_U_BUTTON_STATE == NXCTRL_ON || MENU_D_BUTTON_STATE == NXCTRL_ON) {
    if (IN_MENU) {
      if (canAction()) {
        if (MENU_D_BUTTON_STATE == NXCTRL_ON) {
          if (MENU_IDX < MENU_IDX_COUNT - 1)
            MENU_IDX++;
          else
            MENU_IDX = 0;
        } else {
          if (MENU_IDX > 0)
            MENU_IDX--;
          else
            MENU_IDX = MENU_IDX_COUNT - 1;
        }
        displayMenu(pApp);
      }
    } else {
      IN_MENU = NXCTRL_TRUE;
      displayMenu(pApp);
      canAction();
    }
  }

  if (EXEC_BUTTON_STATE == NXCTRL_ON) {
    if (IN_MENU) {
      if (canAction()) {
        switch (MENU_IDX) {
        case MENU_IDX_EXIT_MENU:
          IN_MENU = NXCTRL_FALSE;
          displayInfo(pApp);
          break;
        case MENU_IDX_SYSTEM_MENU:
          pApp->nCmd = 1;
          return;
        case MENU_IDX_UPDATE_TIME:
          pApp->clearDisplay();
          pApp->setCursor(FONT_WIDTH*5, FONT_HEIGHT*3);
          pApp->writeSTR("UPDATING...");
          pApp->updateDisplay();
          system("/usr/bin/ntpd -gq");
          IN_MENU = NXCTRL_FALSE;
          displayInfo(pApp);
          break;
        default:
          break;
        }
      }
    }
  }
}