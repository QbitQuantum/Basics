void ref_test(const char *in_file, const unsigned int it_cnt, enum test_type t_type, AESREF alg)
{   u4byte          i, kl, test_no, cnt, e_cnt;
    u1byte          key[32], pt[16], iv[16], ect[16], act[32];
    char            str[128], tstr[16];
    int             ty;
    IFILE           inf;

    con_string("\nTest file: "); con_string(in_file); con_string("\nStatus: \n");

    if(!(inf = open_ifile(inf, in_file)))   // reference file for test vectors
    {                                       // if file is not present
        con_string("error in running test\n"); return;
    }

    cnt = 0; e_cnt = test_no = 0;

    for(;;)                         // while there are tests
    {
        ty = find_line(inf, str);   // input a line

        if(ty < 0)                  // until end of file

            break;

        switch(ty)      // process line type
        {
          case 0:   kl = get_dec(str + 8); continue;        // key length
          case 1:   test_no = get_dec(str + 2); continue;   // test number
          case 2:   block_in(iv, str + 3); continue;        // init vector
          case 3:   block_in(key, str + 4); continue;       // key
          case 4:   block_in(pt, str + 3);                  // plaintext
                    if(t_type != ecb_md && t_type != cbc_md)
                        continue;
                    break;
          case 5:   block_in(ect, str + 3);                 // ciphertext
                    if(t_type == ecb_md || t_type == cbc_md)
                        continue;
                    break;
        }

        if(serpent_hack)
        
            block_reverse(key, kl / 8);

        alg.set_key(key, kl, both); // set the key

        if(it_cnt > 100)

            OUT_DOTS(test_no);

        if(t_type == ecb_md || t_type == cbc_md)
        {
            block_copy(act, ect, 16);           // encrypted text to low block

            if(t_type == cbc_md)                // CBC Monte Carlo decryption
            {
                block_copy(act + 16, iv, 16);   // IV to high block

                for(i = 0; i < it_cnt; i += 2)  // do decryptions two at a time
                {
                    if(serpent_hack)
                
                        block_reverse(act, 16);

                    alg.decrypt(act, ect);      // decrypt low block

                    if(serpent_hack)
                    {
                        block_reverse(act, 16); block_reverse(ect, 16);

                    }

                    block_xor(act + 16, ect, 16);// xor into high block

                    if(serpent_hack)
                
                        block_reverse(act + 16, 16);

                    alg.decrypt(act + 16, ect); // decrypt high block

                    if(serpent_hack)
                    {               
                        block_reverse(ect, 16); block_reverse(act + 16, 16);
                    }

                    block_xor(act, ect, 16);    // xor into low block
                }
            }
            else    // ECB Monte Carlo decryption 
            {
                if(serpent_hack)

                    block_reverse(act, 16);

                for(i = 0; i < it_cnt; ++i)
        
                    alg.decrypt(act, act);
        
                if(serpent_hack)

                    block_reverse(act, 16);
            }

            if(!block_cmp(pt, act, 16))
            {
                con_string("\n\ndecryption error on test "); 
                put_dec(tstr, test_no); con_string(tstr); e_cnt++;
            }

            if(t_type == ecb_md)    // test encryption if ECB mode
            {
                if(serpent_hack)

                    block_reverse(act, 16);

                for(i = 0; i < it_cnt; ++i)

                    alg.encrypt(act, act); 

                if(serpent_hack)

                    block_reverse(act, 16);

                if(!block_cmp(ect, act, 16))
                {   
                    con_string("\n\nencryption error on test ");
                    put_dec(tstr, test_no); con_string(tstr); e_cnt++;
                }
            }
        }
        else    // if(t_type == ecb_me || t_type == cbc_me || ecb_vk || ecb_vt)
        {
            if(t_type == cbc_me)                        // CBC Monte Carlo encryption
            {
                block_copy(act, iv, 16); 
                block_copy(act + 16, pt, 16);           // copy IV and plaintext

                for(i = 0; i < it_cnt; i += 2)
                {
                    block_xor(act + 16, act, 16);       // xor low block into high block

                    if(serpent_hack)

                        block_reverse(act + 16, 16);

                    alg.encrypt(act + 16, act + 16);    // encrypt high block

                    if(serpent_hack)

                        block_reverse(act + 16, 16);

                    block_xor(act, act + 16, 16);       // xor high block into low block

                    if(serpent_hack)

                        block_reverse(act, 16);

                    alg.encrypt(act, act);              // encrypt low block
        
                    if(serpent_hack)

                        block_reverse(act, 16);
                }
            }
            else    // ECB Monte Carlo encryption
            {
                block_copy(act, pt, 16);

                if(serpent_hack)

                    block_reverse(act, 16);

                for(i = 0; i < it_cnt; ++i)
        
                    alg.encrypt(act, act);

                if(serpent_hack)
                
                    block_reverse(act, 16);
            }

            if(!block_cmp(ect, act, 16))
            {
                    con_string("\n\nencryption error on test ");
                    put_dec(tstr, test_no); con_string(tstr); e_cnt++;
            }
        
            if(t_type != cbc_me)    // if ECB mode test decrytpion
            {
                if(serpent_hack)
                
                    block_reverse(act, 16);

                for(i = 0; i < it_cnt; ++i)

                    alg.decrypt(act, act); 

                if(serpent_hack)
                
                    block_reverse(act, 16);

                if(!block_cmp(pt, act, 16))
                {   
                    con_string("\n\ndecryption error on test ");
                    put_dec(tstr, test_no); con_string(tstr); e_cnt++;
                }
            }
        }
    }

    close_ifile(inf);

    if(e_cnt > 0)   // report any errors
    {
        put_dec(tstr, e_cnt); con_string("\n"); con_string(tstr);
        con_string(" errors during test\n");
    }
    else            // else report all is well

        con_string("\nall tests correct\n");
}