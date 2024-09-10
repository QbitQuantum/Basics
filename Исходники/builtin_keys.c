void
init_builtin_keys(int *key_mode)
{
	key_conf_t *curr;

	assert(key_mode != NULL);

	mode = key_mode;

	curr = add_cmd(L":", NORMAL_MODE);
	curr->data.handler = keys_colon;

	curr = add_cmd(L"m", NORMAL_MODE);
	curr->type = BUILTIN_WAIT_POINT;
	curr->data.handler = keys_m;
	curr->followed = FOLLOWED_BY_MULTIKEY;

	curr = add_cmd(L"'", NORMAL_MODE);
	curr->type = BUILTIN_WAIT_POINT;
	curr->data.handler = keys_quote;
	curr->followed = FOLLOWED_BY_MULTIKEY;

	curr = add_selector(L"gg", NORMAL_MODE);
	curr->type = BUILTIN_WAIT_POINT;
	curr->data.handler = keys_gg;
	curr->followed = FOLLOWED_BY_NONE;

	curr = add_selector(L"'", NORMAL_MODE);
	curr->type = BUILTIN_WAIT_POINT;
	curr->data.handler = keys_quote;
	curr->followed = FOLLOWED_BY_MULTIKEY;

	curr = add_cmd(L"H", NORMAL_MODE);
	curr->data.handler = keys_H;

	curr = add_cmd(L"gu", NORMAL_MODE);
	curr->data.handler = keys_gu;
	curr->followed = FOLLOWED_BY_SELECTOR;
	curr->type = BUILTIN_WAIT_POINT;

	curr = add_cmd(L"guu", NORMAL_MODE);
	curr->data.handler = keys_gu;

	curr = add_cmd(L"gugu", NORMAL_MODE);
	curr->data.handler = keys_gu;

	curr = add_cmd(L"j", NORMAL_MODE);
	curr->data.handler = keys_j;

	curr = add_selector(L"j", NORMAL_MODE);
	curr->data.handler = keys_j;

	curr = add_cmd(L"j", VISUAL_MODE);
	curr->data.handler = keys_j;

	curr = add_selector(L"j", VISUAL_MODE);
	curr->data.handler = keys_j;

	curr = add_cmd(L"k", NORMAL_MODE);
	curr->data.handler = keys_k;

	curr = add_selector(L"k", NORMAL_MODE);
	curr->data.handler = keys_k;

	curr = add_cmd(L"k", VISUAL_MODE);
	curr->data.handler = keys_k;

	curr = add_selector(L"k", VISUAL_MODE);
	curr->data.handler = keys_k;

	curr = add_selector(L"s", NORMAL_MODE);
	curr->data.handler = keys_s;

	curr = add_selector(L"s", VISUAL_MODE);
	curr->data.handler = keys_s;

	curr = add_cmd(L"i", NORMAL_MODE);
	curr->data.handler = keys_i;

	curr = add_selector(L"if", NORMAL_MODE);
	curr->data.handler = keys_if;

	curr = add_selector(L"if", VISUAL_MODE);
	curr->data.handler = keys_if;

	curr = add_cmd(L"o", NORMAL_MODE);
	curr->type = BUILTIN_CMD;
	curr->data.cmd = wcsdup(L":only");

	curr = add_cmd(L"v", NORMAL_MODE);
	curr->type = BUILTIN_CMD;
	curr->data.cmd = wcsdup(L":vsplit");

	curr = add_cmd(L"<", NORMAL_MODE);
	curr->type = BUILTIN_NIM_KEYS;
	curr->data.handler = keys_ctrl_w_less_than;

	curr = add_cmd(L"d", NORMAL_MODE);
	curr->type = BUILTIN_WAIT_POINT;
	curr->data.handler = keys_delete_selector;
	curr->followed = FOLLOWED_BY_SELECTOR;

	curr = add_cmd(L"dd", NORMAL_MODE);
	curr->data.handler = keys_delete;
	curr->type = BUILTIN_NIM_KEYS;

	curr = add_cmd(L"v", NORMAL_MODE);
	curr->data.handler = keys_v;

	curr = add_cmd(L"v", VISUAL_MODE);
	curr->data.handler = keys_v;

	curr = add_cmd(L"ZQ", NORMAL_MODE);
	curr->data.handler = keys_quit;

	curr = add_cmd(L"ZZ", NORMAL_MODE);
	curr->data.handler = keys_quit;

	curr = add_cmd(L"ZZ", VISUAL_MODE);
	curr->data.handler = keys_quit;

	curr = add_cmd(L"norm", NORMAL_MODE);
	curr->data.handler = keys_norm;
}