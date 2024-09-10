void Rijndael::decrypt(unsigned char* block, int &length){
	if (block == NULL){
		return;
	}
	unsigned char** _last_cipher_text;
	unsigned char** _next_cipher_text;
	if (_mode != ECB){	//allocates temp mem to save last chain block
		_next_cipher_text = new unsigned char* [4];
		_last_cipher_text = new unsigned char* [4];
		for (int i = 0; i < 4; i++){
			_last_cipher_text[i] = new unsigned char [4];
			_next_cipher_text[i] = new unsigned char [4];
		}
	}
	int blocks = length / (_block_char_size);
	if (length % _block_char_size != 0){
		blocks++;
	}	
	unsigned char* _temp_shifted_block = new unsigned char [16];	// do inverse matrix, so pointers for char** are in position
	unsigned char** _temp_block = new unsigned char* [4];
	for (int b = 0; b < blocks; b++){
		for (int i = 0; i < 4; i++){
			memcpy(_temp_shifted_block+i*4, block+i+0+b*16, 1);
			memcpy(_temp_shifted_block+i*4+1, block+i+4+b*16, 1);
			memcpy(_temp_shifted_block+i*4+2, block+i+8+b*16, 1);
			memcpy(_temp_shifted_block+i*4+3, block+i+12+b*16, 1);
		}
		for (int i = 0; i < 4; i++){
			_temp_block[i] = &_temp_shifted_block[i*4];
		}
		switch (_mode){		// pre block mode
			case ECB:
				break;
			case CBC:
				for (int i = 0; i < 4; i++){
					memcpy(_last_cipher_text[i], _next_cipher_text[i], 4);
					memcpy(_next_cipher_text[i], _temp_block[i], 4);
				}
				break;
			case CFB:
			case OFB:
				if (b != 0){
					for (int i = 0; i < 4; i++){
						memcpy(_next_cipher_text[i], _temp_block[i], 4);
						memcpy(_temp_block[i], _last_cipher_text[i], 4);
					}
				}
				else{
					for (int i = 0; i < 4; i++){
						memcpy(_next_cipher_text[i], _temp_block[i], 4);
						memcpy(_temp_block[i], _iv[i], 4);
					}
				}
				break;
		}
		switch (_mode){		// decrypt or encrypt
			case ECB:
			case CBC:
				decrypt(_temp_block);
				break;
			case CFB:
			case OFB:
				encrypt(_temp_block);
				break;
		}
		switch (_mode){		// pos block mode
			case ECB:
				break;
			case CBC:
				if (b != 0){
					xorBlock(_temp_block, _last_cipher_text);			
				}
				else{
					xorBlock(_temp_block, _iv);
				}
				break;
			case CFB:
				xorBlock(_temp_block, _next_cipher_text);
				for (int i = 0; i < 4; i++){
					memcpy(_last_cipher_text[i], _next_cipher_text[i], 4);
				}
				break;
			case OFB:				
				for (int i = 0; i < 4; i++){
					memcpy(_last_cipher_text[i], _temp_block[i], 4);
				}
				xorBlock(_temp_block, _next_cipher_text);
				break;
		}
		for (int i = 0; i < 4; i++){
			memcpy(block+i*4+b*16, _temp_shifted_block+i+0, 1);
			memcpy(block+i*4+1+b*16, _temp_shifted_block+i+4, 1);
			memcpy(block+i*4+2+b*16, _temp_shifted_block+i+8, 1);
			memcpy(block+i*4+3+b*16, _temp_shifted_block+i+12, 1);
		}
	}
	if (_mode != ECB){
		for (int i = 0; i < 4; i++){
			delete[] _last_cipher_text[i];
			delete[] _next_cipher_text[i];
		}
		delete[] _next_cipher_text;
		delete[] _last_cipher_text;
	}
//	removePadding(block, length, blocks);
	delete[] _temp_block;
	delete[] _temp_shifted_block;
}