void PeakHKLErrors::functionDeriv1D(Jacobian *out, const double *xValues,
                                    const size_t nData) {
  PeaksWorkspace_sptr Peaks =
      AnalysisDataService::Instance().retrieveWS<PeaksWorkspace>(
          PeakWorkspaceName);
  boost::shared_ptr<Geometry::Instrument> instNew = getNewInstrument(Peaks);

  const DblMatrix &UB = Peaks->sample().getOrientedLattice().getUB();
  DblMatrix UBinv(UB);
  UBinv.Invert();
  UBinv /= 2 * M_PI;

  double GonRotx = getParameter("GonRotx");
  double GonRoty = getParameter("GonRoty");
  double GonRotz = getParameter("GonRotz");
  Matrix<double> InvGonRotxMat = RotationMatrixAboutRegAxis(GonRotx, 'x');
  Matrix<double> InvGonRotyMat = RotationMatrixAboutRegAxis(GonRoty, 'y');
  Matrix<double> InvGonRotzMat = RotationMatrixAboutRegAxis(GonRotz, 'z');
  Matrix<double> GonRot = InvGonRotxMat * InvGonRotyMat * InvGonRotzMat;

  InvGonRotxMat.Invert();
  InvGonRotyMat.Invert();
  InvGonRotzMat.Invert();

  std::map<int, Kernel::Matrix<double>> RunNums2GonMatrix;
  getRun2MatMap(Peaks, OptRuns, RunNums2GonMatrix);

  g_log.debug()
      << "----------------------------Derivative------------------------\n";

  V3D samplePosition = instNew->getSample()->getPos();
  IPeak &ppeak = Peaks->getPeak(0);
  double L0 = ppeak.getL1();
  double velocity = (L0 + ppeak.getL2()) / ppeak.getTOF();

  double K =
      2 * M_PI / ppeak.getWavelength() / velocity; // 2pi/lambda = K* velocity
  V3D beamDir = instNew->getBeamDirection();

  size_t paramNums[] = {parameterIndex(std::string("SampleXOffset")),
                        parameterIndex(std::string("SampleYOffset")),
                        parameterIndex(std::string("SampleZOffset"))};

  for (size_t i = 0; i < nData; i += 3) {
    int peakNum = boost::math::iround(xValues[i]);
    IPeak &peak_old = Peaks->getPeak(peakNum);
    Peak peak = createNewPeak(peak_old, instNew, 0, peak_old.getL1());

    int runNum = peak_old.getRunNumber();
    std::string runNumStr = std::to_string(runNum);

    for (int kk = 0; kk < static_cast<int>(nParams()); kk++) {
      out->set(i, kk, 0.0);
      out->set(i + 1, kk, 0.0);
      out->set(i + 2, kk, 0.0);
    }

    double chi, phi, omega;
    size_t chiParamNum, phiParamNum, omegaParamNum;

    size_t N = OptRuns.find("/" + runNumStr);
    if (N < OptRuns.size()) {
      chi = getParameter("chi" + (runNumStr));
      phi = getParameter("phi" + (runNumStr));
      omega = getParameter("omega" + (runNumStr));

      peak.setGoniometerMatrix(GonRot * RunNums2GonMatrix[runNum]);

      chiParamNum = parameterIndex("chi" + (runNumStr));
      phiParamNum = parameterIndex("phi" + (runNumStr));
      omegaParamNum = parameterIndex("omega" + (runNumStr));
    } else {

      Geometry::Goniometer Gon(peak.getGoniometerMatrix());
      std::vector<double> phichiOmega = Gon.getEulerAngles("YZY");
      chi = phichiOmega[1];
      phi = phichiOmega[2];
      omega = phichiOmega[0];
      // peak.setGoniometerMatrix( GonRot*Gon.getR());
      chiParamNum = phiParamNum = omegaParamNum = nParams() + 10;
      peak.setGoniometerMatrix(GonRot * peak.getGoniometerMatrix());
    }
    V3D sampOffsets(getParameter("SampleXOffset"),
                    getParameter("SampleYOffset"),
                    getParameter("SampleZOffset"));
    peak.setSamplePos(peak.getSamplePos() + sampOffsets);
    // NOTE:Use getQLabFrame except for below.
    // For parameters the getGoniometerMatrix should remove GonRot, for derivs
    // wrt GonRot*, wrt chi*,phi*,etc.

    // Deriv wrt chi phi and omega
    if (phiParamNum < nParams()) {
      Matrix<double> chiMatrix = RotationMatrixAboutRegAxis(chi, 'z');
      Matrix<double> phiMatrix = RotationMatrixAboutRegAxis(phi, 'y');
      Matrix<double> omegaMatrix = RotationMatrixAboutRegAxis(omega, 'y');

      Matrix<double> dchiMatrix = DerivRotationMatrixAboutRegAxis(chi, 'z');
      Matrix<double> dphiMatrix = DerivRotationMatrixAboutRegAxis(phi, 'y');
      Matrix<double> domegaMatrix = DerivRotationMatrixAboutRegAxis(omega, 'y');

      Matrix<double> InvG = omegaMatrix * chiMatrix * phiMatrix;
      InvG.Invert();
      // Calculate Derivatives wrt chi(phi,omega) in degrees
      Matrix<double> R = omegaMatrix * chiMatrix * dphiMatrix;
      Matrix<double> InvR = InvG * R * InvG * -1;
      V3D lab = peak.getQLabFrame();
      V3D Dhkl0 = UBinv * InvR * lab;

      R = omegaMatrix * dchiMatrix * phiMatrix;
      InvR = InvG * R * InvG * -1;
      V3D Dhkl1 = UBinv * InvR * peak.getQLabFrame();

      R = domegaMatrix * chiMatrix * phiMatrix;
      InvR = InvG * R * InvG * -1;
      V3D Dhkl2 =
          UBinv * InvR * peak.getQLabFrame(); // R.transpose should be R inverse

      out->set(i, chiParamNum, Dhkl1[0]);
      out->set(i + 1, chiParamNum, Dhkl1[1]);
      out->set(i + 2, chiParamNum, Dhkl1[2]);
      out->set(i, phiParamNum, Dhkl0[0]);
      out->set(i + 1, phiParamNum, Dhkl0[1]);
      out->set(i + 2, phiParamNum, Dhkl0[2]);
      out->set(i, omegaParamNum, Dhkl2[0]);
      out->set(i + 1, omegaParamNum, Dhkl2[1]);
      out->set(i + 2, omegaParamNum, Dhkl2[2]);

    } // if optimize for chi phi and omega on this peak

    //------------------------Goniometer Rotation Derivatives
    //-----------------------
    Matrix<double> InvGonRot(GonRot);
    InvGonRot.Invert();
    Matrix<double> InvGon = InvGonRot * peak.getGoniometerMatrix();
    InvGon.Invert();
    V3D DGonx = (UBinv * InvGon * InvGonRotzMat * InvGonRotyMat *
                 DerivRotationMatrixAboutRegAxis(
                     -GonRotx, 'x') * // - gives inverse of GonRot
                 peak.getQLabFrame()) *
                -1;

    V3D DGony = (UBinv * InvGon * InvGonRotzMat *
                 DerivRotationMatrixAboutRegAxis(-GonRoty, 'y') *
                 InvGonRotxMat * peak.getQLabFrame()) *
                -1;
    V3D DGonz =
        (UBinv * InvGon * DerivRotationMatrixAboutRegAxis(-GonRotz, 'z') *
         InvGonRotyMat * InvGonRotxMat * peak.getQLabFrame()) *
        -1;

    size_t paramnum = parameterIndex("GonRotx");
    out->set(i, paramnum, DGonx[0]);
    out->set(i + 1, paramnum, DGonx[1]);
    out->set(i + 2, paramnum, DGonx[2]);
    out->set(i, parameterIndex("GonRoty"), DGony[0]);
    out->set(i + 1, parameterIndex("GonRoty"), DGony[1]);
    out->set(i + 2, parameterIndex("GonRoty"), DGony[2]);
    out->set(i, parameterIndex("GonRotz"), DGonz[0]);
    out->set(i + 1, parameterIndex("GonRotz"), DGonz[1]);
    out->set(i + 2, parameterIndex("GonRotz"), DGonz[2]);
    //-------------------- Sample Orientation derivatives
    //----------------------------------
    // Qlab = -KV + k|V|*beamdir
    // D = pos-sampPos
    //|V|= vmag=(L0 + D )/tof
    // t1= tof - L0/|V|   {time from sample to pixel}
    // V = D/t1
    V3D D = peak.getDetPos() - samplePosition;
    double vmag = (L0 + D.norm()) / peak.getTOF();
    double t1 = peak.getTOF() - L0 / vmag;

    // Derivs wrt sample x, y, z
    // Ddsx =( - 1, 0, 0),  d|D|^2/dsx -> 2|D|d|D|/dsx =d(tranp(D)* D)/dsx =2
    // Ddsx* tranp(D)
    //|D| also called Dmag
    V3D Dmagdsxsysz(D);
    Dmagdsxsysz *= (-1 / D.norm());

    V3D vmagdsxsysz = Dmagdsxsysz / peak.getTOF();

    V3D t1dsxsysz = vmagdsxsysz * (L0 / vmag / vmag);
    Matrix<double> Gon = peak.getGoniometerMatrix();
    Gon.Invert();

    // x=0 is deriv wrt SampleXoffset, x=1 is deriv wrt SampleYoffset, etc.
    for (int x = 0; x < 3; x++) {
      V3D pp;
      pp[x] = 1;
      V3D dQlab1 = pp / -t1 - D * (t1dsxsysz[x] / t1 / t1);
      V3D dQlab2 = beamDir * vmagdsxsysz[x];
      V3D dQlab = dQlab2 - dQlab1;
      dQlab *= K;

      V3D dQSamp = Gon * dQlab;
      V3D dhkl = UBinv * dQSamp;

      out->set(i, paramNums[x], dhkl[0]);
      out->set(i + 1, paramNums[x], dhkl[1]);
      out->set(i + 2, paramNums[x], dhkl[2]);
    }
  }
}