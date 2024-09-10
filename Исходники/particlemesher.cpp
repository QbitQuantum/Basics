void ParticleMesherObject::UpdateUI()
{
   Point3 min,max;
   pblock2->GetValue(particlemesher_customboundsa,0,min,FOREVER);
   pblock2->GetValue(particlemesher_customboundsb,0,max,FOREVER);


   Box3 box;
   box.Init();
   box += min;
   box += max;

   
   TSTR text;
   BOOL useBounds;
   pblock2->GetValue(particlemesher_usecustombounds, 0, useBounds, FOREVER);

   if (useBounds)
      {
      if (box.IsEmpty())
         text.printf(_T("%s"),GetString(IDS_EMPTY));
      else 
         {
         text.printf(_T("(%0.0f,%0.0f,%0.0f)"),min.x,min.y,min.z);
         SetWindowText(GetDlgItem(hParams,IDC_BOUNDSTEXT),
            text);
         text.printf(_T("(%0.0f,%0.0f,%0.0f)"),max.x,max.y,max.z);
         SetWindowText(GetDlgItem(hParams,IDC_BOUNDSTEXT2),
            text);
         }

//make sure we only enable the button in the modify panel
// bug 257747 1/30/01 watje
      if (ip)
         {
         ICustButton *iBut = GetICustButton(GetDlgItem(hParams,IDC_PICKBB));
         if (ip->GetCommandPanelTaskMode()==TASK_MODE_MODIFY)
            {
            if (iBut) iBut->Enable(TRUE);
            }
         ReleaseICustButton(iBut);
         }

      }
   else
      {
      text.printf(_T(" "));
      SetWindowText(GetDlgItem(hParams,IDC_BOUNDSTEXT),
         text);
      text.printf(_T(" "));
      SetWindowText(GetDlgItem(hParams,IDC_BOUNDSTEXT2),
         text);
      ICustButton *iBut = GetICustButton(GetDlgItem(hParams,IDC_PICKBB));
      if (iBut) iBut->Enable(FALSE);
      ReleaseICustButton(iBut);

      }
   
}