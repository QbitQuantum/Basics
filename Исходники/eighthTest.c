void eighthTestCase04(void)
{
    int i, r;
    ArrayList* list;
    Employee* pAux[LENGTH];



    list = al_newArrayList();


    for(i=0; i < LENGTH; i++)
    {
        pAux[i] = newEmployee(id[i],unsortedList[i],unsortedList[i],salary[i],sector[i]);
        list->add(list,pAux[i]);
    }

    r = list->remove(NULL,0);
    utest_assertEqualsIntMsg(r,-1,"Error in return value <remove> if the pointer to array is NULL the correct value to return is -1");

    free(list);

}