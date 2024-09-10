void CBuzzControllerSpiri::SetDirection(const CVector3& c_heading) {
   CVector3 cDir = c_heading;
   if(cDir.SquareLength() > 0.01f) {
      cDir.Normalize();
      cDir *= 0.01;
   }
   m_pcPropellers->SetRelativePosition(cDir);
}