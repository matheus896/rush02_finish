#!/bin/bash

# Cores para saída
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # Sem cor

# Compilação inicial
echo "--- Compilando o projeto ---"
make fclean && make
if [ ! -f "rush-02" ]; then
    echo -e "${RED}Erro: Executável rush-02 não encontrado.${NC}"
    exit 1
fi

test_count=0
success_count=0

run_test() {
    local label=$1
    local args=$2
    local expected_msg=$3
    local check_valgrind=$4
    
    ((test_count++))
    echo -e "\nTeste $test_count: $label"
    echo "Comando: ./rush-02 $args"

    # Execução e captura de saída
    output=$(./rush-02 $args 2>&1)
    
    # Validação de Erro/Saída
    if [[ "$output" == *"$expected_msg"* ]]; then
        echo -e "${GREEN}[OK] Saída esperada encontrada.${NC}"
        ((success_count++))
    else
        echo -e "${RED}[FALHA] Saída incorreta.${NC}"
        echo "  Esperado: $expected_msg"
        echo "  Recebido: $output"
    fi

    # Verificação de Memory Leak com Valgrind
    if [ "$check_valgrind" = true ]; then
        leak_check=$(valgrind --leak-check=full --error-exitcode=1 ./rush-02 $args 2>&1 > /dev/null)
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}[OK] Sem vazamentos de memória.${NC}"
        else
            echo -e "${RED}[ERRO] Vazamento de memória detectado!${NC}"
            valgrind --leak-check=full ./rush-02 $args
        fi
    fi
}

# --- BATERIA DE TESTES ---

# 1. Entradas Inválidas (Devem retornar "Error\n")
run_test "Número negativo" "-42" "Error" true
run_test "Não é um número" "abc" "Error" true
run_test "Número decimal" "10.5" "Error" true
run_test "Espaços/Vazio" " " "Error" true

# 2. Casos de Dicionário (Devem retornar "Dict Error\n")
echo "999: erro_formatacao" > invalid.dict
run_test "Dicionário mal formatado" "invalid.dict 42" "Dict Error" true
rm invalid.dict

# 3. Casos de Sucesso (Exemplos do Subject)
run_test "Conversão Simples (42)" "42" "forty two" true
run_test "Zero" "0" "zero" true
run_test "Número Grande (100.000)" "100000" "one hundred thousand" true

# 4. Stress Test: Números além de Unsigned Int
# O subject exige lidar com números maiores que unsigned int
run_test "Número Gigante (64 bits+)" "123456789012345678901234567890" "" true

echo -e "\n--- Resumo: $success_count/$test_count testes passaram ---"
