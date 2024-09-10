int main() {

    HashTable<int>* h = new HashTable<int>(47);

    h->insert("sylvan",10);
    h->insert("lora",5);
    h->insert("jake",15);
    h->insert("kiran",20);
    h->insert("theo",16);
    h->insert("sylvan",41);
    h->insert("lora",39);
    h->insert("jake",6);
    h->insert("kiran",3);
    h->insert("theo",1);

    h->insert("will",10);
    h->insert("kelly",5);
    h->insert("nadine",15);
    h->insert("nick",20);
    h->insert("zoe",16);
    h->print();

    if (h->find("sylvan")!=0)
        cout << *(h->find("sylvan")) << endl;

    h->remove("sylvan");
    h->remove("lora");
    h->remove("will");
    h->print();

    h->insert("sylvan",30);
    h->insert("lora",28);
    h->insert("aili",0);
    h->insert("richard",70);
    h->insert("robert",70);
    h->insert("sandie",73);
    h->print();

    delete h;

}