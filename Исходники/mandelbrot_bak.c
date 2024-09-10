int main(int argc,char **argv){
	int nproc;
	int rank;
	MPI_Status status;
	int err;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	printf("%d\n",nproc);
	if(nproc!=7){
		printf("7 processes needed\n");
		MPI_Abort(MPI_COMM_WORLD,err);
	}
	if(rank==0){
		int i;
		int windowID;
		for(i=1;i<nproc;i++){
			MPI_Recv(image[(i-1)*100],100*600,MPI_INT,i,0,MPI_COMM_WORLD,&status);
			printf("received message from proc %d\n",i);
		}
		glutInit(&argc,argv);
		createPalette();
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//居中放置
		GLsizei windowX = (glutGet(GLUT_SCREEN_WIDTH)-width)/2;
		GLsizei windowY = (glutGet(GLUT_SCREEN_HEIGHT)-height)/2;
		glutInitWindowPosition(windowX, windowY);
		glutInitWindowSize(width, height);
		windowID = glutCreateWindow("FRAKTALE");

		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glViewport (0, 0, (GLsizei) width, (GLsizei) height);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(minX, maxX, minY, maxY, ((GLfloat)-1), (GLfloat)1);
		glOrtho(0, 600, 0, 600, ((GLfloat)-1), (GLfloat)1);
		glutDisplayFunc(repaint);
		glutMainLoop();
	}else{
		int limage[100][600];
		int i,j;
		int k;
		for(j=0;j<100;j++){
			k=(rank-1)*100+j;
			for(i=0;i<600;i++){
				GLfloat x=minX+i*stepX;
				GLfloat y=minY+k*stepY;
				limage[j][i]=caldepth(x,y);
			}
		}
		MPI_Send(limage,100*600,MPI_INT,0,0,MPI_COMM_WORLD);
	}
	MPI_Finalize();
}