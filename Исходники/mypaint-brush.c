  // Called only from stroke_to(). Calculate everything needed to
  // draw the dab, then let the surface do the actual drawing.
  //
  // This is only gets called right after update_states_and_setting_values().
  // Returns TRUE if the surface was modified.
  gboolean prepare_and_draw_dab (MyPaintBrush *self, MyPaintSurface * surface)
  {
    float x, y, opaque;
    float radius;

    // ensure we don't get a positive result with two negative opaque values
    if (self->settings_value[MYPAINT_BRUSH_SETTING_OPAQUE] < 0) self->settings_value[MYPAINT_BRUSH_SETTING_OPAQUE] = 0;
    opaque = self->settings_value[MYPAINT_BRUSH_SETTING_OPAQUE] * self->settings_value[MYPAINT_BRUSH_SETTING_OPAQUE_MULTIPLY];
    opaque = CLAMP(opaque, 0.0, 1.0);
    //if (opaque == 0.0) return FALSE; <-- cannot do that, since we need to update smudge state.
    if (self->settings_value[MYPAINT_BRUSH_SETTING_OPAQUE_LINEARIZE]) {
      // OPTIMIZE: no need to recalculate this for each dab
      float alpha, beta, alpha_dab, beta_dab;
      float dabs_per_pixel;
      // dabs_per_pixel is just estimated roughly, I didn't think hard
      // about the case when the radius changes during the stroke
      dabs_per_pixel = (
                        mypaint_mapping_get_base_value(self->settings[MYPAINT_BRUSH_SETTING_DABS_PER_ACTUAL_RADIUS]) +
                        mypaint_mapping_get_base_value(self->settings[MYPAINT_BRUSH_SETTING_DABS_PER_BASIC_RADIUS])
                        ) * 2.0;

      // the correction is probably not wanted if the dabs don't overlap
      if (dabs_per_pixel < 1.0) dabs_per_pixel = 1.0;

      // interpret the user-setting smoothly
      dabs_per_pixel = 1.0 + mypaint_mapping_get_base_value(self->settings[MYPAINT_BRUSH_SETTING_OPAQUE_LINEARIZE])*(dabs_per_pixel-1.0);

      // see doc/brushdab_saturation.png
      //      beta = beta_dab^dabs_per_pixel
      // <==> beta_dab = beta^(1/dabs_per_pixel)
      alpha = opaque;
      beta = 1.0-alpha;
      beta_dab = powf(beta, 1.0/dabs_per_pixel);
      alpha_dab = 1.0-beta_dab;
      opaque = alpha_dab;
    }

    x = self->states[MYPAINT_BRUSH_STATE_ACTUAL_X];
    y = self->states[MYPAINT_BRUSH_STATE_ACTUAL_Y];

    float base_radius = expf(mypaint_mapping_get_base_value(self->settings[MYPAINT_BRUSH_SETTING_RADIUS_LOGARITHMIC]));

    if (self->settings_value[MYPAINT_BRUSH_SETTING_OFFSET_BY_SPEED]) {
      x += self->states[MYPAINT_BRUSH_STATE_NORM_DX_SLOW] * self->settings_value[MYPAINT_BRUSH_SETTING_OFFSET_BY_SPEED] * 0.1 * base_radius;
      y += self->states[MYPAINT_BRUSH_STATE_NORM_DY_SLOW] * self->settings_value[MYPAINT_BRUSH_SETTING_OFFSET_BY_SPEED] * 0.1 * base_radius;
    }

    if (self->settings_value[MYPAINT_BRUSH_SETTING_OFFSET_BY_RANDOM]) {
      float amp = self->settings_value[MYPAINT_BRUSH_SETTING_OFFSET_BY_RANDOM];
      if (amp < 0.0) amp = 0.0;
      x += rand_gauss (self->rng) * amp * base_radius;
      y += rand_gauss (self->rng) * amp * base_radius;
    }


    radius = self->states[MYPAINT_BRUSH_STATE_ACTUAL_RADIUS];
    if (self->settings_value[MYPAINT_BRUSH_SETTING_RADIUS_BY_RANDOM]) {
      float radius_log, alpha_correction;
      // go back to logarithmic radius to add the noise
      radius_log  = self->settings_value[MYPAINT_BRUSH_SETTING_RADIUS_LOGARITHMIC];
      radius_log += rand_gauss (self->rng) * self->settings_value[MYPAINT_BRUSH_SETTING_RADIUS_BY_RANDOM];
      radius = expf(radius_log);
      radius = CLAMP(radius, ACTUAL_RADIUS_MIN, ACTUAL_RADIUS_MAX);
      alpha_correction = self->states[MYPAINT_BRUSH_STATE_ACTUAL_RADIUS] / radius;
      alpha_correction = SQR(alpha_correction);
      if (alpha_correction <= 1.0) {
        opaque *= alpha_correction;
      }
    }

    // update smudge color
    if (self->settings_value[MYPAINT_BRUSH_SETTING_SMUDGE_LENGTH] < 1.0 &&
        // optimization, since normal brushes have smudge_length == 0.5 without actually smudging
        (self->settings_value[MYPAINT_BRUSH_SETTING_SMUDGE] != 0.0 || !mypaint_mapping_is_constant(self->settings[MYPAINT_BRUSH_SETTING_SMUDGE]))) {

      float fac = self->settings_value[MYPAINT_BRUSH_SETTING_SMUDGE_LENGTH];
      if (fac < 0.01) fac = 0.01;
      int px, py;
      px = ROUND(x);
      py = ROUND(y);

      // Calling get_color() is almost as expensive as rendering a
      // dab. Because of this we use the previous value if it is not
      // expected to hurt quality too much. We call it at most every
      // second dab.
      float r, g, b, a;
      self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_RECENTNESS] *= fac;
      if (self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_RECENTNESS] < 0.5*fac) {
        if (self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_RECENTNESS] == 0.0) {
          // first initialization of smudge color
          fac = 0.0;
        }
        self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_RECENTNESS] = 1.0;

        float smudge_radius = radius * expf(self->settings_value[MYPAINT_BRUSH_SETTING_SMUDGE_RADIUS_LOG]);
        smudge_radius = CLAMP(smudge_radius, ACTUAL_RADIUS_MIN, ACTUAL_RADIUS_MAX);
        mypaint_surface_get_color(surface, px, py, smudge_radius, &r, &g, &b, &a);

        self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_R] = r;
        self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_G] = g;
        self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_B] = b;
        self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_A] = a;
      } else {
        r = self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_R];
        g = self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_G];
        b = self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_B];
        a = self->states[MYPAINT_BRUSH_STATE_LAST_GETCOLOR_A];
      }

      // updated the smudge color (stored with premultiplied alpha)
      self->states[MYPAINT_BRUSH_STATE_SMUDGE_A ] = fac*self->states[MYPAINT_BRUSH_STATE_SMUDGE_A ] + (1-fac)*a;
      // fix rounding errors
      self->states[MYPAINT_BRUSH_STATE_SMUDGE_A ] = CLAMP(self->states[MYPAINT_BRUSH_STATE_SMUDGE_A], 0.0, 1.0);

      self->states[MYPAINT_BRUSH_STATE_SMUDGE_RA] = fac*self->states[MYPAINT_BRUSH_STATE_SMUDGE_RA] + (1-fac)*r*a;
      self->states[MYPAINT_BRUSH_STATE_SMUDGE_GA] = fac*self->states[MYPAINT_BRUSH_STATE_SMUDGE_GA] + (1-fac)*g*a;
      self->states[MYPAINT_BRUSH_STATE_SMUDGE_BA] = fac*self->states[MYPAINT_BRUSH_STATE_SMUDGE_BA] + (1-fac)*b*a;
    }

    // color part

    float color_h = mypaint_mapping_get_base_value(self->settings[MYPAINT_BRUSH_SETTING_COLOR_H]);
    float color_s = mypaint_mapping_get_base_value(self->settings[MYPAINT_BRUSH_SETTING_COLOR_S]);
    float color_v = mypaint_mapping_get_base_value(self->settings[MYPAINT_BRUSH_SETTING_COLOR_V]);
    float eraser_target_alpha = 1.0;
    if (self->settings_value[MYPAINT_BRUSH_SETTING_SMUDGE] > 0.0) {
      // mix (in RGB) the smudge color with the brush color
      hsv_to_rgb_float (&color_h, &color_s, &color_v);
      float fac = self->settings_value[MYPAINT_BRUSH_SETTING_SMUDGE];
      if (fac > 1.0) fac = 1.0;
      // If the smudge color somewhat transparent, then the resulting
      // dab will do erasing towards that transparency level.
      // see also ../doc/smudge_math.png
      eraser_target_alpha = (1-fac)*1.0 + fac*self->states[MYPAINT_BRUSH_STATE_SMUDGE_A];
      // fix rounding errors (they really seem to happen in the previous line)
      eraser_target_alpha = CLAMP(eraser_target_alpha, 0.0, 1.0);
      if (eraser_target_alpha > 0) {
        color_h = (fac*self->states[MYPAINT_BRUSH_STATE_SMUDGE_RA] + (1-fac)*color_h) / eraser_target_alpha;
        color_s = (fac*self->states[MYPAINT_BRUSH_STATE_SMUDGE_GA] + (1-fac)*color_s) / eraser_target_alpha;
        color_v = (fac*self->states[MYPAINT_BRUSH_STATE_SMUDGE_BA] + (1-fac)*color_v) / eraser_target_alpha;
      } else {
        // we are only erasing; the color does not matter
        color_h = 1.0;
        color_s = 0.0;
        color_v = 0.0;
      }
      rgb_to_hsv_float (&color_h, &color_s, &color_v);
    }

    // eraser
    if (self->settings_value[MYPAINT_BRUSH_SETTING_ERASER]) {
      eraser_target_alpha *= (1.0-self->settings_value[MYPAINT_BRUSH_SETTING_ERASER]);
    }

    // HSV color change
    color_h += self->settings_value[MYPAINT_BRUSH_SETTING_CHANGE_COLOR_H];
    color_s += self->settings_value[MYPAINT_BRUSH_SETTING_CHANGE_COLOR_HSV_S];
    color_v += self->settings_value[MYPAINT_BRUSH_SETTING_CHANGE_COLOR_V];

    // HSL color change
    if (self->settings_value[MYPAINT_BRUSH_SETTING_CHANGE_COLOR_L] || self->settings_value[MYPAINT_BRUSH_SETTING_CHANGE_COLOR_HSL_S]) {
      // (calculating way too much here, can be optimized if neccessary)
      // this function will CLAMP the inputs
      hsv_to_rgb_float (&color_h, &color_s, &color_v);
      rgb_to_hsl_float (&color_h, &color_s, &color_v);
      color_v += self->settings_value[MYPAINT_BRUSH_SETTING_CHANGE_COLOR_L];
      color_s += self->settings_value[MYPAINT_BRUSH_SETTING_CHANGE_COLOR_HSL_S];
      hsl_to_rgb_float (&color_h, &color_s, &color_v);
      rgb_to_hsv_float (&color_h, &color_s, &color_v);
    }

    float hardness = CLAMP(self->settings_value[MYPAINT_BRUSH_SETTING_HARDNESS], 0.0, 1.0);

    // anti-aliasing attempt (works surprisingly well for ink brushes)
    float current_fadeout_in_pixels = radius * (1.0 - hardness);
    float min_fadeout_in_pixels = self->settings_value[MYPAINT_BRUSH_SETTING_ANTI_ALIASING];
    if (current_fadeout_in_pixels < min_fadeout_in_pixels) {
      // need to soften the brush (decrease hardness), but keep optical radius
      // so we tune both radius and hardness, to get the desired fadeout_in_pixels
      float current_optical_radius = radius - (1.0-hardness)*radius/2.0;

      // Equation 1: (new fadeout must be equal to min_fadeout)
      //   min_fadeout_in_pixels = radius_new*(1.0 - hardness_new)
      // Equation 2: (optical radius must remain unchanged)
      //   current_optical_radius = radius_new - (1.0-hardness_new)*radius_new/2.0
      //
      // Solved Equation 1 for hardness_new, using Equation 2: (thanks to mathomatic)
      float hardness_new = ((current_optical_radius - (min_fadeout_in_pixels/2.0))/(current_optical_radius + (min_fadeout_in_pixels/2.0)));
      // Using Equation 1:
      float radius_new = (min_fadeout_in_pixels/(1.0 - hardness_new));

      hardness = hardness_new;
      radius = radius_new;
    }

    // snap to pixel
    float snapToPixel = self->settings_value[MYPAINT_BRUSH_SETTING_SNAP_TO_PIXEL];
    if (snapToPixel > 0.0)
    {
      // linear interpolation between non-snapped and snapped
      float snapped_x = floor(x) + 0.5;
      float snapped_y = floor(y) + 0.5;
      x = x + (snapped_x - x) * snapToPixel;
      y = y + (snapped_y - y) * snapToPixel;

      float snapped_radius = roundf(radius * 2.0) / 2.0;
      if (snapped_radius < 0.5)
        snapped_radius = 0.5;

      if (snapToPixel > 0.9999 )
      {
        snapped_radius -= 0.0001; // this fixes precision issues where
                                  // neighboor pixels could be wrongly painted
      }

      radius = radius + (snapped_radius - radius) * snapToPixel;
    }

    // the functions below will CLAMP most inputs
    hsv_to_rgb_float (&color_h, &color_s, &color_v);
    return mypaint_surface_draw_dab (surface, x, y, radius, color_h, color_s, color_v, opaque, hardness, eraser_target_alpha,
                              self->states[MYPAINT_BRUSH_STATE_ACTUAL_ELLIPTICAL_DAB_RATIO], self->states[MYPAINT_BRUSH_STATE_ACTUAL_ELLIPTICAL_DAB_ANGLE],
                              self->settings_value[MYPAINT_BRUSH_SETTING_LOCK_ALPHA],
                              self->settings_value[MYPAINT_BRUSH_SETTING_COLORIZE]);
  }