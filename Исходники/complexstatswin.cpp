void ComplexStatsWin::refresh()
{
	Time f; // from
	Time t; // to
	
	switch ( (En_stats_interval)((int)interval.GetData()) )
	{
		case siDay:
			{
				Date d = day_date.GetData();
				f = ToTime(d);
				t = Time(d.year, d.month, d.day, 23, 59, 59);
				break;
			}
		case siMonth:
			{
				Date from = FirstDayOfMonth(month_date.GetData());
				Date to = LastDayOfMonth(month_date.GetData());
				f = Time(from.year, from.month, from.day, 0, 0, 0);
				t = Time(to.year, to.month, to.day, 23, 59, 59);
				break;
			}
		case siDateRange:
			{
				Date from = date_from.GetData();
				Date to = date_to.GetData();
				f = Time(from.year, from.month, from.day, 0, 0, 0);
				t = Time(to.year, to.month, to.day, 23, 59, 59);
			}
	};
	
	//record count
	SQL & Select(SqlCountRows()).From(RECORD).Where(REC_DATE >= f && REC_DATE <= t);
	if (SQL.Fetch())
		record_count.SetText(~AsString(SQL[0]));
	
	//income
	SQL & Select(SqlSum(ITEM_PRICE))
		.From(RECORD_ITEM)
		.InnerJoin(RECORD).On(RECORD_ID.Of(RECORD_ITEM) == ID.Of(RECORD))
		.Where(REC_DATE.Of(RECORD) >= f && REC_DATE.Of(RECORD) <= t)
	;
	if (SQL.Fetch())
	{
		String s = ConvertMoney().Format(SQL[0]);
		income.SetText(~s);
	}
	
	//income from invoices only
	SQL & Select(SqlSum(ITEM_PRICE))
		.From(RECORD_ITEM)
		.InnerJoin(RECORD).On(RECORD_ID.Of(RECORD_ITEM) == ID.Of(RECORD))
		.Where(REC_DATE.Of(RECORD) >= f && REC_DATE.Of(RECORD) <= t && NotNull(INVOICE_ID.Of(RECORD)))
	;
	if (SQL.Fetch())
	{
		String s = ConvertMoney().Format(SQL[0]);
		income_inv.SetText(~s);
	}
	
	//income without invoices
	SQL & Select(SqlSum(ITEM_PRICE))
		.From(RECORD_ITEM)
		.InnerJoin(RECORD).On(RECORD_ID.Of(RECORD_ITEM) == ID.Of(RECORD))
		.Where(REC_DATE.Of(RECORD) >= f && REC_DATE.Of(RECORD) <= t && IsNull(INVOICE_ID.Of(RECORD)))
	;
	if (SQL.Fetch())
	{
		String s = ConvertMoney().Format(SQL[0]);
		income_noinv.SetText(~s);
	}
	
	//products
	products.Clear();
	SQL & Select(NAME.Of(LOV_PRODUCT), Count(LOV_PRODUCT))
		.From(RECORD_ITEM)
		.InnerJoin(LOV_PRODUCT).On(PROD_ID.Of(RECORD_ITEM) == ID.Of(LOV_PRODUCT))
		.InnerJoin(RECORD).On(RECORD_ID.Of(RECORD_ITEM) == ID.Of(RECORD))
		.Where(REC_DATE.Of(RECORD) >= f && REC_DATE.Of(RECORD) <= t)
		.GroupBy(NAME.Of(LOV_PRODUCT))
		.OrderBy(Descending(Count(LOV_PRODUCT)))
	;
	while(SQL.Fetch())
		products.Add(SQL);
	
	//clients
	unsigned c = 0;
	clients.Clear();
	SQL & Select(NAME.Of(LOV_TITLE), FIRST_NAME.Of(CLIENT), LAST_NAME.Of(CLIENT))
		.From(RECORD)
		.InnerJoin(PATIENT).On(PATIENT_ID.Of(RECORD) == ID.Of(PATIENT))
		.InnerJoin(CLIENT).On(CLIENT_ID.Of(PATIENT) == ID.Of(CLIENT))
		.LeftJoin(LOV_TITLE).On(TITLE_ID.Of(CLIENT) == ID.Of(LOV_TITLE))
		.Where(REC_DATE.Of(RECORD) >= f && REC_DATE.Of(RECORD) <= t)
		.OrderBy(REC_DATE.Of(RECORD))
	;
	while(SQL.Fetch() && ++c)
		clients.Add(SQL);
	client_count.SetText(AsString(c));
}