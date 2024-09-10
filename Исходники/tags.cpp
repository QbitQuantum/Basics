void TagsEditor::PopulateOrExchange(ShuttleGui & S)
{
   S.StartVerticalLay();
   {
      S.StartHorizontalLay(wxALIGN_LEFT, false);
      {
         S.AddUnits(_("Use arrow keys (or RETURN key after editing) to navigate fields."));
      }
      S.EndHorizontalLay();

      if (mGrid == NULL) {
         mGrid = new Grid(S.GetParent(),
                          wxID_ANY,
                          wxDefaultPosition,
                          wxDefaultSize,
                          wxSUNKEN_BORDER);

         mStringRenderer = new wxGridCellStringRenderer;
         mComboEditor = new ComboEditor(wxArrayString(), true);

         mGrid->RegisterDataType(wxT("Combo"), mStringRenderer, mComboEditor);

         mGrid->SetColLabelSize(mGrid->GetDefaultRowSize());

         wxArrayString cs(WXSIZEOF(names), names);

         // Build the initial (empty) grid
         mGrid->CreateGrid(0, 2); 
         mGrid->SetRowLabelSize(0);
         mGrid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_CENTER);
         mGrid->SetColLabelValue(0, _("Tag"));
         mGrid->SetColLabelValue(1, _("Value"));

         // Resize the name column and set default row height.
         wxComboBox tc(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, cs);
         mGrid->SetColSize(0, tc.GetSize().x);
         mGrid->SetColMinimalWidth(0, tc.GetSize().x);
      }
      S.Prop(true);
      S.AddWindow(mGrid, wxEXPAND | wxALL);

      S.StartMultiColumn(4, wxALIGN_CENTER);
      {
         S.Id(AddID).AddButton(_("&Add"));
         S.Id(RemoveID).AddButton(_("&Remove"));
         S.AddTitle(wxT(" "));
         S.Id(ClearID).AddButton(_("Cl&ear"));
      }
      S.EndMultiColumn();

      S.StartHorizontalLay(wxALIGN_CENTRE, false);
      {
         S.StartStatic(_("Genres"));
         {
            S.StartMultiColumn(4, wxALIGN_CENTER);
            {
               S.Id(EditID).AddButton(_("E&dit..."));
               S.Id(ResetID).AddButton(_("Rese&t..."));
            }
            S.EndMultiColumn();
         }
         S.EndStatic();
         S.StartStatic(_("Template"));
         {
            S.StartMultiColumn(4, wxALIGN_CENTER);
            {
               S.Id(LoadID).AddButton(_("&Load..."));
               S.Id(SaveID).AddButton(_("&Save..."));
               S.AddTitle(wxT(" "));
               S.Id(SaveDefaultsID).AddButton(_("Set De&fault"));
            }
            S.EndMultiColumn();
         }
         S.EndStatic();
      }
      S.EndHorizontalLay();
   }
   S.EndVerticalLay();

   S.AddStandardButtons(eOkButton | eCancelButton);
}