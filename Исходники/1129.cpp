 void Work(void) {
         int Ans = 0, uplast = 1, downlast = 1;
         T.Set(max); T.Insert(a[n], 1); number[a[n]]++;
         for (int i = n - 1; i >= 1; i--) {
                 int Sk = ++number[a[i]], Now = 1;
                 T.Insert(a[i], 1);
                 int count = T.Cal(a[i] - 1);
                 uplast = (Int64) uplast * Divid(n - i, up) % Mod;
                 downlast = (Int64) downlast * Divid(Sk, down) % Mod;
                 if (count) count = Divid(count, yy); else continue;
                 int tmp1 = 1;
                 for (int j = 1; j <= cnt; j++) {
                         tmp1 = (Int64) tmp1 * Pow(factory[j], yy[j] + up[j] - down[j]) % Mod;
                         yy[j] = 0;
                 }
                 int tmp2 = (Int64) uplast * _E(downlast) % Mod;
                 count = (Int64) count * tmp1 % Mod;
                 count = (Int64) count * tmp2 % Mod;
                 Ans = (Int64) ((count + Ans) % Mod);
         }
         printf("%d\n", (Ans + 1) % Mod);
 }