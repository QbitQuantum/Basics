int main(){

    int data,nd,pos1,pos2;
    char ch = 'y';
    Node n;

    while(ch == 'y' || ch == 'Y'){
        cout<<"\nEnter data for new node: ";
        cin>>data;
        p = n.createNode(data);
        n.buildList(p);
        cout<<"\nDo u want to add new element(y/n): ";
        cin>>ch;
    }
    n.printList(first);
    cout<<"\nEnter Value and position of new node: ";
    cin>>nd>>pos1;
    p = n.createNode(nd);
    n.insert(first,p,pos1);
    n.printList(first);
    cout<<"\nEnter positon of node to remove: ";
    cin>>pos2;
    n.remove(first,pos2);
    n.printList(first);
    cout<<"\n list empty";
    n.makeEmpty(first);
    n.printList(first);
    return 0;
}