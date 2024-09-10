int KruskalWallisCommand::execute(){
	try {
		
		if (abort) { if (calledHelp) { return 0; }  return 2;	}
        
        DesignMap designMap(designfile);
        
        //if user did not select class use first column
        if (mclass == "") {  mclass = designMap.getDefaultClass(); m->mothurOut("\nYou did not provide a class, using " + mclass +".\n\n"); }
        
        InputData input(sharedfile, "sharedfile", nullVector);
        SharedRAbundVectors* lookup = input.getSharedRAbundVectors();
        string lastLabel = lookup->getLabel();
        
        //if the users enters label "0.06" and there is no "0.06" in their file use the next lowest label.
        set<string> processedLabels;
        set<string> userLabels = labels;
        vector<string> currentLabels = lookup->getOTUNames();
        
        
        //as long as you are not at the end of the file or done wih the lines you want
        while((lookup != NULL) && ((allLines == 1) || (userLabels.size() != 0))) {
            
            if (m->getControl_pressed()) { delete lookup;  return 0; }
            
            if(allLines == 1 || labels.count(lookup->getLabel()) == 1){
                
                m->mothurOut(lookup->getLabel()+"\n"); 
                
                vector<SharedRAbundVector*> data = lookup->getSharedRAbundVectors();
                process(data, designMap, currentLabels);
                for (int i = 0; i < data.size(); i++) { delete data[i]; } data.clear();
                
                processedLabels.insert(lookup->getLabel());
                userLabels.erase(lookup->getLabel());
            }
            
            if ((util.anyLabelsToProcess(lookup->getLabel(), userLabels, "") ) && (processedLabels.count(lastLabel) != 1)) {
                string saveLabel = lookup->getLabel();
                
                delete lookup;
                lookup = input.getSharedRAbundVectors(lastLabel);
                m->mothurOut(lookup->getLabel()+"\n"); 
                
                vector<SharedRAbundVector*> data = lookup->getSharedRAbundVectors();
                process(data, designMap, currentLabels);
                for (int i = 0; i < data.size(); i++) { delete data[i]; } data.clear();
                
                processedLabels.insert(lookup->getLabel());
                userLabels.erase(lookup->getLabel());
                
                //restore real lastlabel to save below
                lookup->setLabels(saveLabel);
            }
            
            lastLabel = lookup->getLabel();
            //prevent memory leak
            delete lookup;
            
            if (m->getControl_pressed()) { return 0; }
            
            //get next line to process
            lookup = input.getSharedRAbundVectors();
        }
        
        if (m->getControl_pressed()) {  return 0; }
        
        //output error messages about any remaining user labels
        set<string>::iterator it;
        bool needToRun = false;
        for (it = userLabels.begin(); it != userLabels.end(); it++) {
            m->mothurOut("Your file does not include the label " + *it);
            if (processedLabels.count(lastLabel) != 1) {
                m->mothurOut(". I will use " + lastLabel + "."); m->mothurOutEndLine();
                needToRun = true;
            }else {
                m->mothurOut(". Please refer to " + lastLabel + "."); m->mothurOutEndLine();
            }
        }
        
        //run last label if you need to
        if (needToRun )  {
            delete lookup;
            lookup = input.getSharedRAbundVectors(lastLabel);
            
            m->mothurOut(lookup->getLabel()+"\n"); 
            vector<SharedRAbundVector*> data = lookup->getSharedRAbundVectors();
            process(data, designMap, currentLabels);
            for (int i = 0; i < data.size(); i++) { delete data[i]; } data.clear();
            
            delete lookup;
        }
        
		
        //output files created by command
		m->mothurOut("\nOutput File Names: \n"); 
		for (int i = 0; i < outputNames.size(); i++) {	m->mothurOut(outputNames[i] +"\n"); 	} m->mothurOutEndLine();
        return 0;
		
    }
	catch(exception& e) {
		m->errorOut(e, "KruskalWallisCommand", "execute");
		exit(1);
	}
}