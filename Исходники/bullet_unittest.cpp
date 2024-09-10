TEST(Bullet, Slerp)
{

  unsigned int runs = 100;
  seed_rand();

  btQuaternion q1, q2;
  q1.setEuler(0,0,0);
  
  for (unsigned int i = 0 ; i < runs ; i++)
  {
    q2.setEuler(1.0 * ((double) rand() - (double)RAND_MAX /2.0) /(double)RAND_MAX,
                1.0 * ((double) rand() - (double)RAND_MAX /2.0) /(double)RAND_MAX,
                1.0 * ((double) rand() - (double)RAND_MAX /2.0) /(double)RAND_MAX);
    
    
    btQuaternion q3 = slerp(q1,q2,0.5);
    
    EXPECT_NEAR(q3.angle(q1), q2.angle(q3), 1e-5);
  }

}