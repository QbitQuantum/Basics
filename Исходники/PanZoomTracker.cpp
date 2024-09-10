void
PanZoomTracker::
handle_motion(const fastuidraw::vec2 &pos, const fastuidraw::vec2 &delta)
{
  if(!m_button_down)
    {
      return;
    }

  if(m_zoom_time.elapsed() > m_zoom_gesture_begin_time)
    {
      m_is_zooming = true;
    }

  float zdivide(m_scale_zooming * m_zoom_divider);

  if(!m_is_zooming)
    {
      float zdx(pos.x() - m_zoom_pivot.x());
      float zdy(pos.y() - m_zoom_pivot.y());

      m_transformation.translation( m_transformation.translation() + delta);

      if(fastuidraw::t_abs(zdx) > zdivide or fastuidraw::t_abs(zdy) > zdivide)
        {
          m_zoom_time.restart();
          m_zoom_pivot = pos;
          m_start_gesture = m_transformation;
        }
    }
  else
    {
      float zoom_factor(pos.y() - m_zoom_pivot.y());
      ScaleTranslate<float> R;

      zoom_factor /= zdivide;
      if(zoom_factor < 0.0f)
        {
          zoom_factor = -1.0f/fastuidraw::t_min(-1.0f, zoom_factor);
        }
      else
        {
          zoom_factor = fastuidraw::t_max(1.0f, zoom_factor);
        }
      R.scale(zoom_factor);
      R.translation( (1.0f - zoom_factor) * m_zoom_pivot);
      m_transformation = R * m_start_gesture;
    }
}