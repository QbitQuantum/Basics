/**
 * This function explore the normalization grammar to construct
 * the normalization tree. If the 'list' parameter is NULL, then we
 * are in the main call to the main graph; otherwise, we are within
 * a subgraph.
 */
void explore_normalization_fst2(Fst2* fst2,int current_state,
                                struct normalization_tree* node,
                                struct string_hash* tokens,const unichar* output,
                                const Alphabet* alph,struct norm_info** list) {
Fst2State state=fst2->states[current_state];
if (is_final_state(state)) {
   /* If we are in a final state, we behave differently if we are in a subgraph
    * or in the main call to the main graph. */
   if (list!=NULL) {
      (*list)=insert_in_norm_info_list(output,node,(*list));
   }
   else {
      node->outputs=sorted_insert(output,node->outputs);
   }
}
Transition* trans=state->transitions;
unichar tmp[1024];
while (trans!=NULL) {
   if (trans->tag_number<0) {
      /* Case of a subgraph call */
      struct norm_info* tmp_list=NULL;
      explore_normalization_fst2(fst2,fst2->initial_states[-(trans->tag_number)],node,
                                        tokens,output,alph,&tmp_list);
      while (tmp_list!=NULL) {
         /* We continue to explore the current graph */
         explore_normalization_fst2(fst2,trans->state_number,tmp_list->node,
                                        tokens,tmp_list->output,alph,list);
         struct norm_info* z=tmp_list;
         tmp_list=tmp_list->next;
         free_norm_info(z);
      }
   }
   else {
      /* If we have a normal transition */
      Fst2Tag tag=fst2->tags[trans->tag_number];
      u_strcpy(tmp,output);
      u_strcat(tmp," ");
      if (tag->output!=NULL && tag->output[0]!='\0' && u_strcmp(tag->output,"<E>") && !only_spaces(tag->output)) {
         /* We append the output if it exists and is not epsilon */
         u_strcat(tmp,tag->output);
      }
      if (!u_strcmp(tag->input,"<E>")) {
         /* If we have an epsilon transition, we go on in the fst2, but
          * we don't move in the normalization tree */
         explore_normalization_fst2(fst2,trans->state_number,node,tokens,tmp,alph,list);
      } else {
         /* If we have a normal transition, we explore all the tokens that match it */
         struct list_int* l=get_token_list_for_sequence(tag->input,alph,tokens);
         while (l!=NULL) {
            /* Then, we add a branch in the normalization tree for
             * each token. Note that it may introduce combinatory explosions
             * if the the fst2 matches large sequences */
            struct normalization_tree_transition* trans_norm;
            trans_norm=get_transition(l->n,node->trans);
            if (trans_norm==NULL) {
               /* If the transition does not exist in the tree, we create it */
               trans_norm=new_normalization_tree_transition(l->n,new_normalization_tree(),node->trans);
               node->trans=trans_norm;
            }
            explore_normalization_fst2(fst2,trans->state_number,trans_norm->node,
                                           tokens,tmp,alph,list);
            struct list_int* L=l;
            l=l->next;
            free(L);
         }
      }
   }
   trans=trans->next;
}
}