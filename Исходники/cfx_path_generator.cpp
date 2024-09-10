void CFX_PathGenerator::AddArc(FX_FLOAT x,
                               FX_FLOAT y,
                               FX_FLOAT width,
                               FX_FLOAT height,
                               FX_FLOAT start_angle,
                               FX_FLOAT sweep_angle) {
  if (sweep_angle == 0) {
    return;
  }

  const FX_FLOAT bezier_arc_angle_epsilon = 0.01f;
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
                        x + (width * FXSYS_cos(start_angle)),
                        y + (height * FXSYS_sin(start_angle)), FXPT_MOVETO);
  FX_FLOAT total_sweep = 0, local_sweep = 0, prev_sweep = 0;
  bool done = false;
  do {
    if (sweep_angle < 0) {
      prev_sweep = total_sweep;
      local_sweep = -FX_PI / 2;
      total_sweep -= FX_PI / 2;
      if (total_sweep <= sweep_angle + bezier_arc_angle_epsilon) {
        local_sweep = sweep_angle - prev_sweep;
        done = true;
      }
    } else {
      prev_sweep = total_sweep;
      local_sweep = FX_PI / 2;
      total_sweep += FX_PI / 2;
      if (total_sweep >= sweep_angle - bezier_arc_angle_epsilon) {
        local_sweep = sweep_angle - prev_sweep;
        done = true;
      }
    }
    ArcTo(x, y, width, height, start_angle, local_sweep);
    start_angle += local_sweep;
  } while (!done);
}