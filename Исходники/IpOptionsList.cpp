 void OptionsList::PrintList(std::string& list) const
 {
   list.erase();
   char buffer[256];
   Snprintf(buffer, 255, "%40s   %-20s %s\n", "Name", "Value", "# times used");
   list += buffer;
   for (std::map< std::string, OptionValue >::const_iterator p = options_.begin();
        p != options_.end();
        p++ ) {
     Snprintf(buffer, 255, "%40s = %-20s %6d\n", p->first.c_str(),
              p->second.Value().c_str(), p->second.Counter());
     list += buffer;
   }
 }