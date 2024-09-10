void
gamma_rate_mixture_summarize(
        arb_ptr rate_mix_prior, arb_ptr rate_mix_rates, arb_ptr rate_mix_expect,
        const gamma_rate_mixture_t x, enum rate_mixture_mode mode, slong prec)
{
    slong i;
    arb_ptr r;

    arb_t p, q;
    arb_init(p);
    arb_init(q);
    arb_set_d(p, x->invariable_prior);
    arb_sub_si(q, p, 1, prec);
    arb_neg(q, q);

    /* the expectation is designed to be 1 */
    arb_one(rate_mix_expect);

    /* probabilities corresponding to gamma rate categories */
    for (i = 0; i < x->gamma_categories; i++)
    {
        r = rate_mix_prior + i;
        arb_div_si(r, q, x->gamma_categories, prec);
    }

    /* optional probability corresponding to the invariable category */
    if (x->invariable_prior)
    {
        r = rate_mix_prior + x->gamma_categories;
        arb_set(r, p);
    }

    /* set the discretized gamma rates */
    {
        arb_t s;
        arb_init(s);
        arb_set_d(s, x->gamma_shape);
        if (mode == RATE_MIXTURE_GAMMA)
        {
            gamma_rates(
                    rate_mix_rates, x->gamma_categories, s, prec);
        }
        else if (mode == RATE_MIXTURE_GAMMA_MEDIAN)
        {
            normalized_median_gamma_rates(
                    rate_mix_rates, x->gamma_categories, s, prec);
        }
        else
        {
            abort(); /* assert */
        }
        arb_clear(s);
    }

    /* normalize the rates to account for a possible invariable category */
    for (i = 0; i < x->gamma_categories; i++)
    {
        r = rate_mix_rates + i;
        arb_div(r, r, q, prec);
    }

    arb_clear(p);
    arb_clear(q);
}