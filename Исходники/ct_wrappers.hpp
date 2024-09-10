 void clean()
 {
     // end simulation
     fmu.terminate(c);
     fmu.freeInstance(c);
 
     #ifdef _MSC_VER
         FreeLibrary(fmu.dllHandle);
     #else
         dlclose(fmu.dllHandle);
     #endif
     freeModelDescription(fmu.modelDescription);
     deleteUnzippedFiles();
 }