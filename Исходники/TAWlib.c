void zombie()

{
	int s;
	srand((unsigned)time(0));
	s=rand()%4+1;
	switch(s)
	{
	case 1:
		{
			printf("Oh no!You are bitten.You should probably leave now...\nThe zombie seems statified that his job well done and.....\n");
			_sleep(2000);
			printf("Now he's leaving.\n");
			_sleep(2000);
			_pick(uObj_zombie,-1);
			player.health=1;
			condition[Condi_Fakezombiebite]=0;
			break;
		}
	default:
		{
			printf("You alomst got bitten.Thankfully not,you need to go.Like,right now!\n");
			break;
		}
	}
	
}