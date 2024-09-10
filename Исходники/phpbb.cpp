void PhpBB::write_message(const int topic_id, const wstring &text)
{
    wchar_t topic[10];
    _itow(topic_id, topic, 10);
    wstring action = L"message="+text+L"&attach_sig=on&mode=reply&sid="+m_sid+L"&disable_bbcode=&disable_smilies=&t="+topic+L"&post=Отправить";
    if(http.post(TEXT("forum/posting.php"), action.c_str()))
    {
        wstring str =  http.getData();
        int a = 0;
    }
}