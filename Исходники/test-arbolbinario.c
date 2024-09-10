END_TEST

/* Prueba unitaria para arbol_binario_gira_derecha. */
START_TEST(test_arbol_binario_gira_derecha)
{
        srand((unsigned int)time(NULL));
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        int total = rand() % N;
        if (total == 1)
            total++;
        int* a = arreglo_sin_repetidos(total);
        a[total-2] = 2001;
        a[total-1] = 2000;
        for (int i = 0; i < total; i++)
                arbol_binario_ordenado_agrega(arbol, &a[i]);
        NodoArbolBinario* nodo = NULL;
        int Q = -1;
        do {
                Q = a[rand() % total];
                nodo = arbol_binario_ordenado_busca(arbol, &Q);
                fail_unless(nodo != NULL);
                void* e = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(e, &Q));
        } while (nodo_arbol_binario_izquierdo(nodo) == NULL);
        nodo = nodo_arbol_binario_izquierdo(nodo);
        int* n = nodo_arbol_binario_elemento(nodo);
        int P = *n;
        int A = -1, B = -1, C = -1;
        if (nodo_arbol_binario_izquierdo(nodo) != NULL) {
                nodo = nodo_arbol_binario_izquierdo(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                A = *n;
                nodo = nodo_arbol_binario_padre(nodo);
        }
        if (nodo_arbol_binario_derecho(nodo) != NULL) {
                nodo = nodo_arbol_binario_derecho(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                B = *n;
                nodo = nodo_arbol_binario_padre(nodo);
        }
        nodo = nodo_arbol_binario_padre(nodo);
        if (nodo_arbol_binario_derecho(nodo) != NULL) {
                nodo = nodo_arbol_binario_derecho(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                C = *n;
                nodo = nodo_arbol_binario_padre(nodo);
        }
        arbol_binario_gira_derecha(arbol, nodo);
        fail_unless(arbol_binario_elementos(arbol) == total);
        fail_unless(arbol_binario_valido(arbol));
        fail_unless(arbol_binario_ordenado_valido(arbol));
        for (int i = 0; i < total; i++) {
                NodoArbolBinario* tmp;
                tmp = arbol_binario_ordenado_busca(arbol, &a[i]);
                fail_unless(tmp != NULL);
        }
        n = nodo_arbol_binario_elemento(nodo);
        fail_unless(!compara_enteros(n, &Q));
        fail_unless(nodo_arbol_binario_padre(nodo) != NULL);
        nodo = nodo_arbol_binario_padre(nodo);
        n = nodo_arbol_binario_elemento(nodo);
        fail_unless(!compara_enteros(n, &P));
        if (A != -1) {
                fail_unless(nodo_arbol_binario_izquierdo(nodo) != NULL);
                nodo = nodo_arbol_binario_izquierdo(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(n, &A));
                nodo = nodo_arbol_binario_padre(nodo);
        }
        fail_unless(nodo_arbol_binario_derecho(nodo) != NULL);
        nodo = nodo_arbol_binario_derecho(nodo);
        n = nodo_arbol_binario_elemento(nodo);
        fail_unless(!compara_enteros(n, &Q));
        if (B != -1) {
                fail_unless(nodo_arbol_binario_izquierdo(nodo) != NULL);
                nodo = nodo_arbol_binario_izquierdo(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(n, &B));
                nodo = nodo_arbol_binario_padre(nodo);
        }
        if (C != -1) {
                fail_unless(nodo_arbol_binario_derecho(nodo) != NULL);
                nodo = nodo_arbol_binario_derecho(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(n, &C));
                nodo = nodo_arbol_binario_padre(nodo);
        }
        arbol_binario_libera(arbol);
        free(a);
}