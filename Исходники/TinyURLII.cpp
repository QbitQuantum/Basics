int main() {

    TinyUrl2 ty;

    vector<string> urls = {"http://www.lintcode.com/faq/?id=10"};
    for (string& url : urls) {
        string shortUrl = ty.longToShort(url);
        string longUrl = ty.shortToLong(shortUrl);
        cout << longUrl << " " << shortUrl << endl;
        if (longUrl != url)
            cout << "FAIL" << endl;
    }
    string long_url("http://www.lintcode.com/"), short_key("lccode");
    string shortUrl = ty.createCustom(long_url, short_key);
    string longUrl = ty.shortToLong(shortUrl);
    cout << longUrl << " " << shortUrl << endl;
    if (longUrl != long_url)
        cout << "FAIL" << endl;
    string shortUrl2 = ty.longToShort(long_url);
    cout << longUrl << " " << shortUrl2 << endl;
    if (shortUrl2 != shortUrl)
        cout << "FAIL" << endl;
    

    cout << ty.createCustom("http://www.lintcode.com/p1", "000001") << endl;
    ty.createCustom("http://www.lintcode.com/p2", "000002");
    ty.createCustom("http://www.lintcode.com/p3", "000003");
    ty.createCustom("http://www.lintcode.com/p4", "000004");
    ty.longToShort("http://www.lintcode.com/problem/");
    ty.shortToLong("http://tiny.url/000002");
    ty.shortToLong("http://tiny.url/000004");
    ty.createCustom("http://www.facebook.com", "facebook");
    ty.createCustom("http://www.facebook.com", "facebook");
    ty.createCustom("http://www.google.com", "google");
    ty.createCustom("http://www.lintcode.com", "lc");
    ty.shortToLong("http://tiny.url/lc");
    ty.shortToLong("http://tiny.url/google");
    ty.createCustom("http://www.google.com", "google");
    ty.shortToLong("http://tiny.url/facebook");
    ty.longToShort("http://www.lintcode.com");
    ty.longToShort("http://www.google.com");
    ty.longToShort("http://www.facebook.com");
    return 0;
}