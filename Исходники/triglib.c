double hyperbolic_arc_sine(double x, enum angle_type out_type)
{
      switch (out_type)
      {
      case RAD:
            return asinh(x);
            break;

      case DEG:
            return radians_to_degrees(asinh(x));
            break;

      case GRAD:
            return radians_to_grade(asinh(x));
      }
}