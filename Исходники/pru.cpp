/* Set the shared PRU RAM to an input array
 *	Takes an integer array as input, writes it to PRU shared memory
 *	Not much error checking here, don't pass in large arrays or seg faults will happen
 *	TODO: error checking and allow user to select range to set
 */
Handle<Value> setSharedRAM(const Arguments& args) {
	HandleScope scope;
	
	//Check we have a single argument
	if (args.Length() != 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	
	//Check that it's an array
	if (!args[0]->IsArray()) {
		ThrowException(Exception::TypeError(String::New("Argument must be array")));
		return scope.Close(Undefined());
	}
	
	//Get array
	Local<Array> a = Array::Cast(*args[0]);
	
	//Iterate over array
	for (unsigned int i = 0; i<a->Length(); i++) {
		//Get element and check it's numeric
		Local<Value> element = a->Get(i);
		if (!element->IsNumber()) {
			ThrowException(Exception::TypeError(String::New("Array must be integer")));
			return scope.Close(Undefined());
		}
		
		//Set corresponding memory bytes
		sharedMem_int[OFFSET_SHAREDRAM + i] = (unsigned int) element->NumberValue();
	}
	
	//Return nothing
	return scope.Close(Undefined());
};