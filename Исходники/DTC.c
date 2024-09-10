void voltage_switch_inverter_VSI(int S_A, int S_B, int S_C)
{
  /*
  float duty_a=1.0f;
  float duty_b=1.0f;
  float duty_c=1.0f;
  float attenuation =1.0f;
  */
  close_loop=true;
  cur_angle+=2.0f*PI*TICK_PERIOD*ref_freq;
  //converting big angles into something between 0 and 2pi
  if (cur_angle >= (2.0f*PI)) {
    cur_angle=cur_angle-(2.0f*PI);
  }

//close_loop=false;

  if (!close_loop) 
  {
    duty_a=sinf(cur_angle);
    duty_b=sinf(cur_angle+2.0f*PI/3.0f);
    duty_c=sinf(cur_angle+4.0f*PI/3.0f);
  } 
  else
  {
    duty_a=1.0f;
    duty_b=1.0f;
    duty_c=1.0f;
    attenuation =1.0f;//0.5f;//1.0f;
  }

  if (motor_off) 
  {
    duty_a=0.0f;
    duty_b=0.0f;
    duty_c=0.0f;
    attenuation=1.0f;
  }
/*
//#define CURRENT_LIMIT 14.0f
  if ( i_sA        >CURRENT_LIMIT || i_sA        <-CURRENT_LIMIT || 
       i_sB        >CURRENT_LIMIT || i_sB        <-CURRENT_LIMIT || 
       (-i_sA-i_sB)>CURRENT_LIMIT || (-i_sA-i_sB)<-CURRENT_LIMIT)
  {
    duty_a=0.0f;
    duty_b=0.0f;
    duty_c=0.0f;
    attenuation=1.0f;
    motor_stop=true;
    //printf("\n\nMotor off, overcurrent...\n\n");
 }
*/
  
/*      //PWM mode
	TIM_OCM_FROZEN,
	TIM_OCM_ACTIVE,
	TIM_OCM_INACTIVE,
	TIM_OCM_TOGGLE,
	TIM_OCM_FORCE_LOW,
	TIM_OCM_FORCE_HIGH,
	TIM_OCM_PWM1,
	TIM_OCM_PWM2,
*/


//dtc switching selection

if (close_loop)
{
  //----------------SA: S1 and S4---------------------------------
  if (S_A==1)
    {
      timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
      //timer_set_oc_mode       (TIM1, TIM_OC1, TIM_OCM_FORCE_HIGH);
      timer_enable_oc_output  (TIM1, TIM_OC1 );  //S1 on
      timer_disable_oc_output (TIM1, TIM_OC1N);  //S4 off
    }

  else if (S_A==0)
    {
      timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
      //timer_set_oc_mode       (TIM1, TIM_OC1, TIM_OCM_FORCE_HIGH);
      timer_disable_oc_output (TIM1, TIM_OC1);  //S1 off
      timer_enable_oc_output  (TIM1, TIM_OC1N); //S4 on
    }
  else
    {
      duty_a=0.0f;
      timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
      //timer_set_oc_mode       (TIM1, TIM_OC1, TIM_OCM_FORCE_HIGH);
      timer_disable_oc_output (TIM1, TIM_OC1);  //S1 off
      timer_disable_oc_output  (TIM1, TIM_OC1N); //S4 on
    }
  //-------------SB: S3 and S6------------------------------------
  if (S_B==1)
    {
      timer_set_oc_mode(TIM1, TIM_OC2, TIM_OCM_PWM1);
      //timer_set_oc_mode(TIM1, TIM_OC2, TIM_OCM_FORCE_HIGH);
      timer_enable_oc_output(TIM1, TIM_OC2 );    //S3 on
      timer_disable_oc_output (TIM1, TIM_OC2N);  //S6 off
    }


  else if (S_B==0)
    {
      timer_set_oc_mode(TIM1, TIM_OC2, TIM_OCM_PWM1);
      //timer_set_oc_mode(TIM1, TIM_OC2, TIM_OCM_FORCE_HIGH);
      timer_disable_oc_output(TIM1, TIM_OC2 );  //S3 off
      timer_enable_oc_output (TIM1, TIM_OC2N);  //S6 on
    }
  else 
    {
      duty_b=0.0f;
      timer_set_oc_mode(TIM1, TIM_OC2, TIM_OCM_PWM1);
      //timer_set_oc_mode(TIM1, TIM_OC2, TIM_OCM_FORCE_HIGH);
      timer_disable_oc_output(TIM1, TIM_OC2 );  //S3 off
      timer_disable_oc_output (TIM1, TIM_OC2N);  //S6 on
    }
  //-----------SC: S5 and S2--------------------------------------
  if (S_C==1)
    {
      timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);
      //timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_FORCE_HIGH);
      timer_enable_oc_output(TIM1, TIM_OC3 );   //S5 on
      timer_disable_oc_output (TIM1, TIM_OC3N); //S2 off
    }
  else if (S_C==0)
    {

      timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);
      //timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_FORCE_HIGH);
      timer_disable_oc_output(TIM1, TIM_OC3 );  //S5 off
      timer_enable_oc_output (TIM1, TIM_OC3N);  //S2 on
    }
  else 
    {
      duty_c=0.0f;
      timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);
      //timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_FORCE_HIGH);
      timer_disable_oc_output(TIM1, TIM_OC3 );  //S5 off
      timer_disable_oc_output (TIM1, TIM_OC3N);  //S2 on
    }
}

//open loop switching selection
/*
else 
{

  if (duty_a < 0.0f)
    {
      timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
      timer_disable_oc_output(TIM1,TIM_OC1);
      timer_enable_oc_output (TIM1, TIM_OC1N);
      duty_a=-duty_a;
    }
  else
    {
      timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
      timer_enable_oc_output(TIM1, TIM_OC1 );
      timer_disable_oc_output (TIM1, TIM_OC1N);
    }
  if (duty_b < 0.0f)
    {
      timer_set_oc_mode(TIM1, TIM_OC2, TIM_OCM_PWM1);
      timer_disable_oc_output(TIM1, TIM_OC2 );
      timer_enable_oc_output (TIM1, TIM_OC2N);
      duty_b=-duty_b;
    }
  else
    {
      timer_set_oc_mode(TIM1, TIM_OC2, TIM_OCM_PWM1);
      timer_enable_oc_output(TIM1, TIM_OC2 );
      timer_disable_oc_output (TIM1, TIM_OC2N);
    }
  if (duty_c < 0.0f)
    {
      timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);
      timer_disable_oc_output(TIM1, TIM_OC3 );
      timer_enable_oc_output (TIM1, TIM_OC3N);
      duty_c=-duty_c;
    }
  else
    {
      timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);
      timer_enable_oc_output(TIM1, TIM_OC3 );
      timer_disable_oc_output (TIM1, TIM_OC3N);
    }

}
*/


  /* Set the capture compare value for OC1. */
  timer_set_oc_value(TIM1, TIM_OC1, duty_a*attenuation*PWM_PERIOD_ARR);
  /* Set the capture compare value for OC1. */
  timer_set_oc_value(TIM1, TIM_OC2, duty_b*attenuation*PWM_PERIOD_ARR);
  /* Set the capture compare value for OC1. */
  timer_set_oc_value(TIM1, TIM_OC3, duty_c*attenuation*PWM_PERIOD_ARR);
  //tim_force_update_event(TIM1);
}