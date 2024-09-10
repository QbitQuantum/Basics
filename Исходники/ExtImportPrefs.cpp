void ExtImportPrefs::PopulateOrExchange(ShuttleGui & S)
{
   S.SetBorder(2);

   S.TieCheckBox(_("Attempt to use filter in OpenFile dialog first"),
         wxT("/ExtendedImport/OverrideExtendedImportByOpenFileDialogChoice"),
         true);
   S.StartStatic(_("Rules to choose import filters"), 1);
   {
      S.SetSizerProportion(1);
      S.StartHorizontalLay (wxEXPAND, 1);
      {
         bool fillRuleTable = false;
         if (RuleTable == NULL)
         {
            RuleTable = new Grid(S.GetParent(),EIPRuleTable);
           
            RuleTable->SetColLabelSize(RuleTable->GetDefaultRowSize());
#if EXTIMPORT_MIME_SUPPORT
            RuleTable->CreateGrid (0, 2, wxGrid::wxGridSelectRows);
#else
            RuleTable->CreateGrid (0, 1, wxGrid::wxGridSelectRows);
#endif
            RuleTable->DisableDragColMove ();
            RuleTable->DisableDragRowSize ();
            RuleTable->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_CENTER);
            RuleTable->SetColLabelValue (0, _("File extensions"));
#if EXTIMPORT_MIME_SUPPORT
            RuleTable->SetColLabelValue (1, _("Mime-types"));
#endif
            RuleTable->SetRowLabelSize (0);
            RuleTable->SetSelectionMode (wxGrid::wxGridSelectRows);
            RuleTable->AutoSizeColumns ();

            RuleTable->SetDropTarget (dragtarget1);
            RuleTable->EnableDragCell (true);
            fillRuleTable = true;
         }
         S.AddWindow(RuleTable, wxEXPAND | wxALL);
       
         PluginList = S.Id(EIPPluginList).AddListControl ();
           
         if (fillRuleTable)
         {
            PluginList->SetSingleStyle (wxLC_REPORT, true);
            PluginList->SetSingleStyle (wxLC_SINGLE_SEL, true);
            PluginList->InsertColumn (0, _("Importer order"));
            PluginList->SetDropTarget (dragtarget2);

            ExtImportItems *items = wxGetApp().mImporter->GetImportItems();         
            for (unsigned int i = 0; i < items->Count(); i++)
               AddItemToTable (i, &(*items)[i]);
            if (items->Count() > 0)
            {
               RuleTable->SelectRow(0);
               RuleTable->SetGridCursor(0,0);
            }
         }         
      }
      S.EndHorizontalLay();
      S.StartHorizontalLay (wxSHRINK, 0);
      {
          MoveRuleUp = S.Id (EIPMoveRuleUp).AddButton (_("Move rule &up"));
          MoveRuleDown = S.Id (EIPMoveRuleDown).AddButton
                (_("Move rule &down"));
          MoveFilterUp = S.Id (EIPMoveFilterUp).AddButton
                (_("Move f&ilter up"));
          MoveFilterDown = S.Id (EIPMoveFilterDown).AddButton
                (_("Move &filter down"));
      }
      S.EndHorizontalLay();
      S.StartHorizontalLay (wxSHRINK, 0);
      {
          AddRule = S.Id (EIPAddRule).AddButton (_("&Add new rule"));
          DelRule = S.Id (EIPDelRule).AddButton (_("De&lete selected rule"));
      }
      S.EndHorizontalLay();
   }
   S.EndStatic();
   Layout();
   Fit();
   SetMinSize(GetSize());
}