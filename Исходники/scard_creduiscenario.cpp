		LRESULT OnUnhandled(const Context& context)
		{
			if (context.message == WM_USER+1)
			{
				auto consumer = scenario->monitor.getconsumer();
				auto readers = consumer.pop();
				for (auto& reader : readers)
				{
					if (reader.card.valid())
					{
						auto card = reader.card.get();
						for (auto& key : card.certificates)
						{
							unique_winerror winerror;

							PCCERT_CONTEXT certcontext = CertCreateCertificateContext(
								X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
								&key.cert[0],
								key.cert.size()
							);
							winerror = make_winerror_if(!certcontext);

							if (!winerror)
							{

								continue;
							}

							DWORD sizesubject = 0;
							std::wstring subjectname;
							for (bool getsize = true; ; getsize = false)
							{
								sizesubject = CertGetNameString(
									certcontext,
									CERT_ALT_NAME_RFC822_NAME,//CERT_NAME_FRIENDLY_DISPLAY_TYPE,
									0,
									NULL,
									getsize ? nullptr : &subjectname[0],
									sizesubject
								);
								if (sizesubject == 1)
								{
									break;
								}
								if (getsize)
								{
									subjectname.resize(sizesubject - 1);
								}
								else
								{
									break;
								}
							}
						}
					}
				}
				return 0;
			}
			return DefWindowProc(context.window, context.message, context.wParam, context.lParam);
		}