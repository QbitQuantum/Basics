void test_encode(void **state)
{
    int ret;
    struct berval *resp_val;
    struct ipa_extdom_ctx *ctx;
    struct test_data *test_data;

    test_data = (struct test_data *) *state;
    ctx = test_data->ctx;

    ctx->max_nss_buf_size = (128*1024*1024);

    ret = pack_ber_sid(TEST_SID, &resp_val);
    assert_int_equal(ret, LDAP_SUCCESS);
    assert_int_equal(sizeof(res_sid), resp_val->bv_len);
    assert_memory_equal(res_sid, resp_val->bv_val, resp_val->bv_len);
    ber_bvfree(resp_val);

    ret = pack_ber_name(TEST_DOMAIN_NAME, "test", &resp_val);
    assert_int_equal(ret, LDAP_SUCCESS);
    assert_int_equal(sizeof(res_nam), resp_val->bv_len);
    assert_memory_equal(res_nam, resp_val->bv_val, resp_val->bv_len);
    ber_bvfree(resp_val);

    ret = pack_ber_user(ctx, RESP_USER, TEST_DOMAIN_NAME, "test", 12345, 54321,
                        NULL, NULL, NULL, NULL, &resp_val);
    assert_int_equal(ret, LDAP_SUCCESS);
    assert_int_equal(sizeof(res_uid), resp_val->bv_len);
    assert_memory_equal(res_uid, resp_val->bv_val, resp_val->bv_len);
    ber_bvfree(resp_val);

    ret = pack_ber_group(RESP_GROUP, TEST_DOMAIN_NAME, "test_group", 54321,
                         NULL, NULL, &resp_val);
    assert_int_equal(ret, LDAP_SUCCESS);
    assert_int_equal(sizeof(res_gid), resp_val->bv_len);
    assert_memory_equal(res_gid, resp_val->bv_val, resp_val->bv_len);
    ber_bvfree(resp_val);
}