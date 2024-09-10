void XBeeActive::sendAtCommand()
{
	int i10;
	xbee.send(atRequest);
	if (xbee.readPacket(5000)) // подождите до 5 секунд для ответа состояния
	{
		if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) // Должна быть команда отклика AT
		{
			xbee.getResponse().getAtCommandResponse(atResponse);

			if (atResponse.isOk())
			{
				//DEBAG.print("Command [");
				//DEBAG.print(atResponse.getCommand()[0]);
				//DEBAG.print(atResponse.getCommand()[1]);
				//DEBAG.println("] was successful!");

				if (atResponse.getValueLength() > 0)
				{
					Len_XBee = atResponse.getValueLength();
					//DEBAG.print("\nCommand value length is - ");
					//DEBAG.println(atResponse.getValueLength(), DEC);
					//DEBAG.print("Command value: ");
					int i11 = Len_XBee - 1;
					info_XBee_data1[0] = 0;
					info_XBee_data1[1] = 0;
					info_XBee_data1[2] = 0;
					info_XBee_data1[3] = 0;

					for (i10 = 0; i10 < atResponse.getValueLength(); i10++)
					{
						info_XBee_data[i10] = atResponse.getValue()[i10];
						//DEBAG.print(info_XBee_data[i10], HEX);
						//DEBAG.print(" ");
						info_XBee_data1[i11] = info_XBee_data[i10];
						i11--;
					}
					//DEBAG.println("");
				}
			}
			else
			{
				//DEBAG.print("Command return error code: ");
				//DEBAG.println(atResponse.getStatus(), HEX);
			}
		}
		else
		{
			//DEBAG.print("Expected AT response but got ");
			//DEBAG.println(xbee.getResponse().getApiId(), HEX);
		}
	}
	else
	{
		if (xbee.getResponse().isError())             // at command failed
		{
			//DEBAG.print("Error reading packet.  Error code: ");
			//DEBAG.println(xbee.getResponse().getErrorCode());
		}
		else
		{
			//DEBAG.println("No response from radio1");
		}
	}
	delay(200);
}