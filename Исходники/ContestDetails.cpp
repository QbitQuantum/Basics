void __fastcall TContestEntryDetails::VHFCalendarButtonClick( TObject * /*Sender*/ )
{
   std::auto_ptr <TCalendarForm> CalendarDlg(new TCalendarForm(this));

   CalendarDlg->Caption = "VHF Calendar";
   CalendarDlg->description = ContestNameSelected->Text;

   if ( CalendarDlg->ShowModal() == mrOk )
   {
      // set up all the details that we can from the calendar
      ContestNameSelected->Text = CalendarDlg->ic.description.c_str();
      setDetails( CalendarDlg->ic );
   }
   TWinControl *next = getNextFocus();
   if (next)
   {
      next->SetFocus();
   }
   else
   {
      OKButton->SetFocus();
   }
}