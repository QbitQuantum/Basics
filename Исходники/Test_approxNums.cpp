/************** Each round consists of the following:
1. c1.multiplyBy(c0)
2. c0 += random constant
3. c2 *= random constant
4. tmp = c1
5. ea.rotate(tmp, random amount in [-nSlots/2, nSlots/2])
6. c2 += tmp
7. ea.rotate(c2, random amount in [1-nSlots, nSlots-1])
8. c1.negate()
9. c3.multiplyBy(c2) 
10. c0 -= c3
**************/
void testGeneralOps(const FHEPubKey& publicKey, const FHESecKey& secretKey,
                    const EncryptedArrayCx& ea, double epsilon,
                    long nRounds)
{
  long nslots = ea.size();
  char buffer[32];

  vector<cx_double> p0, p1, p2, p3;
  ea.random(p0);
  ea.random(p1);
  ea.random(p2);
  ea.random(p3);

  Ctxt c0(publicKey), c1(publicKey), c2(publicKey), c3(publicKey);
  ea.encrypt(c0, publicKey, p0, /*size=*/1.0);
  ea.encrypt(c1, publicKey, p1, /*size=*/1.0);
  ea.encrypt(c2, publicKey, p2, /*size=*/1.0);
  ea.encrypt(c3, publicKey, p3, /*size=*/1.0);

  resetAllTimers();
  FHE_NTIMER_START(Circuit);

  for (long i = 0; i < nRounds; i++) {

    if (verbose) std::cout << "*** round " << i << "..."<<endl;

     long shamt = RandomBnd(2*(nslots/2) + 1) - (nslots/2);
                  // random number in [-nslots/2..nslots/2]
     long rotamt = RandomBnd(2*nslots - 1) - (nslots - 1);
                  // random number in [-(nslots-1)..nslots-1]

     // two random constants
     vector<cx_double> const1, const2;
     ea.random(const1);
     ea.random(const2);

     ZZX const1_poly, const2_poly;
     ea.encode(const1_poly, const1, /*size=*/1.0);
     ea.encode(const2_poly, const2, /*size=*/1.0);

     mul(p1, p0);     // c1.multiplyBy(c0)
     c1.multiplyBy(c0);
     if (verbose) {
       CheckCtxt(c1, "c1*=c0");
       debugCompare(ea, secretKey, p1, c1, epsilon);
     }

     add(p0, const1); // c0 += random constant
     c0.addConstant(const1_poly);
     if (verbose) {
       CheckCtxt(c0, "c0+=k1");
       debugCompare(ea, secretKey, p0, c0, epsilon);
     }
     mul(p2, const2); // c2 *= random constant
     c2.multByConstant(const2_poly);
     if (verbose) {
       CheckCtxt(c2, "c2*=k2");
       debugCompare(ea, secretKey, p2, c2, epsilon);
     }
     vector<cx_double> tmp_p(p1); // tmp = c1
     Ctxt tmp(c1);
     sprintf(buffer, "tmp=c1>>=%d", (int)shamt);
     rotate(tmp_p, shamt); // ea.shift(tmp, random amount in [-nSlots/2,nSlots/2])
     ea.rotate(tmp, shamt);
     if (verbose) {
       CheckCtxt(tmp, buffer);
       debugCompare(ea, secretKey, tmp_p, tmp, epsilon);
     }
     add(p2, tmp_p);  // c2 += tmp
     c2 += tmp;
     if (verbose) {
       CheckCtxt(c2, "c2+=tmp");
       debugCompare(ea, secretKey, p2, c2, epsilon);
     }
     sprintf(buffer, "c2>>>=%d", (int)rotamt);
     rotate(p2, rotamt); // ea.rotate(c2, random amount in [1-nSlots, nSlots-1])
     ea.rotate(c2, rotamt);
     if (verbose) {
       CheckCtxt(c2, buffer);
       debugCompare(ea, secretKey, p2, c2, epsilon);
     }
     negateVec(p1); // c1.negate()
     c1.negate();
     if (verbose) {
       CheckCtxt(c1, "c1=-c1");
       debugCompare(ea, secretKey, p1, c1, epsilon);
     }
     mul(p3, p2); // c3.multiplyBy(c2) 
     c3.multiplyBy(c2);
     if (verbose) {
       CheckCtxt(c3, "c3*=c2");
       debugCompare(ea, secretKey, p3, c3, epsilon);
     }
     sub(p0, p3); // c0 -= c3
     c0 -= c3;
     if (verbose) {
       CheckCtxt(c0, "c0=-c3");
       debugCompare(ea, secretKey, p0, c0, epsilon);
     }
  }

  c0.cleanUp();
  c1.cleanUp();
  c2.cleanUp();
  c3.cleanUp();

  FHE_NTIMER_STOP(Circuit);

  vector<cx_double> pp0, pp1, pp2, pp3;
   
  ea.decrypt(c0, secretKey, pp0);
  ea.decrypt(c1, secretKey, pp1);
  ea.decrypt(c2, secretKey, pp2);
  ea.decrypt(c3, secretKey, pp3);

  std::cout << "Test "<<nRounds<<" rounds of mixed operations, ";
  if (cx_equals(pp0, p0,conv<double>(epsilon*c0.getPtxtMag()))
      && cx_equals(pp1, p1,conv<double>(epsilon*c1.getPtxtMag()))
      && cx_equals(pp2, p2,conv<double>(epsilon*c2.getPtxtMag()))
      && cx_equals(pp3, p3,conv<double>(epsilon*c3.getPtxtMag())))
    std::cout << "PASS\n\n";
  else {
    std::cout << "FAIL:\n";
    std::cout << "  max(p0)="<<largestCoeff(p0)
              << ", max(pp0)="<<largestCoeff(pp0)
              << ", maxDiff="<<calcMaxDiff(p0,pp0) << endl;
    std::cout << "  max(p1)="<<largestCoeff(p1)
              << ", max(pp1)="<<largestCoeff(pp1)
              << ", maxDiff="<<calcMaxDiff(p1,pp1) << endl;
    std::cout << "  max(p2)="<<largestCoeff(p2)
              << ", max(pp2)="<<largestCoeff(pp2)
              << ", maxDiff="<<calcMaxDiff(p2,pp2) << endl;
    std::cout << "  max(p3)="<<largestCoeff(p3)
              << ", max(pp3)="<<largestCoeff(pp3)
              << ", maxDiff="<<calcMaxDiff(p3,pp3) << endl<<endl;
  }

  if (verbose) {
    std::cout << endl;
    printAllTimers();
    std::cout << endl;
  }
  resetAllTimers();
   }