 static DWORD HashKey(KeyT Key)
 {
     ldiv_t hash_val = ldiv((long)Key, 127773);
     hash_val.rem = 16807 * hash_val.rem - 2836 * hash_val.quot;
     if (hash_val.rem < 0) hash_val.rem += 2147483647;
     return ((DWORD)hash_val.rem);
 }