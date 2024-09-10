void echoSerial(){
 byte index=0;
 char outa[20];
 char outb[20];
 outb[0]='\0';
 boolean foundData=false;
 while (Serial.available() > 0){
   foundData=true;
   if(index < 19){
     outa[index]=Serial.read();
     index++;
     outa[index]= '\0'; 
   }else{ 
     if(index < 39){
       outb[index-20]=Serial.read();
       index++;
       outb[index-20]= '\0';
     }
   }
 }
 if(foundData){
   lcd.clear();
   lcd.home();
   lcd.print(outa);
   lcd.setCursor ( 0, 1 );
   lcd.print(outb);
 }
}