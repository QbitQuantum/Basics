  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@unrotate_by(Rotation rot) Vector3
  // # Author(s): Markus Breyer
  static void mthd_unrotate_by(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      const FVector & vec = *scope_p->this_as<FVector>();
      const FQuat rot = *scope_p->get_arg<FQuat>(SSArg_1);

      *result_pp = as_instance(rot.Inverse().RotateVector(vec));
      }
    }