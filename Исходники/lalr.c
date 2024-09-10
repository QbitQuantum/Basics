void build_relations(void)
{
  register int i;
  register int j;
  register int k;
  register short *rulep;
  register short *rp;
  register shifts *sp;
  register int length;
  register int nedges;
  register int done;
  register int state1;
  register int stateno;
  register int symbol1;
  register int symbol2;
  register short *shortp;
  register short *edge;
  register short *states;
  register short **new_includes;

  includes = NEW2(ngotos, short *);
  edge = NEW2(ngotos + 1, short);
  states = NEW2(maxrhs + 1, short);

  for (i = 0; i < ngotos; i++)
    {
      nedges = 0;
      state1 = from_state[i];
      symbol1 = accessing_symbol[to_state[i]];

      for (rulep = derives[symbol1]; *rulep >= 0; rulep++)
        {
          length = 1;
          states[0] = state1;
          stateno = state1;

          for (rp = ritem + rrhs[*rulep]; *rp >= 0; rp++)
            {
              symbol2 = *rp;
              sp = shift_table[stateno];
              k = sp->nshifts;

              for (j = 0; j < k; j++)
                {
                  stateno = sp->shift[j];
                  if (accessing_symbol[stateno] == symbol2) break;
                }

              states[length++] = stateno;
            }

          add_lookback_edge(stateno, *rulep, i);

          length--;
          done = 0;
          while (!done)
            {
              done = 1;
              rp--;
              if (ISVAR(*rp))
                {
                  stateno = states[--length];
                  edge[nedges++] = map_goto(stateno, *rp);
                  if (nullable[*rp] && length > 0) done = 0;
                }
            }
        }

      if (nedges)
        {
          includes[i] = shortp = NEW2(nedges + 1, short);
          for (j = 0; j < nedges; j++)
            shortp[j] = edge[j];
          shortp[nedges] = -1;
        }
    }

  new_includes = transpose(includes, ngotos);

  for (i = 0; i < ngotos; i++)
    if (includes[i])
      FREE(includes[i]);

  FREE(includes);

  includes = new_includes;

  FREE(edge);
  FREE(states);
}