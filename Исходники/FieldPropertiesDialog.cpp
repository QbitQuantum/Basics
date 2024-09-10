void FieldPropertiesDialog::OnRadioGeneratorClick(wxCommandEvent&
    WXUNUSED(event))
{
    textctrl_generator_name->SetEditable(radio_generator_new->GetValue());
    updateColors();
    choice_generator->Enable(radio_generator_existing->GetValue());
    updateSqlStatement();
}