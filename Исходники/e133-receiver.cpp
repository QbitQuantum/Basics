/**
 * Called when a de-registration request completes.
 */
void SimpleE133Node::DeRegisterCallback(bool ok) {
  OLA_INFO << "in deregister callback, state is " << ok;
  m_ss.Terminate();
}