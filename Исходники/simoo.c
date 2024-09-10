int do_assemble2(program *program, program2 * program2)
{
  int pc = 0;
  int nextpc = 0;
  long long counter = 0;
  instruction2 ist;
  int iname, arg1, arg2, arg3;
    
  while (1) {
    pc = nextpc;

    
    ist = program2->insts[pc];
    iname = ist.name[0];
    arg1 = ist.name[1];
    arg2 = ist.name[2];
    arg3 = ist.name[3];

    /*
      ++counter;

      if(counter > 575600 && counter < 575719)
      {
      print_label_from_index(program, pc);
      print_instruction(program->insts[pc]);
      print_register();
      }
    */
	
    if (iname == 0) {
      // printf("this is nop\n");
    }
    DO_INST_1(1, +)
      DO_INST_1(2, -)
      DO_INST_1(3, *)
      DO_INST_1(4, &)
      DO_INST_1(5, |)
      /*ALU命令 */
    else if (iname == 6) {
      regist[ist.name[1]] = ~(regist[ist.name[2]] | regist[ist.name[3]]);
    }
    else if (iname == 7) {
      regist[ist.name[1]] = regist[ist.name[2]] ^ regist[ist.name[3]];
    }
    else if (iname == 8) {
      regist[ist.name[1]] = regist[ist.name[2]] + ist.name[3];
    }
    else if (iname == 9) {
      regist[ist.name[1]] = regist[ist.name[2]] - ist.name[3];
    }
    else if (iname == 10) {
      regist[ist.name[1]] = regist[ist.name[2]] * ist.name[3];
    }
    else if (iname == 11) {
      regist[ist.name[1]] = regist[ist.name[2]] & ist.name[3];
    }
    else if (iname == 12) {
      regist[ist.name[1]] = regist[ist.name[2]] | ist.name[3];
    }
    else if (iname == 13) {
      regist[ist.name[1]] = ~(regist[ist.name[2]] | ist.name[3]);
    }
    else if (iname == 14) {
      regist[ist.name[1]] = regist[ist.name[2]] ^ ist.name[3];
    }
    /*FPU命令 */
    else if (iname == 15) {
      freg[ist.name[1]] = freg[ist.name[2]] + freg[ist.name[3]];
    }
    else if (iname == 16) {
      freg[ist.name[1]] = freg[ist.name[2]] - freg[ist.name[3]];
    }
    else if (iname == 17) {
      freg[ist.name[1]] = freg[ist.name[2]] * freg[ist.name[3]];
    }
    else if (iname == 18) {
      freg[ist.name[1]] = freg[ist.name[2]] / freg[ist.name[3]];
    }
    else if (iname == 19) {
      freg[ist.name[1]] = 1 / freg[ist.name[2]];
    }
    else if (iname == 20) {
      freg[ist.name[1]] = sqrt(freg[ist.name[2]]);
    }
    else if (iname == 21) {
      freg[ist.name[1]] = floor(freg[ist.name[2]]);
    }
    else if (iname == 22) {
      freg[ist.name[1]] = (float) (regist[ist.name[2]]);
    }


    /*MEM ACSESS命令 */
    else if (iname == 23) {
      //memory_check
      if (check_memory(regist[ist.name[2]] + ist.name[3]) == ACSESS_BAD) {
	printf("Error:ACSESS_BAD :\n");
	//	 printf("%d\n", iname);
	//printf("%lld\n", counter);
	exit(1);
      }
      regist[ist.name[1]] = memory[regist[ist.name[2]] + ist.name[3]].i;
    }

    else if (iname == 24) {
      //memory_check
      if (check_memory(regist[ist.name[2]] + ist.name[3]) == ACSESS_BAD) {
	printf("Error:ACSESS_BAD :\n");
	//printf("%d\n", iname);
	exit(1);
      }
      memory[regist[ist.name[2]] + ist.name[3]].i =  regist[ist.name[1]];
    }

    else if (iname == 25) {
      //memory_check
      if (check_memory(regist[ist.name[2]] + ist.name[3])
	  == ACSESS_BAD) {
	printf("Error:ACSESS_BAD :\n");
	//printf("%d\n", iname);
	exit(1);
      }
      freg[ist.name[1]] =
	memory[regist[ist.name[2]] + ist.name[3]].d;
    }

    else if (iname == 26) {
      //memory_check
      if (check_memory(regist[ist.name[2]] + ist.name[3])
	  == ACSESS_BAD) {
	printf("Error:ACSESS_BAD :\n");
	// printf("%d\n", iname);
	exit(1);
      }
      memory[regist[ist.name[2]] + ist.name[3]].d =
	freg[ist.name[1]];
    }


    /*BRANCH命令 */
    else if (iname == 27) {
      if (regist[ist.name[1]] == regist[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }
    }

    else if (iname == 28) {
      if (regist[ist.name[1]] != regist[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }
    }
    else if (iname == 29) {
      if (regist[ist.name[1]] > regist[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }
    }

    else if (iname == 30) {
      if (regist[ist.name[1]] < regist[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }
    }

    else if (iname == 31) {
      if (regist[ist.name[1]] >= regist[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }
    }

    else if (iname == 32) {
      if (regist[ist.name[1]] <= regist[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }

    } else if (iname == 33) {
      if (freg[ist.name[1]] == freg[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }
    }

    else if (iname == 34) {
      if (freg[ist.name[1]] != freg[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }
    }

    else if (iname == 35) {
      if (freg[ist.name[1]] > freg[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }
    }

    else if (iname == 36) {
      if (freg[ist.name[1]] < freg[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }
    }

    else if (iname == 37) {
      if (freg[ist.name[1]] >= freg[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }
    }

    else if (iname == 38) {
      if (freg[ist.name[1]] <= freg[ist.name[2]]) {
	nextpc = pc + ist.name[3] - 1;
      }
    }


    /*JUMP命令 */
    else if (iname == 39) {
      if (ist.name[1] == -100) {
	freg[2] = atanf(freg[2]);
	nextpc = pop(&call_stack) - 1;
      } else if (ist.name[1] == -200) {
	freg[2] = sqrtf(freg[2]);
	nextpc = pop(&call_stack) - 1;
      } else if (ist.name[1] == -300) {
	regist[4] = read_int();
	printf("read_int: %d\n", regist[4]);
	nextpc = pop(&call_stack) - 1;
      } else if (ist.name[1] == -400) {
	freg[2] = read_float();
	printf("read_float: %f\n", freg[2]);
	nextpc = pop(&call_stack) - 1;
      } else if (ist.name[1] == -500) {
	printf("aaa\n");
	if(ppp < freg[2])
	  {
	    ppp = freg[2];
	  }
	if(nnn > freg[2])
	  {
	    nnn = freg[2];
	  }
	//print_register();
	nextpc = label_trans(program->insts[pc].name[1], program) - 1;
	//freg[2] = sinf(freg[2]);
	//printf("read_float: %f\n", freg[2]);
	//nextpc = pop(&call_stack) - 1;
      } else if (ist.name[1] == -600) {
	freg[2] = cosf(freg[2]);
	//printf("read_float: %f\n", freg[2]);
	nextpc = pop(&call_stack) - 1;
      } else if (ist.name[1] == -700) {
	//print_int
	print_int();
	nextpc = pop(&call_stack) - 1;
      } else if (ist.name[1] == -800) {
	print_float();
	nextpc = pop(&call_stack) - 1;
      }
      else
	{
	  nextpc = ist.name[1] - 1;
	}
      /*
	if(strncmp(program->insts[pc].name[1] , "L_main", 6) == 0)
	{
	print_memory();
	}
      */
    }


    else if (iname == 40) {
          
      nextpc = ist.name[1] - 1;
      /*特殊ラベル*/
      if (ist.name[1] == -100) {
	freg[2] = atanf(freg[2]);
	nextpc = pc;
      } else if (ist.name[1] == -200) {
	freg[2] = sqrtf(freg[2]);
	nextpc = pc;
      } else if (ist.name[1] == -300) {
	regist[4] = read_int();
	printf("read_int: %d\n", regist[4]);
	nextpc = pc;
      } else if (ist.name[1] == -400) {
	freg[2] = read_float();
	printf("read_float: %f\n", freg[2]);
	nextpc = pc;
      } else if (ist.name[1] == -500) {
	printf("aab\n");
	kkk = 1;
	if(ppp < freg[2])
	  {
	    ppp = freg[2];
	  }
	if(nnn > freg[2])
	  {
	    nnn = freg[2];
	  }
	push(&call_stack, (pc + 1));
	nextpc = label_trans(program->insts[pc].name[1], program) - 1;
	
	//freg[2] = sinf(freg[2]);
	//printf("read_float: %f\n", freg[2]);
	//nextpc = pc;
      } else if (ist.name[1] == -600) {
	freg[2] = cosf(freg[2]);
	//printf("read_float: %f\n", freg[2]);
	nextpc = pc;
      } else if (ist.name[1] == -700) {
	//print_int
	print_int();
	nextpc = pc;
      } else if (ist.name[1] == -800) {
	print_float();
	nextpc = pc;
      } else {
	push(&call_stack, (pc + 1));
      }


    }

    else if (iname == 41) {
      nextpc = pop(&call_stack) - 1;
    }

    else if (iname = 42) {
      print_register();
      print_memory();
    }
    //命令が存在しなかった場合error parseでやっているのでいらない。
    //printf("ist = %d\n",iname);

    nextpc++;


    /*命令がラストの行まで行けば処理を終了する */
    if (nextpc >= program2->inst_count) {
      break;
    }
  }

  return 0;
}