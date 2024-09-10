/* Main */
int main(void) {
    // Initialise Arduino functionality
    init();
  
    // Attach USB for applicable processors
    #ifdef USBCON
         USBDevice.attach();
    #endif
    
    /* SETUP */
    int prime = 19211;
    int generator = 6;
    uint16_t private_key = prime + 1;
    
    /* Generates private key, sometimes takes a while */
    while(private_key >= prime){
        private_key = generate_private();
    }
    
    Serial.begin(9600);
    int public_key_A = pow_mod(generator, private_key, prime);
    Serial.print("Public key A: "); Serial.println(public_key_A);
    int public_key_B = enter_public();
    Serial.print("Public key B: "); Serial.println(public_key_B);
    int shared_key = pow_mod(public_key_B, private_key, prime);
    Serial.print("The shared key is: "); Serial.println(shared_key);

    
    /* LOOP */
    Serial3.begin(9600); // Serial3: communication with other board
    int incoming_byte = 0;
    int my_PC_byte = 0;
    while(true){
        
        //grab byte from other Arduino
        incoming_byte = Serial3.read();
        if(incoming_byte != -1){
            //decrypt byte
            int decrypted_byte = decrypt(incoming_byte, shared_key);
            if(decrypted_byte == 10 || decrypted_byte == 13){
                Serial.write('\n'); //character code line feed
                Serial.write('\r'); //carriage return
            }
            else {
                Serial.write(decrypted_byte);
            }
        }
        
        //grab byte from PC
        my_PC_byte = Serial.read();
        if(my_PC_byte != -1){
            //encrypt byte
            char byte_to_send = encrypt(my_PC_byte, shared_key);
            Serial.write((char)my_PC_byte);
            Serial3.write((char)byte_to_send);
        }
    }
    Serial.end();
    Serial3.end();

    return 0;
}