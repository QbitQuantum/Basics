char Encode::encryptChar(char c){
    int enc;
    enc = charToInt(c);

    // Plugboard first time
    enc = plugboard->encode(enc);

    // Rotors encoding
    for(int i = 0; i < numOfRotorFiles; ++i){
        enc = rotors[i]->encode(enc);
    }

    // Reflector
    enc = reflector->encode(enc);

    // Rotors encoding backwords
    for(int i = numOfRotorFiles - 1; i >= 0; --i){
        enc = rotors[i]->encodeBackwords(enc);
    }

    // Plugboard second time
    enc = plugboard->encode(enc);

    // Rotate rotors
    if(numOfRotorFiles > 0){
        rotateRotors();
    }

    return intToChar(enc);
}