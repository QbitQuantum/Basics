StkFloat Whistle :: tick( unsigned int )
{
  StkFloat soundMix, tempFreq;
  StkFloat envOut = 0, temp, temp1, temp2, tempX, tempY;
  double phi, cosphi, sinphi;
  double gain = 0.5, mod = 0.0;

  if ( --subSampCount_ <= 0 )	{
    tempVectorP_ = pea_.getPosition();
    subSampCount_ = subSample_;
    temp = bumper_.isInside( tempVectorP_ );
#ifdef WHISTLE_ANIMATION
    frameCount += 1;
    if ( frameCount >= (1470 / subSample_) ) {
      frameCount = 0;
      printf("%f %f %f\n",tempVectorP_->getX(),tempVectorP_->getY(),envOut);
      fflush(stdout);
    }
#endif
    envOut = envelope_.tick();

    if (temp < (BUMP_RADIUS + PEA_RADIUS)) {
      tempX = envOut * tickSize_ * 2000 * noise_.tick();
      tempY = -envOut * tickSize_ * 1000 * (1.0 + noise_.tick());
      pea_.addVelocity( tempX, tempY, 0 ); 
      pea_.tick( tickSize_ );
    }

    mod  = exp(-temp * 0.01);	  // exp. distance falloff of fipple/pea effect
    temp = onepole_.tick(mod);	// smooth it a little
    gain = (1.0 - (fippleGainMod_*0.5)) + (2.0 * fippleGainMod_ * temp);
    gain *= gain;	              // squared distance/gain
    //    tempFreq = 1.0				//  Normalized Base Freq
    //			+ (fippleFreqMod_ * 0.25) - (fippleFreqMod_ * temp) // fippleModulation 
    //			- (blowFreqMod_) + (blowFreqMod_ * envOut); // blowingModulation
    // short form of above
    tempFreq = 1.0 + fippleFreqMod_*(0.25-temp) + blowFreqMod_*(envOut-1.0);
    tempFreq *= baseFrequency_;

    sine_.setFrequency(tempFreq);

    tempVectorP_ = pea_.getPosition();
    temp = can_.isInside(tempVectorP_);
    temp  = -temp;       // We know (hope) it's inside, just how much??
    if (temp < (PEA_RADIUS * 1.25)) {
      pea_.getVelocity( &tempVector_ );  // This is the can/pea collision
      tempX = tempVectorP_->getX();     // calculation.  Could probably
      tempY = tempVectorP_->getY();     // simplify using tables, etc.
      phi = -atan2(tempY,tempX);

      cosphi = cos(phi);
      sinphi = sin(phi);
      temp1 = (cosphi*tempVector_.getX()) - (sinphi*tempVector_.getY());
      temp2 = (sinphi*tempVector_.getX()) + (cosphi*tempVector_.getY());
      temp1 = -temp1;
      tempX = (cosphi*temp1) + (sinphi*temp2);
      tempY = (-sinphi*temp1) + (cosphi*temp2);
      pea_.setVelocity(tempX, tempY, 0);
      pea_.tick(tickSize_);
      pea_.setVelocity( tempX*canLoss_, tempY*canLoss_, 0 );
      pea_.tick(tickSize_);
    }

    temp = tempVectorP_->getLength();	
    if (temp > 0.01) {
      tempX = tempVectorP_->getX();
      tempY = tempVectorP_->getY();
      phi = atan2( tempY, tempX );
      phi += 0.3 * temp / CAN_RADIUS;
      cosphi = cos(phi);
      sinphi = sin(phi);
      tempX = 3.0 * temp * cosphi;
      tempY = 3.0 * temp * sinphi;
    }
    else {
      tempX = 0.0;
      tempY = 0.0;
    }

    temp = (0.9 + 0.1*subSample_*noise_.tick()) * envOut * 0.6 * tickSize_;
    pea_.addVelocity( temp * tempX, (temp*tempY) - (GRAVITY*tickSize_), 0 );
    pea_.tick( tickSize_ );

    // bumper_.tick(0.0);
  }

  temp = envOut * envOut * gain / 2;
  soundMix = temp * ( sine_.tick() + ( noiseGain_*noise_.tick() ) );
  lastFrame_[0] = 0.20 * soundMix; // should probably do one-zero filter here

  return lastFrame_[0];
}