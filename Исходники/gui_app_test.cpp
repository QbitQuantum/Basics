 static TTestApplication& Create(const TApplicationInfo& info) {
     _instance.reset(new TTestApplication(info));
     return *GetInstance();
 }