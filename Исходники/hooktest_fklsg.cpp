 JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
 {

  if(intifinit)
  {
    return JNI_VERSION_1_6;
  }
  intifinit = 1;
  MSImageRef image_time;
  image_time = MSGetImageByName("/system/lib/libc.so");

  int (*gettimeofday_org)(struct timeval*tv, struct timezone *tz);
  gettimeofday_org = (int (*)(struct timeval*tv, struct timezone *tz)) MSFindSymbol(image_time, "gettimeofday");

  int (*clock_gettime_org)(clockid_t clk_id,struct timespec *tp);
  clock_gettime_org = (int (*)(clockid_t clk_id,struct timespec *tp)) MSFindSymbol(image_time, "clock_gettime");
  
 
  //MSHookFunction((void *)gettimeofday_org, (void*)gettimeofday_hook, (void**)&gettimeofday_f);
  //MSHookFunction((void *)clock_gettime_org, (void*)clock_gettime_hook, (void**)&clock_gettime_f);


 	MSImageRef image;
 	image = MSGetImageByName("/data/data/com.babeltime.fknsango_gwphone/lib/libgame.so");
  LOGD("image is %d" , image) ;
 	void *(*lua_loadbuffer_org_sym)(void *,  char *s, long len,void *s2,void *s5);
 	lua_loadbuffer_org_sym = (void * (*)(void *,  char *s, long len,void *s2,void *s5)) MSFindSymbol(image, "luaL_loadbufferx");
	//lua_gettop =(int (*) (void*)) MSFindSymbol(image, "lua_gettop") ;
 	lua_pcall= (int (*) (void *L, int nargs, int nresults, int errfunc))MSFindSymbol(image, "lua_pcall") ; 
  lua_gettop= (int (*) (void *L))MSFindSymbol(image, "lua_gettop") ; 
  lua_type= (int (*)(void *L,int i))MSFindSymbol(image, "lua_type") ; 
  lua_typename= (char* (* )(void *L, int a2))MSFindSymbol(image, "lua_typename") ; 
  lua_tolstring= (char* (*)(void *L, signed int a2, int a3))MSFindSymbol(image, "lua_tolstring") ; 
  _Z17getPackageNameJNIv = (  char* (* )(std::string &s  ))  MSFindSymbol(image, "_Z17getPackageNameJNIv");
  
  ; 
  _ZN7cocos2d18CCFileUtilsAndroid15getWritablePathEv = (std::string (*)(int a1)) MSFindSymbol(image,"_ZN7cocos2d18CCFileUtilsAndroid15getWritablePathEv") ;
  MSHookFunction((void *)_ZN7cocos2d18CCFileUtilsAndroid15getWritablePathEv, (void*)my_ZN7cocos2d18CCFileUtilsAndroid15getWritablePathEv, (void**)&_ZN7cocos2d18CCFileUtilsAndroid15getWritablePathEv);



	//lua_getfield = ( void (*) (void *L, int index, const char *k)) MSFindSymbol(image, "lua_getfield") ; 
	//MSHookFunction( (void *)lua_getfield,(void*)mylua_getfield,(void**)&lua_getfield);
	if(lua_loadbuffer_org_sym != NULL)
 	 {
 	 	//LOGD("lua_pushlstring_org_sym is %p!!!!!!!!!!!!\n",lua_loadbuffer_org_sym);
 	 	MSHookFunction((void *)lua_loadbuffer_org_sym, (void*)lua_loadbuffer_hook, (void**)&lua_loadbuffer_f);
 	 }
 	 else
 	 {
 	 //	LOGD("lua_pushlstring_org no find!!!!!!!!!!!!!!!!!!\n");
 	 }
   
 




 	//以下为hook java的，为了显示按钮
  JNIEnv *env = GetEnv(vm);
  MSImageRef dvm_image = MSGetImageByName("/system/lib/libc.so");
  void *gp = dlopen("/data/data/com.youzu.snsgz.linyou.youmi/lib/libsubstrate-dvm.so",RTLD_LAZY);
  cydia_dvm_image = MSGetImageByName("/data/data/sh.lilith.dgame.lemon/lib/libsubstrate-dvm.so");
  LOGD("dlopen %d , dvm %d" , gp , cydia_dvm_image) ; 

  jclass gameutil = env->FindClass("com/youzu/sanguohero/GameUtils");
  jmethodID getBRAND = env->GetStaticMethodID( gameutil, "getBRAND","()Ljava/lang/String;");
  jstring jstr =  (jstring)env->CallStaticObjectMethod( gameutil,getBRAND);
  const char* str;  
  str = env->GetStringUTFChars(jstr, false);  
  LOGD("getBRAND %s" , str) ; 
  if( strstr(str,"Meizu") != NULL) {
      return JNI_VERSION_1_6 ;
  }

  find_method = (void (*)(JNIEnv *, jclass , jmethodID , void *, void **)) MSFindSymbol(cydia_dvm_image, "MSJavaHookMethod");
  const char *target_class = "android/app/Instrumentation";//对大部分app来说，这是一个父类
  jvm_org = vm;
  jclass clazzTarget = env->FindClass(target_class);
   
  const char *fun_show = "init",*fun_hid = "hidden";
  javaClientClass_org = env->FindClass("com/youzu/sanguohero/TestWM");
   
  inject_method_show = env->GetStaticMethodID(javaClientClass_org, fun_show, "(Landroid/app/Activity;)V");
  
  inject_method_hidden = env->GetStaticMethodID(javaClientClass_org, fun_hid, "(Landroid/app/Activity;)V");
   
  //显示按钮
  jmethodID method_resume = env->GetMethodID(clazzTarget,
                 "callActivityOnResume",
                 "(Landroid/app/Activity;)V"
             );

  //隐藏按钮
  jmethodID method_pause = env->GetMethodID(clazzTarget,
                   "callActivityOnPause",
                   "(Landroid/app/Activity;)V"
               );


  find_method(env, clazzTarget, method_resume, reinterpret_cast<void *>(&newCodejava_show),reinterpret_cast<void **>(&oldCode_java_show));
  find_method(env, clazzTarget, method_pause, reinterpret_cast<void *>(&newCodejava_hidden),reinterpret_cast<void **>(&oldCode_java_hidden));

  DetachCurrent(vm);
   
  return JNI_VERSION_1_6;
 }