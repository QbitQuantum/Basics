osaGLUTManipulator::osaGLUTManipulator(const std::vector<std::string>& geomfiles,
                      const vctFrm3& Rtw0,
                      const std::string& robotfn,
                      const vctDoubleVec& qinit,
                      const std::string& basefile,
                      bool rotateX90) :
  robManipulator(robotfn, 
                 vctFrame4x4<double>(Rtw0.Rotation(), Rtw0.Translation())),
  q(qinit),
  base(0)
{
    Initialize(geomfiles, basefile, rotateX90);
}