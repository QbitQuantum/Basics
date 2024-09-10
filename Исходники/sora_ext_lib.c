//FINL
void __ext_v_sign_int8(int8 *output, int outlen, int8 *input1, int inlen1, int8 *input2, int inlen2)  
{  
  int cnt = 0;  
  vcs *pi1 = (vcs *)input1;  
  vcs *pi2 = (vcs *)input2;  
  vcs *po = (vcs *)output;  
  
  while (cnt + 16 <= inlen1)  
    {  
      *po = (vcs)_mm_sign_epi8(*pi1, *pi2);  
      pi1++;  
      pi2++;  
      po++;  
      cnt += 16;  
    }  
  
  while (cnt < inlen1)  
    {  
      output[cnt] = (input2[cnt] < 0) ? (-input1[cnt]) : input1[cnt];  
      cnt++;  
    }  
  outlen = inlen1;  
}  