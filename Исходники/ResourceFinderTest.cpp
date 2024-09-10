 void testFindPlugins() {
     report(0,"test get 'home' dirs for writing");
     setUpTestArea(false);
     YarpPluginSelector selector;
     selector.scan();
     Bottle lst = selector.getSelectedPlugins();
     checkTrue(lst.check("fakedev1"),"first device present");
     checkTrue(lst.check("fakedev2"),"second device present");
     checkFalse(lst.check("fakedev3"),"non-existent device absent");
     breakDownTestArea();
 }