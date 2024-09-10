static unsigned
AutoDetect()
{
#ifndef HAVE_POSIX

  // Retrieve the default user language identifier from the OS
  LANGID lang_id = GetUserDefaultUILanguage();
  LogFormat("Units: GetUserDefaultUILanguage() = 0x%x", (int)lang_id);
  if (lang_id == 0)
    return 0;

  return FindLanguage(lang_id);

#elif defined(ANDROID)
  JNIEnv *env = Java::GetEnv();

  Java::Class cls(env, "java/util/Locale");

  // Call static function Locale.getDefault() that
  // returns the user's default Locale object

  jmethodID cid = env->GetStaticMethodID(cls, "getDefault",
                                         "()Ljava/util/Locale;");
  assert(cid != nullptr);

  Java::LocalObject obj(env, env->CallStaticObjectMethod(cls, cid));
  if (!obj)
    return 0;

  // Call function Locale.getLanguage() that
  // returns a two-letter language string

  jstring language = Java::Object::toString(env, obj);
  if (language == nullptr)
    return 0;

  // Convert the jstring to a char string
  const char *language2 = env->GetStringUTFChars(language, nullptr);
  if (language2 == nullptr) {
    env->DeleteLocalRef(language);
    return 0;
  }

  unsigned id = FindLanguage(language2);

  // Clean up the memory
  env->ReleaseStringUTFChars(language, language2);
  env->DeleteLocalRef(language);

  // Return e.g. "de.mo"
  return id;

#else
  // Metric default on Linux
  return 0;
#endif
}