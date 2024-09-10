void
PinguAction::move_with_forces ()
{
  // Apply gravity
  pingu->set_velocity(pingu->get_velocity() + Vector3f(0.0f, 1.0f));

#if 0 // New Code
  Vector3f pos        = pingu->get_pos();
  Vector3f target_pos = pos + pingu->get_velocity();
  Vector3f dir        = target_pos - pingu->get_pos();
  Vector3f velocity   = pingu->get_velocity();

  float length = dir.length();
  dir.normalize();

  for(float i = 0; i < length; ++i)
  {
    pingu->set_pos(pos + (dir * i));

    // If there is something below the Pingu
    if (rel_getpixel(0, -1) != Groundtype::GP_NOTHING)
    {
      // FIXME: this shouldn't be really here, but its a
      // FIXME: quick&dirty way to kill falling pingus
      if (velocity.y > Actions::Faller::deadly_velocity+1)
      {
        // log_debug("Velocity: " << velocity);
        pingu->set_action(Actions::Splashed);
        return;
      }
      else
      {
        // Make it so that the Pingu won't go down any further.
        pingu->set_velocity(Vector3f(0, 0));
        return;
      }
    }
    else if (head_collision_on_walk(0, 1))
    {
      return;
    }
    else if (collision_on_walk(1, 0))
    {
      // Make the Pingu bounce off the wall
      velocity.x = -velocity.x / 3.0f;
      pingu->set_velocity(velocity);
      pingu->direction.change();
      return;
    }
  }
#else // Old Code

  // FIXME: What does this variable do?
  Vector3f resultant_force = pingu->get_velocity();

  // FIXME: and what is this all about?! Can't we just use floats?
  // Strictly speaking x_numerator should be initialised with
  // (resultant_force.y / 2) and y_numerator with (resultant_force.x / 2).
  // This would make the algorithm essentially match the Mid-Point Line
  // Algorithm.  However, zero should do and is more comprehendable.
  int x_numerator = 0;
  int y_numerator = 0;
  int denominator = 0;
  int x_inc = 0;
  int y_inc = 0;

  if (Math::abs(resultant_force.x) > Math::abs(resultant_force.y))
  {
    // Initialise so that we move in whole pixels in x direction and
    // 'fractions' of a pixel in y direction.
    denominator = static_cast<int>(Math::abs(resultant_force.x));
    x_inc = denominator;
    y_inc = static_cast<int>(Math::abs(resultant_force.y));
  }
  else
  {
    // Initialise so that we move in whole pixels in y direction and
    // 'fractions' of a pixel in x direction.
    denominator = static_cast<int>(Math::abs(resultant_force.y));
    x_inc = static_cast<int>(Math::abs(resultant_force.x));
    y_inc = denominator;
  }

  Vector3f force_counter = resultant_force;

  // Keep moving the Pingu until there is only a fraction left
  while (   force_counter.x <= -1
            || force_counter.x >=  1
            || force_counter.y <= -1
            || force_counter.y >=  1)
  {
    x_numerator += x_inc;

    // Is it now not a fraction?
    if (x_numerator >= denominator)
    {
      // Revert back to being a fraction
      x_numerator -= denominator;

      // If there is something to the left of the Pingu
      if (collision_on_walk(1, 0))
      {
        // Make the Pingu reflect off the wall
        force_counter.x = -(force_counter.x);
        resultant_force.x = -(resultant_force.x/3);

        pingu->set_velocity(resultant_force);

        pingu->direction.change();
      }
      else
      {
        // Move the Pingu left
        pingu->set_x(pingu->get_x() + static_cast<float>(pingu->direction));
        force_counter.x -= static_cast<float>(pingu->direction);
      }
    }

    y_numerator += y_inc;

    // Is it now not a fraction?
    if (y_numerator >= denominator)
    {
      // Revert back to being a fraction
      y_numerator -= denominator;

      // Move the Pingu depending on what the direction of the force is
      if (force_counter.y >= 1)
      {
        // If there is something below the Pingu
        if (rel_getpixel(0, -1) != Groundtype::GP_NOTHING)
        {
          // FIXME: this shouldn't be really here, but its a
          // FIXME: quick&dirty way to kill falling pingus
          if (resultant_force.y >= deadly_velocity)
          {
            pingu->set_action(ActionName::SPLASHED);
            return;
          }
          // Make it so that the Pingu won't go down any further.
          pingu->set_velocity(Vector3f(0, 0));
          return;
        }
        else
        {
          // Move the Pingu down
          pingu->set_y(pingu->get_y() + 1);
          force_counter.y--;
        }
      }
      else if (force_counter.y <= -1)
      {
        // If there is something in the way above the Pingu
        if (head_collision_on_walk(0, 1))
        {
          // Make it so that the Pingu won't go up any further.
          force_counter.y = 0;
          resultant_force.y = 0;

          pingu->set_velocity(resultant_force);
        }
        else
        {
          // Move the Pingu up
          pingu->set_y(pingu->get_y() - 1);
          force_counter.y++;
        }
      }
    }
  }
#endif
}