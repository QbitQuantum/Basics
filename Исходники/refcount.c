static void test_iface_refcnt(void)
{
    HRESULT hr;
    IDirectDraw  *DDraw1;
    IDirectDraw2 *DDraw2;
    IDirectDraw4 *DDraw4;
    IDirectDraw7 *DDraw7;
    IDirect3D7   *D3D7;
    IDirect3D3   *D3D3;
    IDirect3D2   *D3D2;
    IDirect3D    *D3D1;
    long ref;

    hr = pDirectDrawCreateEx(NULL, (void **) &DDraw7, &IID_IDirectDraw7, NULL);
    ok(hr == DD_OK || hr==DDERR_NODIRECTDRAWSUPPORT, "DirectDrawCreateEx returned: %lx\n", hr);
    if(!DDraw7)
    {
        trace("Couldn't create DDraw interface, skipping tests\n");
        return;
    }

    ref = getRefcount( (IUnknown *) DDraw7);
    ok(ref == 1, "Initial IDirectDraw7 reference count is %ld\n", ref);

    hr = IDirectDraw7_QueryInterface(DDraw7, &IID_IDirectDraw4, (void **) &DDraw4);
    ok(hr == DD_OK, "IDirectDraw7_QueryInterface returned %08lx\n", hr);
    hr = IDirectDraw7_QueryInterface(DDraw7, &IID_IDirectDraw2, (void **) &DDraw2);
    ok(hr == DD_OK, "IDirectDraw7_QueryInterf&ace returned %08lx\n", hr);
    hr = IDirectDraw7_QueryInterface(DDraw7, &IID_IDirectDraw, (void **) &DDraw1);
    ok(hr == DD_OK, "IDirectDraw7_QueryInterface returned %08lx\n", hr);

    /* All interfaces now have refcount 1! */
    ref = getRefcount( (IUnknown *) DDraw7);
    ok(ref == 1, "IDirectDraw7 reference count is %ld\n", ref);
    ref = getRefcount( (IUnknown *) DDraw7);
    ok(ref == 1, "IDirectDraw7 reference count is %ld\n", ref);
    ref = getRefcount( (IUnknown *) DDraw4);
    ok(ref == 1, "IDirectDraw4 reference count is %ld\n", ref);
    ref = getRefcount( (IUnknown *) DDraw2);
    ok(ref == 1, "IDirectDraw2 reference count is %ld\n", ref);
    ref = getRefcount( (IUnknown *) DDraw1);
    ok(ref == 1, "IDirectDraw reference count is %ld\n", ref);

    hr = IDirectDraw7_QueryInterface(DDraw7, &IID_IDirect3D7, (void **) &D3D7);
    ok(hr == DD_OK, "IDirectDraw7_QueryInterface returned %08lx\n", hr);

    /* Apparently IDirectDrawX and IDirect3DX are linked together */
    ref = getRefcount( (IUnknown *) D3D7);
    ok(ref == 2, "IDirect3D7 reference count is %ld\n", ref);
    ref = getRefcount( (IUnknown *) DDraw7);
    ok(ref == 2, "IDirectDraw7 reference count is %ld\n", ref);

    IDirectDraw7_AddRef(DDraw7);
    ref = getRefcount( (IUnknown *) D3D7);
    ok(ref == 3, "IDirect3D7 reference count is %ld\n", ref);
    ref = getRefcount( (IUnknown *) DDraw7);
    ok(ref == 3, "IDirectDraw7 reference count is %ld\n", ref);

    IDirect3D7_Release(D3D7);
    ref = getRefcount( (IUnknown *) D3D7);
    ok(ref == 2, "IDirect3D7 reference count is %ld\n", ref);
    ref = getRefcount( (IUnknown *) DDraw7);
    ok(ref == 2, "IDirectDraw7 reference count is %ld\n", ref);

    /* Can't get older d3d interfaces. WHY????? */
    hr = IDirectDraw7_QueryInterface(DDraw4, &IID_IDirect3D3, (void **) &D3D3);
    todo_wine ok(hr == E_NOINTERFACE, "IDirectDraw7_QueryInterface returned %08lx\n", hr);
    if(hr == DD_OK && D3D3) IDirect3D3_Release(D3D3);

    hr = IDirectDraw4_QueryInterface(DDraw4, &IID_IDirect3D3, (void **) &D3D3);
    todo_wine ok(hr == E_NOINTERFACE, "IDirectDraw4_QueryInterface returned %08lx\n", hr);
    if(hr == DD_OK && D3D3) IDirect3D3_Release(D3D3);

    hr = IDirectDraw7_QueryInterface(DDraw7, &IID_IDirect3D2, (void **) &D3D2);
    todo_wine ok(hr == E_NOINTERFACE, "IDirectDraw7_QueryInterface returned %08lx\n", hr);
    if(hr == DD_OK && D3D2) IDirect3D2_Release(D3D2);

    hr = IDirectDraw2_QueryInterface(DDraw2, &IID_IDirect3D2, (void **) &D3D2);
    todo_wine ok(hr == E_NOINTERFACE, "IDirectDraw2_QueryInterface returned %08lx\n", hr);
    if(hr == DD_OK && D3D2) IDirect3D2_Release(D3D2);

    hr = IDirectDraw7_QueryInterface(DDraw7, &IID_IDirect3D, (void **) &D3D1);
    todo_wine ok(hr == E_NOINTERFACE, "IDirectDraw7_QueryInterface returned %08lx\n", hr);
    if(hr == DD_OK && D3D1) IDirect3D_Release(D3D1);

    hr = IDirectDraw_QueryInterface(DDraw1, &IID_IDirect3D, (void **) &D3D1);
    todo_wine ok(hr == E_NOINTERFACE, "IDirectDraw_QueryInterface returned %08lx\n", hr);
    if(hr == DD_OK && D3D1) IDirect3D_Release(D3D1);

    hr = IDirect3D7_QueryInterface(D3D7, &IID_IDirect3D, (void **) &D3D1);
    todo_wine ok(hr == E_NOINTERFACE, "IDirect3D7_QueryInterface returned %08lx\n", hr);
    if(hr == DD_OK && D3D1) IDirect3D_Release(D3D1);

    /* Try an AddRef, it only affects the AddRefed interface */
    IDirectDraw4_AddRef(DDraw4);
    ref = getRefcount( (IUnknown *) DDraw7);
    ok(ref == 2, "IDirectDraw7 reference count is %ld\n", ref); /* <-- From the d3d query */
    ref = getRefcount( (IUnknown *) DDraw4);
    ok(ref == 2, "IDirectDraw4 reference count is %ld\n", ref); /* <-- The AddRef call */
    ref = getRefcount( (IUnknown *) DDraw2);
    ok(ref == 1, "IDirectDraw2 reference count is %ld\n", ref);
    ref = getRefcount( (IUnknown *) DDraw1);
    ok(ref == 1, "IDirectDraw reference count is %ld\n", ref);
    ref = getRefcount( (IUnknown *) D3D7);
    ok(ref == 2, "IDirect3D7 reference count is %ld\n", ref); /* <-- From the d3d query */
    IDirectDraw4_Release(DDraw4);

    /* Make sure that they are one object, not different ones */
    hr = IDirectDraw4_SetCooperativeLevel(DDraw4, GetDesktopWindow(), DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    ok(hr == DD_OK, "IDirectDraw4::SetCooperativeLevel returned %08lx\n", hr);
    /* After an window has been set, DDSCL_SETFOCUSWINDOW should return DDERR_HWNDALREADYSET, see the mode test */
    hr = IDirectDraw7_SetCooperativeLevel(DDraw7, NULL, DDSCL_SETFOCUSWINDOW);
    ok(hr == DDERR_HWNDALREADYSET, "IDirectDraw7::SetCooperativeLevel returned %08lx\n", hr);

    /* All done, release all interfaces */
    IDirectDraw7_Release(DDraw7);
    IDirectDraw4_Release(DDraw4);
    IDirectDraw2_Release(DDraw2);
    IDirectDraw_Release(DDraw1);
    IDirect3D7_Release(D3D7);
}