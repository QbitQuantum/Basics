void displayDate() {
	clock.getTime();
	lcd.setCursor(1,0);
	switch (clock.dayOfWeek) {
    	case 1:
    		lcd.print("Lun");
    		break;
    	case 2:
    		lcd.print("Mar");
    		break;
    	case 3:
    		lcd.print("Mer");
    		break;
    	case 4:
    		lcd.print("Jeu");
    		break;
    	case 5:
    		lcd.print("Ven");
    		break;
    	case 6:
    		lcd.print("Sam");
    		break;
    	case 7:
    		lcd.print("Dim");
    		break;
    	default:
    		lcd.print("---");
	}
	lcd.print(" ");
	lcd.print(clock.dayOfMonth);
	lcd.print(" ");
	switch (clock.month) {
    	case 1:
    		lcd.print("Jan");
    		break;
    	case 2:
    		lcd.print("Fev");
    		break;
    	case 3:
    		lcd.print("Mar");
    		break;
    	case 4:
    		lcd.print("Avr");
    		break;
    	case 5:
    		lcd.print("Mai");
    		break;
    	case 6:
    		lcd.print("Jun");
    		break;
    	case 7:
    		lcd.print("Jui");
    		break;
    	case 8:
    		lcd.print("Aou");
    		break;
    	case 9:
    		lcd.print("Sep");
      	  	  break;
    	case 10:
    		lcd.print("Oct");
    		break;
    	case 11:
    		lcd.print("Nov");
    		break;
    	case 12:
    		lcd.print("Dec");
    		break;
    	default:
    		lcd.print("---");
	}
	lcd.print(" ");
	lcd.print("20");
	lcd.print(clock.year);
	lcd.print("  ");
}