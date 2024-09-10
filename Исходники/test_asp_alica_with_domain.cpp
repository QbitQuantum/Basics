 virtual void TearDown()
 {
     // stop time measurement and report
     std::chrono::_V2::system_clock::time_point end = std::chrono::high_resolution_clock::now();
     cout << "Measured Time: " << std::chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"
          << endl;
     ae->shutdown();
     sc->shutdown();
     delete ae->getIAlicaClock();
     delete ae->getCommunicator();
     delete cc;
     delete bc;
     delete uc;
     delete crc;
 }