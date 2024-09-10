//------------------------------------------------------------------
void List::add(string flag,string name,bool noreply,string element) {

    string noReply="";
    if(noreply)
        noReply="noreply ";

    connection.send("LADD "+flag+" "+name+" "+noReply+"#1"+Foo::endOfLine );
    connection.send(Foo::toString( element.size() ) + Foo::endOfLine );
    connection.send(element+Foo::endOfLine);

    //--------------reply message did't received from server.(ignored)

}