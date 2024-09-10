//! new range-controller.
//! this controller accepts ranges of accepted positions and
//! lowers the weight to zero when inside that range. 
void ChainTask::doControl_ranges()
{
  /// HACK FOR THE RPY ANGLES, PART 1
  double middle[3], margin[3];
  for(int i=0; i < 3; i++)
  {
    double lo = ros_constraint_command.pos_lo[i+3];
    double hi = ros_constraint_command.pos_hi[i+3];
    middle[i] = (hi + lo)/2.0;
    margin[i] = (hi - lo)/2.0;
  }

  Rotation desired = Rotation::RPY(middle[0], middle[1], middle[2]);
  Rotation measured = Rotation::RPY(chi_f_spatula(0), chi_f_spatula(1), chi_f_spatula(2));
  Vector rot = diff(desired, measured);
  rot = measured.Inverse()*rot;
  /// ///

  double s = 0.05;
  for(int i=0; i < 6; i++)
  {
    if(ros_constraint_command.weight[i] == 0.0)
    {
      ydot(i) = 0.0;
      continue;
    }

    double value = chi_f(i);

    double lo = ros_constraint_command.pos_lo[i];
    double hi = ros_constraint_command.pos_hi[i];

    if(i >= 3 && !new_rotation) /// HACK FOR THE RPY ANGLES, PART 2
    {
      lo = value + rot(i-3) - margin[i-3];
      hi = value + rot(i-3) + margin[i-3];
    } /// ///

    // adjust margin if range is too small
    double ss = (hi - lo < 2*s) ? (hi - lo) / 2 : s;

    if(value > hi - ss)
    {
      ydot(i) = feedback_gain[i]*(hi - ss - value);
      desired_values[i] = hi - ss;
    }
    else if(value < lo + ss)
    {
      ydot(i) = feedback_gain[i]*(lo + ss - value);
      desired_values[i] = lo + ss;
    }
    else
    {
      ydot(i) = 0.0;
      desired_values[i] = value;
    }


    if(value > hi || value < lo)
    {
      weights[i] = 1.0;
    }
    else
    {
      double w_lo = (1/s)*(-hi + value)+1;
      double w_hi = (1/s)*( lo - value)+1;

      w_lo = (w_lo > 0.0) ? w_lo : 0.0;
      w_hi = (w_hi > 0.0) ? w_hi : 0.0;

      weights[i] = (w_lo > w_hi) ? w_lo : w_hi;
    }
  }
}