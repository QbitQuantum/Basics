int main() { // Main
  int i;
#if defined(DJGPP) || defined(__WATCOMC__)
   // Put the fpu in a low precision, no exception state
  _control87(MCW_EM|PC_24,MCW_EM|MCW_PC); 
#endif

  exSetGraphics(); // Set graphics

  CubeMat = plMatCreate();    // Create the material for the cube
  CubeMat->NumGradients = 100; // Have it use 100 colors
  CubeMat->ShadeType = PL_SHADE_FLAT; // Make the cube flat shaded
  plMatInit(CubeMat);          // Initialize the material

  AllMaterials[0] = CubeMat; // Make list of materials
  AllMaterials[1] = 0; // Null terminate list of materials
  plMatMakeOptPal(ThePalette,1,255,AllMaterials); // Create a nice palette

  ThePalette[0] = ThePalette[1] = ThePalette[2] = 0; // Color 0 is black

  plMatMapToPal(CubeMat,ThePalette,0,255); // Map the material to our palette

  // Convert std 8 bit/chan palette to vga's 6 bit/chan palette
  for (i = 0; i < 768; i ++) ThePalette[i] >>= 2;
  exSetPalette(ThePalette); // Set the palette
 
  TheCube = plMakeBox(100.0,100.0,100.0,CubeMat); // Create the cube

  TheCamera = plCamCreate(320, // Screen width
                          200, // Screen height
                          320*3.0/(200*4.0), // Aspect ratio
                          90.0, // Field of view
                          TheFrameBuffer, // Framebuffer
                          NULL // ZBuffer (none)
                          ); // Create the camera
  TheCamera->Z = -300; // Back the camera up from the origin

  TheLight = plLightSet(plLightCreate(), // Create a light to be set up
             PL_LIGHT_VECTOR, // vector light
             0.0,0.0,0.0, // rotation angles
             1.0, // intensity
             1.0); // falloff, not used for vector lights
             
  while (!exGetKey()) { // While the keyboard hasn't been touched
    TheCube->Xa += 1.0; // Rotate by 1 degree on each axis
    TheCube->Ya += 1.0;
    TheCube->Za += 1.0;
    memset(TheFrameBuffer,0,320*200); // clear framebuffer for next frame
    plRenderBegin(TheCamera);        // Start rendering with the camera
    plRenderLight(TheLight);         // Render our light
    plRenderObj(TheCube);            // Render our object
    plRenderEnd();                   // Finish rendering
    exWaitVSync();                   // Sync with retrace
    memcpy(exGraphMem,TheFrameBuffer,320*200); // dump to screen
  }
  exSetText(); // Restore text mode
  return 0;          // Quit
}