			mutex::mutex()
			{
				#if defined(EA_PLATFORM_MICROSOFT)
					static_assert(sizeof(mMutexBuffer) == sizeof(CRITICAL_SECTION), "mMutexBuffer size failure");
					//static_assert(EA_ALIGN_OF(mMutexBuffer) >= EA_ALIGN_OF(CRITICAL_SECTION), "mMutexBuffer alignment failure"); // Enabling this causes the VS2012 compiler to crash.

					#if !defined(_WIN32_WINNT) || (_WIN32_WINNT < 0x0403)
						InitializeCriticalSection((CRITICAL_SECTION*)mMutexBuffer);
					#elif !EA_WINAPI_FAMILY_PARTITION(EA_WINAPI_PARTITION_DESKTOP)
						BOOL result = InitializeCriticalSectionEx((CRITICAL_SECTION*)mMutexBuffer, 10, 0);
						EASTL_ASSERT(result != 0); EA_UNUSED(result);
					#else
						BOOL result = InitializeCriticalSectionAndSpinCount((CRITICAL_SECTION*)mMutexBuffer, 10);
						EASTL_ASSERT(result != 0); EA_UNUSED(result);
					#endif

				#elif defined(EA_PLATFORM_POSIX)
					pthread_mutexattr_t attr;

					pthread_mutexattr_init(&attr);
					pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_PRIVATE); 
					pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
					pthread_mutex_init(&mMutex, &attr);
					pthread_mutexattr_destroy(&attr);
				#endif
			}