void CFX_PathGenerator::AddArc(FX_FLOAT x,
                               FX_FLOAT y,
                               FX_FLOAT width,
                               FX_FLOAT height,
                               FX_FLOAT start_angle,
                               FX_FLOAT sweep_angle) {
#if 0
    FX_FIXFLOAT32 sweep = sweep_angle;
    while (sweep > FIXFLOAT32_PI * 2) {
        sweep -= FIXFLOAT32_PI * 2;
    }
    if (sweep == 0) {
        return;
    }
    m_pPathData->AddPointCount(1);
    m_pPathData->SetPoint(m_pPathData->GetPointCount() - 1,
                          x + fixmul_8_32_to_8(width, fixcos(start_angle)),
                          y + fixmul_8_32_to_8(height, fixsin(start_angle)), FXPT_MOVETO);
    FX_FIXFLOAT32 angle1 = 0, angle2;
    FX_BOOL bDone = FALSE;
    do {
        angle2 = angle1 + FIXFLOAT32_PI / 2;
        if (angle2 >= sweep) {
            angle2 = sweep;
            bDone = TRUE;
        }
        ArcTo(x, y, width, height, start_angle + angle1, angle2 - angle1);
        angle1 = angle2;
    } while (!bDone);
#else
  if (sweep_angle == 0) {
    return;
  }
  static const FX_FLOAT bezier_arc_angle_epsilon = (FX_FLOAT)(0.01f);
  while (start_angle > FX_PI * 2) {
    start_angle -= FX_PI * 2;
  }
  while (start_angle < 0) {
    start_angle += FX_PI * 2;
  }
  if (sweep_angle >= FX_PI * 2) {
    sweep_angle = FX_PI * 2;
  }
  if (sweep_angle <= -FX_PI * 2) {
    sweep_angle = -FX_PI * 2;
  }
  m_pPathData->AddPointCount(1);
  m_pPathData->SetPoint(m_pPathData->GetPointCount() - 1,
                        x + FXSYS_Mul(width, FXSYS_cos(start_angle)),
                        y + FXSYS_Mul(height, FXSYS_sin(start_angle)),
                        FXPT_MOVETO);
  FX_FLOAT total_sweep = 0, local_sweep = 0, prev_sweep = 0;
  FX_BOOL done = FALSE;
  do {
    if (sweep_angle < 0) {
      prev_sweep = total_sweep;
      local_sweep = -FX_PI / 2;
      total_sweep -= FX_PI / 2;
      if (total_sweep <= sweep_angle + bezier_arc_angle_epsilon) {
        local_sweep = sweep_angle - prev_sweep;
        done = TRUE;
      }
    } else {
      prev_sweep = total_sweep;
      local_sweep = FX_PI / 2;
      total_sweep += FX_PI / 2;
      if (total_sweep >= sweep_angle - bezier_arc_angle_epsilon) {
        local_sweep = sweep_angle - prev_sweep;
        done = TRUE;
      }
    }
    ArcTo(x, y, width, height, start_angle, local_sweep);
    start_angle += local_sweep;
  } while (!done);
#endif
}