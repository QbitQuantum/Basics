v8::Handle<v8::Value> Contacts::addCategory(const v8::Arguments& args) {
	AppLogTag("Contacts", "Entered Contacts::addCategory (args length:%d)", args.Length());

//	if (args.Length() < 1 || Util::isArgumentNull(args[0])) {
    if (args.Length() < 1) {
    	AppLogTag("Contacts", "Bad parameters");
        return v8::ThrowException(v8::String::New("Bad parameters"));
    }
    v8::HandleScope scope;

    String newCategory = null;
    if(args[0]->IsString())
    {
    	newCategory = UNWRAP_STRING(args[0]).c_str();
    	AppLogTag("Contacts","Now add new Category:%ls", newCategory.GetPointer());
    }

    if(newCategory == null)
    {
    	AppLogTag("Contacts","category name is null");
    }

    Category category;
    category.SetName(newCategory);

    AddressbookManager* pAddressbookManager = AddressbookManager::GetInstance();
    Addressbook* pAddressbook = pAddressbookManager->GetAddressbookN(DEFAULT_ADDRESSBOOK_ID);

    pAddressbook->AddCategory(category);

    if (IsFailed(GetLastResult())) {
        return scope.Close(v8::Boolean::New(false));
    } else {
        return scope.Close(v8::Boolean::New(true));
    }
}