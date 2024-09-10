void VCButton::saveToFile(QFile& file, unsigned int parentID)
{
  QString s;
  QString t;

  // Comment
  s = QString("# Virtual Console Button Entry\n");
  file.writeBlock((const char*) s, s.length());

  // Entry type
  s = QString("Entry = Button") + QString("\n");
  file.writeBlock((const char*) s, s.length());

  // Name
  s = QString("Name = ") + caption() + QString("\n");
  file.writeBlock((const char*) s, s.length());

  // Parent ID
  t.setNum(parentID);
  s = QString("Parent = ") + t + QString("\n");
  file.writeBlock((const char*) s, s.length());

  // X
  t.setNum(x());
  s = QString("X = ") + t + QString("\n");
  file.writeBlock((const char*) s, s.length());

  // Y
  t.setNum(y());
  s = QString("Y = ") + t + QString("\n");
  file.writeBlock((const char*) s, s.length());

  // W
  t.setNum(width());
  s = QString("Width = ") + t + QString("\n");
  file.writeBlock((const char*) s, s.length());

  // H
  t.setNum(height());
  s = QString("Height = ") + t + QString("\n");
  file.writeBlock((const char*) s, s.length());

  // Text color
  if (ownPalette())
    {
      t.setNum(qRgb(paletteForegroundColor().red(),
		    paletteForegroundColor().green(),
		    paletteForegroundColor().blue()));
      s = QString("Textcolor = ") + t + QString("\n");
      file.writeBlock((const char*) s, s.length());

      // Background color
      t.setNum(qRgb(paletteBackgroundColor().red(),
		    paletteBackgroundColor().green(),
		    paletteBackgroundColor().blue()));
      s = QString("Backgroundcolor = ") + t + QString("\n");
      file.writeBlock((const char*) s, s.length());
    }

  // Background pixmap
  if (paletteBackgroundPixmap())
    {
      s = QString("Pixmap = " + iconText() + QString("\n"));
      file.writeBlock((const char*) s, s.length());
    }

  // Font
  s = QString("Font = ") + font().toString() + QString("\n");
  file.writeBlock((const char*) s, s.length());

  // Function
  s.sprintf("Function = %d\n", m_functionID);
  file.writeBlock((const char*) s, s.length());

  // Key binding
  assert(m_keyBind);

  s.sprintf("BindKey = %d\n", m_keyBind->key());
  file.writeBlock((const char*) s, s.length());

  s.sprintf("BindMod = %d\n", m_keyBind->mod());
  file.writeBlock((const char*) s, s.length());

  s.sprintf("BindPress = %d\n", m_keyBind->pressAction());
  file.writeBlock((const char*) s, s.length());
  
  s.sprintf("BindRelease = %d\n", m_keyBind->releaseAction());
  file.writeBlock((const char*) s, s.length());
}