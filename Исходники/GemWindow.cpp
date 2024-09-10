void GemWindow::destroyGemWindow(void){
  // tell all objects that this context is vanishing
  sendContextDestroyedMsg(gensym("__gemBase")->s_thing);
  // do the rest
  m_pimpl->mycontext=destroyContext(m_pimpl->mycontext);
  m_pimpl->undispatch();
  m_context=m_pimpl->mycontext;
}