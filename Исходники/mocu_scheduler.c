void main(int argc,char* argv[]){

  struct timeval tv0,tv1;

  gettimeofday(&tv0,NULL);

  int res = 0;
  int launched_num = 0;
  int received_num = 0;

  register_signal();

  srand(100);

  while(launched_num < num){

    pid_t child;
    int random;

    random = rand()%6;
    
    child = fork();
    
    if(child == 0){

      printf("Rand = %d\n",random);

      switch(random){
      case 0:
	execl(P1,NULL);
	break;
      case 1:
	execl(P2,NULL);
	break;
      case 2:
	execl(P3,NULL);
	break;
      case 3:
	execl(P4,NULL);
	break;
      case 4:
	execl(P5,NULL);
	break;
      case 5:
	execl(P6,NULL);
	break;
      }

      res ++;
      
      exit(0);
    }else{

      PIDs[launched_num] = child;
      Procs[launched_num] = random;
      launched_num++;
    }

    sleep(1);

  }

  while(received_num < num){

    pid_t res;
    int status;

    res = wait(&status);

    received_num++;
  }

  printf("FINISH!!!!!!!\n");

  gettimeofday(&tv1,NULL);
  
  printf("Result time : %f[sec]\n",elapsed(tv0,tv1));
}