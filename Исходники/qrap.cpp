void QRap::GetLink(double lat, double lon)
{
	cout << "mMouseType = CLEAN in QRap::GetLink(double lat, double lon)" << endl;
	mMouseType = CLEAN;
	char Lat[33];
	char Lon[33];
	gcvt(lat,8,Lat);
	gcvt(lon,8,Lon);
	string query = "SELECT id, txinst,rxinst, linkname, frequency, kfactor ";
	query += "FROM links WHERE line && ST_GeomFromText('POINT(";
	query +=  Lon;
	query += " ";
	query += Lat;
	query += ")',4326)";
	if (!gDb.PerformRawSql(query))
	{
		cout << "In QRap::GetLink(...)  Database link select failed"<< endl;
	}
	else
	{
		pqxx::result Li;
		gDb.GetLastResult(Li);
		if (Li.size()>0)
		{
			cout << "In QRap::GetLink(...) Database link select suceeded" << endl;
			int ID =(int)atof(Li[0]["id"].c_str()) ;
			int TxID =(int)atof(Li[0]["txinst"].c_str()) ;
			int RxID = (int)atof(Li[0]["rxinst"].c_str());
			double frequency = (double)atof(Li[0]["frequency"].c_str());
			double kfactor = (double)atof(Li[0]["kfactor"].c_str());
			string name = Li[0]["linkname"].c_str();
			cout << name << endl;
			cConfirmLink *ConfirmLink = new cConfirmLink(mQGisIface->mainWindow(), QgisGui::ModalDialogFlags);
			cout << "In QRap::GetLink(...) After constructor " << endl;
			if (ConfirmLink->SetOldLink(ID,TxID,RxID,name,frequency, kfactor))
			{
				cout << "In QRap::GetLink(...) SetOldLink success " << endl;
				if (ConfirmLink->exec()==1)
				{
					cLinkAnalysis *Plot = new cLinkAnalysis(mQGisIface->mainWindow(), QgisGui::ModalDialogFlags);
					Plot->DoAndSetUpDisplay(ConfirmLink->Units, ConfirmLink->Downlink, ConfirmLink->Frequency,
							ConfirmLink->kFactor, ConfirmLink->PlotResolution,
							ConfirmLink->DEMsource,	ConfirmLink->ClutterSource, ConfirmLink->UseClutter,
							ConfirmLink->TxID, ConfirmLink->RxID, ConfirmLink->mLinkName,
							ConfirmLink->TxName, ConfirmLink->RxName, ID);
					if (Plot->exec())
					{
						mQGisIface->mapCanvas()->refresh();
					}
				}
			}
		}	
	}
}