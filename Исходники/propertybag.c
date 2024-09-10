static void test_propertybag_read(IPropertyBag2 *property)
{
    HRESULT hr;
    PROPBAG2 options[3] = {{0}};
    VARIANT values[3];
    HRESULT itm_hr[3] = {S_OK, S_OK, S_OK};

    /* 1. One unknown property */
    options[0].pstrName = (LPOLESTR)wszTestInvalidProperty;
    hr = IPropertyBag2_Read(property, 1, options, NULL, values, itm_hr);
    ok(hr == E_FAIL,
       "Read for an unknown property did not fail with expected code, hr=%x\n", hr);

    /* 2. One known property */
    options[0].pstrName = (LPOLESTR)wszTestProperty1;
    itm_hr[0] = E_FAIL;
    hr = IPropertyBag2_Read(property, 1, options, NULL, values, itm_hr);
    ok(hr == S_OK, "Read failed, hr=%x\n", hr);
    if (SUCCEEDED(hr))
    {
        ok(itm_hr[0] == S_OK,
           "Read failed, itm_hr[0]=%x\n", itm_hr[0]);
        ok(V_VT(&values[0]) == VT_UI1,
           "Read failed, V_VT(&values[0])=%x\n", V_VT(&values[0]));
        ok(V_UNION(&values[0], bVal) == 12,
           "Read failed, &values[0]=%i\n", V_UNION(&values[0], bVal));

        VariantClear(&values[0]);
    }

    /* 3. Two known properties */
    options[0].pstrName = (LPOLESTR)wszTestProperty1;
    options[1].pstrName = (LPOLESTR)wszTestProperty2;
    itm_hr[0] = E_FAIL;
    itm_hr[1] = E_FAIL;
    hr = IPropertyBag2_Read(property, 2, options, NULL, values, itm_hr);
    ok(hr == S_OK, "Read failed, hr=%x\n", hr);
    if (SUCCEEDED(hr))
    {
        ok(itm_hr[0] == S_OK, "Read failed, itm_hr[0]=%x\n", itm_hr[0]);
        ok(V_VT(&values[0]) == VT_UI1, "Read failed, V_VT(&values[0])=%x\n", V_VT(&values[0]));
        ok(V_UNION(&values[0], bVal) == 12, "Read failed, &values[0]=%i\n", V_UNION(&values[0], bVal));

        ok(itm_hr[1] == S_OK, "Read failed, itm_hr[1]=%x\n", itm_hr[1]);
        ok(V_VT(&values[1]) == VT_R4, "Read failed, V_VT(&values[1])=%x\n", V_VT(&values[1]));
        ok(V_UNION(&values[1], fltVal) == (float)3.14, "Read failed, &values[1]=%f\n", V_UNION(&values[1], fltVal));

        VariantClear(&values[0]);
        VariantClear(&values[1]);
    }


    /* 4. One unknown property between two valid */

    /* Exotic initializations so we can detect what is unchanged */
    itm_hr[0] = -1; itm_hr[1] = -1; itm_hr[2] = -1;
    V_VT(&values[0]) = VT_NULL;
    V_VT(&values[1]) = VT_NULL;
    V_VT(&values[2]) = VT_NULL;
    V_UNION(&values[0], bVal) = 254;
    V_UNION(&values[1], bVal) = 254;
    V_UNION(&values[2], bVal) = 254;

    options[0].pstrName = (LPOLESTR)wszTestProperty1;
    options[1].pstrName = (LPOLESTR)wszTestInvalidProperty;
    options[2].pstrName = (LPOLESTR)wszTestProperty2;

    hr = IPropertyBag2_Read(property, 3, options, NULL, values, itm_hr);
    ok(hr == E_FAIL, "Read failed, hr=%x\n", hr);
    if (hr == E_FAIL)
    {
        ok(itm_hr[0] == S_OK, "Read error code has unexpected value, itm_hr[0]=%x\n", itm_hr[0]);
        ok(itm_hr[1] == -1,   "Read error code has unexpected value, itm_hr[1]=%x\n", itm_hr[1]);
        ok(itm_hr[2] == -1,   "Read error code has unexpected value, itm_hr[2]=%x\n", itm_hr[2]);

        ok(V_VT(&values[0]) == VT_UI1,  "Read variant has unexpected type, V_VT(&values[0])=%x\n", V_VT(&values[0]));
        ok(V_VT(&values[1]) == VT_NULL, "Read variant has unexpected type, V_VT(&values[1])=%x\n", V_VT(&values[1]));
        ok(V_VT(&values[2]) == VT_NULL, "Read variant has unexpected type, V_VT(&values[2])=%x\n", V_VT(&values[2]));

        ok(V_UNION(&values[0], bVal) == 12,  "Read variant has unexpected value, V_UNION(&values[0])=%i\n", V_UNION(&values[0], bVal));
        ok(V_UNION(&values[1], bVal) == 254, "Read variant has unexpected value, V_UNION(&values[1])=%i\n", V_UNION(&values[1], bVal));
        ok(V_UNION(&values[2], bVal) == 254, "Read variant has unexpected value, V_UNION(&values[2])=%i\n", V_UNION(&values[2], bVal));
    }
}