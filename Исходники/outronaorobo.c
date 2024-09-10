/*=======================================================================*/
int main(int argc, char **argv)
/*=======================================================================*/
{
        int pid = 0;
        pid = getProcessId(argv[1]);
        if( pid < 0 ){
                printf("process [%s] not found in the system\n", argv[1]);
        } else {
                printf("pid of [%s] is %d\n", argv[1], pid);
        }
}