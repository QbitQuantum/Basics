int main()
{
    const unsigned int START_SIZE = 32768;
    unsigned int largest_size = START_SIZE * pow(2,10);
    unsigned int elems_tested = START_SIZE * 16;
    //unsigned int current_size = START_SIZE;
    //unsigned int old_size = 0;
//    int max_size = START_SIZE^(INCREMENT_FACTOR*number_of_trials);
// for our outputting of the results
    ofstream ofs("results.txt");

// this is going to hold the measurements
    vector<recorder<timer> > stats(number_of_algorithms);

// The "U" is the type for the queues x and y (poorly named, i know). Using the largest sequence multiplied by factor to allocate memory
    //EMAQueue<U> x(current_size);

    cout << "________";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << headings[i];
    cout << endl;

    cout << "  Range ";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << "|      Time      ";
    cout << endl;

    //initialize vector of ints
    vector<int> testVector;
    //initialize vector of keys
    vector<int> keyVector;
    //initialize random stuff
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(START_SIZE, largest_size); // define the range
    for (unsigned int i = 0; i < elems_tested; ++i) {
        testVector.push_back(distr(eng));
        keyVector.push_back(testVector[i]%101);
    }



    for (int count = 0; count < number_of_trials; count ++)
    {
        //displays the number of elements that will be added to the data structures
        cout << setw(8) << 1+ largest_size - START_SIZE << flush;
        ofs << setw(8) << 1+ largest_size - START_SIZE;
        //resets stats
        for (int i = 0; i < number_of_algorithms; ++i)
            stats[i].reset();

        //start of testing
        for (int j = 0; j < number_of_trials; ++j)
        {
            //initialize data structures each trial
            Hashtable<unsigned int> emHash;
            unordered_map<unsigned int, unsigned int> stlMap;
            HashMap sepChain;
            hashdict<unsigned int, unsigned int> bookHash(elems_tested, -1);
            //does test for each algorithm
            for (int i = 0; i < number_of_algorithms; ++i)
            {
               //resets timer
               timer1.restart();
                //completes the test "current_size" times
            for (unsigned int k = 0; k < elems_tested; ++k)
            {
                 //data type operations to be tested
                switch (i)
                {
                    //insert values to Emily's Hash
                    case 0: emHash.insert(testVector[k]);
                            //emHash.insert(k);
                        break;
                    case 1: stlMap.insert(make_pair(keyVector[k], testVector[k]));
                            //stlMap.insert(k, k);
                        break;
                    /*
                    case 2: //sepChain.insert(testVector[k]);
                            //sepChain.insert(k);
                        break;
                    case 3: //bookHash.insert(keyVector[k], testVector[k]);
                            //bookHash.insert(k, k);
                        break;
                    */
                    case 2: emHash.remove(testVector[k]);
                            //emHash.remove(k);
                       break;
                    case 3: stlMap.erase(testVector[k]);
                            //stlMap.erase(k);
                    /*    break;
                    case 6: //sepChain.remove(testVector[k]);
                            //sepChain.remove(k);
                        break;
                    case 7: bookHash.removeAny();
                    */
                }
            }
            //stops timer
            timer1.stop();
            //records stats
            stats[i].record(timer1);
            }
            //cout << "insert: " << START_SIZE << "to: " << largest_size << endl;
        } // end of trials loop

        for (int i = 0; i < number_of_algorithms; ++i)
        {
            //outputs results console
            stats[i].report(cout);
            //outputs results to file
            stats[i].report(ofs);
        }

        cout << endl;
        ofs << endl;

        //delete vector
        testVector.clear();
        keyVector.clear();
        largest_size = largest_size/2;
        //repopulate with smaller distribution
        std::uniform_int_distribution<> distr(START_SIZE, largest_size); // define the range
        for (unsigned int m = 0; m < elems_tested; ++m) {
            testVector.push_back(distr(eng));
            keyVector.push_back(testVector[m]%101);
        }
    }
    return 0;
}