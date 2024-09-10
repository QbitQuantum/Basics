/**
 * Windows DLL entry point function. This ensures that the environment
 * variable \c TWEEK_BASE_DIR is set as soon as this DLL is attached to the
 * process. If it is not set, then it sets it based on an assumption about the
 * structure of a Tweek installation. More specifically, an assumption is made
 * that this DLL lives in the \c lib subdirectory of the Tweek installation.
 * Therefore, the root of the Tweek installation is the parent of the
 * directory containing this DLL.
 */
BOOL __stdcall DllMain(HINSTANCE module, DWORD reason, LPVOID reserved)
{
   switch (reason)
   {
      case DLL_PROCESS_ATTACH:
         {
            char* env_dir(NULL);
#if defined(_MSC_VER) && _MSC_VER >= 1400
            size_t len;
            _dupenv_s(&env_dir, &len, "TWEEK_BASE_DIR");
#else
            env_dir = std::getenv("TWEEK_BASE_DIR");
#endif

            try
            {
               fs::path base_dir;

               // If TWEEK_BASE_DIR is not set, look up the path to this DLL
               // and use it to provide a default setting for that environment
               // variable.
               if ( NULL == env_dir )
               {
                  char tmppath[1024];
                  std::memset(tmppath, 0, sizeof(tmppath));
                  GetModuleFileName(module, tmppath, sizeof(tmppath));

                  const fs::path dll_path(tmppath, fs::native);
                  base_dir = dll_path.branch_path().branch_path();
#if (defined(JUGGLER_DEBUG) || defined(TWEEK_DEBUG)) && ! defined(_DEBUG)
                  // The debug DLL linked against the release runtime is in
                  // <base_dir>\lib\debug.
                  base_dir = base_dir.branch_path();
#endif

                  const std::string base_dir_str =
                     base_dir.native_directory_string();

#if defined(_MSC_VER) && _MSC_VER >= 1400
                  _putenv_s("TWEEK_BASE_DIR", base_dir_str.c_str());
#else
                  std::ostringstream env_stream;
                  env_stream << "TWEEK_BASE_DIR=" << base_dir_str;
                  putenv(env_stream.str().c_str());
#endif
               }
               else
               {
                  base_dir = fs::path(env_dir, fs::native);
#if defined(_MSC_VER) && _MSC_VER >= 1400
                  std::free(env_dir);
                  env_dir = NULL;
#endif
               }

#if defined(_MSC_VER) && _MSC_VER >= 1400
               _dupenv_s(&env_dir, &len, "TWEEK_DATA_DIR");
#else
               env_dir = std::getenv("TWEEK_DATA_DIR");
#endif

               // If TWEEK_BASE_DIR is not set, set a default relative to
               // base_dir.
               if ( NULL == env_dir )
               {
                  fs::path data_dir(base_dir / "share" / "tweek");
                  const std::string data_dir_str =
                     data_dir.native_directory_string();

#if defined(_MSC_VER) && _MSC_VER >= 1400
                  _putenv_s("TWEEK_DATA_DIR", data_dir_str.c_str());
#else
                  std::ostringstream env_stream;
                  env_stream << "TWEEK_DATA_DIR=" << data_dir_str;
                  putenv(env_stream.str().c_str());
#endif
               }
#if defined(_MSC_VER) && _MSC_VER >= 1400
               else
               {
                  std::free(env_dir);
                  env_dir = NULL;
               }
#endif
            }
            catch (fs::filesystem_error& ex)
            {
               std::cerr << "Automatic assignment of Tweek environment "
                         << "variables failed:\n" << ex.what() << std::endl;

#if defined(_MSC_VER) && _MSC_VER >= 1400
               if ( NULL != env_dir )
               {
                  std::free(env_dir);
               }
#endif
            }
         }
         break;
      default:
         break;
   }

   return TRUE;
}