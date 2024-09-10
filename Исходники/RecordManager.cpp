vector<TableRowPtr> RecordManager::select(TableInfo tableInfo, vector<Condition> conds) {
		TablePtr tPtr(new Table(tableInfo));
        vector<TableRowPtr> aVector;
		TableRowPtr rPtr = tPtr->getHead();
        //cout << rPtr->getAddr().getOffset() << endl;
//        TableRowPtr rPtr( new TableRow(tPtr->getHeadAddr(), tPtr->getRowSize()) );
        while (true) {
            cout << "va: " << rPtr->getValues()[0] << endl;
            if (!rPtr->isBlank()) {
                //cout << rPtr->getValues()[0] << endl;
                bool chosen = true;
                for (int i = 0; i < conds.size(); i++) {
                    int k = conds[i].getKthAttri();
                    if (!conds[i].check(rPtr->getValues()[k])) {
                        chosen = false;
                        break;
                    }
                }
                if (chosen) aVector.push_back(rPtr);
            }
            //cout << rPtr->getAddr().getOffset() << endl;
            if (tPtr->isTail(rPtr)) break;
			rPtr = tPtr->getNext(rPtr);
		}
		return aVector;
}