void Case :: randomize()
{
    Timer t;
    for(int i = 1000;i <= 10000;i += 1000)
    {
       pattern[1] = '\0';
       cout << "\nFor operation : " << i;
       textlen = i;patternlen = (int)( textlen / ((rand() % 10) + 1) );
       for(int j = 0;j < textlen - 1;j++) text[j] = (rand() % 26) + 'a';
 
       strrev(text);
       strncpy(pattern,text,patternlen);
       strrev(pattern);
       strrev(text);
 
        t.start();Horspool_Machine();t.stop();
        cout << " time taken : " << t.time() << " seconds";t.reset();
    }
}