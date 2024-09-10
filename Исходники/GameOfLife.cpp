int main(void)
{
	lcd.clearMarkers();
	//init analog if needed
	init_analog();
	srand(adc_read(0));
	
	//pin 0 on portb output. 
	//led stays on if iterations between fields are the same (same number of cells)
	DDRB |= _BV(PB0);
	
	//clear the buffer.
	clearArray(buffer);
	
	//if house define insert that.
	#ifdef PATTERN
		insert_pattern(field, Glider, 0,0);
	#endif
	//else random field.
	#ifdef RANDOM
		createRandomField(field);
	#endif
	
	//set contrast.
	lcd.setContrast(17);
	//make sure to start at location 0,0
	lcd.setCursor(0,0);
	
	//position is field size, I refresh the screen Backwards.
	position = fieldSize;
	while(position--)
	{
		//display field with current position
		showField(field, fieldSize-position);
		//here the rules of the game of life are checked.
		//if a position has a cell (1),
		//then look how many around,
		//if 2 or 3 around it lives, else it dies.
		//if(field[position])
		//{
		//	if(totalAround(field, position)==surviveAbility)
		//	{
		//		buffer[position]=1;
		//	}
		//	else if(totalAround(field, position)==surviveAbility+1)
		//	{
		//		buffer[position]=1;
		//	}
		//	else
		//	{
		//		buffer[position]=0;
		//	}
		//}
		//else
		//{
			//but if a position in the field is empty
			//and it has 3 around, that position becomes alife.
			
		//	if(totalAround(field, position)==reproductiveNumber)
		//	{
		//		buffer[position] = 1;
		//	}
		//	else
		//	{
		//		buffer[position] = 0;
		//	}
		//}
		//position keeps position in the field array,
		//and at the same time drawing location on
		//screen.
		if(position == 0)
		{
			//insert changes into the field.
			copy_buffer(buffer, field);
			//reset position to 0
			position = fieldSize;
			//set frame rate with a blocking delay..
			delay(adc_read(1));
			//check wether we are in a steady state or just still evolving.
			currentState = checkField(field);
			//set contrast with pot meter on analog pin 1 (not 0)
			lcd.setContrast(32/2);
			//change field if field the same a while, or iterations goes above a certain number which meens it's probaly in a loop
			//check if button is pressed and create a new field.
			if(changeCount == holdingNumber || (iterations > 1000) || (PINB & (1<<PB2)))
			{
				//reset changeCount
				changeCount = 0;
				//reset iteration count.
				iterations = 0;
				//create a random playing field.
				#ifdef PATTERN
					insert_pattern(field, Glider, 0,0);
				#endif
					//createRandomField(field);
				//put a pattern we created onto the field.
				//insert_field(stable, field);
				
			}
			//if the field states stay the same.
			else if(currentState == previousState)
			{
				PORTB |= (1<<PB0);
				changeCount++;
			}
			//if the field states are different.
			else
			{
				PORTB &= ~(1<<PB0);
				previousState = currentState;
				//that is why setting it to zero.
				iterations++;
				//changeCount shouldn't change if the inbetween states happen te be the same.
				changeCount = 0;
			}
		//set location and nicely print something.
		lcd.setCursor(0,5);
		writeFormated(iterations,changeCount,"Game of Life:");
		}
	}
	return 0;
}