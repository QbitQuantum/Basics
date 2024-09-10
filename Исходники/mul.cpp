#include <cstdio>
#include <cstring>
#include <cmath>

typedef long long Long;
const int MAXN=32768;
const double pi=acos(-1.0);
const Long MOD=100000;
const int TEN=5;

double ra[MAXN];
double ia[MAXN];
double rb[MAXN];
double ib[MAXN];
double rc[MAXN];
double ic[MAXN];
char a[MAXN];
char b[MAXN];
int slena;
int slenb;
int lena;
int lenb;
int n,logn;
Long ans[MAXN];

int rev(int x,int bit)
{
    int ans=0;
    for (int i=0; i<bit; i++)
    {
        ans<<=1;