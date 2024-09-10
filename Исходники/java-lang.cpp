extern "C" JNIEXPORT jstring JNICALL
Java_java_lang_System_getProperty(JNIEnv* e, jclass, jstring name,
                                  jbooleanArray found)
{
  jstring r = 0;
  const char* chars = e->GetStringUTFChars(name, 0);
  if (chars) {
#ifdef PLATFORM_WINDOWS 
    if (strcmp(chars, "line.separator") == 0) {
      r = e->NewStringUTF("\r\n");
    } else if (strcmp(chars, "file.separator") == 0) {
      r = e->NewStringUTF("\\");
    } else if (strcmp(chars, "os.name") == 0) {
      r = e->NewStringUTF("Windows");
    } else if (strcmp(chars, "os.version") == 0) {
      unsigned size = 32;
      RUNTIME_ARRAY(char, buffer, size);
      OSVERSIONINFO OSversion;
      OSversion.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
      ::GetVersionEx(&OSversion);
      snprintf(RUNTIME_ARRAY_BODY(buffer), size, "%i.%i", (int)OSversion.dwMajorVersion, (int)OSversion.dwMinorVersion);
      r = e->NewStringUTF(RUNTIME_ARRAY_BODY(buffer));
    } else if (strcmp(chars, "os.arch") == 0) {
#ifdef ARCH_x86_32
      r = e->NewStringUTF("x86");
#elif defined ARCH_x86_64
      r = e->NewStringUTF("x86_64");
#elif defined ARCH_powerpc
      r = e->NewStringUTF("ppc");
#elif defined ARCH_arm
      r = e->NewStringUTF("arm");
#endif
    } else if (strcmp(chars, "java.io.tmpdir") == 0) {
      TCHAR buffer[MAX_PATH];
      GetTempPath(MAX_PATH, buffer);
      r = e->NewStringUTF(buffer);
    } else if (strcmp(chars, "user.dir") == 0) {
      TCHAR buffer[MAX_PATH];
      GetCurrentDirectory(MAX_PATH, buffer);
      r = e->NewStringUTF(buffer);
    } else if (strcmp(chars, "user.home") == 0) {
#  ifdef _MSC_VER
      WCHAR buffer[MAX_PATH];
      size_t needed;
      if (_wgetenv_s(&needed, buffer, MAX_PATH, L"USERPROFILE") == 0) {
        r = e->NewString(reinterpret_cast<jchar*>(buffer), lstrlenW(buffer));
      } else {
        r = 0;
      }
#  else
      LPWSTR home = _wgetenv(L"USERPROFILE");
      r = e->NewString(reinterpret_cast<jchar*>(home), lstrlenW(home));
#  endif
    }
#else
    if (strcmp(chars, "line.separator") == 0) {
      r = e->NewStringUTF("\n");
    } else if (strcmp(chars, "file.separator") == 0) {
      r = e->NewStringUTF("/");
    } else if (strcmp(chars, "os.name") == 0) {
#ifdef __APPLE__
      r = e->NewStringUTF("Mac OS X");
#elif defined __FreeBSD__
      r = e->NewStringUTF("FreeBSD");
#else
      r = e->NewStringUTF("Linux");
#endif
    } else if (strcmp(chars, "os.version") == 0) {
#if (defined __APPLE__) && (! defined AVIAN_IOS)
      unsigned size = 32;
      char buffer[size];
#ifdef ARCH_x86_64
      int32_t minorVersion, majorVersion;
#else
      long minorVersion, majorVersion;
#endif
      
      Gestalt(gestaltSystemVersionMajor, &majorVersion);
      Gestalt(gestaltSystemVersionMinor, &minorVersion);
      
      snprintf(buffer, size, "%d.%d", static_cast<int32_t>(majorVersion),
               static_cast<int32_t>(minorVersion));
      r = e->NewStringUTF(buffer);
#else
      struct utsname system_id; 
      uname(&system_id);
      r = e->NewStringUTF(system_id.release);
#endif
    } else if (strcmp(chars, "os.arch") == 0) {
#ifdef ARCH_x86_32
      r = e->NewStringUTF("x86");
#elif defined ARCH_x86_64
      r = e->NewStringUTF("x86_64");
#elif defined ARCH_powerpc
      r = e->NewStringUTF("ppc");
#elif defined ARCH_arm
      r = e->NewStringUTF("arm");
#endif
    } else if (strcmp(chars, "java.io.tmpdir") == 0) {
      r = e->NewStringUTF("/tmp");
    } else if (strcmp(chars, "user.dir") == 0) {
      char buffer[PATH_MAX];
      r = e->NewStringUTF(getcwd(buffer, PATH_MAX));
    } else if (strcmp(chars, "user.home") == 0) {
      r = e->NewStringUTF(getenv("HOME"));
    }
#endif
    else if (strcmp(chars, "user.language") == 0) {
      Locale locale = getLocale();
      if (strlen(locale.getLanguage())) r = e->NewStringUTF(locale.getLanguage());
    } else if (strcmp(chars, "user.region") == 0) {
      Locale locale = getLocale();
      if (strlen(locale.getRegion())) r = e->NewStringUTF(locale.getRegion());
    }

    e->ReleaseStringUTFChars(name, chars);
  }

  if (r) {
    jboolean v = true;
    e->SetBooleanArrayRegion(found, 0, 1, &v);
  }

  return r;
}