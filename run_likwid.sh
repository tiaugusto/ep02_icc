#!/usr/bin/env bash
#
# run_likwid.sh — saída normal + depois só FP_ARITH_INST_RETIRED_SCALAR_DOUBLE,valor
#
# Uso: ./run_likwid.sh [INPUT_FILE] [CPU]
# Ex.: ./run_likwid.sh caso_teste.txt 3

INPUT=${1:-}    # se vazio, lê de stdin
CPU=${2:-3}     # core padrão

# 1) saída normal do programa
if [[ -n "$INPUT" ]]; then
  ./resolveEDO < "$INPUT"
else
  ./resolveEDO
fi

# 2) roda LIKWID e extrai só as linhas do contador (campo numérico entre pipes)
if [[ -n "$INPUT" ]]; then
  likwid-perfctr -C "$CPU" -g FLOPS_DP -m -- ./resolveEDO < "$INPUT"
else
  likwid-perfctr -C "$CPU" -g FLOPS_DP -m -- ./resolveEDO
fi \
| awk -F'|' '/FP_ARITH_INST_RETIRED_SCALAR_DOUBLE/ { gsub(/ /, "", $4); print "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE," $4 }'
