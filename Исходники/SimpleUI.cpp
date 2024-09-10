/*向界面中加入数据相
*/
void SimpleDataUI::add( const MyGUI::UString& caption,SimpleData sd ){

	MyGUI::TextBox* pt = mParent->createWidget<MyGUI::TextBox>(
		"TextBox",MyGUI::IntCoord(),
		MyGUI::Align::Left|MyGUI::Align::Top);
	
	pt->setTextAlign( MyGUI::Align::Right );
	pt->setCaption( caption );
	pt->setUserData( MyGUI::Any(string("@")) ); //打一个标记为删除做准备

	if( sd.type==SimpleData::BOOL ){
		MyGUI::Button* pe = mParent->createWidget<MyGUI::Button>(
		"CheckBox",MyGUI::IntCoord(),
		MyGUI::Align::Left|MyGUI::Align::Top);
		pe->setStateSelected(sd.b);
		sd.change = mep;
		pe->setUserData(MyGUI::Any(sd));
		pe->eventMouseButtonClick += newDelegate(_simpleDataCheckChange);
	}else if( sd.sv.empty() ){//编辑
		MyGUI::EditBox* pe = mParent->createWidget<MyGUI::EditBox>(
		"EditBox",MyGUI::IntCoord(),
		MyGUI::Align::Left|MyGUI::Align::Top);
		if( sd.type== SimpleData::STRING )
			pe->setCaption( sd.str );
		else if( sd.type== SimpleData::REAL)
		{
			pe->setCaption( (boost::format("%.2f")%sd.real).str() );
		}

		sd.change = mep;
		pe->setUserData(MyGUI::Any(sd));
		//数据改变
		pe->eventEditTextChange += newDelegate(_simpleDataEditTextChange);
	}else{//有可选数据
		MyGUI::ComboBox* pc = mParent->createWidget<MyGUI::ComboBox>(
		"ComboBox",MyGUI::IntCoord(),
		MyGUI::Align::Left|MyGUI::Align::Top);
		if( sd.type== SimpleData::STRING )
			pc->setCaption( sd.str );
		else if( sd.type== SimpleData::REAL )
			pc->setCaption( boost::lexical_cast<string>(sd.real) );
		for( vector<MyGUI::UString>::const_iterator i = sd.sv.begin();
			i!=sd.sv.end();++i){
			pc->addItem(*i);
			if( *i == sd.str ){
				if( sd.type== SimpleData::STRING )
					pc->setEditStatic(true);
				pc->setIndexSelected(i-sd.sv.begin());
			}
		}

		sd.change = mep;
		pc->setUserData(MyGUI::Any(sd));
		//数据改变
		pc->eventComboChangePosition += newDelegate(_simpleDataChange);
	}
}