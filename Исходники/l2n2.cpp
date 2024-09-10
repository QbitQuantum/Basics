void CL2N2::ComputeRegAndGradient(CModel& model, double& reg, TheMatrix& grad)
{
   reg = 0;
   TheMatrix &w = model.GetW();
   w.Norm2(reg);
   reg = 0.5*reg*reg;
   grad.Assign(w); 	
}