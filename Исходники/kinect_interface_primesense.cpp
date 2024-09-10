 void KinectInterfacePrimesense::printMode(const openni::VideoMode& mode) {
   std::cout << "Res: " << mode.getResolutionX() << "x";
   std::cout << mode.getResolutionY() << ", fps = " << mode.getFps();
   std::cout << ", format = " << formatToString(mode.getPixelFormat());
   std::cout << std::endl;
 }