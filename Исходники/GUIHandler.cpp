void GUIHandler::ReleaseFocus (int controlid)
{
  Control *control = GetControl (controlid);

  if (control)
    control->SetFocus (false);

  if (controlid == focusid)
      {
        focusid = 0;
        if (default_focusid)
          SetFocus (default_focusid);
      }
}