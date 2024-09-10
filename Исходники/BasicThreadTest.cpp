 void Run(void) override {
   WaitForStateUpdate([this] { return m_continue; });
   while(m_spinCount--);
   GetThreadTimes(m_kernelTime, m_userTime);
 }