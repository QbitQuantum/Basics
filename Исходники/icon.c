IconNode *LoadSuffixedIcon(const char *path, const char *name,
                           const char *suffix)
{

   IconNode *result;
   ImageNode *image;
   char *iconName;
   unsigned int len;

   Assert(path);
   Assert(name);
   Assert(suffix);

   len = strlen(name) + strlen(path) + strlen(suffix);
   iconName = Allocate(len + 1);
   strcpy(iconName, path);
   strcat(iconName, name);
   strcat(iconName, suffix);

   result = FindIcon(iconName);
   if(result) {
      Release(iconName);
      return result;
   }

   image = LoadImage(iconName);
   if(image) {
      result = CreateIcon();
      result->name = iconName;
      result->images = image;
      InsertIcon(result);
      return result;
   } else {
      Release(iconName);
      return NULL;
   }

}