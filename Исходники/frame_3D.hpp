 /**
  * Inversion operator, i.e. "this->addBefore( ~this ) == Parent".
  * \note Forces are negated and rotated.
  */
 self operator ~() {
   rot_mat_3D<value_type> R(this->Quat.getRotMat());
   self result;
   result.Quat = invert(this->Quat);
   result.AngVelocity = R * (-AngVelocity);
   result.AngAcceleration = R * (-AngAcceleration);
   result.Position = (-this->Position) * R;
   result.Velocity = -((result.AngVelocity % this->Position) + Velocity) * R;
   result.Acceleration = -((result.AngVelocity % (result.AngVelocity % this->Position)) + (value_type(2.0) * result.AngVelocity % Velocity) + (result.AngAcceleration % this->Position) + Acceleration) * R;
   result.Force = -Force * R;
   result.Torque = R * (-Torque); //action-reaction
   return result;
 };