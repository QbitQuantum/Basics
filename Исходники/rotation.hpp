  void Rotation<T>::normalize()
  {
    using std::fmod;

    if (radians_ > pi)
    {
      radians_ = fmod(radians_ + pi, double_pi) - pi;
    }

    else if (radians_ < -pi)
    {
      radians_ = fmod(radians_ - pi, double_pi) + pi;
    }
  }