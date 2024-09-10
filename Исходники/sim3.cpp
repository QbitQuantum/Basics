Sim3 Sim3
::from_SE3(const SE3 & se3)
{
  return Sim3(ScSO3(1.,se3.so3()),se3.translation());
}