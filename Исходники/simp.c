/*
 * Having successfully marked some points for removal ("successfully" here
 * means that doing so did not force us to mark p->point), make a copy of
 * the pattern, and remove the marked points from it.
 */
static pattern *execute_removal(pattern *p)
{
  node *n, *m, *m_next;
  pattern *q;
  int i;

  q = copy_pattern(p);

  for ( i=0, n=p->first_node, m=q->first_node; n; n = n->next, m = m_next )
  {
    m_next = m->next;

    if ( n->simplify_data == SIMPL_MARKED )
    {
      UNLINK( m, q->first_node, q->last_node, next, prev );
      kill_node( m );
    }
    else
    {
      /*
       * Maintain a running count of how many nodes we DON'T remove,
       * so we can fix the nodecount after the dust settles.
       */
      i++;
    }
  }

  q->nodes = i;

  for ( i = 0, m = q->first_node; m; m = m->next )
    m->position = i++;

  return q;
}