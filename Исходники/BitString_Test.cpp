int main(int argc, const char** argv, char **envp, char **apple) {
    srand ( time(NULL) );
    ___invalidate___ = false;
    //unit tests
    BitString bitString0;
    GeneratorContext context;
   /*
    
    if(!bitString0.is_valid())
        cout << "is_valid failed\n";
    
    if(bitString0.get_bit_offset() != 0)
        cout << "get_bit_offset failed\n";
        
    if(bitString0.get_byte_index() != 0)
        cout << "get_byte_index failed\n";
        
    bitString0.set_byte(1);
    if(bitString0.peek_byte() != 1)
        cout << "set_byte / peek_byte failed\n";
        
    if(bitString0.is_cleared())
        cout << "is_cleared failed\n";
        
    bitString0.clear();
    
    if(bitString0.is_cleared() == false)
        cout << "clear failed!\n";
        
    bitString0.write_bit(true);
    bitString0.reset_index();
    if(bitString0.peek_bit() != true)
        cout << "set_byte / peek_bit failed\n";
        
    if(bitString0.read_bit() != true)
        cout << "set_byte / read_bit failed\n";
      
    
    bitString0.clear();
    
    
    int bits = 17;
    int value = 70000;
    int read_value = 0;
    
    
    bitString0.write_bits_from_int(bits, value);
    bitString0.rewind(bits);
    read_value = bitString0.read_bits_as_int(bits);
    
    if(read_value != value)
        cout << "write_bits/read_bits failed\n";

    


        
    bitString0.gen_valid(context);

    //need enough bits for the test
    if(bitString0.bits_available() > bits + 1) {
        cout << "Test Started\n";
        bitString0.write_bit(false);
        bitString0.rewind(1);
        if(bitString0.peek_bit() != false)
            cout << "set_byte / peek_bit failed\n";
        
        if(bitString0.read_bit() != false)
            cout << "set_byte / read_bit failed\n";

        
        bitString0.set_bit_index(4);
        
        bitString0.write_bits_from_int(bits, value);
        bitString0.rewind(bits);
        read_value = bitString0.read_bits_as_int(bits);
    
        if(read_value != value)
            cout << "write_bits/read_bits failed after gen_valid with value = " << value << " and read_value " << read_value << "\n";
    }

*/
    

    BitString bitString;
    bitString.gen_valid(context);
    
    test_long_write_read(16683730362329794560ULL, 64, bitString);
    
    
    for(int i = 0; i < 1000; i++) {
        cout << "*";
        
        bitString.gen_valid(context);
        //BitString original_bitstring(bitString);
        
        //add a byte and then make sure that index is correct
        
        int available_bits = bitString.bits_available();
        
        if(available_bits > 0 && false) {
            
            int max_int_value = min(available_bits, 32);
        
            //test that all the functions are invalid
        
            int bits  = context.gen_int(1, max_int_value);
            unsigned int value = context.gen_int(0); 
            //clear the other bits
            value = value << (32 - bits);
            value = value >> (32 - bits);
        
            bitString.write_bits_from_int(bits, value);
            bitString.rewind(bits);
            unsigned int read_value = bitString.read_bits_as_int(bits);
           
            if(value != read_value) {
                cout << "\nFailed write_bits_from_int with value " << value << " and read_value " 
                     << read_value << endl;
            }
        }
        
        
        if(available_bits > 0) {
            int max_int_value = min(available_bits, 64);
        
            //test that all the functions are invalid
        
            int bits  = context.gen_int(1, max_int_value);
            unsigned long long value = context.gen_long(); 
            //clear the other bits
            value = value << (64 - bits);
            value = value >> (64 - bits);
        
            test_long_write_read(value, bits, bitString);
        }