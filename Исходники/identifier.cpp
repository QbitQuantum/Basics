// This Identifier is stored in binary form.
// But what if you want a pretty string version of it?
// Just call this function.
void Identifier::GetString(String& id) const
{
    auto data = Data::Factory();
    data->Assign(&type_, sizeof(type_));

    OT_ASSERT(1 == data->size());

    if (0 == size()) { return; }

    data->Concatenate(this->data(), size());

    auto output = String::Factory("ot");
    output->Concatenate(String::Factory(
        OT::App().Crypto().Encode().IdentifierEncode(data).c_str()));
    id.swap(output);
}