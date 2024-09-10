void GUI(){
  DefineGraphN_R("Density",density,&size,&densityreq);
  StartMenu("GUI",1);
    DefineDouble("T",&T);
    DefineDouble("omega",&omega);
    StartMenu("Restart",0);
      DefineMod("size",&size,SIZE+1);
      DefineDouble("Amplitude",&Amplitude);
      DefineFunction("Restart sin",&init);
      DefineFunction("Restart step",&init2);
    EndMenu();
    DefineGraph(curve2d_,"Density graph");
    DefineBool("Pause",&pause);
    DefineBool("Single step",&sstep);
    DefineInt("Repeat",&Repeat);    DefineBool("Done",&done);
  EndMenu();
}