	int QueryParser::parseIt(int sessionId, string query, TreeNode *&qTree, string &tcResultString, bool toBeTypeChecked, bool toBeOptimized) {
		QueryParser::setStatEvalRun(0);
		ErrorConsole &ec(ErrorConsole::get_instance(EC_QUERY_PARSER));

		try{
			qTree = parser->parse(query).release();
			debug_print(ec,  "Query not parsed properly...\n");
			debug_print(ec,  (ErrQParser | ENotParsed));
		} catch (LoximException &ex) {
			debug_print(ec, "Query parsed");
			return (ErrQParser | ENotParsed);
		}

		Indexes::QueryOptimizer::optimizeWithIndexes(qTree);

		//Nothing more needs to be done, if this is an internal query. (no screen logging, typechecking, optimization)
		if (!toBeTypeChecked && !toBeOptimized) {
			return 0;
		}

		if (Deb::ugOn()) {
			cout << " Tree before optimization:";
			cout << "\n--------------------------------------\n";
			qTree->putToString();
			cout << "\n--------------------------------------\n";
		}
		if ((shouldTypeCheck || shouldOptimize) && !qTree->skipPreprocessing()) {
			TreeNode *nt = qTree->clone();
			bool metadataCorrect = DataScheme::dScheme(sessionId)->getIsComplete();
			bool metadataUpToDate = DataScheme::dScheme(sessionId)->getIsUpToDate();
			if (!metadataCorrect || !metadataUpToDate) {
				debug_print(ec,  "Data scheme is not complete or not up to date); optimization and typechecking blocked.");
			}

			int typeCheckErrCode = 0;
			if (shouldTypeCheck && toBeTypeChecked && metadataCorrect && metadataUpToDate) {
				if (isTcOffTmp()) { debug_print(ec,  "Typechecking turned off temporarily"); tcResultString = "";}
				else {
					Deb::ug(" \n \n TYPECHECK BEGIN !!! \n \n");
					TypeChecker *tc = new TypeCheck::TypeChecker(nt);
					typeCheckErrCode = tc->doTypeChecking(tcResultString);
					Deb::ug(" \n \n TYPECHECK DONE... \n ");
					if ((typeCheckErrCode != 0) && (typeCheckErrCode != (ErrTypeChecker | ETCNotApplicable))) {
						debug_print(ec,  "TC, Parser: typeCheckErrorCode says general TC error, should return string to user.\n");
						return typeCheckErrCode;
					}
					if (typeCheckErrCode == 0) {
						delete qTree;
						qTree = nt;
					}
				}
			} else {
				if (shouldTypeCheck && toBeTypeChecked && dmlIncompleteAction == DML_AC_RETURN_ERROR) {
					if (!metadataCorrect) return (ErrTypeChecker | EIncompleteMetadata);
					else return (ErrTypeChecker | EMetadataOutdated);
				}
				tcResultString = "";
				Deb::ug("TypeChecking is disabled.");
			}

			if (shouldOptimize && toBeOptimized && metadataCorrect && metadataUpToDate) {
				Deb::ug(" optimisation is set ON !");
				int optres = 0;
				int stat_ev_res;
				nt = qTree->clone();
				if ((stat_ev_res = this->statEvaluate(sessionId, nt)) != 0) {
					Deb::ug("static evaluation did not work out ...");
					optres = -1;
				} else {
					int optres = -2;
					DeathRmver *rmver = new DeathRmver(this);
					rmver->rmvDeath(nt);
					if (this->statEvaluate(sessionId, nt) != 0) optres = -1;
	/* The main optimisation loop - factor out single independent subqueries *
	* as long as ... such exist !                                           */
					while (optres == -2) {
						optres = nt->optimizeTree();
						while (nt->getParent() != NULL) nt = nt->getParent();
						/*one more static eval, to make sure nodes have the right info.. */
						fprintf (stderr, "one more stat eval..\n");
						if (this->statEvaluate(sessionId, nt) != 0) optres = -1;
					}
					AuxRmver *auxRmver = new AuxRmver(this);
					auxRmver->rmvAux(nt);
					JoinRpcer *joinRpcer = new JoinRpcer(this);
					joinRpcer->replaceJoin(nt);
				}
				if (optres != -1) {
					Deb::ug("I'll return optimized tree\n");
					qTree = nt;
					if (Deb::ugOn()) {
						cout << "Tree after optimization:\n--------------------------------------\n";
						qTree->putToString(); cout << "\n--------------------------------------\n";
					}
				} else { Deb::ug("I'll return the tree from before static eval..");}
			} else {
				if (shouldTypeCheck && toBeTypeChecked && dmlIncompleteAction == DML_AC_RETURN_ERROR) {
					if (!metadataCorrect) return (ErrTypeChecker | EIncompleteMetadata);
					else return (ErrTypeChecker | EMetadataOutdated);
				}
				Deb::ug(" optimisation is disabled. \n");
			}
		} else {
			qTree->qpLocalAction(this);
		}
		Deb::ug(" ParseIt() ends successfully!");
		/*			cout << "td1------------------------------------------------------------\n";
					testDeath("EMP.NAME");
					cout << "td2------------------------------------------------------------\n";
					testDeath("(EMP join (WORKS_IN.DEPT)).NAME;");
					cout << "td3------------------------------------------------------------\n";
		*/
		if (Deb::ugOn()) {
			cout << "===================================================================" << endl;
			cout << "P    A    R    S    E    R        R    E    T    U    R    N    S :" << endl;
			qTree->serialize();
			cout << "\n===================================================================" << endl;
		}
		return 0;
	}