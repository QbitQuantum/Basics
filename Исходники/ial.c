E_CODE BTInsert (tBTree *T,tString *key, void *data) {
/*   --------
** Vloží do stromu nový uzel s hodnotou Content.
**
** Z pohledu vkládání chápejte vytvářený strom jako binární vyhledávací strom,
** kde uzly s hodnotou menší než má otec leží v levém podstromu a uzly větší
** leží vpravo. Pokud vkládaný uzel již existuje, neprovádí se nic (daná hodnota
** se ve stromu může vyskytnout nejvýše jednou). Pokud se vytváří nový uzel,
** vzniká vždy jako list stromu. Funkci implementujte nerekurzivně.
**/
	if (T->root==NULL){ //prázdný strom
	        T->root=mmuMalloc(sizeof(struct tBTreeNode));
            T->root->key=key;
            T->root->data=data;
            T->root->left=T->root->right=NULL;
            T->root->height=0;
            T->lastAdded=T->root;
            return ERROR_OK;
	}
    tBTNode tmp = T->root;
    int cmpResult;
	while(tmp!=NULL){
            cmpResult=strCmp(key,tmp->key);
            if (cmpResult<0){
                if(tmp->left==NULL){
                //vlož levý
                tmp->left=mmuMalloc(sizeof(struct tBTreeNode));
                tmp->left->key=key;
                tmp->left->data=data;
                tmp->left->left=tmp->left->right=NULL;
                tmp->left->height=(tmp->height)+1;
                T->lastAdded=tmp->left;
                return ERROR_OK;
                }
                else tmp=tmp->left;//hledej dál vlevo
            }
            else if (cmpResult>0){
                if (tmp->right==NULL){
                //vlož pravý
                tmp->right=mmuMalloc(sizeof(struct tBTreeNode));
                tmp->right->key=key;
                tmp->right->data=data;
                tmp->right->left=tmp->right->right=NULL;
                tmp->right->height=(tmp->height)+1;
                T->lastAdded=tmp->right;
                return ERROR_OK;
                }
                else tmp=tmp->right;//hledej dál vpravo
            }
            else{ T->lastAdded=tmp;return ERROR_INS_EXIST; }
        }
    return ERROR_OK;
}