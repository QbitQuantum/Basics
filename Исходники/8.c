int main(void)
{
	struct planestats plane[SEATS];
	int choice;
	int i;
	size_t size = sizeof(struct planestats);
	FILE *fp;
	
	if((fp = fopen("air.dat","rb")) == NULL)
		{
			fprintf(stderr, "Can't open file %s","air.dat\n");
			if((fp = fopen("air.dat","wb")) == NULL)
				{
					exit(1);
				}
			for(i = 0; i < SEATS; i++)
				{
						plane[i].seat_id = i + 1;
						plane[i].status = 0;
				}	
				
			fwrite(plane, size , SEATS, fp);
			puts("We created the file air.dat now.");
			exit(1);
		}
	
	for(i = 0; i < SEATS; i++)
		{
				plane[i].seat_id = i + 1;
				plane[i].status = 0;
		}
	fread(plane, size , SEATS, fp);
	fclose(fp);
	
	while((choice = getmenu()) != 'f')	
		{
			switch(choice)
			{
				case 'a': printf("%d seat is empty!\n",empty_seat(plane,SEATS));
									break;
				case 'b':	show_empty(plane,SEATS);
									break;
				case 'c':	show_seats(plane,SEATS);
									break;
				case 'd':	assign_seat(plane,SEATS);
									break;
				case 'e':	delet_seat(plane,SEATS);
									break;				
			}	
		}
		
	if((fp = fopen("air.dat","wb")) == NULL)
		{
			fprintf(stderr, "Can't open file %s","air.dat");
			exit(1);
		}	
	fwrite(plane, size , SEATS, fp);
	fclose(fp);	
		
	puts("Bye!");	
			
	return 0;
}