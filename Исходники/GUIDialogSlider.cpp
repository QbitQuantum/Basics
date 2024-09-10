void CGUIDialogSlider::Display(int label, float value, float min, float delta, float max, ISliderCallback *callback)
{
  // grab the slider dialog
  CGUIDialogSlider *slider = CServiceBroker::GetGUI()->GetWindowManager().GetWindow<CGUIDialogSlider>(WINDOW_DIALOG_SLIDER);
  if (!slider)
    return;

  // set the label and value
  slider->Initialize();
  slider->SetAutoClose(1000);
  slider->SetSlider(g_localizeStrings.Get(label), value, min, delta, max, callback, NULL);
  slider->SetModalityType(DialogModalityType::MODELESS);
  slider->Open();
}