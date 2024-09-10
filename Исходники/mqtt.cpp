TparameterResult ApplicationMQTTClient::dissectParameter(String Parameter){

	TparameterResult par;
	par.count = 0;
    for (int i = 0; i < 11; i++) {
    	par.item[i] = "";
    }

    String str = Parameter;

    int index = -1;
    int i = 0;

    do{
     index = str.indexOf(",");
     if (index != -1){
    	 par.item[i] = str.substring(0, index);
         //Serial.println("Parameter[" + String(i) + "] = " + par.item[i]);
         str.remove(0, index +1);
         i++;
         if (str.indexOf(",") == -1 and str.length() > 0){    //best of the rest
        	 index = -1;
        	 par.item[i] = str;
        	 //Serial.println("Parameter[" + String(i) + "] = " + par.item[i]);
        	 i++;
         }
  	  }else{
  	  }
    } while (index != -1);

    par.count = i;
    return par;

}