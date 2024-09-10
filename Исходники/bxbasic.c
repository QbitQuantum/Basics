void parser()
{
  int ab_code=4, x=line_ndx;
  int I;

  switch(token)
  {
    case 0:
      break;

    case 1:
      parse_let();
      break;
	
    case 2:
      cls();
      break;
    
    case 3:
      locate();
      break;
	
    case 4:
      xstring_array(); 
      get_prnstring(); 
      break;

    case 5:
      go_to();
      break;
	
    case 6:
      beep();
      break;
	
    case 7:
      cls();
      break;
	
    case 8:
      line_ndx = nrows;
      break;

    case 9:
      do_gs();
      break;

    case 10:
      do_ret();
      break;

    case 11:
      do_loop();
      break;

    case 12:
      do_next();
      break;

    case 13:
      do_iloop();
      break;

    case 14:
      do_iloop();
      break;
    
    case 15:
      return;
      break;

    case 16:
      return;
      break;

    case -1:
      break;

    default:
      printf("parser Inside DEFAULT\n");
      printf("p_string = %s\n",p_string);
      a_bort(ab_code, x);
      break;
  }
}