TVector3 CalculateScatVec(TVector3 Incoming ,TVector3 ScatLab){
  
      //What is quicker passing in same value each time or defining value here each time?
      
      zprime = income.Unit();
      yprime = zlab.Cross(-income);
      yprime = yprime.Unit();
      xprime = yprime.Cross(zprime);    
      xprime = xprime.Unit();
  
  
      RotM[0][0] = xlab.Dot(xprime) ;
      RotM[0][1] = xlab.Dot(yprime);
      RotM[0][2] = xlab.Dot(zprime);
      RotM[1][0] = ylab.Dot(xprime);
      RotM[1][1] = ylab.Dot(yprime) ;
      RotM[1][2] = ylab.Dot(zprime) ;
      RotM[2][0] = zlab.Dot(xprime);
      RotM[2][1] = zlab.Dot(yprime);
      RotM[2][2] = zlab.Dot(zprime);
      
      TVector3 ScatNuc;
      
      ScatNuc(0) = (RotM[0][0]*ScatLab(0) +  RotM[1][0]*ScatLab(1) + RotM[2][0]*ScatLab(2) );
      ScatNuc(1) = (RotM[0][1]*ScatLab(0) +  RotM[1][1]*ScatLab(1) + RotM[2][1]*ScatLab(2) );
      ScatNuc(2) = (RotM[0][2]*ScatLab(0) +  RotM[1][2]*ScatLab(1) + RotM[2][2]*ScatLab(2) );
      
      //std::cout << zprime(0) << " " << zprime(1) << " " << zprime(2) <<std::endl;
      return ScatNuc;
  
}