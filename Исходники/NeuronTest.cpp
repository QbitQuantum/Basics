TEST(learnWithBPTest, XOR100)
{
  Entry<double> a;
  Entry<double> b;
  Bias<double> bias1(1);
  Bias<double> bias2(1);
  Neuron<double, LinearActivationFunction<double >> n11(0.1);
  Neuron<double, LinearActivationFunction<double >> n12(0.1);
  Neuron<double, LinearActivationFunction<double >> n22(0.1);
  Exit<double> exit;
  std::vector < Link<double >> links(10);
  //wejścia do 1 neuronu
  a.setLinkOut(&links[0]);
  b.setLinkOut(&links[1]);
  bias1.setLinkOut(&links[2]);
  n11.setLinkIn(&links[2]);
  n11.setLinkIn(&links[0]);
  n11.setLinkIn(&links[1]);
  //wejścia do drugiego neuronu
  a.setLinkOut(&links[3]);
  b.setLinkOut(&links[4]);
  bias1.setLinkOut(&links[5]);
  n12.setLinkIn(&links[5]);
  n12.setLinkIn(&links[3]);
  n12.setLinkIn(&links[4]);
  //połączenia międzyneuronowe
  n11.setLinkOut(&links[6]);
  n12.setLinkOut(&links[7]);
  bias2.setLinkOut(&links[8]);
  n22.setLinkIn(&links[8]);
  n22.setLinkIn(&links[6]);
  n22.setLinkIn(&links[7]);
  //do wyjścia
  n22.setLinkOut(&links[9]);
  bias1.sendBiasToLinks();
  bias2.sendBiasToLinks();
  //n.printWages();
  exit.setLinkIn(&links[9]);

  //uczenie
  for (int i = 0; i < 5000; i++)
  {
    a.setEntry(0);
    b.setEntry(0);
    n11.calculateOutput();
    n12.calculateOutput();
    n22.calculateOutput();
    exit.learn(0);
    n22.propagateAnswer();
    n22.learnDelta();
    n11.learnBP();
    n12.learnBP();
    
    // Qstd::cout<< "0,0: " << exit.getExit() << "\n";
    
    a.setEntry(1);
    b.setEntry(0);
    n11.calculateOutput();
    n12.calculateOutput();
    n22.calculateOutput();
    exit.learn(1);
    n22.propagateAnswer();
    n22.learnDelta();
    n11.learnBP();
    n12.learnBP();
    
    // Qstd::cout<< " 1,0: " << exit.getExit() << "\n";
    
    a.setEntry(0);
    b.setEntry(1);
    n11.calculateOutput();
    n12.calculateOutput();
    n22.calculateOutput();
    exit.learn(1);
    n22.propagateAnswer();
    n22.learnDelta();
    n11.learnBP();
    n12.learnBP();
    
    // Qstd::cout<< " 0,1: " << exit.getExit() << "\n";
    
    a.setEntry(1);
    b.setEntry(1);
    n11.calculateOutput();
    n12.calculateOutput();
    n22.calculateOutput();
    exit.learn(0);
    n22.propagateAnswer();
    n22.learnDelta();
    n11.learnBP();
    n12.learnBP();
    
    // Qstd::cout<< " 1,1: " << exit.getExit() << "\n";
//    for (auto l : links)
//    {
//      // Qstd::cout<< " " << l.getValue();
//    }
//    // Qstd::cout<< "\n";
    
  //n11.printWages();
  //n12.printWages();
  //n22.printWages();
  }
  n11.printWages();
  n12.printWages();
  n22.printWages();
  a.setEntry(0);
  b.setEntry(0);
  n11.calculateOutput();
  n12.calculateOutput();
  n22.calculateOutput();
  ASSERT_GT(0.1, exit.getExit());
  a.setEntry(1);
  b.setEntry(0);
  n11.calculateOutput();
  n12.calculateOutput();
  n22.calculateOutput();
  ASSERT_LT(0.9, exit.getExit());
  a.setEntry(0);
  b.setEntry(1);
  n11.calculateOutput();
  n12.calculateOutput();
  n22.calculateOutput();
  ASSERT_LT(0.9, exit.getExit());
  a.setEntry(1);
  b.setEntry(1);
  n11.calculateOutput();
  n12.calculateOutput();
  n22.calculateOutput();
  ASSERT_GT(0.1, exit.getExit());
}