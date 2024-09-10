int lc_evpprintf(const lc_arg_env_t *env, lc_appendable_t *app, const char *fmt,
                 va_list args)
{
	(void)args;

	int         res  = 0;
	const char *last = fmt + strlen(fmt);

	/* Find the first % */
	const char *s = strchr(fmt, '%');

	/* Emit the text before the first % was found */
	size_t addlen = (s ? s : last) - fmt;
	lc_appendable_snadd(app, fmt, addlen);
	res += addlen;

	while (s != NULL) {
		lc_arg_value_t val;

		/* We must be at a '%' */
		assert(*s == '%');

		/* Reset the occurrence structure */
		lc_arg_occ_t occ;
		memset(&occ, 0, sizeof(occ));

		/* Eat all flags and set the corresponding flags in the occ struct */
		for (++s; strchr("#0-+", *s); ++s) {
			switch (*s) {
				case '#':
					occ.flag_hash = 1;
					break;
				case '0':
					occ.flag_zero = 1;
					break;
				case '-':
					occ.flag_minus = 1;
					break;
				case '+':
					occ.flag_plus = 1;
					break;
				case ' ':
					occ.flag_space = 1;
					break;
			}
		}

		/* Read the width if given */
		s = read_int(s, &occ.width);

		occ.precision = -1;

		/* read the precision if given */
		if (*s == '.') {
			int precision;
			s = read_int(s + 1, &precision);

			/* Negative or lacking precision after a '.' is treated as
			 * precision 0. */
			occ.precision = MAX(0, precision);
		}

		/*
		 * Now, we can either have:
		 * - a named argument like {node}
		 * - some modifiers followed by a conversion specifier
		 * - or some other character, which ends this format invalidly
		 */
		char            ch  = *s;
		const lc_arg_t *arg = NULL;
		switch (ch) {
			case '%':
				s++;
				lc_appendable_chadd(app, '%');
				++res;
				break;
			case '{': {
				const char *named = ++s;

				/* Read until the closing brace or end of the string. */
				for (ch = *s; ch != '}' && ch != '\0'; ch = *++s) {
				}

				if (s - named) {
					size_t n = s - named;
					char *name;
					lc_arg_t tmp;

					name = (char*) malloc(sizeof(char) * (n + 1));
					MEMCPY(name, named, n);
					name[n] = '\0';
					tmp.name = name;

					arg = set_find(lc_arg_t, env->args, &tmp, sizeof(tmp), hash_str(named));
					occ.modifier = "";
					occ.modifier_length = 0;

					/* Set the conversion specifier of the occurrence to the
					 * letter specified in the argument description. */
					if (arg)
						occ.conversion = arg->letter;

					free(name);

					/* If we ended with a closing brace, move the current
					 * pointer after it, since it is not to be dumped. */
					if (ch == '}')
						s++;
				}
				break;
			}

			default: {
				const char *mod = s;

				/* Read, as long there are letters */
				while (isalpha((unsigned char)ch) && !arg) {
					int              base = 'a';
					lc_arg_t *const *map  = env->lower;

					/* If uppercase, select the uppercase map from the
					 * environment */
					if (isupper((unsigned char)ch)) {
						base = 'A';
						map = env->upper;
					}

					if (map[ch - base] != NULL) {
						occ.modifier = mod;
						occ.modifier_length = s - mod;
						occ.conversion = ch;
						arg = map[ch - base];
					}

					ch = *++s;
				}
			}
		}

		/* Call the handler if an argument was determined */
		if (arg != NULL && arg->handler != NULL) {
			const lc_arg_handler_t *handler = arg->handler;

			/* Let the handler determine the type of the argument based on the
			 * information gathered. */
			occ.lc_arg_type = handler->get_lc_arg_type(&occ);

			/* Store the value according to argument information */
			switch (occ.lc_arg_type) {
#define LC_ARG_TYPE(type,name,va_type) \
			case lc_arg_type_ ## name: val.v_ ## name = va_arg(args, va_type); break;
#include "lc_printf_arg_types.def"
#undef LC_ARG_TYPE
			}

			/* Finally, call the handler. */
			res += handler->emit(app, &occ, &val);
		}

		const char *old = s;
		s = strchr(s, '%');
		size_t addlen = (s ? s : last) - old;
		lc_appendable_snadd(app, old, addlen);
		res += addlen;
	}

	return res;
}