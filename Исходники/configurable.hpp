 /// Initialize this instance using the specified configuration property tree
 void configure(utility::Configuration::CursorPtr theprops)
 {
   if (theprops) {
     p_configCursor = theprops->getCursor(this->p_key);
   }
   this->p_configure(p_configCursor);
   p_isConfigured = true;
 }