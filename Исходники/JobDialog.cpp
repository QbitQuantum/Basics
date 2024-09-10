bool
JobDialog(SingleWindow &parent, const DialogLook &dialog_look,
          const TCHAR *caption,
          Job &job, bool cancellable)
{
  WindowStyle form_style;
  form_style.Hide();
  WndForm form(parent, dialog_look,
               parent.GetClientRect(),
               caption);

  ContainerWindow &client_area = form.GetClientAreaWindow();

  ProgressWindowOperation progress(client_area);
  DialogJobThread thread(progress, job, form);
  thread.Start();

  JobCancelButton cancel_button(thread);
  if (cancellable) {
    ButtonWindowStyle style;
    style.TabStop();

    PixelRect rc = client_area.GetClientRect();
    rc.right -= Layout::Scale(2);
    rc.left = rc.right - Layout::Scale(78);
    rc.top += Layout::Scale(2);
    rc.bottom = rc.top + Layout::Scale(35);
    cancel_button.set(client_area, _("Cancel"), rc,
                      style);
    cancel_button.SetFont(*dialog_look.button.font);
    cancel_button.BringToTop();
  }

  int result = form.ShowModal();

  thread.Cancel();
  thread.Join();

  return result == mrOK;
}