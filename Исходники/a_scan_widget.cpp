QPainterPath AscanWidget::paint_wave()
{
    QPainterPath path;

    float xRatio1 = 1.0;
    float xRatio2 = 1.0;
    float yRatio = y_axis_length() / 255.0;

    int drawPoints = 0;
    if ( m_beam.size() < x_axis_length()) {
        xRatio1 = x_axis_length() / 1.0 / m_beam.size();
        drawPoints = m_beam.size();
    } else {
        xRatio2 = m_beam.size() / 1.0 / x_axis_length();
        drawPoints = x_axis_length();
    }

    for (int i = 0; i < drawPoints; ++i) {
        path.lineTo( i*xRatio1,
                     ((quint8)(m_beam.at((int)(i*xRatio2)))) * yRatio + 0.5);
    }

    return path;
}