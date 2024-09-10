QHash<QString,QList<XDGDesktop> > LXDG::sortDesktopCats(QList<XDGDesktop> apps){
  //Sort the list of applications into their different categories (main categories only)
  //Create the category lists
  QList<XDGDesktop> multimedia, dev, ed, game, graphics, network, office, science, settings, sys, utility, other, wine;
  //Sort the apps into the lists
  for(int i=0; i<apps.length(); i++){
    if(apps[i].catList.contains("AudioVideo")){ multimedia << apps[i]; }
    else if(apps[i].catList.contains("Development")){ dev << apps[i]; }
    else if(apps[i].catList.contains("Education")){ ed << apps[i]; }
    else if(apps[i].catList.contains("Game")){ game << apps[i]; }
    else if(apps[i].catList.contains("Graphics")){ graphics << apps[i]; }
    else if(apps[i].catList.contains("Network")){ network << apps[i]; }
    else if(apps[i].catList.contains("Office")){ office << apps[i]; }
    else if(apps[i].catList.contains("Science")){ science << apps[i]; }
    else if(apps[i].catList.contains("Settings")){ settings << apps[i]; }
    else if(apps[i].catList.contains("System")){ sys << apps[i]; }
    else if(apps[i].catList.contains("Utility")){ utility << apps[i]; }
    else if(apps[i].catList.contains("Wine")){ wine << apps[i]; }
    else{ other << apps[i]; }
  }
  //Now create the output hash
  QHash<QString,QList<XDGDesktop> > out;
  if(!multimedia.isEmpty()){ out.insert("Multimedia", LXDG::sortDesktopNames(multimedia)); }
  if(!dev.isEmpty()){ out.insert("Development", LXDG::sortDesktopNames(dev)); }
  if(!ed.isEmpty()){ out.insert("Education", LXDG::sortDesktopNames(ed)); }
  if(!game.isEmpty()){ out.insert("Game", LXDG::sortDesktopNames(game)); }
  if(!graphics.isEmpty()){ out.insert("Graphics", LXDG::sortDesktopNames(graphics)); }
  if(!network.isEmpty()){ out.insert("Network", LXDG::sortDesktopNames(network)); }
  if(!office.isEmpty()){ out.insert("Office", LXDG::sortDesktopNames(office)); }
  if(!science.isEmpty()){ out.insert("Science", LXDG::sortDesktopNames(science)); }
  if(!settings.isEmpty()){ out.insert("Settings", LXDG::sortDesktopNames(settings)); }
  if(!sys.isEmpty()){ out.insert("System", LXDG::sortDesktopNames(sys)); }
  if(!utility.isEmpty()){ out.insert("Utility", LXDG::sortDesktopNames(utility)); }
  if(!wine.isEmpty()){ out.insert("Wine", LXDG::sortDesktopNames(wine)); }
  if(!other.isEmpty()){ out.insert("Unsorted", LXDG::sortDesktopNames(other)); }
  //return the resulting hash
  return out;
}