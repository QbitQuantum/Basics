/**
 * Adds a match to the global list of matches. The function takes into
 * account the match policy. For instance, we don't take [2;3] into account
 * if we are in longest match mode and if we already have [2;5].
 *
 * This function is derived from the 'add_match' one in 'Matches.cpp', but it differs because
 * in Locate, we know exactly where we are in the text, so that we can filter matches easily. When
 * exploring a text automaton, it's not so easy to sort matches, because the state from where we
 * started the match may correspond to a position in text lower than the one of a previous match.
 *
 * IMPORTANT: 'e' is to be copied if the corresponding match must be added to the list
 */
struct tfst_simple_match_list* add_element_to_list(struct locate_tfst_infos* p,struct tfst_simple_match_list* list,struct tfst_simple_match_list* e) {
if (list==NULL) {
	/* We can always add a match to the empty list */
	return new_tfst_simple_match_list(e,NULL);
}
switch (compare_matches(&(list->m),&(e->m))) {
   case A_BEFORE_B:
   case A_BEFORE_B_OVERLAP: {
	   /* If the candidate starts after the end of the current match, then we have to go on,
	    * no matter the mode (shortest, longest or all matches) */
	   list->next=add_element_to_list(p,list->next,e);
	   return list;
   }

   case A_INCLUDES_B: {
	   if (p->match_policy==SHORTEST_MATCHES) {
		   /* e must replace the current match in the list */
		   replace_match(list,e);
		   return list;
	   } else if (p->match_policy==LONGEST_MATCHES) {
		   /* Our match is shorter than a match in the list, we discard it */
		   return list;
	   } else {
		   list->next=add_element_to_list(p,list->next,e);
		   return list;
	   }
   }

   case A_EQUALS_B: {
	   /* In any mode we replace the existing match by the new one, except if we allow
	    * ambiguous outputs */
	   if (u_strcmp(list->output,e->output)) {
		   if (p->ambiguous_output_policy==ALLOW_AMBIGUOUS_OUTPUTS) {
			   list=new_tfst_simple_match_list(e,list);
			   return list;
		   } else {
				/* If we don't allow ambiguous outputs, we have to print an error message */
				error("Unexpected ambiguous outputs:\n<%S>\n<%S>\n",list->output,e->output);
		   }
	   }
	   replace_match(list,e);
	   return list;
   }

   case B_INCLUDES_A: {
	   if (p->match_policy==SHORTEST_MATCHES) {
		   /* Our match is longer than a match in the list, we discard it */
		   return list;
   	   } else if (p->match_policy==LONGEST_MATCHES) {
   		   /* e must replace the current match in the list */
   		   replace_match(list,e);
   		   return list;
   	   } else {
   		   list->next=add_element_to_list(p,list->next,e);
   		   return list;
   	   }
   }

   case A_AFTER_B:
   case A_AFTER_B_OVERLAP: {
	   /* If the candidate ends before the start of the current match, then we have to insert it
	    * no matter the mode (shortest, longest or all matches) */
	   list=new_tfst_simple_match_list(e,list);
	   return list;
   }
}
/* Should not arrive here */
return NULL;
}