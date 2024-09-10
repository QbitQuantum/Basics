 void Heart::update(Engine& ctx)
 {
    if(m_heartThr(ctx.clock().ticks())) // Regulate animation speed
    {
       // Change direction when the y-coordinate reaches
       // upper or lower limit
       if(m_direction == -1 && y() <= m_baseY - height()/2 || 
          m_direction == 1 && y() >= m_baseY + height()/2)
       {
          m_direction *= -1;
       }
       setY(y() + m_direction);
    }
 }