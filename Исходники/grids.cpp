void
Grids::processCommand(int idx, QString cmd)
{
  bool ok;
  QString origCmd = cmd;
  cmd = cmd.toLower();
  QStringList list = cmd.split(" ", QString::SkipEmptyParts);
  
  if (list[0] == "normalize" ||
      list[0] == "normalise")
    {
      m_grids[idx]->normalize();
    }
  else if (list[0] == "insertrow")
    {
      if (list.count() == 2)
	{
	  int r = list[1].toInt();
	  m_grids[idx]->insertRow(r);
	}
      else
	QMessageBox::information(0, "Error", "Row number not specified");
    }	   
  else if (list[0] == "removerow")
    {
      if (list.count() == 2)
	{
	  int r = list[1].toInt();
	  m_grids[idx]->removeRow(r);
	}
      else
	QMessageBox::information(0, "Error", "Row number not specified");
    }	   
  else if (list[0] == "insertcol")
    {
      if (list.count() == 2)
	{
	  int r = list[1].toInt();
	  m_grids[idx]->insertCol(r);
	}
      else
	QMessageBox::information(0, "Error", "Row number not specified");
    }	   
  else if (list[0] == "removecol")
    {
      if (list.count() == 2)
	{
	  int r = list[1].toInt();
	  m_grids[idx]->removeCol(r);
	}
      else
	QMessageBox::information(0, "Error", "Row number not specified");
    }	   
  else if (list[0] == "sticktosurface")
    {
      int radius = 1;
      if (list.size() > 1)
	{
	  radius = list[1].toInt(&ok);
	  radius = qMin(radius, 200);
	}
      QList< QPair<Vec, Vec> > gridPNs = m_grids[idx]->getPointsAndNormals();
      emit gridStickToSurface(idx, radius, gridPNs);
    }
  else if (list[0] == "save")
    {
      QString flnm;
      flnm = QFileDialog::getSaveFileName(0,
					  "Save grid points to text file",
					  Global::previousDirectory(),
					  "Files (*.*)");
      
      if (flnm.isEmpty())
	return;
      
      QList<Vec> pts = m_grids[idx]->points();
      
      QFile fgrid(flnm);
      fgrid.open(QFile::WriteOnly | QFile::Text);
      QTextStream fd(&fgrid);
      fd << m_grids[idx]->columns()
	 << "   "
	 <<  m_grids[idx]->rows()
	 << "\n";
      for(int pi=0; pi < pts.count(); pi++)
	fd << pts[pi].x << " " << pts[pi].y << " " << pts[pi].z << "\n";
      
      fd.flush();
    }
  else
    QMessageBox::information(0, "Grid Command Error",
			     QString("Cannot understand the command : ") +
			     cmd);
  
}