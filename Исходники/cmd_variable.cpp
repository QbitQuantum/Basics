bool CmdVariable::onServer(DebuggerProxy *proxy) {
  FrameInjection *frame = ThreadInfo::s_threadInfo->m_top;
  for (int i = 0; i < m_frame && frame; i++) {
    frame = frame->getPrev();
  }
  m_global = (!frame || !frame->getPrev());

  if (frame) {
    EvalFrameInjection *eframe = dynamic_cast<EvalFrameInjection*>(frame);
    if (eframe) {
      m_variables = eframe->getEnv().getDefinedVariables();
      m_variables.remove("GLOBALS");
    }
  }
  return proxy->send(this);
}