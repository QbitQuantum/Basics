void ClassUnit::Modify(bool tag) {
	//0表示人数不够，需要从当前包含的模式当中抽取一定数量的学生来平衡这个班级的人数
	//1表示人数过多，需要把当前的学生数量放一部分到其他的班级当中
	//对于每个模式而言，都有一个不在当前的班级的表，只有当该班级在这些模式当中存在可以替换的班级列表才能将这个模式选中
	cout << unit_id_ << " " << tag << " " << stu_num_ << endl;
	//int neednum = tag ? (stu_num_ - stu_upper_) : (stu_lower_ - stu_num_);
	int neednum = stu_num_ - course_.stu_upper_;
	vector<Pattern* > avlpatque;
	map<Pattern*, int> avlinpat;
	map<Pattern*, bool>::iterator it = patterns_.begin();
	for (; it != patterns_.end(); it++) {
		if (it->first->not_in_table_.find(this) != it->first->not_in_table_.end()) {
			avlpatque.push_back(it->first);
		}
	}
	//根据具体的是人数不够还是超过来进行分类讨论
	//1.选出可以供认出的人的去处
	int temp, avlstusum = 0;
	for (int i = 0; i < avlpatque.size(); i++) {
		temp = avlpatque[i]->GetAvlStuNum(this, tag);
		//如果人数过多，想要移走，也只能把属于该pat的学生都移走
		if (tag)temp = min(temp, patterns_stus_[avlpatque[i]]);
		if (temp) {
			avlinpat[avlpatque[i]] = temp;
			avlstusum += temp;
		}
	}
	cout << "end of get avl stu num" << endl;
	cout << avlstusum << "                      " << neednum << endl;
	//2.选出哪些学生需要被扔出去
	//如果供应人数多那么就随机选择需求数量，如果不够就全部都用来满足需求
	/*if (tag)DecreaseStuNum(neednum, avlstusum, avlstunum, avlnumpat);
	else IncreaseStuNum(neednum, avlstusum, avlstunum, avlnumpat);*/
	int i = 0;
	vector<int> needused = vector<int>(avlpatque.size(), 0);
	map<Pattern*, int>::iterator ita = avlinpat.begin();
	map<Pattern*, int> patused;
	if (tag) {
		if (avlstusum > neednum) {
			//要先选中哪些学生需要被换出去
			while (neednum) {
				if (ita->second) {
					temp = rand() % (ita->second + 1);
					if (temp > neednum)temp = neednum;
					ita->second -= temp;
					if (patused.find(ita->first) == patused.end())patused[ita->first] = 0;
					patused[ita->first] += temp;
					neednum -= temp;
				}
				ita++;
				if (ita == avlinpat.end())ita = avlinpat.begin();
			}
		}
		else {
			for (; ita != avlinpat.end(); ita++) {
				patused[ita->first] = ita->second;
			}
		}
		GetSelectedStus(patused);
	}
	else {
		//依然用selected来装每个pat能存放的最大的人员数量
		map<Pattern*, bool>::iterator itp = patterns_.begin();
		while (itp != patterns_.end()) {
			selected_stus_[itp->first].insert(itp->first->GetMxStuNum(this));
		}
	}
	cout << "end of get needused" << endl;
	//3.将扔出去的人进行数据交换
	//对每个模式进行人员的分配
	map<Pattern*, int>::iterator itp = patused.begin();
	for (; itp != patused.end(); itp++) {
		if(itp->second)itp->first->ModifyStuNum(tag, this, itp->second);
	}
	cout << "end of modify stu num" << endl;
	//如果人数不够就把人数加进来
	if (!tag)AddStu2Path(patused);
	//如果人数超过还要把当前的人数搬出去
	if (tag) {
		map<Pattern*, map<int, int> >::iterator its = selected_stus_.begin();
		while (its != selected_stus_.end()) {
			map<int, int>::iterator itm = its->second.begin();
			//int psum = 0;
			while (itm != its->second.end()) {
				//psum += itm->second;
				its->first->DecreaseStuNum(itm->first, itm->second);
				//pat_path_stus_num_[its->first][itm->first] -= itm->second;
				itm++;
			}
			//patterns_stus_[its->first] -= psum;
			its++;
		}
	}
	cout << "end of motify stu num" << endl;
}