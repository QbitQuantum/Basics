// copy-pasted from above
void HitRectSur::Polygon(const std::vector<RenderVertex> &rgv)
{
   if (m_fFailedAlready)
   {
      return;
   }

   for (unsigned i = 0; i < rgv.size(); ++i)
   {
      if (!PTINRECT(rgv[i].x, rgv[i].y))
      {
         FailObject();
         return;
      }
   }
}