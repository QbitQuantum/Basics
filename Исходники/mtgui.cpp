void modeltest::editNexus(wxCommandEvent& event)
{
	wxString wxline, nexusFile, nexP, finalB, nexTemp, temp, BICblock, AICblock, HLRTblock;
	char line[2000];
	string p1, p2, p3, sline; int pBpos, sel;
	bool pBlock = false, toIns = true;
	wxArrayString block;
	const wxString choices[] = { _T("hLRTs"), _T("AIC"), _T("BIC")};


	wxFileDialog* dialog = new wxFileDialog (this, "Select NEXUS file to insert PAUP block", "", "", FILETYPES3, wxOPEN, wxDefaultPosition);

    if (dialog->ShowModal() == wxID_OK)
    {
		nexusFile = dialog->GetPath();
		this->outputText->SaveFile("temp.txt");
		ifstream modelOut ("temp.txt");
	
		wxSingleChoiceDialog dialog(this, _T("Select LSET command to parse into NEXUS files"),_T("Please select one"), 3, choices);
		if(dialog.ShowModal() == wxID_OK)
		{
			sel = dialog.GetSelection();
			//if(sel == 1)
			//{
			//	toIns = false;
			//}

			/* getting PAUP blocks from modeltest result file*/
			while(!modelOut.eof())
			{
				modelOut.getline(line, 2000);
				wxline = line;
				if(wxline.Contains("PAUP* Commands Block"))
				{
						modelOut.getline(line, 2000);
						wxline = line;
						do
						{
							if(wxline.Length() >= 1)
							{
								block.Add(wxline+"\n");
							}
							temp += wxline + "\n";
							modelOut.getline(line, 2000);
							wxline = line;
						}while(!wxline.Contains("END"));
						block.Add("END;\n");
						temp += "END;\n";
				}
			}
			HLRTblock = block[0]+block[1]+block[2]+block[3]+block[4]+block[5];
			AICblock = block[6]+block[7]+block[8]+block[9]+block[10]+block[11];
			if(BIC == true)
			{
				BICblock = block[6]+block[7]+block[8]+block[9]+block[10]+block[11];
			}
			modelOut.close();
			/*inserting block on nexus file*/
			string nexustr;
			nexustr = nexusFile;
			ifstream nex(nexustr.c_str());
			nexTemp = nexusFile + "temp";
			ofstream nexT(nexTemp);
			while(!nex.eof())
			{
				nex.getline(line, 2000);
				wxline = line;
				nexT << line << "\n";
			}
			if(sel == 0)
			{
				p1 = HLRTblock;
				nexT << p1 << "\n";
			}
			else if(sel == 1)
			{
				p2 = AICblock;
				nexT << p2 << "\n";
			}
			else if(sel == 2 && BIC == true)
			{
				p3 = BICblock;
				nexT << p3 << "\n";
			}
			else if(sel == 2 && BIC == false)
			{
				wxMessageBox("BIC analysis not available.\nPlease rerun ModelTest with this option enabled");
			}
			nexT << line << "\n";
			nex.close();
			nexT.close();
			remove(nexusFile);
			rename(nexTemp, nexusFile);
		}
	}
}