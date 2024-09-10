void CL1N1::ComputeReg(CModel& model, double& reg)
{
   reg = 0;
   TheMatrix &w = model.GetW();
   w.Norm1(reg);
}