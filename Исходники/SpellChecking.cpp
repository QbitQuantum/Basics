/**
 * Explores the given dictionary to match the given word.
 */
static void explore_dic(int offset,unichar* word,int pos_word,Dictionary* d,SpellCheckConfig* cfg,
		Ustring* output,SpellCheckHypothesis* *list,int base,Ustring* inflected) {
int original_offset=offset;
int original_base=base;
int final,n_transitions,inf_code;
int z=save_output(output);
int size_pairs=cfg->pairs->nbelems;
offset=read_dictionary_state(d,offset,&final,&n_transitions,&inf_code);
if (final) {
	if (word[pos_word]=='\0') {
		/* If we have a match */
		deal_with_matches(d,inflected->str,inf_code,output,cfg,base,list);
	}
	base=output->len;
}
/* If we are at the end of the token, then we stop */
if (word[pos_word]=='\0') {
	return;
}
unsigned int l2=inflected->len;
unichar c;
int dest_offset;
for (int i=0;i<n_transitions;i++) {
	restore_output(z,output);
	offset=read_dictionary_transition(d,offset,&c,&dest_offset,output);
	/* For backup_output, see comment below */
	int backup_output=save_output(output);
	if (c==word[pos_word] || word[pos_word]==u_toupper(c)) {
		u_strcat(inflected,c);
		explore_dic(dest_offset,word,pos_word+1,d,cfg,output,list,base,inflected);
	} else {
		/* We deal with the SP_SWAP case, made of 2 SP_CHANGE_XXX */
		if (cfg->current_errors!=cfg->max_errors && cfg->current_SP_SWAP!=cfg->max_SP_SWAP
				&& is_letter_swap(cfg,word,pos_word,inflected,c)) {
			/* We don't modify the number of errors since we override an existing
			 * SP_CHANGE_XXX one */
			cfg->current_SP_SWAP++;
			/* We override the previous change */
			int a=cfg->pairs->tab[cfg->pairs->nbelems-2];
			int b=cfg->pairs->tab[cfg->pairs->nbelems-1];
			cfg->pairs->tab[cfg->pairs->nbelems-2]=pos_word-1;
			cfg->pairs->tab[cfg->pairs->nbelems-1]=SP_SWAP_DEFAULT;
			u_strcat(inflected,c);
			explore_dic(dest_offset,word,pos_word+1,d,cfg,output,list,base,inflected);
			cfg->pairs->tab[cfg->pairs->nbelems-2]=a;
			cfg->pairs->tab[cfg->pairs->nbelems-1]=b;
			cfg->current_SP_SWAP--;
		} else /* We deal with the SP_CHANGE case */
		       if (cfg->current_errors!=cfg->max_errors && cfg->current_SP_CHANGE!=cfg->max_SP_CHANGE
				/* We want letters, not spaces or anything else */
				&& is_letter(c,NULL)
		        /* We do not allow the replacement of a lowercase letter by an uppercase
		         * letter at the beginning of the word like Niserable, unless the whole word
		         * is in uppercase or the letter is the same, module the case */
		        && (cfg->allow_uppercase_initial || pos_word>0 || (!is_upper(word[0],NULL) || is_upper(word[1],NULL) || word[0]==u_toupper(c)))) {
			cfg->current_errors++;
			cfg->current_SP_CHANGE++;
			/* Now we test all possible kinds of change */
			vector_int_add(cfg->pairs,pos_word);
			u_strcat(inflected,c);
			/* We always add the default case */
			vector_int_add(cfg->pairs,SP_CHANGE_DEFAULT);
			int n_elem=cfg->pairs->nbelems;
			explore_dic(dest_offset,word,pos_word+1,d,cfg,output,list,base,inflected);
			/* Then we test the accent case */
			if (u_deaccentuate(c)==u_deaccentuate(word[pos_word])) {
				/* After a call to explore_dic, we must restore the output.
				 * But, when dealing with SP_CHANGE_XXX ops, we must restore the
				 * output including the output associated to the current transition,
				 * which is why we don't use z (output before the current transition)
				 * but backup_output */
				restore_output(backup_output,output);
			    cfg->pairs->nbelems=n_elem;
			    cfg->pairs->tab[cfg->pairs->nbelems-1]=SP_CHANGE_DIACRITIC;
			    explore_dic(dest_offset,word,pos_word+1,d,cfg,output,list,base,inflected);
			}
			/* And the case variations */
			if (u_tolower(c)==u_tolower(word[pos_word])) {
			    restore_output(backup_output,output);
			    cfg->pairs->nbelems=n_elem;
				cfg->pairs->tab[cfg->pairs->nbelems-1]=SP_CHANGE_CASE;
				explore_dic(dest_offset,word,pos_word+1,d,cfg,output,list,base,inflected);
			}
			/* And finally the position on keyboard */
			if (areCloseOnKeyboard(c,word[pos_word],cfg->keyboard)) {
			    restore_output(backup_output,output);
			    cfg->pairs->nbelems=n_elem;
				cfg->pairs->tab[cfg->pairs->nbelems-1]=SP_CHANGE_KEYBOARD;
				explore_dic(dest_offset,word,pos_word+1,d,cfg,output,list,base,inflected);
			}
			cfg->pairs->nbelems=size_pairs;
			cfg->current_errors--;
			cfg->current_SP_CHANGE--;
			/* End of the SP_CHANGE case */
		}
	}
    restore_output(backup_output,output);
	truncate(inflected,l2);
	/* Now we deal with the SP_SUPPR case */
	if (cfg->current_errors!=cfg->max_errors && cfg->current_SP_SUPPR!=cfg->max_SP_SUPPR
		/* We want letters, not spaces or anything else */
		&& is_letter(c,NULL)) {
		cfg->current_errors++;
		cfg->current_SP_SUPPR++;
		vector_int_add(cfg->pairs,pos_word);
		if (pos_word>=1 && c==word[pos_word-1]) {
			vector_int_add(cfg->pairs,SP_SUPPR_DOUBLE);
		} else {
			vector_int_add(cfg->pairs,SP_SUPPR_DEFAULT);
		}
		u_strcat(inflected,c);
		explore_dic(dest_offset,word,pos_word,d,cfg,output,list,original_base,inflected);
		truncate(inflected,l2);
		cfg->pairs->nbelems=size_pairs;
		cfg->current_errors--;
		cfg->current_SP_SUPPR--;
	}
}
restore_output(z,output);
/* Finally, we deal with the SP_INSERT case, by calling again the current
 * function with the same parameters, except pos_word that will be increased of 1 */
if (cfg->current_errors!=cfg->max_errors && cfg->current_SP_INSERT!=cfg->max_SP_INSERT
	/* We want letters, not spaces or anything else */
	&& is_letter(word[pos_word],NULL)
	/* We do not allow the insertion of a capital letter at the beginning of
	 * the word like Astreet, unless the whole word is in uppercase like ASTREET */
    && (cfg->allow_uppercase_initial || pos_word>0 || (!is_upper(word[0],NULL) || is_upper(word[1],NULL)))) {
	cfg->current_errors++;
	cfg->current_SP_INSERT++;
	vector_int_add(cfg->pairs,pos_word);
	if (pos_word>=1 && word[pos_word]==word[pos_word-1]) {
		vector_int_add(cfg->pairs,SP_INSERT_DOUBLE);
	} else {
		vector_int_add(cfg->pairs,SP_INSERT_DEFAULT);
	}
	explore_dic(original_offset,word,pos_word+1,d,cfg,output,list,original_base,inflected);
	truncate(inflected,l2);
	cfg->pairs->nbelems=size_pairs;
	cfg->current_errors--;
	cfg->current_SP_INSERT--;
}
/* Finally, we restore the output as it was when we enter the function */
restore_output(z,output);
}