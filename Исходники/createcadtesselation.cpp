void CreateCadTesselation::operate()
{
  double preview_memory = min(1024*1024*100.0, m_ScanMemory);
  int N = int(pow(preview_memory/sizeof(float), 1.0/3.0));
  m_Ni = N;
  m_Nj = N;
  m_Nk = N;
  m_X1 = vec3_t(-1e6,-1e6,-1e6);
  m_X2 = vec3_t( 1e6, 1e6, 1e6);
  m_Dx = (m_X2[0] - m_X1[0])/(m_Ni-1);
  m_Dy = (m_X2[1] - m_X1[1])/(m_Nj-1);
  m_Dz = (m_X2[2] - m_X1[2])/(m_Nk-1);
  double new_vol, old_vol;
  int count = 0;
  do {
    old_vol = (m_X2[0]-m_X1[0])*(m_X2[1]-m_X1[1])*(m_X2[2]-m_X1[2]);
    QString num;
    QString text = "scanning (V=";
    num.setNum(old_vol);
    text += num + ")";

    GuiMainWindow::pointer()->resetProgress(text, 3*N*N);
    scan(false);
    if (m_GeometryFound) {
      m_X1 = m_XScan1 - 2*vec3_t(m_Dx, m_Dy, m_Dz);
      m_X2 = m_XScan2 + 2*vec3_t(m_Dx, m_Dy, m_Dz);
    } else {
      m_X1 *= 0.1;
      m_X2 *= 0.1;
    }
    new_vol = (m_X2[0]-m_X1[0])*(m_X2[1]-m_X1[1])*(m_X2[2]-m_X1[2]);
  } while (count < 20 && (old_vol - new_vol)/old_vol > 0.05);

  // bounding box should now be established
  // last scan run with the full resoluion (if required)
  double Lx = m_X2[0] - m_X1[0];
  double Ly = m_X2[1] - m_X1[1];
  double Lz = m_X2[2] - m_X1[2];
  double max_size = m_ScanMemory/sizeof(float);
  double delta = max(m_SmallestResolution, pow(Lx*Ly*Lz/max_size, 1.0/3.0));
  int interlaces = 0;
  if (preserveFluid() || preserveSolid()) {
    interlaces = int(2*delta/m_SmallestFeatureSize);
  }
  m_Ni = int(Lx/delta) + 1;
  m_Nj = int(Ly/delta) + 1;
  m_Nk = int(Lz/delta) + 1;
  QString num;
  QString text = "scanning (h=";
  num.setNum(delta/(interlaces+1));
  text += num + ")";
  GuiMainWindow::pointer()->resetProgress(text, m_Ni*m_Nj + m_Ni*m_Nk + m_Nj*m_Nk);
  scan(true, interlaces);

  updateNodeIndex(m_Grid);
  updateCellIndex(m_Grid);
  GuiMainWindow::pointer()->resetXmlDoc();
  GuiMainWindow::pointer()->clearBCs();
  GuiMainWindow::pointer()->setBC(1, BoundaryCondition("imported", "patch", 1));

  GuiMainWindow::pointer()->resetProgress(" ", 100);
}