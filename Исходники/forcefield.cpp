  // LineSearch 
  //
  // atom: coordinates of atom at iteration k (x_k)
  // direction: search direction ( d = -grad(x_0) )
  //
  // ALGORITHM:
  // 
  // step = 1
  // for (i = 1 to 100) {                max steps = 100
  //   e_k = energy(x_k)                 energy of current iteration
  //   x_k = x_k + step * d              update coordinates
  //   e_k+1 = energy(x_k+1)             energy of next iteration
  //   
  //   if (e_k+1 < e_k)
  //     step = step * 1.2               increase step size
  //   if (e_k+1 > e_k) {
  //     x_k = x_k - step * d            reset coordinates to previous iteration
  //     step = step * 0.5               reduce step size
  //   }
  //   if (e_k+1 == e_k)
  //     end                             convergence criteria reached, stop
  // }
  vector3 OBForceField::LineSearch(OBAtom *atom, vector3 &direction)
  {
    double e_n1, e_n2, step;
    vector3 old_xyz, orig_xyz, xyz_k, dir(0.0, 0.0, 0.0);

    step = 0.2;
    direction.normalize();
    orig_xyz = atom->GetVector();
    
    e_n1 = Energy(false); // calculate e_k
    
    unsigned int i;
    for (i=0; i<100; i++) {
      old_xyz = atom->GetVector();
      
      xyz_k = atom->GetVector() + direction*step;
      atom->SetVector(xyz_k);  // update coordinates
    
      e_n2 = Energy(false); // calculate e_k+1
      
      // convergence criteria, this is 10 times the default convergence
      // of SteepestDescent or ConjugateGradients. A higher precision here 
      // only takes longer with the same result.
      if (IsNear(e_n2, e_n1, 1.0e-7))
        break;

      if (e_n2 > e_n1) { // decrease stepsize
        step *= 0.5;
        atom->SetVector(old_xyz);
      }
      if (e_n2 < e_n1) {  // increase stepsize
        e_n1 = e_n2;
        step *= 1.2;
        if (step > 1.0)
          step = 1.0;
      }
      
    }
    //cout << "LineSearch steps: " << i << endl;

    dir = atom->GetVector() - orig_xyz;
    atom->SetVector(orig_xyz);     

    // cutoff accuracy
    if (dir.length() < 1.0e-8)
      return VZero;

    return dir;
  }