bool ancestorLZTrie (lztrie T, trieNode i, trieNode j)

   { return (i <= j) && (j < findclose (T->pdata,i));
   }