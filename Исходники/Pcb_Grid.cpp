void PCB_Grid::LoadGridSettings(CString fileName, BOOL warnFileOpen)
{
   char     line[255];
   char     *lp;
   FILE     *fp;

   if ((fp = fopen(fileName,"rt")) == NULL)
   {
      if (warnFileOpen)
         ErrorMessage(fileName, "Unable to Open File!", MB_ICONEXCLAMATION | MB_OK);
      return;
   }

   double scale = 1;
   int decimal = GetDecimals(doc->getSettings().getPageUnits());

   while (fgets(line,255,fp))
   {
      if ((lp = get_string(line," \t\n")) == NULL) continue;
      if (lp[0] != '.')                            continue;

      if (!STRCMPI(lp,".Units"))
      {
         if ((lp = get_string(NULL," \t\n")) == NULL) continue;

         int units = GetUnitIndex(lp);

         if (units > -1)
         {
            m_pageUnits = units;
            scale = Units_Factor(units, doc->getSettings().getPageUnits());
         }
         else
         {
            // unit error
         }
      }
      else if (!STRCMPI(lp,".Horizontal"))
      {
         if ((lp = get_string(NULL," \t\n")) == NULL) continue;

         m_horz = atoi(lp);

         if ((lp = get_string(NULL," \t\n")) == NULL) continue;

         m_hSteps = atoi(lp);

         if ((lp = get_string(NULL," \t\n")) == NULL) continue;

         setHSizePageUnits(atof(lp));
      }
      else if (!STRCMPI(lp,".Vertical"))
      {
         if ((lp = get_string(NULL," \t\n")) == NULL) continue;

         m_vert = atoi(lp);

         if ((lp = get_string(NULL," \t\n")) == NULL) continue;

         m_vSteps = atoi(lp);

         if ((lp = get_string(NULL," \t\n")) == NULL) continue;

         setVSizePageUnits(atof(lp));
      }
      else if (!STRCMPI(lp,".Thickness"))
      {
         if ((lp = get_string(NULL," \t\n")) == NULL) continue;

         m_gridThickness = atof(lp);
      }
   }

   fclose(fp);

   UpdateData(FALSE);
}