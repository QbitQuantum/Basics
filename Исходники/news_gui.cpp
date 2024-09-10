	virtual void DrawWidget(const Rect &r, int widget) const
	{
		switch (widget) {
			case WID_N_CAPTION:
				DrawCaption(r, COLOUR_LIGHT_BLUE, this->owner, STR_NEWS_MESSAGE_CAPTION);
				break;

			case WID_N_PANEL:
				this->DrawNewsBorder(r);
				break;

			case WID_N_MESSAGE:
				CopyInDParam(0, this->ni->params, lengthof(this->ni->params));
				DrawStringMultiLine(r.left, r.right, r.top, r.bottom, this->ni->string_id, TC_FROMSTRING, SA_CENTER);
				break;

			case WID_N_MGR_FACE: {
				const CompanyNewsInformation *cni = (const CompanyNewsInformation*)this->ni->free_data;
				DrawCompanyManagerFace(cni->face, cni->colour, r.left, r.top);
				GfxFillRect(r.left, r.top, r.right, r.bottom, PALETTE_NEWSPAPER, FILLRECT_RECOLOUR);
				break;
			}
			case WID_N_MGR_NAME: {
				const CompanyNewsInformation *cni = (const CompanyNewsInformation*)this->ni->free_data;
				SetDParamStr(0, cni->president_name);
				DrawStringMultiLine(r.left, r.right, r.top, r.bottom, STR_JUST_RAW_STRING, TC_FROMSTRING, SA_CENTER);
				break;
			}
			case WID_N_COMPANY_MSG:
				DrawStringMultiLine(r.left, r.right, r.top, r.bottom, this->GetCompanyMessageString(), TC_FROMSTRING, SA_CENTER);
				break;

			case WID_N_VEH_BKGND:
				GfxFillRect(r.left, r.top, r.right, r.bottom, PC_GREY);
				break;

			case WID_N_VEH_NAME:
			case WID_N_VEH_TITLE:
				DrawStringMultiLine(r.left, r.right, r.top, r.bottom, this->GetNewVehicleMessageString(widget), TC_FROMSTRING, SA_CENTER);
				break;

			case WID_N_VEH_SPR: {
				assert(this->ni->reftype1 == NR_ENGINE);
				EngineID engine = this->ni->ref1;
				DrawVehicleEngine(r.left, r.right, (r.left + r.right) / 2, (r.top + r.bottom) / 2, engine, GetEnginePalette(engine, _local_company), EIT_PREVIEW);
				GfxFillRect(r.left, r.top, r.right, r.bottom, PALETTE_NEWSPAPER, FILLRECT_RECOLOUR);
				break;
			}
			case WID_N_VEH_INFO: {
				assert(this->ni->reftype1 == NR_ENGINE);
				EngineID engine = this->ni->ref1;
				DrawStringMultiLine(r.left, r.right, r.top, r.bottom, GetEngineInfoString(engine), TC_FROMSTRING, SA_CENTER);
				break;
			}
		}
	}