NXCTRL_VOID
NXCTRLAPP_clean (LPNXCTRLAPP pApp) {
  pApp->setCursor(FONT_WIDTH*3, FONT_HEIGHT*3);
  pApp->writeSTR("AppClean\n");
  pApp->updateDisplay();
}