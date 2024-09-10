 virtual unsigned long long get_current_system_time_() const
 {
     FILETIME ft_idle_time, ft_kernel_time, ft_user_time;
     GetSystemTimes(&ft_idle_time, &ft_kernel_time, &ft_user_time);
     unsigned long long kernel_time = convert_filetime_to_ulonglong_(
         ft_kernel_time);
     unsigned long long user_time = convert_filetime_to_ulonglong_(
         ft_user_time);
     return kernel_time + user_time;
 }