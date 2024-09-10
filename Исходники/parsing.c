closure *parse_list(FILE *file, closure *accum)
{
    //printf("parse list\n");
    //print_closure(accum);
    wchar_t c = fgetwc(file);
    if(c == L')'){
	return reverse(accum);
    } else {
	ungetwc(c, file); 
	closure *boo = parse_null(file, nil());
	if (boo != NULL){
	    return parse_list(file, cons(boo, accum));
	} else {
	    return parse_list(file, accum);
	}
    }
}