char alu(Statusflags& object, int addsuborlogic=0, char ACC = 0b00000000, char Databus = 0b00000000, int addsub = 0, int Csel = 0, int logic = 0){
	int output=0b00000000; // output will be the value that gets returned
	char Cin = 0;

	switch (addsuborlogic){
	case 0: // Using adder unit to compute values

		switch(Csel){ // Determining which C value to use in addition/subtraction
		case 0:
			Cin = object.getc();  // Cin will be equal to global Carry flag variable
			break;
		case 1:
			Cin = ~object.getc(); // Cin will be equal to inversion of global Carry Flag variable
			break;
		case 2:
			Cin = 0; // Cin will be equal to 0
			break;
		case 3:
			Cin = 1; // Cin will be equal to 1
			break;
		}

		switch(addsub){ // Use addition or subtraction?
		case 0:

			output = ACC + Databus + Cin;
			object.checkc(0, ACC, Databus, Cin);
			break;
		case 1:
			output = ACC - Databus - Cin;
			object.checkc(1, ACC, Databus, Cin);
			break;
		}

		break;

	case 1: // Using logic unit to compute values
		switch(logic){
		case 0: // AND bitwise operation
			output = ACC & Databus;
			break;
		case 1: // OR bitwise operation
			output = ACC | Databus;
			break;
		case 2: // INV bitwise operation
			output = ~ACC;
			break;
		case 3: // XOR bitwise operation
			output = ACC ^ Databus;
			break;
		}
		break;
	}

	object.checkz(output);
	object.checkn(output);

	return output;
}