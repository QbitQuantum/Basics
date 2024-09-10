void  User_Interface::run()
{
	switch (this->status){

	case OUTPUT_DATA:
		{
			int max = this->calcMtrl->size();
			for (unsigned int i = 0; i < max; i++)
			{
				this->calcMtrl->pop_back();
			}
			this->redraw_window();
			this->type_build_box->set_top_index(0);
			this->num_floors_edit->set_text("");
			this->length_edit->set_text("");
			this->width_edit->set_text("");
			this->mat_fund_box->set_top_index(0);
			this->mat_wall_box->set_top_index(0);
			this->mat_roof_box->set_top_index(0);
			//this->mat_panel_box->set_top_index(0);

			this->enable_all(true);
			this->OK_button->set_text("Расчет");

			this->OK_button->show(SW_SHOW);
			this->show(SW_SHOW);
			this->status = INPUT_DATA;
			break;
		}

		case INPUT_DATA:
		{
			if (!this->materials->empty()){
				int type_build = this->type_build_box->get_top_index();

				int num_floors = _ttoi(this->num_floors_edit->get_text());
				double length = _ttof(this->length_edit->get_text());
				double width = _ttof(this->width_edit->get_text());

				int mat_fund = this->mat_fund_box->get_id_top_material();
				
				int mat_wall = this->mat_wall_box->get_id_top_material();
				
				int mat_roof = this->mat_roof_box->get_id_top_material();
				
				//int mat_panel = this->mat_panel_box->get_id_top_material();

				bool podval = this->checkbox->isChecked();

				Building* building = nullptr;
				switch (type_build)
				{
				case 0:
					building = new Home((double)width, (double)length, num_floors);
					break;
				case 1:
					building = new Office((double)width, (double)length, num_floors);
					break;
				case 2:
					building = new Storage((double)width, (double)length, num_floors);
					break;
				case 3:
					building = new Garage((double)width, (double)length, num_floors);
					break;
				default:
					break;
				}


				if (building){

					building->createFoundation(mat_fund, podval);
					building->createWall(type_build, mat_wall);
					building->createRoof(mat_roof, type_build);
					building->calculate();
					building->addMaterials(this->materials, this->calcMtrl);

					this->enable_all(false);
					this->OK_button->set_text("Новый");
					this->OK_button->show(SW_SHOW);
					this->status = OUTPUT_DATA;

					int X = 10, Y = 320;
					this->textout("Материал", 10, Y);
					this->textout("Количество", 230, Y);
					this->textout("Цена/шт", 330, Y);
					this->textout("Сумма грн", 400, Y);
					this->line(5,Y-5, 475, Y-5);
					this->line(5, Y + 20, 475, Y + 20);
					this->line(5, Y - 5, 5, Y + 20);
					this->line(225, Y - 5, 225, Y + 20);
					this->line(325, Y - 5, 325, Y + 20);
					this->line(395, Y - 5, 395, Y + 20);
					this->line(475, Y - 5, 475, Y + 20);
					Y += 25;
					double itogo = 0;
					char * buf = 0;
					int decimal;
					int sign;
					int err;
					if (!this->calcMtrl->empty()){
						for (unsigned int i = 0; i < this->calcMtrl->size(); i++)
						{
							if (this->calcMtrl->at(i)->count != 0)
							{
								char name[25];
								strncpy_s(name,25, this->calcMtrl->at(i)->type.c_str(), 24);
								this->textout((TCHAR*)name, 10, Y);


								buf = (char*)malloc(_CVTBUFSIZE);
								err = _fcvt_s(buf, _CVTBUFSIZE, this->calcMtrl->at(i)->count, 0, &decimal, &sign);
								this->textout((TCHAR*)buf, 230, Y);
								_itoa_s(this->calcMtrl->at(i)->price, buf, _CVTBUFSIZE, 10);
								this->textout((TCHAR*)buf, 330, Y);
								double summa = this->calcMtrl->at(i)->count * this->calcMtrl->at(i)->price;
								err = _fcvt_s(buf, _CVTBUFSIZE, summa, 0, &decimal, &sign);
								this->textout((TCHAR*)buf, 400, Y);
								itogo += summa;
								this->line(5, Y + 20, 475, Y + 20);
								this->line(5, Y - 5, 5, Y + 20);
								this->line(225, Y - 5, 225, Y + 20);
								this->line(325, Y - 5, 325, Y + 20);
								this->line(395, Y - 5, 395, Y + 20);
								this->line(475, Y - 5, 475, Y + 20);
								Y += 25;
							}
						}

						this->textout("Итого:", 350, Y);
						err = _fcvt_s(buf, _CVTBUFSIZE, itogo, 0, &decimal, &sign);
						this->textout((TCHAR*)buf, 400, Y);
						this->line(345, Y + 20, 475, Y + 20);
						this->line(345, Y - 5, 345, Y + 20);
						this->line(395, Y - 5, 395, Y + 20);
						this->line(475, Y - 5, 475, Y + 20);
					}
				}
			}
			else{
				this->textout("Нет данных о строительных материалах", 10, 320);
				this->status = OUTPUT_DATA;
			}
			break;
		}

		

	}
}