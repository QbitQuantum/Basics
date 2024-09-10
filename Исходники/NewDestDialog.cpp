void CNewDestDialog::RemoveInputFocus()
{
   CCoeControl* control = ControlOrNull( EWayFinderCtrlNewDestCityEdwin );
   if( control ) {
      control->SetFocus( EFalse );
   }
   control = ControlOrNull( EWayFinderCtrlNewDestHouseNumEdwin);
   if( control ) {
      control->SetFocus( EFalse );
   }
   control = ControlOrNull( EWayFinderCtrlNewDestStringEdwin );
   if( control ) {
      control->SetFocus( EFalse );
   }
   control = ControlOrNull( EWayFinderCtrlNewDestCountryEdwin );
   if( control ) {
      control->SetFocus( EFalse );
   }
   iHasFocus = EFalse;
}