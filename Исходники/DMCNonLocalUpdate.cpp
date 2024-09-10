  /** advance all the walkers with killnode==no
   * @param nat number of particles to move
   * 
   * When killnode==no, any move resulting in node-crossing is treated
   * as a normal rejection.
   */
  void DMCNonLocalUpdate::advanceWalkers(WalkerIter_t it, WalkerIter_t it_end,
      bool measure) 
  {

    //RealType plusFactor(Tau*Gamma);
    //RealType minusFactor(-Tau*(1.0-Alpha*(1.0+Gamma)));

    for(; it!=it_end; ++it)
    {
      Walker_t& thisWalker(**it);

      //save old local energy
      RealType eold    = thisWalker.Properties(LOCALENERGY);
      RealType signold = thisWalker.Properties(SIGN);
      RealType enew  = eold;

      //create a 3N-Dimensional Gaussian with variance=1
      makeGaussRandomWithEngine(deltaR,RandomGen);

      W.R = m_sqrttau*deltaR + thisWalker.R + thisWalker.Drift;
      
      //update the distance table associated with W
      //DistanceTable::update(W);
      W.update();
      
      //evaluate wave function
      RealType logpsi(Psi.evaluateLog(W));

      nonLocalOps.reset();

      bool accepted=false; 
      if(branchEngine->phaseChanged(Psi.getPhase(),thisWalker.Properties(SIGN))) 
      {
        thisWalker.Age++;
        ++nReject;
      } 
      else 
      {
        //RealType enew(H.evaluate(W,nonLocalOps.Txy));
        enew=H.evaluate(W,nonLocalOps.Txy);
        RealType logGf = -0.5*Dot(deltaR,deltaR);
        setScaledDrift(Tau,W.G,drift);

        deltaR = (*it)->R - W.R - drift;
        RealType logGb = -m_oneover2tau*Dot(deltaR,deltaR);

        RealType prob= std::min(std::exp(logGb-logGf +2.0*(logpsi-thisWalker.Properties(LOGPSI))),1.0);
        if(RandomGen() > prob){
          thisWalker.Age++;
          ++nReject;
          enew=eold;
        } else {
          accepted=true;  
          thisWalker.R = W.R;
          thisWalker.Drift = drift;
          thisWalker.resetProperty(logpsi,Psi.getPhase(),enew);
          H.saveProperty(thisWalker.getPropertyBase());
          //emixed = (emixed+enew)*0.5;
          //eold=enew;
          ++nAccept;
        }
      }

      int ibar=nonLocalOps.selectMove(RandomGen());

      //make a non-local move
      if(ibar) {
        int iat=nonLocalOps.id(ibar);
        W.R[iat] += nonLocalOps.delta(ibar);
        W.update();
        logpsi=Psi.evaluateLog(W);
        setScaledDrift(Tau,W.G,thisWalker.Drift);
        thisWalker.resetProperty(logpsi,Psi.getPhase(),eold);
        thisWalker.R[iat] = W.R[iat];
        ++NonLocalMoveAccepted;
      } 

      thisWalker.Weight *= branchEngine->branchWeight(eold,enew);
      //branchEngine->accumulate(eold,1);
    }
  }