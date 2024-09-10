//-------------------------------------------------------------------------------------------------------------------------------------------
Image* loadImage(string fileName, hash_map<string, Image*> *images){
    Image* image = NULL;

    image = (*images)[fileName];
    if (image == NULL){
        image = new Image(fileName);
        image->LoadImageW();
        (*images)[fileName] = image;
    }

    return image;
}