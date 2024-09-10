 bool SetFocus() override {
   if (allow_navigation)
     goto_button.SetFocus();
   return true;
 }