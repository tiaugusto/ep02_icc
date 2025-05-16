#ifndef __EQDIFF_H__
#define __EQDIFF_H__

typedef double real_t;

#define FORMAT "%23.15e"

// Sistema linear Tri-diagonal
typedef struct {
  real_t *D, *Di, *Ds, *B;
  int n;
} Tridiag;

// Equação Diferencial Ordinária
typedef struct {
  int n; // número de pontos internos na malha
  real_t a, b; // intervalo
  real_t ya, yb; // condições contorno
  real_t p, q, r1, r2, r3, r4; // coeficientes EDO genérica
} EDo;

// Funções auxiliares

// Geração e liberação do sistema
Tridiag *genTridiag (EDo *edoeq);
void prnEDOsl (EDo *edoeq);
void freeTridiag(Tridiag *sl);

// Solução da EDO
real_t *solveTridiag(Tridiag *sl);

// Computa LU
void factorLU(Tridiag *sl);

#endif // __EQDIFF_H__

