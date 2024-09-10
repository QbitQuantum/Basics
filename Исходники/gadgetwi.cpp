//
/// When the gadget window receives a WM_COMMAND message, it is likely from a gadget
/// or control within a TControlGadget. This reroutes it to the command target.
//
TResult
TGadgetWindow::EvCommand(uint id, HWND hWndCtl, uint notifyCode) 
{
  TRACEX(OwlCmd, 1, "TGadgetWindow::EvCommand - id(" << id << "), ctl(" <<\
                     hex << uint(hWndCtl) << "), code(" << notifyCode  << ")");

  // First allow any derived class that wants to handle the command
  // NOTE: This search only caters for menu-style WM_COMMANDs (not those
  //       sent by controls)
  //
  TEventInfo  eventInfo(0, id);
  if (Find(eventInfo)) {
    Dispatch(eventInfo, id);
    return 0;
  }


#if 0
  // Prior versions of TGadgetWindow relied on TWindow's EvCommand for
  // dispatching WM_COMMAND events. This required that one derives from
  // a decoration class (eg. TControlbar, TToolbox) to handle control
  // notifications. The current version uses a more generalized logic
  // involving the CommandTarget and a frame ancestor class. This allows
  // a client window to handle notifications of a control in a toolbar
  // without using a TControlbar-derived class.
  // However, if you need to previous behaviour, simply invoke TWindow's
  // EvCommand from this handler.

  return TWindow::EvCommand(id, hWndCtl, notifyCode);
#endif

  TWindow* target;
  TFrameWindow* frame;

  // Find the frame who is our latest ancestor and make it our command target
  //
  for (target = GetParentO(); target; target = target->GetParentO()) {
    frame = TYPESAFE_DOWNCAST(target, TFrameWindow);
    if (frame || !target->GetParentO())
      break;
  }

  // Make sure the frame doesn't think we are its command target, or a BAD
  // loop will happen
  //
  if (target && (!frame || frame->GetCommandTarget() != GetHandle())) {
    CHECK(target->IsWindow());
    return target->EvCommand(id, hWndCtl, notifyCode);
  }

  // If all command routing fails, go back to basic dispatching of TWindow
  //
  return TWindow::EvCommand(id, hWndCtl, notifyCode);
}