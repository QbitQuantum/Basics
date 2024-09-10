void call21h()
{
	/*
	 * 对21h 中的功能号进行测试
	 */
	while(1)
	{
		cls();
		print("\r\n         Now, you can run some commands to test the 21h:\n\n\r");
		print("        1.ouch  -- to ouch          2.upper -- change the letter to upper\n\r");
		print("        3.lower         -- change the letter to lower\n\r"); 
		print("        4.to_digit      -- change the string to digit\r\n"); 
		print("        5.to_string     -- change the digit to string\r\n"); 
		print("        6.display_where -- you can assign where to display\r\n");
		print("        7.to_deci      -- change the Hex to a decimal digit\r\n"); 
		print("        8.reverse      -- to reverse your string\r\n"); 
		print("        9.strlen      --  get the length of your string\r\n"); 
		print("        10.quit          -- just to quit\r\n\r\n"); 
		print("Please input your choice:"); 
		getline(input,20);
	    if(strcmp(input,"1") || strcmp(input,"ouch"))
		{
			/*
			 * 测试 0 号功能
			 */
			to_OUCH();
		}
	    else if(strcmp(input,"2") || strcmp(input,"upper"))
		{
			/*
			 * 测试 1 号功能
			 */
			while(1)
			{
				print("\r\nPlease input a sentence or quit to back:");
				getline(input,30);
				if(strcmp(input,"quit")) break;
				upper(input);
				print("\r\nThe upper case is:");
				print(input);
				print("\r\n");
			}
		}
	    else if(strcmp(input,"3") || strcmp(input,"lower"))
		{
			/*
			 * 测试 2 号功能
			 */
		    while(1)
			{
				print("\r\nPlease input a sentence or quit to back:");
				getline(input,30);
				if(strcmp(input,"quit")) break;
				lower(input);
				print("\r\nThe lower case is:");
				print(input);
				print("\r\n");
			}
		}
	    else if(strcmp(input,"4") || strcmp(input,"to_digit"))
		{
			/*
			 * 测试 3 号功能
			 */
			print("\r\nDo you want to continue? Y | N :");
			getline(input,2);
			while(1)
			{
				int t1,t2,t3;
				t1 = 0;t2 = 0;
				if(strcmp(input,"n") || strcmp(input,"N")) break;
				print("\r\nPlease input the first digit:");
				getline(input,4);
				if(isDigit(input))
				{
				    t1 = digital(input);
				}
				else 
				{
					print("\r\nInvalid digit!We assume it is 12\n\r");
					t1 = 12;
				}
				print("\r\nPlease input the second digit:");
				getline(input,4);
				if(isDigit(input))
				{
					t2 = digital(input);
				}
				else 
				{
					print("\r\nInvalid digit!We assume it is 21\n\r");
					t2 = 21;
				}
				print("\r\nThe sum of the them is:");
				t3 = t1 + t2;
				printInt(t3);
				print("\r\n");
				print("\r\nDo you want to continue? Y | N :");
				getline(input,2);
			}
		}
	    else if(strcmp(input,"5") || strcmp(input,"to_string"))
		{
			/*
			 * 测试 4 号功能
			 */
			print("\r\nDo you want to continue? Y | N: ");
			getline(input,2);
			while(1)
			{
				char *cht;
				int tt = rand();
				if(strcmp(input,"n") || strcmp(input,"N")) break;
				cht = convertToString(tt);
				print("\r\nI am a string: ");
				print(cht);
				print("\r\n");
				print("\r\nDo you want to continue? Y | N: ");
				getline(input,2);
			}
		}
	    else if(strcmp(input,"6") || strcmp(input,"display_where"))
		{
			/*
			 * 测试 5 号功能
			 */
			int row,col;
			print("\r\nPlease input the row:");
			getline(input,3);
			if(isDigit(input))
			{
				row = digital(input);
			}
			else 
			{
				print("\r\nInvalid digit!We assume it is 12\n\r");
			    row = 12;
			}
			print("\r\nPlease input column:");
			getline(input,3);
			if(isDigit(input))
			{
				col = digital(input);
			}
			else 
			{
				print("\r\nInvalid digit!We assume it is 40\n\r");
			    col = 40;
			}
			print("\r\nPlease input the string:");
			getline(input,30);
			display(row,col,input);
		}
		else if(strcmp(input,"7") || strcmp(input,"to_dec"))
		{
			/*
			 * 测试 6 号功能
			 */
			print("\r\nDo you want to continue? Y | N :");
			getline(input,2);
			while(1)
			{
				int t1;
				t1 = 0;
				if(strcmp(input,"n") || strcmp(input,"N")) break;
				print("\r\nPlease input the hex digit:");
				getline(input,3);
				if(isHex(input))
				{
				    t1 = convertHexToDec(input);
				}
				else 
				{
					print("\r\nInvalid Hex!We assume it is 12\n\r");
					t1 = 12;
				}
				print("\r\nThe decimal form is:");
				printInt(t1);
				print("\r\n");
				print("\r\nDo you want to continue? Y | N :");
				getline(input,2);
			}
		}
		else if(strcmp(input,"8") || strcmp(input,"reverse"))
		{
			/*
			 * 测试 7 号功能
			 */
			print("\r\nDo you want to continue? Y | N :");
			getline(input,2);
			while(1)
			{
				if(strcmp(input,"n") || strcmp(input,"N")) break;
				print("\r\nPlease input the your string:");
				getline(input,30);
				reverse(input,strlen(input));
				print("\r\nThe string after reverse is:");
				print(input);
				print("\r\n");
				print("\r\nDo you want to continue? Y | N :");
				getline(input,2);
			}
		}
		else if(strcmp(input,"9") || strcmp(input,"strlen"))
		{
			/*
			 * 测试 8 号功能
			 */
			print("\r\nDo you want to continue? Y | N :");
			getline(input,2);
			while(1)
			{
				int t;
				if(strcmp(input,"n") || strcmp(input,"N")) break;
				print("\r\nPlease input the your string:");
				getline(input,30);
				t = strlen(input);
				print("\r\nThe length of the string is:");
				printInt(t);
				print("\r\n");
				print("\r\nDo you want to continue? Y | N :");
				getline(input,2);
			}
		}
	    else if(strcmp(input,"10") || strcmp(input,"quit"))
		{
			/*
			 * 退出
			 */
			break;
		}
	}
}