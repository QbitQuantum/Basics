void CDropbox::RequestAccountInfo()
{
	HttpRequest *request = new HttpRequest(hNetlibUser, REQUEST_GET, DROPBOX_API_URL "/account/info");
	request->AddBearerAuthHeader(db_get_sa(NULL, MODULE, "TokenSecret"));
	mir_ptr<NETLIBHTTPREQUEST> response(request->Send());

	delete request;

	MCONTACT hContact = CDropbox::GetDefaultContact();

	if (response && response->resultCode == HTTP_STATUS_OK)
	{
		JSONROOT root(response->pData);
		if (root)
		{
			JSONNODE *node = json_get(root, "referral_link");
			if (node)
			{
				ptrW referral_link = ptrW(json_as_string(node));
				db_set_ws(hContact, MODULE, "Homepage", referral_link);
			}

			node = json_get(root, "display_name");
			if (node)
			{
				ptrW display_name = ptrW(json_as_string(node));
				wchar_t *sep = wcsrchr(display_name, L' ');
				if (sep)
				{
					db_set_ws(hContact, MODULE, "LastName", sep + 1);
					display_name[wcslen(display_name) - wcslen(sep)] = '\0';
					db_set_ws(hContact, MODULE, "FirstName", display_name);
				}
				else
				{
					db_set_ws(hContact, MODULE, "FirstName", display_name);
					db_unset(hContact, MODULE, "LastName");
				}
			}

			node = json_get(root, "country");
			if (node)
			{
				ptrW isocodeW(json_as_string(node));
				ptrA isocode(mir_u2a(isocodeW));

				if (!strlen(isocode))
					db_unset(hContact, MODULE, "Country");
				else
				{
					char *country = (char *)CallService(MS_UTILS_GETCOUNTRYBYISOCODE, (WPARAM)isocode, 0);
					db_set_s(hContact, MODULE, "Country", country);
				}
			}

			node = json_get(root, "quota_info");
			JSONNODE *nroot = json_as_node(node);
			if (nroot)
			{
				node = json_get(nroot, "shared");
				if (node)
					db_set_dw(hContact, MODULE, "SharedQuota", json_as_int(node));
				node = json_get(nroot, "normal");
				if (node)
					db_set_dw(hContact, MODULE, "NormalQuota", json_as_int(node));
				node = json_get(nroot, "quota");
				if (node)
					db_set_dw(hContact, MODULE, "TotalQuota", json_as_int(node));
			}
		}
	}

	HandleHttpResponseError(hNetlibUser, response);
}