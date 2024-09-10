int SM_Manager::Exec(const char *instr) {
	vector<string> argv;
	string cur;
	cout << instr << endl;
	for (int i = 0; ; i++) {
		if (instr[i] == ' ' || instr[i] == '(' || instr[i] == ')' || instr[i] == ',' || instr[i] == 0) {
			if (cur.length() > 0) {
				argv.push_back(cur);
				cur = "";
			}
			if (instr[i] == 0){
				break;
			}
		}
		else {
			cur = cur + instr[i];
		}
	}
	if (argv.size() < 3)
		return -1;
	if (argv[0] == "CREATE" && argv[1] =="DATABASE") {
		CreateDb(argv[2].c_str());
		return 0;
	}
	if (argv[0] == "DROP" && argv[1] == "DATABASE") {
		DropDb(argv[2].c_str());
		return 0;
	}
	if (argv[0] == "USE" && argv[1] == "DATABASE") {
		CloseDb();
		OpenDb(argv[2].c_str());
		return 0;
	}
	if (argv[0] == "SHOW" && argv[1] == "DATABASE") {
		ShowDb(argv[2].c_str());
		return 0;
	}
	if (argv[0] == "CREATE" && argv[1] == "TABLE") {
		string tablename = argv[2];
		vector<AttrInfo> attrs;
		for (int i = 3; i < argv.size();) {
			AttrInfo attr;
			if (argv[i] == "PRIMARY" && argv[i + 1] == "KEY") {
				attr.primaryKey = true;
				i += 2;
			}
			cout << argv[i] << endl;
			strcpy(attr.attrName, argv[i].c_str());
			i += 1;
			if (argv[i] == "int") {
				attr.attrType = MyINT;
				attr.attrLength = 4;
				i += 1;
				cout << "lala" << endl;
			} else if (argv[i] == "float") {
				attr.attrType = FLOAT;
				attr.attrLength = 4;
				i += 1;
			} else if (argv[i] == "char") {
				attr.attrType = STRING;
				attr.attrLength = atoi(argv[i + 1].c_str());
				i += 2;
			}
			if (i + 1 < argv.size() && argv[i] == "NOT" && argv[i + 1] == "NULL") {
				attr.notNull = true;
				i += 2;
			}
			attrs.push_back(attr);
		}
		AttrInfo *x = new AttrInfo[attrs.size()];
		for (int i = 0; i < attrs.size(); i++)
			x[i] = attrs[i];
		CreateTable(tablename.c_str(), attrs.size(), x);
		delete x;
		return 0;
	}
	if (argv[0] == "DROP" && argv[1] == "TABLE") {
		DropTable(argv[2].c_str());
		return 0;
	}
	if (argv[0] == "SHOW" && argv[1] == "TABLE") {
		ShowTable(argv[2].c_str());
		return 0;
	}
	return 0;
}