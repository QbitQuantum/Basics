void
WidgetDialog::CreatePreliminary(SingleWindow &parent, const TCHAR *caption)
{
  WndForm::Create(parent, parent.GetClientRect(), caption, GetDialogStyle());
}