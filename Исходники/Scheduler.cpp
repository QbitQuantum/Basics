//This function responds to the user commands	
	 void Scheduler::Invoke(String binaryInput)
	 {
	         Tokenize(binaryInput);
			 if(elevatorID==3)      //special code for toggling userType (shortage of input pins)
			 return;
			 
	         if(userType == "Operator")
			  {Operator();return;}
			 else
			  {Passenger();return;}
	  	  
	 }