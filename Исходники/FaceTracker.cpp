CLBPFeatures::CLBPFeatures(int num) : IFeatures(num)
{
    srand (time(NULL));
    for (int i = 0; i < m_num/2; i++)
    {
        TLFRect* r = new TLFRect();
        awpRect rr;

          rr.left = 1+rand() % 15;
          rr.top = 1+rand() % 15;
          rr.right = rr.left + 2 + 2*rand() % 4;
          rr.bottom = rr.top + 2 + 2*rand()% 4;


        r->SetRect(rr);
        this->m_patches.Add(r);
    }
}