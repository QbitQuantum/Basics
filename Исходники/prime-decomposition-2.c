 FOR(lint m, primes()){
     lint p = powl(2, m) - 1;
     printf("2**%lld-1 = %lld, with factors:",m,p);
     FOR(lint factor, decompose(p)){
         printf(" %lld",factor);
         fflush(stdout);
         CONTINUE;
     }