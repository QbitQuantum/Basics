  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@unrotate_by(Rotation rot) Vector3
  // # Author(s): Markus Breyer
  static void mthd_unrotate_by(SkInvokedMethod * scope_p, SkInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      const FVector & vec = scope_p->this_as<SkVector3>();
      const FQuat rot = scope_p->get_arg<SkRotation>(SkArg_1);

      *result_pp = SkVector3::new_instance(rot.Inverse().RotateVector(vec));
      }
    }