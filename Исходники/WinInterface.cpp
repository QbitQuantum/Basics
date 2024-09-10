//---------------------------------------------------------------------------
void __fastcall TWinInteractiveCustomCommand::Prompt(
  const UnicodeString & Prompt, UnicodeString & Value)
{
  UnicodeString APrompt = Prompt;
  if (APrompt.IsEmpty())
  {
    APrompt = FMTLOAD(CUSTOM_COMMANDS_PARAM_PROMPT, (FCustomCommandName));
  }
  TStrings * History = CustomWinConfiguration->History[L"CustomCommandParam"];
  if (InputDialog(FMTLOAD(CUSTOM_COMMANDS_PARAM_TITLE, (FCustomCommandName)),
        APrompt, Value, HELP_CUSTOM_COMMAND_PARAM, History))
  {
    CustomWinConfiguration->History[L"CustomCommandParam"] = History;
  }
  else
  {
    Abort();
  }
}