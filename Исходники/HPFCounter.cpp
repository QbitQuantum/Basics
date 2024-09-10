// Stop the timer
void
HPFCounter::Stop()
{
  if(m_start.QuadPart)
  {
    QueryPerformanceCounter(&m_end);
    m_total += ((double)(m_end.QuadPart - m_start.QuadPart)) / (double)m_frequency.QuadPart;

    m_start.QuadPart = 0L;
    m_end  .QuadPart = 0L;
  }

  // Get the thread times, ignoring creation and end
  FILETIME creation   = { 0, 0};
  FILETIME exitTime   = { 0, 0};
  FILETIME kernelTime = { 0, 0};
  FILETIME userTime   = { 0, 0};
  GetThreadTimes(GetCurrentThread(),&creation,&exitTime,&kernelTime,&userTime);

//   TRACE ("Thread times\n");
//   TRACE ("- User   hi : %x\n",userTime.dwHighDateTime);
//   TRACE ("- User   lo : %x\n",userTime.dwLowDateTime);
//   TRACE ("- Kernel hi : %x\n",kernelTime.dwHighDateTime);
//   TRACE ("- Kernel lo : %x\n\n",kernelTime.dwLowDateTime);

  // Calculate how much kernel time we just used since last time
  FILETIME slice = SubFiletimes(&kernelTime,&m_kernelTime);
  m_kernelTimeSlice = AddFiletimes(&m_kernelTimeSlice,&slice);
  m_kernelTime = kernelTime;

//   TRACE("Kernel Slice times\n");
//   TRACE ("- slice hi : %x\n",m_kernelTimeSlice.dwHighDateTime);
//   TRACE ("- slice lo : %x\n",m_kernelTimeSlice.dwLowDateTime);

  // Calculate how much user time we just used since last time
  slice = SubFiletimes(&userTime,&m_userTime);
  m_userTimeSlice = AddFiletimes(&m_userTimeSlice,&slice);
  m_userTime = userTime;

//   TRACE("User Slice times\n");
//   TRACE ("- slice hi : %x\n",m_userTimeSlice.dwHighDateTime);
//   TRACE ("- slice lo : %x\n",m_userTimeSlice.dwLowDateTime);
}