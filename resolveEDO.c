#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>
#include "utils.h" 
#include "edo.h"
#include <likwid.h>

int main() {
    EDo edo;
    // 1ª linha: n
    if (scanf("%d", &edo.n) != 1) return 0;
    // 2ª linha: a b
    scanf("%lf %lf", &edo.a, &edo.b);
    // 3ª linha: ya yb
    scanf("%lf %lf", &edo.ya, &edo.yb);
    // 4ª linha: p q
    scanf("%lf %lf", &edo.p, &edo.q);

    // Define arredondamento para baixo
    fesetround(FE_DOWNWARD);

    // Para cada conjunto de r1, r2, r3, r4
    while (scanf("%lf %lf %lf %lf", &edo.r1, &edo.r2, &edo.r3, &edo.r4) == 4) {
        // Gera sistema tridiagonal
        Tridiag *sl = genTridiag(&edo);
        // Imprime matriz aumentada
        prnEDOsl(&edo);

        // Fatoração LU (inplace)
        factorLU(sl);

        // Mede tempo de resolução
        rtime_t t0 = timestamp();
        real_t *sol = solveTridiag(sl);

        // Imprime vetor solução
        for (int i = 0; i < sl->n; ++i) {
            printf(" % .15e", sol[i]);
        }
        printf("\n");

        // Imprime tempo em milissegundos
        rtime_t t_elapsed = timestamp() - t0;
        printf("%.8e\n", t_elapsed);

        // Limpeza
        //free(sol);
        //freeTridiag(sl);

        printf("\n");
    }
    return 0;
}
