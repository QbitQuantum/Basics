void L3node::right_force_accumulate(Vector3f& x, Vector3f& xdot, float alpha, const Vector3f& f) {

    Vector3f dxRight = x - *world_x;
    dxRight.normalize();
    *force = dxRight.dot(f) * f * (1.0-alpha);
    *force += rho * Vector3f(0,-g,0) * l0;
    float restLengthLeft = l0 * alpha;
    float restLengthRight = l0;
    
    Vector3f deltaXDotLeft = *(world_x_dot) - xdot;
    Vector3f deltaXDotRight = *(world_x_dot) - *(right->world_x_dot);
    Vector3f deltaXLeft = *world_x - x;
    Vector3f deltaXRight = *world_x - *(right->world_x);

   if(deltaXLeft.dot(deltaXLeft) < 0.2) { //ball overlaps L3node
      deltaXDotLeft = *(world_x_dot) - *(left->world_x_dot);
      deltaXLeft = *world_x - *(left->world_x);
      restLengthLeft = l0;
      *force = f + rho * Vector3f(0,-g,0)*l0;
   }

    float absDeltaXLeft = sqrt(deltaXLeft.dot(deltaXLeft));
    float absDeltaXRight = sqrt(deltaXRight.dot(deltaXRight));
    Vector3f constant = -(ks * (absDeltaXLeft - restLengthLeft) + kd * deltaXDotLeft.dot(deltaXLeft)/absDeltaXLeft)*deltaXLeft/absDeltaXLeft - (ks * (absDeltaXRight - restLengthRight) + kd * deltaXDotRight.dot(deltaXRight)/absDeltaXRight)*deltaXRight/absDeltaXRight;
   *force += constant;
    
        //   cout << "force" << *force << endl;

}