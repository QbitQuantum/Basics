linked_list* find_top_bottom(const image_t* img,uint16_t height_min,uint16_t leftCutoff,linked_list* groupings){
    /* finds all vertical lines (stems, measure markers)
     Returns:
    groupings - indices within goodLines array of start and end of each vertical line
       ex: [40 42
            55 58
            100 110]
    
     goodLines - array of structs for each vertical found
       .top
       .bottom
       .left
       .right*/
    
    /*Var Declarations*/
    uint16_t height,width,col,row,test_length,i,real_length;
    linked_list *goodlines_first;/*since unsure of size, trim down later*/
    flex_array_t *starts;
    uint8_t inLine,shift,step;
    uint16_t cursor1,cursor2;
    good_lines_t *lines;
    /*End Var Declarations*/
    
    height=img->height;
    width=img->width;

    goodlines_first=create_linked_list();                                   
   
    real_length=0;
    for (col=0;col<width;col++){
        test_length=0;
        i=0;
        for (row=1;row<height;row++){
            if(!getPixel(img,row-1,col) && getPixel(img,row,col)) test_length++;
        }
        starts=make_flex_array(test_length);
        for (row=1;row<height;row++){
            if(!getPixel(img,row-1,col) && getPixel(img,row,col)) starts->data[i++]=row;;
        }
        
        for (i=0;i<test_length;i++) {/*start = starts;*/
            inLine = 1;
            cursor1=starts->data[i];
            cursor2=col;
            shift = 0;
            
            while(inLine){
                step = 0;
                if ( getPixel(img,cursor1+1,cursor2)==1 ){ /*right below*/
                    cursor1++;
                    step = 1;
                }
    
                if ( cursor2+1 < width && !step ){ /*to the bottom right*/
                    if (getPixel(img,cursor1+1,cursor2+1) ){
                        cursor1++;
                        cursor2++;
                        step = 1;
                        shift++;
                    }
                }
                    
                if ( cursor2-1 >= 0 && !step){ /*to the bottom left*/
                    if (getPixel(img,cursor1+1,cursor2-1) ){
                        cursor1++;
                        cursor2--;
                        step = 1;
                        shift ++;
                    }
                }
                    
                if (!step || shift > 3){ /*can't continue black run*/
                   if (cursor1-(starts->data[i])>=height_min){
                        real_length++;
                        lines=(good_lines_t *)malloc(sizeof(good_lines_t));
                        lines->bottom=cursor1;
                        lines->index=col;
                        lines->left= col<cursor2 ? col : cursor2;
                        lines->top=starts->data[i];
                        lines->right=col>cursor2 ? col: cursor2;
                        lines->left +=leftCutoff-1;
                        lines->right+= leftCutoff-1;
                        push_bottom(goodlines_first,lines);
                   }
                   inLine = 0;
                }
                
            } /*end while in line*/
        
        } /*end for thru each starting location*/
        delete_flex_array(starts);   
        
    } /*end for thru each column*/
    starts=make_flex_array(real_length);
    for (i=0;i<real_length;i++){
        starts->data[i]=((good_lines_t*)getIndexData(goodlines_first,i))->left;
    }
    /*GROUP LINES TOGETHER*/
    fill_group_indices(groupings,starts,5); /*2nd arg chosen to group close lines together*/
    
    delete_flex_array(starts);
    return goodlines_first;

}