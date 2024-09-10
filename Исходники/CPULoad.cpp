void CCPULoad::readSystemValues(ULARGE_INTEGER *sysIdle, ULARGE_INTEGER *sysKernel, ULARGE_INTEGER *sysUser)
{
   FILETIME               ft_sys_idle;
   FILETIME               ft_sys_kernel;
   FILETIME               ft_sys_user;

   if (!GetSystemTimes(&ft_sys_idle, &ft_sys_kernel, &ft_sys_user))
   {
      std::stringstream Message;
      Message << "GetSystemTimes failed with status:";
      Message << std::hex << GetLastError();
      shared::exception::CException(Message.str());
   }

   CopyMemory(sysIdle, &ft_sys_idle, sizeof(FILETIME)); // Could been optimized away...
   CopyMemory(sysKernel, &ft_sys_kernel, sizeof(FILETIME)); // Could been optimized away...
   CopyMemory(sysUser, &ft_sys_user, sizeof(FILETIME)); // Could been optimized away...
}