ProgressDialog::ProgressDialog(SingleWindow &parent,
                               const DialogLook &dialog_look,
                               const TCHAR *caption)
  :WndForm(parent, dialog_look, parent.GetClientRect(), caption),
   progress(GetClientAreaWindow())
{
}