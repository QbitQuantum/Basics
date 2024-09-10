    void ExperimentRun::finishEvaluations()
    {
        cout << "Cleaning up...\n";
        //int generationDumpModulo = int(NEAT::Globals::getSingleton()->getParameterValue("GenerationDumpModulo"));
        if (cleanup)
            population->cleanupOld(INT_MAX/2);

        cout << "Adjusting fitness...\n";
        population->adjustFitness();

        population->getGeneration()->setIDs();
        if((NEAT::Globals::getSingleton()->getParameterValue("DumpAll",0.0) > 0.5) || (population->getGenerationCount() % 50 == 0) ) {
            cout << "Dumping individuals...\n";
            population->dump(outputFileName/*+string(".backup.xml")*/,true,true);
            
            TiXmlElement *root = new TiXmlElement("Genetics");
		    NEAT::Globals::getSingleton()->dump(root);
		    TiXmlPrinter rootPrinter;
			root->Accept( &rootPrinter );
		    string s = rootPrinter.CStr();
		    string rootFileName = outputFileName + string("-root.backup.xml");
		    ofstream out( rootFileName.c_str() );
		    out << s.substr(0, s.length() - 3) << ">" <<endl;
		    out.close();

        } else {
            cout << "Dumping best individuals...\n";
            //population->dumpBest(outputFileName+string(".backup.xml"),true,true);
            population->dumpBest(outputFileName/*+string(".backup.xml")*/,true,true);

            //population->cleanupOld(25);
            //population->dumpBest("out/dumpBestWithGenes(backup).xml",true);
        }
        cout << "Done Dumping\n";

#ifndef HCUBE_NOGUI
        if (frame)
        {
            frame->updateNumGenerations(population->getGenerationCount());
        }
#endif

        cout << "Resetting generation data...\n";
        shared_ptr<NEAT::GeneticGeneration> generation = population->getGeneration();
        experiments[0]->resetGenerationData(generation);

        for (int a=0;a<population->getIndividualCount();a++)
        {
            //cout << __FILE__ << ":" << __LINE__ << endl;
            experiments[0]->addGenerationData(generation,population->getIndividual(a));
        }

        /*
        if(experimentType == EXPERIMENT_TIC_TAC_TOE_GAME)
        {
        //Take the best individual and run him a lot

        ((TicTacToeGameExperiment*)experiment)->setNumGames(20000);
        ((TicTacToeGameExperiment*)experiment)->setNumGames(100);
        }
        */
        
    }