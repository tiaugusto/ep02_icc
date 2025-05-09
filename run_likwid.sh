#!/usr/bin/env bash
#
# run_likwid.sh — executa resolveEDO sob LIKWID e extrai só o FP_ARITH_INST_RETIRED_SCALAR_DOUBLE
#
# Uso: 
#   ./run_likwid.sh [arquivo_de_entrada]

INPUT_ARG=""
if [ -n "$1" ]; then
  INPUT_ARG="< \"$1\""
fi

# Ajuste de afinidade e seleção de core: aqui exemplificamos S0:0, 
# mas você pode usar -C all ou outro core/socket conforme sua máquina.
CORE_SPEC="3"

# Executa resolveEDO sob LIKWID em modo marker, capturando FLOPS_DP
# e filtra apenas as linhas com o contador desejado.
eval likwid-perfctr -C ${CORE_SPEC} -g FLOPS_DP -m -- ./resolveEDO ${INPUT_ARG} 2>&1 \
  | grep 'FP_ARITH_INST_RETIRED_SCALAR_DOUBLE' \
  | sed -E 's/.*\|\s*FP_ARITH_INST_RETIRED_SCALAR_DOUBLE\s*\|\s*([0-9]+)\s*\|.*/FP_ARITH_INST_RETIRED_SCALAR_DOUBLE,\1/' 
