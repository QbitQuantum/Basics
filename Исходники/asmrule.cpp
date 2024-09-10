/* 
 * this must be thread safe . no global, no static.
 *           return value  next symbol : success
 *                              S_NULL : end
 *                             S_ERROR : error
 *  forereading is not necessary , so do not do it.
 */
static int get_sym(struct c_desc *cd)
{
    char *p;
    int len;
    int val;
  
    /* skip white space */
    while(*cd->cur_p == ' ') cd->cur_p++;
  
    if(*cd->cur_p == '$') { /* $Foobar */
	p = cd->cur_p + 1;
	while(isalpha(*p)) p++;
	len = p - cd->cur_p - 1;
    
	if(cd->id_len < len + 1) {
	    cd->id = (char *)xrealloc(cd->id,len + 1);
	    cd->id_len = len + 1;
	}
	memcpy(cd->id,cd->cur_p + 1,len);
	cd->id[len] = '\0';
	cd->cur_p = p;
	cd->op = S_ID;
    }
    else if(isdigit(*cd->cur_p)) {
	val = 0;
	while(isdigit(*cd->cur_p)) { /* always decimal */
	    val *= 10;
	    val += *cd->cur_p - '0';
	    cd->cur_p++;
	}
	cd->op = S_NUM;
	cd->val = val;
    }
    else if(*cd->cur_p == '<') {
	cd->cur_p++;
	if(*cd->cur_p == '=') {
	    cd->cur_p++;
	    cd->op = S_LESSEQ;
	}
	else {
	    cd->op = S_LESS;
	}
    }
    else if(*cd->cur_p == '>') {
	cd->cur_p++;
	if(*cd->cur_p == '=') {
	    cd->cur_p++;
	    cd->op = S_MOREEQ;
	}
	else {
	    cd->op = S_MORE;
	}
    }
    else if(*cd->cur_p == '&') {
	cd->cur_p++;
	if(*cd->cur_p == '&') {
	    cd->cur_p++;
	    cd->op = S_AND;
	}
	else {
	    cd->op = S_ERROR;   /* & operator is not supported */
	}
    }
    else if(*cd->cur_p == '|') {
	cd->cur_p++;
	if(*cd->cur_p == '|') {
	    cd->cur_p++;
	    cd->op = S_OR;
	}
	else {
	    cd->op = S_ERROR;   /* | operator is not supported */
	}
    }
    else if(*cd->cur_p == '=') {
	cd->cur_p++;
	if(*cd->cur_p == '=') {
	    cd->cur_p++;
	    cd->op = S_EQ;
	}
	else {
	    cd->op = S_SUBSTI;
	}
    }
    else if(*cd->cur_p == '(') {
	cd->cur_p++;
	cd->op = S_LPAREN;
    }
    else if(*cd->cur_p == ')') {
	cd->cur_p++;
	cd->op = S_RPAREN;
    }
    else if(*cd->cur_p == ',' || *cd->cur_p == ';') { /*end of condition ',' */
	cd->op = S_NULL; /*END*/
    }
    else {
	display(MSDL_ERR,"asmrule: syntax error\n");
	cd->op = S_ERROR;
    }
  
    return cd->op;
}