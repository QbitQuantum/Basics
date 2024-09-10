void ScheduleManager::registerPrice(Schedule &schedule)
{
	for (Price price;;)
	{
		system("cls");
		cout <<
			"극장 관리 시스템\n"
			" > 상영 일정 관리\n"
			"  > 상영 일정 확인/수정\n"
			"   > 가격 등록\n\n"

			"선택한 상영 일정\n";
		schedule.date.show();
		schedule.screen.show();
		schedule.show();
		
		if (0 < price.getCode())
		{
			cout << "\n선택한 가격 정보\n";
			price.show();

			cout << "\n등록하시겠습니까?(y/n): ";
			switch (inputYN())
			{
			case FUNCTION_ERROR:
				cout << "\n잘못된 입력입니다.\n";
				system("pause");
				break;
			case FUNCTION_SUCCESS:
				SQLWCHAR sql[BUFSIZ];
				swprintf_s(sql, L""
					"INSERT INTO d%d "
					"(schedule_id, code, name, won) "
					"VALUES (%d, ?, ?, ?);", schedule.date.getValue(), schedule.getId());
				if (SQL_SUCCESS == price.bindParameter(MDF_PRICE)
					&& SQL_SUCCESS == price.execute(MDF_PRICE, sql))
				{
					cout << "\n등록되었습니다.\n";
					system("pause");
				}
				else
				{
					cout << "\n오류가 발생했습니다.(registerPrice)\n";
					system("pause");
					break;
				}
			case FUNCTION_CANCEL:
				price.initialize();
			}
		}
		else
		{
			if (SQL_SUCCESS != price.bindCol(MDF_THEATER)
				|| SQL_SUCCESS != price.prepare(MDF_THEATER, L"SELECT code, name, won FROM price;"))
			{
				cout << "오류가 발생했습니다.(registerPrice)\n";
				system("pause");
				return;
			}

			switch (price.choose(MDF_THEATER))
			{
			case FUNCTION_NULL:
				cout << "등록된 가격 정보가 없습니다.\n";
				system("pause");
			case FUNCTION_ERROR:
			case FUNCTION_CANCEL:
				return;
			}
		}
	}
}