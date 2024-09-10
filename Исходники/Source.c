int Long_sentence_practice(wchar_t*** Long_sentence,int Long_Num,int sentence_Count[],FILE* Info_practice)
{
	wchar_t Example_sentence[50];	//ÇÑÁÙ¾¿ Ã½
	wchar_t typing_One_word[7][50] = {L"",L"",L"",L"",L"",L"",L""}; //±æ±ÛÀº ÃÖ´ë 7¹®ÀåÀ¸·Î ±¸¼º. ÇÑ ¹®Àå´ç 50°³ÀÇ ¹®ÀÚ ÀúÀå
	wchar_t temp[500] = L"";
	wchar_t tmp[1000];
	double typing_start_Time,typing_finish_Time;
	double typing_duration_Time;
	int start_Typing=1,present = 0,correct_word_Count =0;	//start_typingÀÌ 0ÀÌ¸é ÀÔ·Â½ÃÀÛ
	int len_Example_sentence ;
	int X_Cursor = 3;		//X Ä¿¼­À§Ä¡
	int Y_Cursor = 5;		//Y Ä¿¼­À§Ä¡
	int i,j = 0;
	int Highest_Typist = 0;		//ÃÖ´ë Å¸ÀÚ¼ö
	int User_input_typist;		//»ç¿ëÀÚ°¡ ÀÔ·ÂÇÑ ±ÛÀÚ°³¼ö
	long long Typist = 0;		//Å¸ÀÚ¼ö
	int typing_Accuracy = 0;	//Á¤È®µµ
	int sentence_word_Count;	//±ä±Û ¹®Àå¿¡¼­ÀÇ ±ÛÀÚ°³¼ö
	int Check_accuracy[100] = {-1,};	//-1ÀÌ¸é ¹«ÀÔ·Â »óÅÂ, -2ÀÌ¸é ¸Â´Â ÀÔ·Â, ´Ù¸¥°ªÀ¸¸Â
	int Random;
	int k;
	
	setlocale(LC_ALL, "Korean");
	k = Long_prac_Main(Long_sentence,Long_Num);	//¸Þ´º¿¡¼­ ¸î¹øÂ° ±ä±ÛÀÎÁö ¼±ÅÃ
	if(k == -1)
		return 0;
	else if(k == -2)
		return -1;
	else
	{
		UI_Long_prac(Long_sentence[k],sentence_Count[k]);	//»ç¿ëÀÚ°¡ ¼±ÅÃÇÑ ±ä±Û Ãâ·Â.
		while(j != sentence_Count[k])		//±ä±ÛÀÌ ³¡³¯‹š±îÁö
		{
			start_Typing = 1;			//°ªµé ÃÊ±âÈ­
			X_Cursor = 0;
			present = 0;
			memset(Check_accuracy,-1,4*100);
			memset(Example_sentence,0,sizeof(wchar_t)*50);
			
			wcscpy(Example_sentence,Long_sentence[k][j]);		//±ä±ÛÀÇ ÇÑ ¹®ÀåÀ» ÀÐ´Â´Ù.
			len_Example_sentence = wcslen(Example_sentence);	//À§¿¡¼­ ÀÐÀº ¹®ÀåÀÇ ±æÀÌ
			while(1)
			{

				gotoxy(3,4+(j*2));
				for(i = 0 ; i < len_Example_sentence ; i++)		//»ç¿ëÀÚ ÀÔ·Â°ú ¿¹½Ã¹®°úÀÇ ÀÏÄ¡ ½Ç½Ã°£ È®ÀÎ
				{
					if(Check_accuracy[i] == i)		//Æ²¸±°æ¿ì
					{
						RED;
					}
					else if(Check_accuracy[i] == -2)	//¸Â´Â°æ¿ì
					{
						COROL;
					}
					else			//¹«ÀÔ·Â»óÅÂ
					{
						WHITE;
					}
					printf("%C",Example_sentence[i]);
				}
				if(present>=len_Example_sentence-1)	//¹®ÀÚ ±æÀÌº¸´Ù ¸¹ÀÌ ÀÔ·Â¹ÞÀ¸¸é Á¾·á
				{
					break;
				}	
				gotoxy(3+X_Cursor,Y_Cursor+(j*2));
				typing_One_word[j][present] = _getwche();	//¹®ÀÚ ÇÏ³ª¸¦ ÀÔ·Â¹ÞÀ½
				if(typing_One_word[j][present] == 27)	// ESCÅ°¸¦ ´©¸£¸é ¿¬½ÀÁ¾·á
				{
					break;
				}
				if(typing_One_word[j][present] == 8 && present == 0)	//Ä¿¼­°¡ Ã³À½ÀÌ°í, ¹é½ºÆäÀÌ½º¸¦ ´©¸£¸é 
					gotoxy(X_Cursor+3,Y_Cursor+(j*2));		//µ¿ÀÛ¾ø´Â°ÍÃ³·³ º¸ÀÌ°Ô.
				else if(typing_One_word[j][present] == 8)	//¹é½ºÆäÀÌ½º¸¦ ´©¸£¸é
				{
					if(present>=1)
					{
						if(Example_sentence[present-1] < 256)	//Àü ±ÛÀÚ°¡ 1byteÀÌ¸é
						{
							present--;
							X_Cursor-=1;						//Ä¿¼­ ÇÏ³ª¸¸ µÚ·Î ÀÌµ¿
							gotoxy(X_Cursor+3,Y_Cursor+(j*2));
							printf(" ");		//Áö¿öÁø°ÍÃ³·³ º¸ÀÌ°Ô µ¤¾î¾¸
						}
						else				//Àü ±ÛÀÚ°¡ 2byte¸é
						{	
							present--;		
							X_Cursor-=2;		//Ä¿¼­ µÎ°³ ÀÌµ¿
							gotoxy(X_Cursor+3,Y_Cursor+(j*2));
							printf("  ");
						}
					}
					Check_accuracy[present] = -1;	//Áö¿öÁø ¿¹½Ã±Û ´Ù½Ã ÇÏ¾á»öÀ¸·Î Ãâ·ÂµÇ°Ô °ª º¯°æ
				}
				else if(typing_One_word[j][present] != Example_sentence[present])  //¿¹½Ã¹®ÀÌ¶û ´Þ¸¦°æ¿ì
				{
					if(present== 0 && start_Typing == 1 &&j == 0)		//ÃÖÃÊÀÔ·Â½Ã¿¡
					{
						start_Typing = 0 ;				//ÃÖÃÊÀÔ·Âº¯¼ö 0À¸·Î º¯°æ
						typing_start_Time = (double)(clock())/CLOCKS_PER_SEC;	//ÀÔ·Â ½Ã°£ ½ÃÀÛ
					}
					if(typing_One_word[j][present] <256 && Example_sentence[present] <256)	//¹®ÀÚ Å©±â¿¡ µû¸¥ Ä¿¼­ ÀÌµ¿
					{
						X_Cursor+=1;
						Check_accuracy[present] = present;
					}
					else if(typing_One_word[j][present] > 256 && Example_sentence[present] <256)
					{
						if(Example_sentence[present+1] < 256)
						{
							Check_accuracy[present] = present;
							Check_accuracy[present+1] = present+1;
							X_Cursor+= 2;
							present++;
						}
						else
						{
							X_Cursor+= 3;
							Check_accuracy[present] = present;
							Check_accuracy[present+1] = present+1;
							present++;
						}
					}
					else if(typing_One_word[j][present] < 256 && Example_sentence[present] > 256)
					{
						X_Cursor+= 2;
						Check_accuracy[present] = present;
					}
					else if(typing_One_word[j][present] >256 && Example_sentence[present] > 256)
					{
						X_Cursor+= 2;
						Check_accuracy[present] = present;
					}
					present++;
				}
				else  //¿¹½Ã¹®ÀÌ¶û °°°Ô ÀÔ·Â
				{
					if(present== 0 && start_Typing == 1 &&j == 0)
					{
						start_Typing = 0 ;
						typing_start_Time = (double)(clock())/CLOCKS_PER_SEC;
					}
					if(typing_One_word[j][present] < 256)
					{
						Check_accuracy[present] = -2;
						X_Cursor+= 1;
					}
					else
					{
						Check_accuracy[present] = -2;
						X_Cursor+=2;
					}
					present++;
				}
			}
			if(typing_One_word[j][present] == 27)
			{
				break;
			}
			j++;
		}
		if(typing_One_word[j][present] == 27)		//ÀÔ·ÂµµÁß ESCÅ° ÀÔ·ÂÇÏ¸é Á¾·á
			return 0;
		typing_finish_Time = (double)(clock())/CLOCKS_PER_SEC;	//¿¬½ÀÁ¾·á½Ã°£
		correct_word_Count = 0;
		for(j = 0 ; j < sentence_Count[k] ; j++)
		{
			memset(Example_sentence,0,sizeof(wchar_t)*50);
			wcscpy(Example_sentence,Long_sentence[k][j]);
			len_Example_sentence = wcslen(Example_sentence);
			for(i = 0 ; i <= len_Example_sentence ; i++)
			{
				if((typing_One_word[j][i] == Example_sentence[i]) && (typing_One_word[j][i] != 0))
				{
					temp[correct_word_Count] = Example_sentence[i];
					correct_word_Count++;
				}
			}
		}
		memset(tmp,0,sizeof(wchar_t)*1000);
		wcscpy(tmp,Example_sentence);
		typing_duration_Time = (typing_finish_Time-typing_start_Time)+0.5;//CLOCKS_PER_SEC;
		User_input_typist = BreakHan(temp,tmp,sizeof temp);	//»ç¿ëÀÚ°¡ ÀÔ·ÂÇÑ Å¸¼ö

		memset(tmp,0,sizeof(wchar_t)*1000);
		wcscpy(tmp,Example_sentence);
		memset(temp,0,sizeof(wchar_t)*500);
		//wcscpy(temp,Example_sentence);
		for(i = 0 ; i < sentence_Count[k] ; i++)
			wcscat(temp,Long_sentence[k][i]);
		sentence_word_Count = BreakHan(temp,tmp,sizeof temp);	//±ä±Û¿¡ ÀÔ·ÂÇØ¾ß ÇÏ´Â Å¸¼ö

		typing_Accuracy = (float)(User_input_typist)/(sentence_word_Count-sentence_Count[k])*100;	//Á¤È®µµ°è»ê
		Typist = (User_input_typist*60)/(typing_duration_Time);		//Å¸ÀÚ¼ö °è»ê
		/*for( i = 0 ; i < Long_Num ; i++)
		{
			for(j = 0 ; j < sentence_Count[i] ; j++)
				free(Long_sentence[i][j]);
		}
		free(Long_sentence);*/

		Result_Long_prac(typing_Accuracy,Typist);		//°á°úÈ­¸é Ãâ·Â
		fprintf(Info_practice,"%d %d\n",typing_Accuracy,Typist);	//ÅØ½ºÆ®ÆÄÀÏ¿¡ ¾²±â
	}
}