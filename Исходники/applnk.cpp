void AppLnk::setPreloaded(bool yesNo) {
  // Preload information is stored in the Launcher config in v1.5.
  Config cfg("Launcher");
  cfg.setGroup("Preload");
  QStringList apps = cfg.readListEntry("Apps", ',');
  if (apps.contains(exec()) && !yesNo)
    apps.remove(exec());
  else if (yesNo && !apps.contains(exec()))
    apps.append(exec());
  cfg.writeEntry("Apps", apps, ',');
}