bool InputWindowXWin::config(jccl::ConfigElementPtr e)
{
   unsigned required_definition_ver(1);

   if (e->getVersion() < required_definition_ver)
   {
      vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CRITICAL_LVL)
         << clrOutBOLD(clrRED, "ERROR")
         << ": [gadget::InputWindowXWin::config()] Element named '"
         << e->getName() << "'" << std::endl << vprDEBUG_FLUSH;
      vprDEBUG_NEXT(gadgetDBG_INPUT_MGR, vprDBG_CRITICAL_LVL)
         << "is version " << e->getVersion()
         << ", but we require at least version " << required_definition_ver
         << ". Ignoring.\n" << vprDEBUG_FLUSH;
      return false;
   }

   if ( ! ( InputArea::config(e) && Input::config(e) ) )
   {
      return false;
   }

   const char neg_one_STRING[] = "-1";

   // Get size and position
   mWidth  = e->getProperty<int>("size", 0);
   mHeight = e->getProperty<int>("size", 1);

   // Sanity checks.
   if (mWidth == 0)
   {
      mWidth = 400;
   }
   if (mHeight == 0)
   {
      mHeight = 400;
   }

   mX = e->getProperty<int>("origin", 0);
   mY = e->getProperty<int>("origin", 1);

   // Get the X display string
   int x_disp_num = e->getProperty<int>("display_number");
   jccl::ConfigElementPtr disp_sys_elt =
      gadget::InputManager::instance()->getDisplaySystemElement();

   vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CONFIG_LVL)
      << "gadget::InputWindowXWin: display_number: " << x_disp_num
      << std::endl << vprDEBUG_FLUSH;

   if (NULL == disp_sys_elt.get())
   {
      vprDEBUG(vprDBG_ERROR, vprDBG_CONFIG_LVL)
         << clrOutNORM(clrRED, "ERROR")
         << ": [gadget::InputWindowXWin::config()] display_system element "
         << "is NULL.\n" << vprDEBUG_FLUSH;
      return false;
   }

   if ( x_disp_num >= 0 && disp_sys_elt.get() != NULL )
   {
      if ( disp_sys_elt->getVersion() < 3 )
      {
         vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_WARNING_LVL)
            << clrOutBOLD(clrYELLOW, "WARNING") << ": Display system element '"
            << disp_sys_elt->getName() << "'" << std::endl;
         vprDEBUG_NEXTnl(gadgetDBG_INPUT_MGR, vprDBG_WARNING_LVL)
            << "         is out of date.\n";
         vprDEBUG_NEXTnl(gadgetDBG_INPUT_MGR, vprDBG_WARNING_LVL)
            << "         Expected version 3 but found version "
            << disp_sys_elt->getVersion() << ".  Pipe\n";
         vprDEBUG_NEXTnl(gadgetDBG_INPUT_MGR, vprDBG_WARNING_LVL)
            << "         configurations will not work.\n" << vprDEBUG_FLUSH;
      }

      mXDisplayString = disp_sys_elt->getProperty<std::string>("pipes",
                                                               x_disp_num);
      
      vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CONFIG_LVL)
         << "[gadget::InputWindowXWin::config()] Display: " << mXDisplayString
         << std::endl << vprDEBUG_FLUSH;
   }
   else
   {
      mXDisplayString = std::string("-1");
   }

   if ((mXDisplayString.empty()) || (strcmp(mXDisplayString.c_str(), neg_one_STRING) == 0))    // Use display env
   {
      const std::string DISPLAY_str("DISPLAY");
      vpr::System::getenv(DISPLAY_str, mXDisplayString);
   }
   return true;
}