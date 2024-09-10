void CEyeBotCircle::MoveAlongCircle() {
   if(m_eState != STATE_MOVE_ALONG_CIRCLE) {
      /* State initialization */
      m_eState = STATE_MOVE_ALONG_CIRCLE;
      m_unWaypoint = 0;
   }
   else {
      if(m_unWaypoint >= CIRCLE_WAYPOINTS) {
         /* State transition */
         GoToCenter();
      }
      else {
         /* State logic */
         m_cTargetPos.Set(
            CIRCLE_RADIUS * Cos(CIRCLE_SLICE * m_unWaypoint),
            CIRCLE_RADIUS * Sin(CIRCLE_SLICE * m_unWaypoint),
            0.0f);
         m_cTargetPos += m_cCircleCenter;
         m_pcPosAct->SetAbsolutePosition(m_cTargetPos);
         ++m_unWaypoint;
      }
   }
}