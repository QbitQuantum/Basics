static inline void do_layout(VisualRow *vrow, VTLayout *vtlayout)
{
#define SIZE 4096
  size_t logical_char2cell_index[SIZE];
  size_t in2out[SIZE];
  size_t out2in[SIZE];
  char logical[SIZE]; /* is this enough? */
  int logical_width, logical_length;
  char visual[SIZE];  /* is this enough? */
  size_t visual_length = SIZE;
  wchar_t wc;
  mbstate_t ps;
  size_t mb_len;
  int consumed = 0;
  int cursor_pos = 0;
  int current_char = 0;
  int width;
  int logical_cell_index;
  Char mbchar;

  memset(logical_char2cell_index,0,SIZE);
  memset(logical,0,SIZE);
  memset(visual,0,SIZE);
  memset(in2out,0,SIZE);
  memset(out2in,0,SIZE);
  memset(&ps,0,sizeof(ps));

  construct_char2cell_index(vrow->row,logical_char2cell_index);

  Row_compose_bytes(vrow->row,
                    0,vrow->row->num_columns,
                    logical,SIZE,
                    &logical_length,&logical_width,1);
#undef SIZE  
#if  debug
  printf("logical: [%s]\n",logical);
  printf("logical_length = %u\n",logical_length);
#endif

  vtlayout->transform(vtlayout,
                     logical, logical_length,
                     visual, &visual_length,
                     in2out,out2in,NULL);
#if debug
  printf("visual : [%s]\n",visual);
  printf("visual_length  = %u\n\n",visual_length);
#endif  

      /* Well off course, I need to refine this code ;-) */
  while(consumed < visual_length)
  {
    mb_len = mbrtowc(&wc,visual+consumed,visual_length-consumed,&ps);
    if(mb_len == 0 || mb_len == (size_t)-1 || mb_len == (size_t)-2 )
    {
#if debug      
      printf("found invalid or NULL character(%u)\n",mb_len); 
#endif
      break;
    }
    else
    {
      logical_cell_index = logical_char2cell_index[out2in[current_char]];
#if debug      
      printf("logical char index[%d] <-> visual char index[%d]\n",
             out2in[current_char],current_char);
#endif      
      if(Row_is_char_drawn(vrow->row,logical_cell_index))
                          
      {
        width = wcwidth(wc);
        Char_init(mbchar,visual+consumed,mb_len,width,(width>0));
        Row_add_char(vrow->vrow,
                     cursor_pos,
                     &mbchar,
                     Row_is_bold(vrow->row,logical_cell_index),
                     Row_is_blink(vrow->row,logical_cell_index),
                     Row_is_inverse(vrow->row,logical_cell_index),
                     Row_is_underline(vrow->row,logical_cell_index),
                     Row_get_foreground(vrow->row,logical_cell_index),
                     Row_get_background(vrow->row,logical_cell_index),
                     Row_get_charset(vrow->row,logical_cell_index));
      }
      else
      {
        Row_set_char_drawn(vrow->vrow,cursor_pos,0);
        width = 1;
      }
      
      vrow->visual2logical_index[cursor_pos] = logical_cell_index;
      vrow->logical2visual_index[logical_cell_index] = cursor_pos;
#if debug      
      printf("logical cell index[%d] <-> visual  cell index[%d]\n",
             logical_cell_index,cursor_pos);
#endif      
                   
    }
        /* process for multi column character */
    if(width > 1 && Row_is_char_drawn(vrow->row,logical_cell_index) &&
       width == Row_get_cell_width(vrow->row,logical_cell_index) )
    {
      int i;
      for(i=1;i<width;i++)
      {
        vrow->visual2logical_index[cursor_pos+i] = logical_cell_index+i;
        vrow->logical2visual_index[logical_cell_index+i] = cursor_pos+i;
      }
    }
    cursor_pos+=width;
    current_char++;
    consumed+=mb_len;
  }
      /* The visual row possibly has ligatures */
  if(cursor_pos < vrow->row->num_columns &&
     !vtlayout->is_direction_LTR(vtlayout))
      Row_insert_cells(vrow->vrow,0,vrow->row->num_columns-cursor_pos);
      
}