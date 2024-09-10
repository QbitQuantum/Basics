 ///<summary> Retrieve the temperature from the OneWire sensor</summary>
 ///<param name="Sensors">Location of the bus for the OneWire sensors</param>
 ///<return>True if successful, false otherwise</return>
 bool TemperatureSensor::RetrieveTemperatureFromSensor(OneWire Sensors)
 {
     float retVal = INVALID_DATA;
     byte data[2];
   //Found the sensor we were looking for, read the data from it
     if(0 == Sensors.reset())
     {
       Logger::Log(F("Unable to reset the bus"), ERR);
       goto cleanup;
     }  
     
     Sensors.select(m_SensorAddress);
     
     //Send the 0x44 command, which is the convert command
     Sensors.write(0x44);

	 //TODO: Can only do this when not in parasitic power mode
	 while(Sensors.read() == 0) 
	 {
		 //Chill for 5 ms to see if it's all done
		 delay(5);
	 }

	 //TODO: This might not be needed for non-parasite powered sensors
     if(0 == Sensors.reset())
     {
       Logger::Log(F("Unable to reset the bus after converting temperature"), ERR);
       goto cleanup;
     }
     Sensors.select(m_SensorAddress);
	 
	 

     //Send the 0xBE command, which is read the scratchpad
     Sensors.write(0xBE);     
     
     //The data is of the format LSB, MSB
     data[0] = Sensors.read();
     data[1] = Sensors.read();
     retVal = ((data[1] << 8) | data[0]); //using two's compliment
     retVal = retVal / 16.0;
     retVal = Utility::ToFahrenheit(retVal);
     
     //Reset the communication
     Sensors.reset();
     
     //Assign our temperature data
     m_Temperature = retVal;
cleanup:     
     return retVal;
 }