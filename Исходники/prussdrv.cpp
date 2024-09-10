/* Get single integer or byte from shared or data memory
 *	Takes integer index argument, returns Number at that index
 *  Careful: index for int and byte will differ! index for int == index for byte / 4 (simplified)
 *  Legacy considerations: execute() above takes the PRU num as the first argument, but since
 *  previously getDataRAMInt defaulted to PRU num 1 we don't want to break programs. Therefore,
 *  the PRU num stays optional and defaults to 0.
 */
Local<Value> getOrSetXFromOrToY(char mode, char what, char where, Nan::NAN_METHOD_ARGS_TYPE args) {	//array
	Nan::HandleScope scope;
	int pruNum = 0;
	unsigned int val = 0;
	const char maxArgs = (mode == M_GET)? 2 : 3;
		
	//Check we have at least one argument
	if (args.Length() < 1 || args.Length() > maxArgs) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return Nan::Null();
	}
	
	//Check if arguments are numbers
	if 	(!args[0]->IsNumber() || (args.Length() > 1 && !args[1]->IsNumber()) || (args.Length() > 2 && !args[2]->IsNumber())) {
		Nan::ThrowTypeError("Argument must be Integer");
		return Nan::Null();
	}
	
	if (mode == M_SET) {
		if (what == X_INT) {
			val = (where == Y_DATAMEM && args.Length() > 2)? (unsigned int)Array::Cast(*args[2])->NumberValue() : (unsigned int)Array::Cast(*args[1])->NumberValue();
		} else {
			val = (where == Y_DATAMEM && args.Length() > 2)? (unsigned char)Array::Cast(*args[2])->NumberValue() : (unsigned char)Array::Cast(*args[1])->NumberValue();
		}
	}
	
	//Get index value
	unsigned short index;
	if (where == Y_DATAMEM && args.Length() > 1) {
		index = (unsigned short)Array::Cast(*args[1])->NumberValue();
		pruNum = args[0]->Int32Value();
	} else {
		index = (unsigned short)Array::Cast(*args[0])->NumberValue();
	}
	
	unsigned int* addr;
	if (where == Y_DATAMEM) {
		if (pruNum == 0) {
			addr = dataMem_pru0_int;
		} else {
			addr = dataMem_pru1_int;
		}
	} else {
		addr = sharedMem_int + offset_sharedRam;
	}
	
	if (what == X_INT) {
		if (mode == M_SET) {
			addr[index] = val;
		}
		return Nan::New<v8::Number>(addr[index]);
	} else {
		if (mode == M_SET) {
			((unsigned char*) addr)[index] = val;
		}
		return Nan::New<v8::Number>(((unsigned char*) addr)[index]);
	}
};