static void test_properties(void)
{
    HINTERACTIONCONTEXT context;
    UINT32 value;
    HRESULT hr;

    hr = CreateInteractionContext(&context);
    ok(hr == S_OK, "Failed to create context, hr %#x.\n", hr);

    hr = GetPropertyInteractionContext(context, INTERACTION_CONTEXT_PROPERTY_FILTER_POINTERS, &value);
    ok(hr == S_OK, "Failed to get property, hr %#x.\n", hr);
    ok(value == TRUE, "Got unexpected value %#x.\n", value);

    hr = SetPropertyInteractionContext(context, INTERACTION_CONTEXT_PROPERTY_FILTER_POINTERS, TRUE);
    ok(hr == S_OK, "Failed to set property, hr %#x.\n", hr);
    hr = GetPropertyInteractionContext(context, INTERACTION_CONTEXT_PROPERTY_FILTER_POINTERS, &value);
    ok(hr == S_OK, "Failed to get property, hr %#x.\n", hr);
    ok(value == TRUE, "Got unexpected value %#x.\n", value);

    hr = SetPropertyInteractionContext(context, INTERACTION_CONTEXT_PROPERTY_FILTER_POINTERS, FALSE);
    ok(hr == S_OK, "Failed to set property, hr %#x.\n", hr);
    hr = GetPropertyInteractionContext(context, INTERACTION_CONTEXT_PROPERTY_FILTER_POINTERS, &value);
    ok(hr == S_OK, "Failed to get property, hr %#x.\n", hr);
    ok(value == FALSE, "Got unexpected value %#x.\n", value);

    hr = SetPropertyInteractionContext(context, INTERACTION_CONTEXT_PROPERTY_FILTER_POINTERS, 2);
    ok(hr == E_INVALIDARG, "Got hr %#x.\n", hr);
    hr = SetPropertyInteractionContext(context, INTERACTION_CONTEXT_PROPERTY_FILTER_POINTERS, 3);
    ok(hr == E_INVALIDARG, "Got hr %#x.\n", hr);

    hr = SetPropertyInteractionContext(context, 0xdeadbeef, 0);
    ok(hr == E_INVALIDARG, "Got hr %#x.\n", hr);
    hr = GetPropertyInteractionContext(context, 0xdeadbeef, &value);
    ok(hr == E_INVALIDARG, "Got hr %#x.\n", hr);

    hr = GetPropertyInteractionContext(context, INTERACTION_CONTEXT_PROPERTY_FILTER_POINTERS, NULL);
    ok(hr == E_POINTER, "Got hr %#x.\n", hr);

    hr = SetPropertyInteractionContext(NULL, INTERACTION_CONTEXT_PROPERTY_FILTER_POINTERS, FALSE);
    ok(hr == E_HANDLE, "Got hr %#x.\n", hr);
    hr = GetPropertyInteractionContext(NULL, INTERACTION_CONTEXT_PROPERTY_FILTER_POINTERS, &value);
    ok(hr == E_HANDLE, "Got hr %#x.\n", hr);

    hr = DestroyInteractionContext(context);
    ok(hr == S_OK, "Failed to destroy context, hr %#x.\n", hr);
}