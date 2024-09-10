int main() {

    /**
     * @var Рабочая матрица.
     */ 
    int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];

    /**
     * @var Размер матрицы.
     */ 
    int size;

    /**
     * @vars Переменные для индексов строк и столбцов.
     */ 
    int i, j;

    /**
     * @var Переменная для обхода матрицы при линеаризации.
     */ 
    int k;

    /**
     * @var Флаг направления движения "наискосок".
     *          Если он четный, то двигаться надо 
     *              вниз по строкам и вправо по столбцам.
     *          Если он нечетный, то двигаться надо
     *              вверх по строкам и влево по столбцам.
     */ 
    int direction = 1; 

    /**
     * @var Флаг изменения строк.
     */ 
    bool_t is_row_changed = TRUE; 

    /**
     * @var Флаг изменения столбцов.
     */ 
    bool_t is_col_changed = TRUE;

    /*
     * Cчитываем размер матрицы.
     */ 
    scanf("%d", &size);

    /*
     * Защита от дурака.
     */ 
    if(!((0 <= size) &&  (size <= MAX_MATRIX_SIZE))){
        printf("wrong input\n");
        return 1;
    }
    
    /*
     * Cчитываем саму матрицу.
     */ 
    for(i = 0; i != size; ++i)
        for(j = 0; j != size; ++j)
            scanf("%d", &matrix[i][j]);

    /*
     * Обход и печать матрицы
     */ 
    i = size - 1; 
    j = 0;
    printf("%d ", matrix[i][j]);

    for(k = 1; k <= size * size - 1; ++k){
        if(
            (TRUE == is_row_changed) 
            && (
                (
                    /* матрица четная */
                    (0 == (size % 2)) 
                    && (0 != i) 
                    && ((0 == j) || ((size - 1) == j))
                ) || (
                    /* матрица нечетная */
                    (0 != (size % 2))
                    && (0 != i) 
                    && ((size - 1) != i) 
                    && ((0 == j) || ((size - 1) == j))
                ) || (
                    (size - 1 == i) 
                    && (0 == j)
                )
            )
        ){
            if(DEBUG){
                /* Отладочная печать */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d\n", 
                    k, i, j, matrix[i][j]
                );
            }
            /*
             * Идем вверх по стокам.
             */ 
            --i;
            is_row_changed = FALSE;
            is_col_changed = TRUE;
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d (up)\n", 
                    k, i, j, matrix[i][j]
                );
            }
        }
        else if(
            (TRUE == is_col_changed)
            && (
                (
                    (0 == (size % 2)) 
                    && ((size - 1) != j) 
                    && (0 != j) 
                    && ((0 == i) || ((size - 1) == i))
                ) || (
                    (0 != (size % 2))  
                    && ((0 == i) || ((size - 1) == i))
                )
            )
        ){
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d\n", 
                    k, i, j, matrix[i][j]
                );
            }
            /*
             * Идем вправо по столбцам.
             */ 
            ++j;
            is_row_changed = TRUE;
            is_col_changed = FALSE;
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d (right)\n", 
                    k, i, j, matrix[i][j]
                );
            }
        }
        else if(0 != (direction % 2)) {
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d\n", 
                    k, i, j, matrix[i][j]
                );
            }
            /*
             * Идем вниз по строкам и вправо по столбцам.
             */ 
            ++i;
            ++j;
            if(((size - 1) == i) || ((size - 1) == j)){
                ++direction;
            }
            is_row_changed = TRUE;
            is_col_changed = TRUE;
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d (down, right)\n", 
                    k, i, j, matrix[i][j]
                );
            }
        }
        else {
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d\n", 
                    k, i, j, matrix[i][j]
                );
            }
            /*
             * Идем вверх по строкам и влево по столбцам.
             */ 
            --i;
            --j;
            if ((0 == i) || (0 == j)){
                ++direction;
            }
            is_col_changed = TRUE;
            is_row_changed = TRUE;
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d (top, left)\n", 
                    k, i, j, matrix[i][j]
                );
            }
        }
        printf("%d ", matrix[i][j]);
    }
     printf("\n");
    return 0;
}