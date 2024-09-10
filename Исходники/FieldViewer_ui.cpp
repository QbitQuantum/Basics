GLMotif::Popup* Viewer::createDynamicsTogglesMenu()
{
   WidgetFactory factory;

   // create the top-level shell
   GLMotif::Popup* dynamicsTogglesMenuPopup=factory.createPopupMenu("DynamicsTogglesMenuPopup");

   // create button array inside top-level shell
   GLMotif::RowColumn* dynamicsTogglesMenu=factory.createMenu("DynamicsTogglesMenu");

   // for each of the experiment names
   for (std::vector<std::string>::const_iterator name=experiment_names.begin(); name!=experiment_names.end(); ++name)
   {
      size_t iIndex = (*name).rfind("Hidden");
      if( iIndex != std::string::npos )
      {
         // then while loaded, we do not make this experiment available to the user
         continue;
      }

      // create toggle button
      std::string toggle_name=(*name) + "toggle";
      GLMotif::ToggleButton* toggle=factory.createToggleButton(const_cast<char*> (toggle_name.c_str()), const_cast<char*> ((*name).c_str()));

      // turn on the first toggle
      //if (name == experiment_names.begin())
      //   toggle->setToggle(true);

      toggle->getValueChangedCallbacks().add(this, &Viewer::dynamicsMenuCallback);
      dynamicsToggleButtons.push_back(toggle);

   }

   dynamicsTogglesMenu->manageChild();

   return dynamicsTogglesMenuPopup;
}