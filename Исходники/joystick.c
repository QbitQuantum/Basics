void loop() {   
  
 String cmd = cal();
 
 for(int i=0;i<cmd.length();i++){
   payload[i] = cmd[i];
 }
 payload[cmd.length()] = ',';
  
  if(lastx!=x||lasty!=y||lasts!=s){
    xbee.send(zbTx);
    lastx=x;
    lasty=y;
    lasts=s;
  }
  
  delay(10);
}