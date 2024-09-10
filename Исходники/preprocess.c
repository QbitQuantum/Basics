static void handle_elif()
#endif
{
    if (iftop) {
        if (iftop->state == EXPECT_ELSE) {
            /* last cond was false... */
            int cond;
            ifstate_t *p = iftop;

            /* pop previous condition */
            iftop = p->next;
            FREE((char *) p);

#ifdef LEXER
            *--outp = '\0';
            add_input(sp);
#endif
            cond = cond_get_exp(0);
#ifdef LEXER
            if (*outp++) {
                yyerror("Condition too complex in #elif");
                while (*outp++);
#else
            if (*outp != '\n') {
                yyerror("Condition too complex in #elif");
#endif
            } else handle_cond(cond);
        } else {/* EXPECT_ENDIF */
            /*
             * last cond was true...skip to end of
             * conditional
             */
            skip_to("endif", (char *) 0);
        }
    } else {
        yyerrorp("Unexpected %celif");
    }
}

static void handle_else (void) {
    if (iftop) {
        if (iftop->state == EXPECT_ELSE) {
            iftop->state = EXPECT_ENDIF;
        } else {
            skip_to("endif", (char *) 0);
        }
    } else {
        yyerrorp("Unexpected %cendif");
    }
}

static void handle_endif (void) {
    if (iftop && (iftop->state == EXPECT_ENDIF ||
                  iftop->state == EXPECT_ELSE)) {
        ifstate_t *p = iftop;

        iftop = p->next;
        FREE((char *) p);
    } else {
        yyerrorp("Unexpected %cendif");
    }
}

#define BNOT   1
#define LNOT   2
#define UMINUS 3
#define UPLUS  4

#define MULT   1
#define DIV    2
#define MOD    3
#define BPLUS  4
#define BMINUS 5
#define LSHIFT 6
#define RSHIFT 7
#define LESS   8
#define LEQ    9
#define GREAT 10
#define GEQ   11
#define EQ    12
#define NEQ   13
#define BAND  14
#define XOR   15
#define BOR   16
#define LAND  17
#define LOR   18
#define QMARK 19

static char _optab[] =
{0, 4, 0, 0, 0, 26, 56, 0, 0, 0, 18, 14, 0, 10, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 50, 40, 74,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 70, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63, 0, 1};
static char optab2[] =
{BNOT, 0, 0, LNOT, '=', NEQ, 7, 0, 0, UMINUS, 0, BMINUS, 10, UPLUS, 0, BPLUS, 10,
 0, 0, MULT, 11, 0, 0, DIV, 11, 0, 0, MOD, 11,
 0, '<', LSHIFT, 9, '=', LEQ, 8, 0, LESS, 8, 0, '>', RSHIFT, 9, '=', GEQ, 8, 0, GREAT, 8,
 0, '=', EQ, 7, 0, 0, 0, '&', LAND, 3, 0, BAND, 6, 0, '|', LOR, 2, 0, BOR, 4,
 0, 0, XOR, 5, 0, 0, QMARK, 1};

#define optab1 (_optab-' ')

static int cond_get_exp (int priority)
{
    int c;
    int value, value2, x;

#ifdef LEXER
    do
        c = exgetc();
    while (is_wspace(c));
    if (c == '(') {
#else
    if ((c = exgetc()) == '(') {
#endif
        value = cond_get_exp(0);
#ifdef LEXER
        do
            c = exgetc();
        while (is_wspace(c));
        if (c != ')') {
            yyerror("bracket not paired in #if");
            if (!c) *--outp = '\0';
        }
#else
        if ((c = exgetc()) != ')') yyerrorp("bracket not paired in %cif");
#endif
    } else if (ispunct(c)) {
        if (!(x = optab1[c])) {
            yyerrorp("illegal character in %cif");
            return 0;
        }
        value = cond_get_exp(12);
        switch (optab2[x - 1]) {
        case BNOT:
            value = ~value;
            break;
        case LNOT:
            value = !value;
            break;
        case UMINUS:
            value = -value;
            break;
        case UPLUS:
            value = value;
            break;
        default:
            yyerrorp("illegal unary operator in %cif");
        }
    } else {
        int base;

        if (!isdigit(c)) {
#ifdef LEXER
            if (!c) {
#else
            if (c == '\n') {
#endif
                yyerrorp("missing expression in %cif");
            } else
                yyerrorp("illegal character in %cif");
            return 0;
        }
        value = 0;
        if (c != '0')
            base = 10;
        else {
            c = *outp++;
            if (c == 'x' || c == 'X') {
                base = 16;
                c = *outp++;
            } else
                base = 8;
        }
        for (;;) {
            if (isdigit(c))
                x = -'0';
            else if (isupper(c))
                x = -'A' + 10;
            else if (islower(c))
                x = -'a' + 10;
            else
                break;
            x += c;
            if (x > base)
                break;
            value = value * base + x;
            c = *outp++;
        }
        outp--;
    }
    for (;;) {
#ifdef LEXER
        do
            c = exgetc();
        while (is_wspace(c));
        if (!ispunct(c))
            break;
#else
        if (!ispunct(c = exgetc()))
            break;
#endif
        if (!(x = optab1[c]))
            break;
        value2 = *outp++;
        for (;; x += 3) {
            if (!optab2[x]) {
                outp--;
                if (!optab2[x + 1]) {
                    yyerrorp("illegal operator use in %cif");
                    return 0;
                }
                break;
            }
            if (value2 == optab2[x])
                break;
        }
        if (priority >= optab2[x + 2]) {
            if (optab2[x]) *--outp = value2;
            break;
        }
        value2 = cond_get_exp(optab2[x + 2]);
        switch (optab2[x + 1]) {
        case MULT:
            value *= value2;
            break;
        case DIV:
            if (value2)
                value /= value2;
            else
                yyerrorp("division by 0 in %cif");
            break;
        case MOD:
            if (value2)
                value %= value2;
            else
                yyerrorp("modulo by 0 in %cif");
            break;
        case BPLUS:
            value += value2;
            break;
        case BMINUS:
            value -= value2;
            break;
        case LSHIFT:
            value <<= value2;
            break;
        case RSHIFT:
            value >>= value2;
            break;
        case LESS:
            value = value < value2;
            break;
        case LEQ:
            value = value <= value2;
            break;
        case GREAT:
            value = value > value2;
            break;
        case GEQ:
            value = value >= value2;
            break;
        case EQ:
            value = value == value2;
            break;
        case NEQ:
            value = value != value2;
            break;
        case BAND:
            value &= value2;
            break;
        case XOR:
            value ^= value2;
            break;
        case BOR:
            value |= value2;
            break;
        case LAND:
            value = value && value2;
            break;
        case LOR:
            value = value || value2;
            break;
        case QMARK:
#ifdef LEXER
            do
                c = exgetc();
            while (isspace(c));
            if (c != ':') {
                yyerror("'?' without ':' in #if");
                outp--;
                return 0;
            }
#else
            if ((c = exgetc()) != ':') yyerrorp("'?' without ':' in %cif");
#endif
            if (value) {
                cond_get_exp(1);
                value = value2;
            } else
                value = cond_get_exp(1);
            break;
        }
    }
    outp--;
    return value;
}

static void
handle_cond (int c)
{
    ifstate_t *p;

    if (!c)
        skip_to("else", "endif");
    p = ALLOCATE(ifstate_t, TAG_COMPILER, "handle_cond");
    p->next = iftop;
    iftop = p;
    p->state = c ? EXPECT_ENDIF : EXPECT_ELSE;
}