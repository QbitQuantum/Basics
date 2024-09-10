int main(int argc, char* argv[])
{
		rsa_packet packet;
		int i;
		bool cipher_done = 0;
		Command cmd;
		timeval hard_time;
	
    int sceMiVersion = SceMi::Version( SCEMI_VERSION_STRING );
    SceMiParameters params("scemi.params");
    SceMi *sceMi = SceMi::Init(sceMiVersion, &params);
    	
    // Initialize the crypto library
    crypto_init();

    // Initialize the SceMi inport
    InportProxyT<Command> inport ("", "scemi_rsaxactor_req_inport", sceMi);

    // Initialize the SceMi outport
    OutportQueueT<BIG_INT> outport ("", "scemi_rsaxactor_resp_outport", sceMi);

    ResetXactor reset("", "scemi", sceMi);
    ShutdownXactor shutdown("", "scemi_shutdown", sceMi);

    // Service SceMi requests
    SceMiServiceThread *scemi_service_thread = new SceMiServiceThread (sceMi);

    reset.reset();
	
    char *test_texts[] = { "deadbeef"
                         , "badf00d"
                         , "0ff1ce"
                         , "cafe"
                         , "defaced"
                         , "aeb45a0ee831ad6e538f9c59300290db92696abbaa06a0b1df6ca317239292160d81f220c99bd788cce66cc41033e2c3eddb"
                         , "46f4ef8bf4cf769bc5ab709267981dbb44801f9c419e99a2fc7639baaf6de6741cee37af64d5d50c87402713505cb51a88fb"
                         , "4d889e31f9a92bd62df29e16047beb747fc92e3eceebab44d399b386825d1f55294f6d854e56d0f9a7b610c67b2ae7b5e5bd36"
                         , "8ecbff22d54c29902bda135826fd302787742d4ce7a064f73c4ecca822235035fbdf1350bb7d9abcb4f54eb3257f2c96798d2e"
                         , "853493ee4fd1fe0cde743cba9b180bff20bd457c152e258b9e3b478bd25fa60a6766b8d36a95885c2c47aaa63f22ff93ebea08"
                         , "050e383b35f7688879a54ef463961533f040f943467b6a5617fdf88000c91c662d0688ddd5144f12c49106d8d81a5e04ff5ca2"
                         , "f355db88fb426ebea4a551ad129d4fcb243b903411e638a08a81e22bfe250937f1194caea4d1f312f06ecfa906d79e8c948a0d"
                         , "11d1e35094599325a2122f2f919a64e4d4ace48812f192ea7c11410c539707149c5d335f921f132d11795bcc1ebbf4a20b65e9"
                         , "7b101a938d50b8dc88780235f226bc1c6650df830c3290565e12d6b9c347c06b1fb0b6fb2e648019c8526e2d4adc4dc766dba5"
                         , "7305d1b0e93f54de5fa19eb1089fa6fbc566f8479cd381ca5894492c3078d23ef3d7a1923b9a96ffb7bf2b727fc28c6d522e54"
                         , "4228043134c88aed152a8cd0d9aef45f742e6d12511d0ecbfbf34ea593998c499f19c6315e8779184ab58dd8e731a25d410d61"
                         , "c04bb261996776e003d70116c3d7d56c6e2375f349983d478416f6600edeec1dbc286d4a57445be4ded180dcb7e157b35a8a4f"
                         , "eac2be8a8e3ef31a292c4faafa9c8a63acf1e4046672c5379215f6f145ce2062ace5587f3ea226f628178426062dd9ff81186c"
                         , "c3387e260634be9995b52c1f7114cf23d01cce8ef598cc8e5364db272aee60d06e626a2a67964d7391d5ed5c7193ab36eba81e"
                         , "ac84645df2aaca9dee4d03e8b900007905f9bfe93bbef391ea7b57513948ec88b252add18db987b0ff886e1c7d25152f7dc1af"
                         , "7176de621be4b8d4f5060b6ae0ab188d2c33f3aeddaddbe639cd89a8ca5784a8cdb0135108eb7f35020556795764c71536b49e"
                         , "1a3f9f30e4c3d5d244c1d9e6cfb8f4dd47f686efb74e99de63358750e6f0622b24afc212a472bf9a93b0d39e79ff4a71ee57c6"
                         , "68a9101d17cadfa1d89353a1d12d878dede2630904fbd8bf08ee36ccaa3c2b1759415ec3fe54bfa9f1034c5a20d01673fa06f6"
                         , "31206814135169d02ec6893064bcaab54d9a2cc44fedc5e16dba2d97adca09fd6838af21e06def28a3815dccae369ce1e2f4af"
                         , "f536b2e57395c6421008095dc6832282d8083ac466debc88f5979e8ada0e0b4820754f0325de29d77c46eada3683bb5be3fd10"
                         };
    for (int tests = 0; tests < 20; tests++) {
      char *public_key, *private_key;
      printf("Generating keypair in software...");
      generate_key(&packet, &public_key, &private_key);
      
      #ifdef DEFINE
        printf("Raw data dump\n Modulus length: %zi\n", packet.mod_len);
        for(i = 0; i < packet.mod_len; i++) {
          printf("%02X", packet.mod[i]);
        }
        
        printf("\nPrivate exponent length: %zi\n", packet.priv_len);
        for(i = 0; i < packet.priv_len; i++) {
          printf("%02X", packet.priv_exp[i]);
        }
        
          printf("\nPublic exponent length: %zi\n", packet.pub_len);
        for(i = 0; i < packet.pub_len; i++) {
          printf("%02X", packet.pub_exp[i]);
        }
      #endif

      printf("Public Key:\n%s\n", public_key);
      printf("Private Key:\n%s\n", private_key);
    
      char *plaintext = test_texts[tests];
      printf("Plain Text:\n%s\n\n", plaintext);
    
      char *ciphertext;
      ciphertext = encrypt(&packet, public_key, plaintext);
      printf("Software-calculated cipher Text:\n%s\n", ciphertext);
    
          printf("\nCiphertext length: %zi\n", packet.cipher_len);
        for(i = 0; i < packet.cipher_len; i++) {
          printf("%02X", packet.ciphertext[i]);
        }		  
    
    
      char *decrypted;
      decrypted = decrypt(private_key, ciphertext);
      printf("\nSoftware-decrypted plain Text:\n%s\n\n", decrypted);
    
      /*char *signature;
      signature = sign(private_key, plaintext);
      printf("Software signature:\n%s\n", signature);
      
      if (verify(public_key, plaintext, signature)) {
        printf("Software signature GOOD!\n");
      } else {
        printf("Software signature BAD!\n");
      }*/
      
      printf("Sending to FPGA..\n");

      
      // Pack the command for transport to FPGA
      // Command is specified in Command.h, run build and look in tbinclude
      // Assuming mod_len >= priv_len/pub_len/len(ciphertext)
      for(i = 0; i < packet.mod_len; i++) {
        cmd.m_modulus = packet.mod[packet.mod_len - i - 1];
        
        // Send the data for decryption
        if(i < packet.priv_len) {
          cmd.m_exponent = packet.priv_exp[packet.priv_len - i - 1];
        } else {
          cmd.m_exponent = 0;
        }
        
        // Since the exponent is short, pack it backwards
        if(i < packet.cipher_len) {
          cmd.m_data = packet.ciphertext[packet.cipher_len - i - 1];
        } else {
          cmd.m_data = 0;
        }
        
        //printf("Sending message %i, mod: %X coeff: %X data:%X\n", i, cmd.m_data.get(), cmd.m_exponent.get(), cmd.m_data.get());
        inport.sendMessage(cmd);
      }
        
      printf("Sending padding, 1 packet");
      cmd.m_modulus = 0;
      cmd.m_exponent = 0;
      cmd.m_data = 0;
      timer_start(&hard_time);
      inport.sendMessage(cmd);
        
      printf("Getting result..");
      
      std::cout << "Result: " << outport.getMessage() << std::endl;
      timer_poll("FPGA wall time: %d.%06d    seconds\n", &hard_time);
    }

    std::cout << "shutting down..." << std::endl;
    shutdown.blocking_send_finish();
    scemi_service_thread->stop();
    scemi_service_thread->join();
    SceMi::Shutdown(sceMi);
    std::cout << "finished" << std::endl;

    return 0;
}