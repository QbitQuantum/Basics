bool ObjectiveFunction::evaluate_with_Hessian_diagonal( EvalType type, 
                                        PatchData& pd,
                                        double& value_out,
                                        std::vector<Vector3D>& grad_out,
                                        std::vector<SymMatrix3D>& hess_diag_out,
                                        MsqError& err )
{
  MsqHessian hess;
  hess.initialize( pd, err ); MSQ_ERRZERO(err);
  bool val = evaluate_with_Hessian( type, pd, value_out, grad_out, hess, err );
  MSQ_ERRZERO(err);
  hess_diag_out.resize( hess.size() );
  for (size_t i = 0; i < hess.size(); ++i)
    hess_diag_out[i] = hess.get_block(i,i)->upper();
  return val;
}