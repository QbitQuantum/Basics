void encrypt3(char *s,FILE* f,FILE* p,int decrypt){
    char PC1[56]={0};
    char PC2[48]={0};
    unsigned char input[8]={0};
    char V[16]={0};
    int K1[16][48],K2[16][48],K3[16][48];
    char IP[64]={0};
    char IP1[64]={0};
    unsigned int m[64]={0};
    int L0[32]={0},R0[32]={0};
    int i=0,j,k,temp,c,r;
    char E[48]={0};
    char S[8][64];
    char P[32];
    int Rtemp[48]={0};
    char T[32]={0};
    char fun[32]={0};
    int output[64]={0};
    int outtemp[64]={0};
    int cc;
    int flag=0;
    int count=0;
    //fseek(f,0,SEEK_SET);
    if(tablecheck(f,PC1,V,PC2,IP,E,S,P)==false){
        
        fprintf(stderr,"malformed table\n");
        return ;
    }
    if(s[0]!='1'){
        fprintf(stderr,"key too short\n");
        return ;
    }
    
    key_schedule(s,PC1,V,PC2,K1);
    key_schedule(s+16,PC1,V,PC2,K2);
    key_schedule(s+32,PC1,V,PC2,K3);
    while((cc=fgetc(p))!=EOF){
        
        input[count]=cc;
        
        
        count++;
        
        if (count==8) {
            
            array_hex_to_bin(input,m,8,0);
            
            
            
            for(i=0;i<32;i++){
                L0[i]=m[IP[i]-1];//  IP (m1m2...m64)
            }
            
            for(i=32;i<64;i++){
                R0[i-32]=m[IP[i]-1];
            }
            if (flag==0) {
                fprintf(stderr,"(L0,R0)=");
                print_hex_from_bin(L0,32);
                print_hex_from_bin(R0,32);
                fprintf(stderr,"\n");
            }
            
            for(i=0;i<16;i++){
                for(j=0;j<48;j++)
                {
                    if(decrypt==0){
                        Rtemp[j]=(R0[E[j]-1]+K1[i][j])%2;//  E(Ri-1)+ki
                    }else{
                        
                        Rtemp[j]=(R0[E[j]-1]+K3[15-i][j])%2;
                    }
                    
                }
                
                for(j=0;j<8;j++){
                    r=Rtemp[j*6]*2+Rtemp[j*6+5];//r and c
                    c=0;
                    temp=8;
                    for(k=1;k<5;k++){
                        
                        c+=Rtemp[j*6+k]*temp;
                        temp/=2;
                    }
                    temp=S[j][r*16+c];// Sbox
                    T[j*4+3]=temp%2;
                    temp/=2;
                    T[j*4+2]=temp%2;
                    temp/=2;
                    T[j*4+1]=temp%2;
                    temp/=2;
                    T[j*4]=temp%2;
                }
                for(j=0;j<32;j++){
                    fun[j]=T[P[j]-1];//P permutation
                }
                for(j=0;j<32;j++){
                    Rtemp[j]=(L0[j]+fun[j])%2;//L0 +
                }
                if (flag==0) {
                    fprintf(stderr,"(L%d,R%d)=",i+1,i+1);
                    
                    print_hex_from_bin(R0,32);
                    print_hex_from_bin(Rtemp,32);
                    fprintf(stderr,"\n");
                }
                if(i!=15){
                    for(j=0;j<32;j++){
                        L0[j]=R0[j];
                    }
                    for(j=0;j<32;j++){
                        R0[j]=Rtemp[j];
                    }
                }
            }
            inverse(IP,IP1);
            for(i=0;i<64;i++){
                if(i<32)
                    outtemp[i]=Rtemp[i];
                else
                    outtemp[i]=R0[i-32];
            }
            
            
            for(i=0;i<64;i++){
                output[i]=outtemp[IP1[i]-1];
                
            }
            //----------------------------------------------------------------------------------------------
            
            
            for(i=0;i<64;i++){
                m[i]=output[i];
            }
            
            
            
            for(i=0;i<32;i++){
                L0[i]=m[IP[i]-1];//  IP (m1m2...m64)
            }
            
            for(i=32;i<64;i++){
                R0[i-32]=m[IP[i]-1];
            }
            if (flag==0) {
                fprintf(stderr,"(L0,R0)=");
                print_hex_from_bin(L0,32);
                print_hex_from_bin(R0,32);
                fprintf(stderr,"\n");
            }
            
            for(i=0;i<16;i++){
                for(j=0;j<48;j++)
                {
                    if(decrypt==1){
                        Rtemp[j]=(R0[E[j]-1]+K2[i][j])%2;//  E(Ri-1)+ki
                    }else{
                        
                        Rtemp[j]=(R0[E[j]-1]+K2[15-i][j])%2;
                    }
                    
                }
                
                for(j=0;j<8;j++){
                    r=Rtemp[j*6]*2+Rtemp[j*6+5];//r and c
                    c=0;
                    temp=8;
                    for(k=1;k<5;k++){
                        
                        c+=Rtemp[j*6+k]*temp;
                        temp/=2;
                    }
                    temp=S[j][r*16+c];// Sbox
                    T[j*4+3]=temp%2;
                    temp/=2;
                    T[j*4+2]=temp%2;
                    temp/=2;
                    T[j*4+1]=temp%2;
                    temp/=2;
                    T[j*4]=temp%2;
                }
                for(j=0;j<32;j++){
                    fun[j]=T[P[j]-1];//P permutation
                }
                for(j=0;j<32;j++){
                    Rtemp[j]=(L0[j]+fun[j])%2;//L0 +
                }
                if (flag==0) {
                    fprintf(stderr,"(L%d,R%d)=",i+1,i+1);
                    
                    print_hex_from_bin(R0,32);
                    print_hex_from_bin(Rtemp,32);
                    fprintf(stderr,"\n");
                }
                if(i!=15){
                    for(j=0;j<32;j++){
                        L0[j]=R0[j];
                    }
                    for(j=0;j<32;j++){
                        R0[j]=Rtemp[j];
                    }
                }
            }
            inverse(IP,IP1);
            for(i=0;i<64;i++){
                if(i<32)
                    outtemp[i]=Rtemp[i];
                else
                    outtemp[i]=R0[i-32];
            }
            
            
            for(i=0;i<64;i++){
                output[i]=outtemp[IP1[i]-1];
                
            }
            
            
            
            //----------------------------------------------------------------------------------------------
            
            
            
            for(i=0;i<64;i++){
                m[i]=output[i];
            }
            
            
            
            for(i=0;i<32;i++){
                L0[i]=m[IP[i]-1];//  IP (m1m2...m64)
            }
            
            for(i=32;i<64;i++){
                R0[i-32]=m[IP[i]-1];
            }
            if (flag==0) {
                fprintf(stderr,"(L0,R0)=");
                print_hex_from_bin(L0,32);
                print_hex_from_bin(R0,32);
                fprintf(stderr,"\n");
            }
            
            for(i=0;i<16;i++){
                for(j=0;j<48;j++)
                {
                    if(decrypt==0){
                        Rtemp[j]=(R0[E[j]-1]+K3[i][j])%2;//  E(Ri-1)+ki
                    }else{
                        
                        Rtemp[j]=(R0[E[j]-1]+K1[15-i][j])%2;
                    }
                    
                }
                
                for(j=0;j<8;j++){
                    r=Rtemp[j*6]*2+Rtemp[j*6+5];//r and c
                    c=0;
                    temp=8;
                    for(k=1;k<5;k++){
                        
                        c+=Rtemp[j*6+k]*temp;
                        temp/=2;
                    }
                    temp=S[j][r*16+c];// Sbox
                    T[j*4+3]=temp%2;
                    temp/=2;
                    T[j*4+2]=temp%2;
                    temp/=2;
                    T[j*4+1]=temp%2;
                    temp/=2;
                    T[j*4]=temp%2;
                }
                for(j=0;j<32;j++){
                    fun[j]=T[P[j]-1];//P permutation
                }
                for(j=0;j<32;j++){
                    Rtemp[j]=(L0[j]+fun[j])%2;//L0 +
                }
                if (flag==0) {
                    fprintf(stderr,"(L%d,R%d)=",i+1,i+1);
                    
                    print_hex_from_bin(R0,32);
                    print_hex_from_bin(Rtemp,32);
                    fprintf(stderr,"\n");
                }
                if(i!=15){
                    for(j=0;j<32;j++){
                        L0[j]=R0[j];
                    }
                    for(j=0;j<32;j++){
                        R0[j]=Rtemp[j];
                    }
                }
            }
            inverse(IP,IP1);
            for(i=0;i<64;i++){
                if(i<32)
                    outtemp[i]=Rtemp[i];
                else
                    outtemp[i]=R0[i-32];
            }
            
            
            for(i=0;i<64;i++){
                output[i]=outtemp[IP1[i]-1];
                
            }
            
            
            
            //----------------------------------------------------------------------------------------------
            
            
            print_char_from_bin(output,64);
            
            flag=1;
            count=0;
        }
        
    }
    if(count>0){
        
        array_hex_to_bin(input,m,count,8-count);
        
        for(i=0;i<32;i++){
            L0[i]=m[IP[i]-1];//  IP (m1m2...m64)
        }
        
        for(i=32;i<64;i++){
            R0[i-32]=m[IP[i]-1];
        }
        if (flag==0) {
            fprintf(stderr,"(L0,R0)=");
            print_hex_from_bin(L0,32);
            print_hex_from_bin(R0,32);
            fprintf(stderr,"\n");
        }
        
        for(i=0;i<16;i++){
            for(j=0;j<48;j++)
            {
                if(decrypt==0){
                    Rtemp[j]=(R0[E[j]-1]+K1[i][j])%2;//  E(Ri-1)+ki
                }else{
                    
                    Rtemp[j]=(R0[E[j]-1]+K3[15-i][j])%2;
                }
                
            }
            
            for(j=0;j<8;j++){
                r=Rtemp[j*6]*2+Rtemp[j*6+5];//r and c
                c=0;
                temp=8;
                for(k=1;k<5;k++){
                    
                    c+=Rtemp[j*6+k]*temp;
                    temp/=2;
                }
                temp=S[j][r*16+c];// Sbox
                T[j*4+3]=temp%2;
                temp/=2;
                T[j*4+2]=temp%2;
                temp/=2;
                T[j*4+1]=temp%2;
                temp/=2;
                T[j*4]=temp%2;
            }
            for(j=0;j<32;j++){
                fun[j]=T[P[j]-1];//P permutation
            }
            for(j=0;j<32;j++){
                Rtemp[j]=(L0[j]+fun[j])%2;//L0 +
            }
            if (flag==0) {
                fprintf(stderr,"(L%d,R%d)=",i+1,i+1);
                
                print_hex_from_bin(R0,32);
                print_hex_from_bin(Rtemp,32);
                fprintf(stderr,"\n");
            }
            if(i!=15){
                for(j=0;j<32;j++){
                    L0[j]=R0[j];
                }
                for(j=0;j<32;j++){
                    R0[j]=Rtemp[j];
                }
            }
        }
        inverse(IP,IP1);
        for(i=0;i<64;i++){
            if(i<32)
                outtemp[i]=Rtemp[i];
            else
                outtemp[i]=R0[i-32];
        }
        
        
        for(i=0;i<64;i++){
            output[i]=outtemp[IP1[i]-1];
            
        }
        
        
        
        
        //----------------------------------------------------------------------------------------------
        
        
        for(i=0;i<64;i++){
            m[i]=output[i];
        }
        
        
        
        for(i=0;i<32;i++){
            L0[i]=m[IP[i]-1];//  IP (m1m2...m64)
        }
        
        for(i=32;i<64;i++){
            R0[i-32]=m[IP[i]-1];
        }
        if (flag==0) {
            fprintf(stderr,"(L0,R0)=");
            print_hex_from_bin(L0,32);
            print_hex_from_bin(R0,32);
            fprintf(stderr,"\n");
        }
        
        for(i=0;i<16;i++){
            for(j=0;j<48;j++)
            {
                if(decrypt==1){
                    Rtemp[j]=(R0[E[j]-1]+K2[i][j])%2;//  E(Ri-1)+ki
                }else{
                    
                    Rtemp[j]=(R0[E[j]-1]+K2[15-i][j])%2;
                }
                
            }
            
            for(j=0;j<8;j++){
                r=Rtemp[j*6]*2+Rtemp[j*6+5];//r and c
                c=0;
                temp=8;
                for(k=1;k<5;k++){
                    
                    c+=Rtemp[j*6+k]*temp;
                    temp/=2;
                }
                temp=S[j][r*16+c];// Sbox
                T[j*4+3]=temp%2;
                temp/=2;
                T[j*4+2]=temp%2;
                temp/=2;
                T[j*4+1]=temp%2;
                temp/=2;
                T[j*4]=temp%2;
            }
            for(j=0;j<32;j++){
                fun[j]=T[P[j]-1];//P permutation
            }
            for(j=0;j<32;j++){
                Rtemp[j]=(L0[j]+fun[j])%2;//L0 +
            }
            if (flag==0) {
                fprintf(stderr,"(L%d,R%d)=",i+1,i+1);
                
                print_hex_from_bin(R0,32);
                print_hex_from_bin(Rtemp,32);
                fprintf(stderr,"\n");
            }
            if(i!=15){
                for(j=0;j<32;j++){
                    L0[j]=R0[j];
                }
                for(j=0;j<32;j++){
                    R0[j]=Rtemp[j];
                }
            }
        }
        inverse(IP,IP1);
        for(i=0;i<64;i++){
            if(i<32)
                outtemp[i]=Rtemp[i];
            else
                outtemp[i]=R0[i-32];
        }
        
        
        for(i=0;i<64;i++){
            output[i]=outtemp[IP1[i]-1];
            
        }
        
        
        
        //----------------------------------------------------------------------------------------------
        
        
        
        for(i=0;i<64;i++){
            m[i]=output[i];
        }
        
        
        
        for(i=0;i<32;i++){
            L0[i]=m[IP[i]-1];//  IP (m1m2...m64)
        }
        
        for(i=32;i<64;i++){
            R0[i-32]=m[IP[i]-1];
        }
        if (flag==0) {
            fprintf(stderr,"(L0,R0)=");
            print_hex_from_bin(L0,32);
            print_hex_from_bin(R0,32);
            fprintf(stderr,"\n");
        }
        
        for(i=0;i<16;i++){
            for(j=0;j<48;j++)
            {
                if(decrypt==0){
                    Rtemp[j]=(R0[E[j]-1]+K3[i][j])%2;//  E(Ri-1)+ki
                }else{
                    
                    Rtemp[j]=(R0[E[j]-1]+K1[15-i][j])%2;
                }
                
            }
            
            for(j=0;j<8;j++){
                r=Rtemp[j*6]*2+Rtemp[j*6+5];//r and c
                c=0;
                temp=8;
                for(k=1;k<5;k++){
                    
                    c+=Rtemp[j*6+k]*temp;
                    temp/=2;
                }
                temp=S[j][r*16+c];// Sbox
                T[j*4+3]=temp%2;
                temp/=2;
                T[j*4+2]=temp%2;
                temp/=2;
                T[j*4+1]=temp%2;
                temp/=2;
                T[j*4]=temp%2;
            }
            for(j=0;j<32;j++){
                fun[j]=T[P[j]-1];//P permutation
            }
            for(j=0;j<32;j++){
                Rtemp[j]=(L0[j]+fun[j])%2;//L0 +
            }
            if (flag==0) {
                fprintf(stderr,"(L%d,R%d)=",i+1,i+1);
                
                print_hex_from_bin(R0,32);
                print_hex_from_bin(Rtemp,32);
                fprintf(stderr,"\n");
            }
            if(i!=15){
                for(j=0;j<32;j++){
                    L0[j]=R0[j];
                }
                for(j=0;j<32;j++){
                    R0[j]=Rtemp[j];
                }
            }
        }
        inverse(IP,IP1);
        for(i=0;i<64;i++){
            if(i<32)
                outtemp[i]=Rtemp[i];
            else
                outtemp[i]=R0[i-32];
        }
        
        
        for(i=0;i<64;i++){
            output[i]=outtemp[IP1[i]-1];
            
        }
        //----------------------------------------------------------------------------------------------
        
        print_char_from_bin(output,64);
        
        
    }
    return;
    
}