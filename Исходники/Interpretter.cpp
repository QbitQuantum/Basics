void Interpretter::evalRules(vector <Rule>& rulelist) {

    for (Rule rule : rulelist) {
        cout << rule.toString();
        output += rule.toString();
        
        //get the first rule, then iterate thru the rest, adding to the new "joined" Relation
        Relation joined = db[rule.getPredicates()[0].getID()];
        
        // set a joined scheme, based on predicate[0]'s params. And give it to me in tuple format
        joined.redoScheme(rule.getPredicates()[0].getParams());
        if (rulelist.size() > 1) {
            vector <Relation> processedPreds;
            if (rule.getPredicates().size() > 1) {
                
                //for each Predicate (after the first) in the rule
                for (int i = 1; i < rule.getPredicates().size(); i++) {
                    Relation r = db[rule.getPredicates()[i].getID()];
                    Tuple predT = predToTuple(rule.getPredicates()[i]);
                    
                    Relation selected = r.select(predT);
                    //output += selected.toString();
                    
                    //Relation projected = selected.project(predT);
                    //output += projected.toString();
                    
                    Relation renamed = selected.rename(predT);
                    processedPreds.push_back(renamed);
                    joined = joined.join(renamed);
                }
            }
        }

        Tuple renameScheme;
        //cout << "rule.getName() = " << rule.getName() << endl;
        for (auto item : rule.getParams()) {
            renameScheme.push_back(item.getVal());
        }
        //cout << "joined" << joined.toString();
        Relation projectRule = joined.project2(renameScheme); //project with the original columns
        //Relation renameRule = projectRule.rename(renameScheme); // use the original scheme
        //cout << renameRule.toString();
        int prevSize = db[rule.getName()].getRelSize();
        for (auto tuple : projectRule.getTuples()) {

            db[rule.getName()].add(tuple);

            //if it actually added
            if (db[rule.getName()].getRelSize() > prevSize) {
                output += db[rule.getName()].tupleToString(tuple);
                prevSize = db[rule.getName()].getRelSize();
                addedTuples++;
            }
        }
        
    }
}