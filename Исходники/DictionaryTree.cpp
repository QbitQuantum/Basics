/**
 * This function moves outputs from final nodes to transitions leading to final nodes.
 */
static void subsequential_to_normal_transducer(struct dictionary_node* root,
		struct dictionary_node* node,
		struct string_hash* inf_codes,
		int pos,unichar* z,
		Ustring* normalizedOutput) {
struct dictionary_node_transition* tmp=node->trans;
int prefix_set=0;
Ustring* prefix=new_Ustring();
while (tmp!=NULL) {
	z[pos]=tmp->letter;
	z[pos+1]='\0';
	subsequential_to_normal_transducer(root,tmp->node,inf_codes,pos+1,z,normalizedOutput);
	/* First, if the destination state is final, we place its output on the output
	 * of the current transition */

	if (tmp->node->single_INF_code_list!=NULL) {
		//error("<%S>: output=<%S>\n",z,normalizedOutput->str);
		tmp->output=u_strdup(inf_codes->value[tmp->node->INF_code]);
	}
	if (normalizedOutput->len!=0) {
		/* Then, we add the normalized output obtained recursively, if any */
		//error("<%S>: moving normalized output <%S>\n",z,normalizedOutput->str);
		if (tmp->output==NULL) {
			tmp->output=u_strdup(normalizedOutput->str);
		} else {
			tmp->output=(unichar*)realloc(tmp->output,sizeof(unichar)*(1+normalizedOutput->len+u_strlen(tmp->output)));
		}
	}
	if (!prefix_set) {
		prefix_set=1;
		u_strcpy(prefix,tmp->output);
	} else {
		get_longest_common_prefix(prefix,tmp->output);
	}
	tmp=tmp->next;
}
if (node==root || node->single_INF_code_list!=NULL) {
	/* If we are in the initial state or a final one, we let the transitions as they are, since
	 * their outputs can not move more to the left */
	z[pos]='\0';
	free_Ustring(prefix);
	empty(normalizedOutput);
	return;
}
tmp=node->trans;
while (tmp!=NULL) {
	//error("prefix removal: <%S> => ",tmp->output);
	remove_prefix(prefix->len,tmp->output);
	//error("<%S>\n",tmp->output);
	tmp=tmp->next;
}
z[pos]='\0';
u_strcpy(normalizedOutput,prefix);
free_Ustring(prefix);
}