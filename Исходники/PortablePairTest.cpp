 void checkStandard() {
     PortablePair<Bottle,Bottle> pp;
     pp.head.fromString("1 2 3");
     pp.body.fromString("yes no");
     BufferedConnectionWriter writer;
     pp.write(writer);
     ConstString s = writer.toString();
     Bottle bot;
     bot.fromBinary(s.c_str(),s.length());
     checkEqual(bot.size(),2,"it is a pair");  
     checkEqual(bot.get(0).asList()->size(),3,"head len is right");  
     checkEqual(bot.get(1).asList()->size(),2,"body len is right");  
 }