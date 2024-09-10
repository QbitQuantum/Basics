void ConsoleState::Update(const ActionMap & actions, unsigned int tElapsed)  {
   const InputState & input = *actions.GetInputState();

   if (input.KeyDown(SDLKey::SDLK_PAGEUP))
      console.ScrollUp(3);

   if (input.KeyDown(SDLKey::SDLK_PAGEDOWN))
      console.ScrollDown(3);

   if (!input.KeyDown(SDLKey::SDLK_BACKQUOTE))
      _input->Update(actions, tElapsed);

   if (input.KeyDown(SDLKey::SDLK_RETURN)) {
      ConsoleCommand c = _parseCommand(_input->GetText());

      if (c.Command == "dumplog")  {

         if (c.Params.size() > 0) 
            console.Write(c.Params.at(0).c_str());
         else
            console.Write("console.log");

         console.AddLine("Successfully wrote console log to file!");

      } else if (c.Command == "showfps")  {

         Preferences.SetValue<bool>("SHOWFPS", !Preferences.GetValue<bool>("SHOWFPS"));
         if (Preferences.GetValue<bool>("SHOWFPS"))
            console.AddLine("Frames per second display on.");
         else
            console.AddLine("Frames per second display off.");

      } else
         console.AddLine(std::string("[echo] ") + _input->GetText());

      _input->SetText(std::string(""));
   }
}