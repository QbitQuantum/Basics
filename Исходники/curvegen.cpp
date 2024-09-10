 CurveData* CurveGen::generate() {
   utils::GeneratorParams params = utils::generate_params((unsigned int) this->_prime_length);
   unsigned int v = params.first;
   unsigned int w = params.second;
   CurveData *curve = new CurveData();

   while(true) {
     // steps 2 to 7
     BigInt A = utils::generate_number(this->_seed, params);

     // step 8
     if(!_can_solve_z_equation(A)) {
       this->_seed.update();
       continue;
     }

     // step 9
     curve->_A = A;
     curve->_seed_A = this->_seed;

     // step 10
     this->_seed.update();

     // steps 11 ~ 16
     BigInt B = utils::generate_number(this->_seed, params);

     // step 17
     if(B.is_square_mod_p(this->_prime)) {
       this->_seed.update();
       continue;
     }

     // step 18
     curve->_B = B;
     curve->_seed_B = this->_seed;

     // step 19
     BigInt equation = ((A.pow(3) * 4) + (B.pow(2) * 27)) * - 16;
     if(equation == 0) {
       this->_seed.update();
       continue;
     }

     // step 20
     if(!_fulfills_security_checks(A, B, this->_prime)) {
       this->_seed.update();
       continue;
     }

     // step 21
     this->_seed.update();

     // step 22
     curve->_seed_BP = this->_seed;

     // steps 23 ~ 28
     BigInt Mult = utils::generate_number(this->_seed, params);

     // TODO: Step 29: Find a base point
     // TODO: Step 30: Output the result
     break;
   }

   return curve;
 }