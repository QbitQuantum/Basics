void one_word(){

    ///\fn void one_word()
    ///\brief Corectarea un cuvant introdus.
    ///
    ///Implementarea corectarii a unui cuvant introdus de la tastatura.


    char word[50]; // cuvantul care va fi verificat
    List sim_words ;  // lista cuvintelor asemanatoare cu cuvantul citit

// golirea bufferului
    fflush(stdin);
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        continue;

    system("cls");
    printf("\n\t\tOne word function: \n\n");

   while( 1 ){        //repeat while ESC isn't pressed

        tryAgain:
        system("cls");
        printf("\n\tPlease enter the word:  ");
        gets(word);
        if(word[strlen(word)-1]=='\n')
            word[strlen(word)-1]='\0';
        if(strlen(word)<=2)
            goto tryAgain;

            // if the word is incorrect
            if(list_search(&dict_lex, word)==NULL){

                Beep(20,200);

                find_sim_words(&sim_words, word, strlen(word), dict_lex.head, dict_lex.tail);

                if(sim_words.head==NULL){
                    ClearSelectAreea();
                    Beep(90,200);
                    GotoXY(3,3);
                    printf("The word \"%s\" is incorrect and there are no word like him!\n",word);
                    getchar();
                    return;
                }
                else{
                    Beep(70,200);
                    List_Node * newTail = malloc(sizeof(List_Node));
                    newTail->word = malloc(sizeof(char)*strlen(word)+1);
                    strcpy(newTail->word,word);
                    list_insert(&sim_words,newTail);
                    Select_correct_word(word, &sim_words);
                    free_list(&sim_words);
                    return;
                }
            }
            else{
                ClearSelectAreea();
                GotoXY(3,3);
                printf("The word \"%s\" is correct!\n",word);
                return;
            }
    }
}