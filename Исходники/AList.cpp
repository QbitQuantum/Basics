int main()
{
    List<int>* list = new LList<int>();
    list->prev();
    list->append(0);
    int n = 5;
    int a[] = {1, 4, 5, 6, 7};
    for(int i=0;i<n;i++)
       list->append(a[i]);
       
    for(list->moveToStar();list->currPos()<list->length();list->next())
        cout<<list->getValue();
    cout<<endl;
    list->prev();
    int& temp = list->getValue();
    cout<<list->getValue()<<endl;
    
    list->moveToPos(3);
    for(int i=0;i<800;i++)
    {
        list->insert(i);
        list->next();
    }
    for(list->moveToStar();list->currPos()<list->length();list->next())
        cout<<list->getValue();
    cout<<endl;
    delete list;
}