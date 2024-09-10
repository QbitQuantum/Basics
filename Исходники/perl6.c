static void
findPerl6Tags (void)
{
    struct p6Ctx ctx;

#define RESET_TOKENS() do { ctx.n_tokens = 0; } while (0)

#define PUSH_TOKEN(_t_) do {                                            \
    if (ctx.n_tokens < ARRAY_SIZE(ctx.tokens)) {			\
        ctx.tokens[ ctx.n_tokens ] = _t_;                               \
        ++ctx.n_tokens;                                                 \
    } else {                                                            \
        Assert(!"Token stack overflown: this is quite odd");            \
        RESET_TOKENS();                                                 \
    }                                                                   \
} while (0)

    initP6Ctx(&ctx);

    const char *s;
    int len;

    while ((len = getNonSpaceStr(&ctx, &s)) > 0) {
        enum token token = matchToken(s, len);
        if ((int) token >= 0) {
            PUSH_TOKEN(token);
        } else if (ctx.n_tokens > 0) {
            possiblyMakeTag(&ctx, s, len);
            RESET_TOKENS();
        }
    }

    deinitP6Ctx(&ctx);
}