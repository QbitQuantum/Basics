static void
gl_transpose(void)
/* switch character under cursor and to left of cursor */
{
    int    c;

    if (gl_pos > 0 && gl_cnt > gl_pos) {
	if(mbcslocale) {
	    int l_len = 0;
	    int r_len = 0;
	    int i = 0;
	    int j = 0;
	    mbstate_t mb_st;

	    mbs_init(&mb_st);
	    for (i = 0; i < gl_pos;) {
		l_len = mbrlen(gl_buf+i, MB_CUR_MAX, &mb_st);
		i += l_len;
	    }
	    mbs_init(&mb_st);
	    r_len = mbrlen(gl_buf+gl_pos, MB_CUR_MAX, &mb_st);
	    for (i = 0; i < r_len; i++) {
		for(j = 0; j < l_len; j++) {
		    c = gl_buf[gl_pos+i-j];
		    gl_buf[gl_pos+i-j] = gl_buf[gl_pos+i-j-1];
		    gl_buf[gl_pos+i-j-1] = (char)c;
		}
	    }
	    gl_extent = l_len + r_len;
	    gl_fixup(gl_prompt, gl_pos - l_len, gl_pos + (r_len - l_len)); 
	} else {
	    c = gl_buf[gl_pos-1];
	    gl_buf[gl_pos-1] = gl_buf[gl_pos];
	    gl_buf[gl_pos] = (char) c;
	    gl_extent = 2;
	    gl_fixup(gl_prompt, gl_pos-1, gl_pos);
	}
    } else
	gl_beep();
}