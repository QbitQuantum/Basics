bool IsAeroGlassEnabled() {
  if (IsWindowsXP()) {
    return false;
  }

  BOOL enabled = FALSE;
  return SUCCEEDED(DwmIsCompositionEnabled(&enabled)) && enabled;
}