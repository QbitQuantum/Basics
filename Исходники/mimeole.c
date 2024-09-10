static void test_BodyDeleteProp(void)
{
    static const char topic[] = "wine topic";
    HRESULT hr;
    IMimeMessage *msg;
    IMimeBody *body;
    PROPVARIANT prop;

    hr = MimeOleCreateMessage(NULL, &msg);
    ok(hr == S_OK, "ret %08x\n", hr);

    PropVariantInit(&prop);

    hr = IMimeMessage_BindToObject(msg, HBODY_ROOT, &IID_IMimeBody, (void**)&body);
    ok(hr == S_OK, "ret %08x\n", hr);

    hr = IMimeBody_DeleteProp(body, "Subject");
    ok(hr == MIME_E_NOT_FOUND, "ret %08x\n", hr);

    hr = IMimeBody_DeleteProp(body, PIDTOSTR(PID_HDR_SUBJECT));
    ok(hr == MIME_E_NOT_FOUND, "ret %08x\n", hr);

    prop.vt = VT_LPSTR;
    prop.u.pszVal = CoTaskMemAlloc(strlen(topic)+1);
    strcpy(prop.u.pszVal, topic);
    hr = IMimeBody_SetProp(body, "Subject", 0, &prop);
    ok(hr == S_OK, "ret %08x\n", hr);
    PropVariantClear(&prop);

    hr = IMimeBody_DeleteProp(body, "Subject");
    ok(hr == S_OK, "ret %08x\n", hr);

    hr = IMimeBody_GetProp(body, "Subject", 0, &prop);
    ok(hr == MIME_E_NOT_FOUND, "ret %08x\n", hr);

    prop.vt = VT_LPSTR;
    prop.u.pszVal = CoTaskMemAlloc(strlen(topic)+1);
    strcpy(prop.u.pszVal, topic);
    hr = IMimeBody_SetProp(body, PIDTOSTR(PID_HDR_SUBJECT), 0, &prop);
    ok(hr == S_OK, "ret %08x\n", hr);
    PropVariantClear(&prop);

    hr = IMimeBody_DeleteProp(body, PIDTOSTR(PID_HDR_SUBJECT));
    ok(hr == S_OK, "ret %08x\n", hr);

    hr = IMimeBody_GetProp(body, PIDTOSTR(PID_HDR_SUBJECT), 0, &prop);
    ok(hr == MIME_E_NOT_FOUND, "ret %08x\n", hr);

    IMimeBody_Release(body);
    IMimeMessage_Release(msg);
}