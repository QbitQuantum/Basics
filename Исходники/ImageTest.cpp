 void testStandard() {
     report(0,"checking standard compliance of description...");
     ImageOf<PixelRgb> img;
     img.resize(8,4);
     img.zero();
     BufferedConnectionWriter writer;
     img.write(writer);
     ConstString s = writer.toString();
     Bottle bot;
     bot.fromBinary(s.c_str(),s.length());
     checkEqual(bot.size(),4,"plausible bottle out");
     checkEqual(bot.get(0).toString().c_str(),"mat","good tag");
     YARP_DEBUG(Logger::get(),"an example image:");
     YARP_DEBUG(Logger::get(),bot.toString().c_str());
 }