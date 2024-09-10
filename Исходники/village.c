int Looper()
{
        while (!feof(tdf))
        {
                if (strlen(temp) < 2) fgets(temp, 80, tdf);

                p = strtok(temp, " ");
                if (strstr(p, "Airport"))
                {
                        Select = 1;
                }
                if (strstr(p, "Label"))
                {
                        Select = 2;
                }
                p = strtok(NULL, " ");
                p = strtok(NULL, " ");
                strcpy(kala, p);


                ptr = (char *) &kala;

                while (*ptr && (*ptr != ',')) ptr++;

                *ptr = 0;

                strcpy(xcoord, kala);
                x = atoi(xcoord);
// printf("xcoord: %s - int x: %i\n",xcoord,x);

                p = strchr(p, ',');
                strcpy(ycoord, p + 1);
                y = atoi(ycoord);
// printf("ycoord: %s - int y: %i\n",ycoord,y);


                p       = strtok(NULL, " ");
                kala[1] = '\0';

                if (p == NULL)
                {
                        printf("hey guy, your village.txt has some missing data!\n"
                               "this is right after the coordinate datas, it not only\n"
                               "missing the name data, but the type data also.\n\n"
                               "last line we compiled OK is:\n\n%s\n", writeme);
                        exit(1);
                }

                strcpy(kala, p);

                cityh = atoi(kala);
                p     = strtok(NULL, " ");
                _strnset(name, '\0', 80);

                while (p)
                {
                        strcat(tempname, p);
                        strcat(tempname, " ");
                        p = strtok(NULL, " ");
                }
// printf("its lenght is %i - tempname |%s|",strlen(tempname),tempname);
                px = strlen(tempname);
                if (px == 0) px = 3;
                if (px <= 3)
                        strcpy(name, "NoName");
                else
                        strncpy(name, tempname, strlen(tempname) - ch_nuke);

                _strnset(tempname, '\0', 80);



                WriteMe();
        }

        fclose(tdf);
        fclose(output);

        return 0;
}