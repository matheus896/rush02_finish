# Guia de Defesa - Rush02
## Conversor de Números para Texto Extenso

> **Autores:** matalmei, gabrielo, cida-sil
> **Projeto:** Rush02 - 42 Piscine  
> **Data:** Fevereiro 2026

---

# Parte 1: Explicação Arquitetural (O "Big Picture")

## 1.1 Visão Geral do Fluxo de Dados

O Rush02 converte um número (string) para sua representação textual em inglês, usando um dicionário customizável. O fluxo completo pode ser visualizado assim:

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                              FLUXO PRINCIPAL                                │
└─────────────────────────────────────────────────────────────────────────────┘

    ./rush-02 [dict] <number>
              │
              ▼
    ┌─────────────────┐
    │     main()      │  ──► Valida argc (2 ou 3 args)
    │    main.c       │  ──► Seleciona path do dicionário
    └────────┬────────┘  ──► Valida se input é dígito (is_digit)
             │
             ▼
    ┌─────────────────┐      ┌──────────────────────────────┐
    │  parse_dict()   │ ───► │  read_file()                 │
    │    main.c       │      │  Lê arquivo para string      │
    └────────┬────────┘      └──────────────────────────────┘
             │                         │
             │                         ▼
             │               ┌──────────────────────────────┐
             │               │  get_lines()                 │
             │               │  Conta '\n' para dimensionar │
             │               │  o array de t_dict           │
             │               └──────────────────────────────┘
             │                         │
             │                         ▼
             │               ┌──────────────────────────────┐
             │               │  fill_dict()                 │
             │               │  Percorre string, extrai     │
             │               │  linhas e chama fill_struct  │
             │               └──────────────────────────────┘
             │                         │
             │                         ▼
             │               ┌──────────────────────────────┐
             │               │  fill_struct()               │
             │               │  - Separa key:value pelo ':' │
             │               │  - ft_trim() remove espaços  │
             │               │  - ft_strdup() aloca cópias  │
             │               └──────────────────────────────┘
             │
             ▼
    ┌─────────────────┐
    │ process_solve() │  ──► Prepara struct t_solver
    │    main.c       │  ──► Executa ft_solve() 2x (validação + impressão)
    └────────┬────────┘
             │
             ▼
    ┌─────────────────┐
    │   ft_solve()    │  ──► Recursão: processa chunks de 3 dígitos
    │  solver_2.c     │  ──► Chama solve_chunk() para cada trio
    └────────┬────────┘
             │
             ├────────────────────────┐
             ▼                        ▼
    ┌─────────────────┐      ┌─────────────────┐
    │ print_3_digits()│      │print_magnitude()│
    │   solver.c      │      │   solver.c      │
    │                 │      │                 │
    │ Decompõe:       │      │ Imprime:        │
    │ - Centenas      │      │ thousand        │
    │ - Dezenas       │      │ million         │
    │ - Unidades      │      │ billion...      │
    └─────────────────┘      └─────────────────┘
             │
             ▼
    ┌─────────────────┐
    │ search_and_print│ ──► get_word() busca no dicionário
    │  ft_utils2.c    │ ──► ft_putword() imprime com espaço
    └─────────────────┘
             │
             ▼
         STDOUT
```

---

## 1.2 Estruturas de Dados

### t_dict - O Dicionário
```c
typedef struct s_dict
{
    char    *key;   // Ex: "1000000" (string, não int!)
    char    *word;  // Ex: "million"
}           t_dict;
```

**Por que `key` é `char *` e não `unsigned long long`?**
- O subject exige lidar com números **além do range de unsigned int**
- Armazenar como string permite comparar números de qualquer tamanho
- Evita problemas de overflow na comparação de chaves

### t_solver - O Estado do Solver
```c
typedef struct s_solver
{
    t_dict  *dict;   // Ponteiro para o array de dicionário
    int     size;    // Quantidade de entradas no dicionário
    int     *first;  // Flag: "é a primeira palavra?" (para espaços)
    int     print;   // Flag: 0 = só validar, 1 = imprimir
}           t_solver;
```

**Por que usar uma struct auxiliar?**
- Evita passar 4+ parâmetros para cada função (limite da Norma)
- `first` é um **ponteiro** porque precisa ser modificado por várias funções
- `print` permite reusar a lógica: primeiro valida, depois imprime

---

## 1.3 O Parser de Dicionário (dict_parser.c)

### Etapa 1: read_file()
```
┌────────────────────────────────────────────────────────────┐
│ 1ª PASSAGEM: Conta tamanho (byte a byte)                   │
│    fd = open() ──► while(read(fd, &buffer, 1)) ──► close() │
│                                                            │
│ 2ª PASSAGEM: Lê conteúdo completo                          │
│    fd = open() ──► read(fd, content, total_size) ──► close │
└────────────────────────────────────────────────────────────┘
```

### Etapa 2: fill_dict()
```
Entrada: "20 : twenty\n30: thirty\n"
                      │
                      ▼
         Percorre procurando '\n'
                      │
      ┌───────────────┴───────────────┐
      ▼                               ▼
   linha 1                         linha 2
 "20 : twenty"                   "30: thirty"
      │                               │
      ▼                               ▼
 fill_struct()                   fill_struct()
```

### Etapa 3: fill_struct()
```
Entrada: "20 : twenty"
              │
              ▼
    Encontra ':' na posição 3
    Substitui por '\0': "20 \0 twenty"
              │
              ▼
    ft_trim("20 ")  ──►  "20"      (remove espaços)
    ft_trim(" twenty") ──► "twenty"
              │
              ▼
    dict[i].key = ft_strdup("20")
    dict[i].word = ft_strdup("twenty")
```

---

## 1.4 O Algoritmo de Decomposição (solver.c / solver_2.c)

### Conceito Central: Decomposição em Trios

Números são decompostos em grupos de 3 dígitos (da direita para esquerda), cada grupo associado a uma magnitude:

```
Número: 1,234,567,890
        │ │   │   │
        │ │   │   └── 890 (unidades)
        │ │   └────── 567 thousand
        │ └────────── 234 million
        └──────────── 1   billion
```

### ft_solve() - A Recursão

```c
int ft_solve(char *num_str, t_solver *s)
{
    len = str_len(num_str);        // Tamanho restante
    chunk = len % 3;               // Quantos dígitos no primeiro chunk
    if (chunk == 0) chunk = 3;     // Se divisível por 3, pega 3
    
    solve_chunk(num_str, chunk, len, s);  // Processa este chunk
    
    return ft_solve(num_str + chunk, s);  // Recursão: próximo chunk
}
```

**Exemplo visual com "1234567":**

```
Iteração 1: "1234567" (len=7)
            chunk = 7 % 3 = 1
            Processa "1" + magnitude(6 zeros) = "one million"
            Recursão com "234567"

Iteração 2: "234567" (len=6)
            chunk = 6 % 3 = 0 → chunk = 3
            Processa "234" + magnitude(3 zeros) = "two hundred thirty four thousand"
            Recursão com "567"

Iteração 3: "567" (len=3)
            chunk = 3 % 3 = 0 → chunk = 3
            Processa "567" + sem magnitude = "five hundred sixty seven"
            Recursão com "" (vazio)

Iteração 4: "" (len=0)
            return (1) ── FIM DA RECURSÃO
```

### print_3_digits() - Decomposição de um Trio

```
Entrada: n = 234
         │
         ▼
┌────────────────────────────────────┐
│ Se n >= 100:                       │
│   print(n/100) + print("hundred")  │  ──► "two hundred"
│   n = n % 100 = 34                 │
└────────────────────────────────────┘
         │
         ▼
┌────────────────────────────────────┐
│ Se n >= 20:                        │
│   print((n/10)*10) = print(30)     │  ──► "thirty"
│   Se n%10 > 0: print(n%10) = 4     │  ──► "four"
└────────────────────────────────────┘

Resultado: "two hundred thirty four"
```

### print_magnitude() - Geração de Chave Dinâmica

```c
// Para imprimir "million" (6 zeros):
key = malloc(zeros + 2);  // "1" + 6 zeros + '\0'
key[0] = '1';
// Preenche com '0': key = "1000000"
word = get_word("1000000", dict, size);  // Retorna "million"
```

---

## 1.5 O Mecanismo de Duas Passagens

```c
void process_solve(t_dict *dict, char *num, int count)
{
    // PASSAGEM 1: Validação (print = 0)
    s.print = 0;
    if (ft_solve(num, &s))  // Se retornou 1, todas as palavras existem
    {
        // PASSAGEM 2: Impressão (print = 1)
        s.print = 1;
        ft_solve(num, &s);  // Agora imprime
        write(1, "\n", 1);
    }
    else
        write(1, "Dict Error\n", 11);
}
```

**Por que duas passagens?**
- Evita imprimir parcialmente e depois falhar
- Garante output limpo: ou imprime tudo, ou imprime "Dict Error"

---

# Parte 2: Inquisição do Avaliador (Perguntas e Respostas)

## Categoria: Memória e I/O

### P1: "Por que você lê o arquivo caractere por caractere em read_file() para pegar o tamanho? Isso é eficiente? Por que fechar e abrir o fd novamente?"

**Resposta Ideal:**
> "Lemos byte a byte na primeira passagem porque as únicas funções permitidas são `read`, `write`, `malloc`, `free`, `open` e `close`. Não temos acesso a `fstat()` ou `lseek()` para descobrir o tamanho do arquivo de forma mais eficiente.
>
> Fechamos e reabrimos porque após a primeira `read()` completa, o cursor do arquivo está no final. Poderíamos usar `lseek(fd, 0, SEEK_SET)` para reposicionar, mas `lseek` não está na lista de funções permitidas. A alternativa seria armazenar cada byte lido num buffer dinâmico com `realloc`, mas isso adiciona complexidade e `realloc` também não é permitido.
>
> Quanto à eficiência: sim, é O(2n), mas para arquivos de dicionário pequenos (alguns KB) é aceitável. O trade-off foi simplicidade vs. performance."

---

### P2: "O que acontece se eu mudar o tamanho do buffer em read_file() de 1 para 1024? O código quebra?"

**Resposta Ideal:**
> "A lógica atual assume `buffer` de 1 byte. Com buffer maior:
>
> 1. `total_size++` ainda incrementa 1 por iteração, não pelo número de bytes lidos
> 2. O tamanho calculado seria incorreto (menor que o real)
> 3. A segunda `read()` alocaria menos memória que necessário → **buffer overflow**
>
> Para corrigir, teríamos que fazer `total_size += bytes_read` e ajustar a lógica para considerar o último `read()` parcial."

---

### P3: "O que acontece se eu remover o free_dictionary() no final do main?"

**Resposta Ideal:**
> "O programa ainda funcionaria corretamente em termos de output, mas teríamos **memory leak**. Especificamente:
>
> - Cada entrada do dicionário tem `key` e `word` alocados via `ft_strdup()` → `malloc()`
> - Com ~30 entradas e strings de ~10 chars, perderíamos ~600 bytes por execução
> - Na avaliação, ferramentas como `valgrind --leak-check=full` detectariam isso
> - O subject exige: 'Any memory allocated in the heap must be properly freed'"

---

### P4: "Por que vocês usam ft_strdup() para key e word em vez de apenas apontar para a string original?"

**Resposta Ideal:**
> "Por três razões:
>
> 1. **Modificamos a string original**: `fill_dict()` substitui `\n` por `\0` e `fill_struct()` substitui `:` por `\0`. Se apontássemos diretamente, as strings seriam válidas, mas...
>
> 2. **Liberamos file_str após o parse**: `free(file_str)` em `parse_dict()` invalida todos os ponteiros para dentro dela. `ft_strdup()` cria cópias independentes.
>
> 3. **Lifetime management**: Com cópias, cada `t_dict` é autossuficiente. Podemos liberar `file_str` imediatamente após o parse, reduzindo uso de memória durante a execução do solver."

---

## Categoria: Lógica e Algoritmo

### P5: "Em ft_solve(), como vocês decidem quando imprimir a magnitude (thousand, million)?"

**Resposta Ideal:**
> "A decisão é baseada em `len - chunk`, que representa quantos dígitos restam após o chunk atual:
>
> ```c
> if (len - chunk > 0)
>     print_magnitude(len - chunk, s);
> ```
>
> - Se `len - chunk = 3`, imprimimos magnitude para 1000 (thousand)
> - Se `len - chunk = 6`, imprimimos magnitude para 1000000 (million)
>
> `print_magnitude()` constrói a chave dinamicamente: `'1'` seguido de `(len - chunk)` zeros. Isso permite suportar magnitudes arbitrárias, desde que existam no dicionário."

---

### P6: "Por que chunk = len % 3 e depois if (chunk == 0) chunk = 3?"

**Resposta Ideal:**
> "Porque decompomos da **esquerda para a direita**, mas os grupos são definidos da **direita para a esquerda**:
>
> ```
> 1,234,567 → grupos: [1] [234] [567]
>             len=7, 7%3=1, primeiro chunk tem 1 dígito
>
> 234,567 → grupos: [234] [567]  
>           len=6, 6%3=0, mas queremos 3, não 0
> ```
>
> Quando `len % 3 == 0`, significa que todos os grupos têm exatamente 3 dígitos, então o primeiro chunk também deve ter 3."

---

### P7: "Por que vocês tratam números de 1-19 diferente de 20-99 em print_3_digits()?"

**Resposta Ideal:**
> "Porque a língua inglesa tem palavras únicas para 1-19 (one, two, ..., eleven, twelve, ..., nineteen), mas de 20 em diante segue um padrão composto (twenty + one, thirty + five, etc.).
>
> ```c
> if (n >= 20)
>     print((n/10)*10);  // "twenty", "thirty"...
>     print(n % 10);     // "one", "two"...
> else if (n > 0)
>     print(n);          // "eleven", "thirteen"...
> ```
>
> Se tentássemos decompor 'fifteen' como 'ten' + 'five', seria incorreto. O dicionário precisa ter entradas explícitas para 10-19."

---

### P8: "Por que criar uma struct t_solver em vez de passar variáveis soltas?"

**Resposta Ideal:**
> "Por conformidade com a Norma 42:
>
> 1. **Limite de 4 parâmetros por função**: `ft_solve()` precisa de `dict`, `size`, `first`, e `print`. Sem a struct, já atingimos o limite, impossibilitando passar `num_str`.
>
> 2. **Manutenibilidade**: Adicionar um novo estado (ex: idioma, separador) requer apenas modificar a struct, não a assinatura de todas as funções.
>
> 3. **Semântica clara**: `t_solver` encapsula 'o contexto necessário para resolver o número'. É mais legível que `int *first, int print, t_dict *dict, int size`."

---

## Categoria: Edge Cases e Validação

### P9: "O que acontece se o input for '0'? E se for '00000'?"

**Resposta Ideal:**
> "Ambos funcionam corretamente:
>
> - Para `'0'`: `ft_solve()` processa chunk de 1 dígito, `ft_atoi("0") = 0`, entra no `else if (*s->first == 1 && len == chunk)` em `solve_chunk()`, imprime 'zero'.
>
> - Para `'00000'`: Os chunks serão `[00]` e `[000]`. `ft_atoi("00") = 0` e `ft_atoi("000") = 0`. Como os valores são 0, não imprimem nada (ignorados), exceto o último chunk quando `first` ainda é 1.
>
> Importante: `is_digit()` aceita `'00000'` como válido (são todos dígitos), e a lógica do solver trata corretamente."

---

### P10: "O código lida corretamente com o maior unsigned int (4294967295)? E números maiores?"

**Resposta Ideal:**
> "Sim, e essa é uma das decisões arquiteturais mais importantes:
>
> 1. **Nunca convertemos o número completo para int**: O número permanece como string durante todo o processamento.
>
> 2. **ft_atoi() só é chamado para chunks de até 3 dígitos**: O máximo é 999, que cabe confortavelmente em um `int`.
>
> 3. **Comparação de chaves é string vs string**: `get_word()` usa `ft_strcmp()`, não comparação numérica.
>
> 4. **Magnitudes suportadas**: O dicionário inclui até 'undecillion' (10^36), muito além de `unsigned long long` (máx ~1.8×10^19).
>
> O único limite é o tamanho da string de input e as entradas disponíveis no dicionário."

---

### P11: "E se o dicionário tiver uma linha malformada como '20: ' (valor vazio)?"

**Resposta Ideal:**
> "A linha seria aceita:
>
> 1. `fill_struct()` encontra o `:`, separa key='20' e value=' '
> 2. `ft_trim(' ')` retorna string vazia `''`
> 3. `ft_strdup('')` aloca 1 byte contendo apenas `\0`
> 4. `dict[i].word` aponta para string vazia válida
>
> Quando `get_word('20')` retorna `''`, `ft_putword()` verifica `if (*word == '\0') return;` e não imprime nada.
>
> **Impacto**: O número 20 seria silenciosamente ignorado na saída. Poderíamos adicionar validação em `fill_struct()` para rejeitar valores vazios se desejado."

---

### P12: "O que acontece se o dicionário não tiver a entrada para '100' (hundred)?"

**Resposta Ideal:**
> "O programa imprime 'Dict Error':
>
> ```c
> // Em print_hundreds() (solver.c)
> if (!get_word('100', s->dict, s->size))
> {
>     free(k);
>     return (0);  // Propaga falha
> }
> ```
>
> A falha propaga: `print_hundreds() → print_3_digits() → solve_chunk() → ft_solve() → process_solve()`, que detecta o retorno 0 e imprime 'Dict Error'.
>
> É por isso que fazemos duas passagens: a primeira (print=0) valida que todas as palavras necessárias existem antes de imprimir qualquer coisa."

---

### P13: "Por que is_digit() aceita '+' no início mas não '-'?"

**Resposta Ideal:**
> "O subject especifica: 'If the argument that represents the number is not a valid and positive integer, your program must print Error'.
>
> Números negativos são explicitamente rejeitados ('positive integer'). O `+` é comum como prefixo opcional em representações numéricas, então decidimos aceitá-lo por conveniência.
>
> ```c
> if (num[i] == '+')
>     i++;  // Pula o +, processa o resto como dígitos
> ```
>
> Se quiséssemos ser mais estritos, poderíamos remover essa tolerância."

---

### P14: "Há risco de overflow no ft_atoi() que vocês implementaram?"

**Resposta Ideal:**
> "Teoricamente sim, mas na prática não:
>
> ```c
> int ft_atoi(char *str)
> {
>     atoi *= 10;
>     atoi += str[i] - '0';
> }
> ```
>
> **Risco teórico**: Se passássemos uma string como '9999999999', haveria overflow.
>
> **Proteção na prática**: `ft_atoi()` só é chamado em dois lugares:
> 1. `solve_chunk()` com `temp_chunk[4]` - máximo 3 dígitos (999)
> 2. `print_3_digits()` já recebe `int n` que veio do chunk
>
> O chunk nunca excede 3 caracteres, então o máximo é 999, seguro para `int`.
>
> Se quiséssemos robustez extra, poderíamos adicionar verificação de overflow ou usar `unsigned int`."

---

### P15: "Explique a flag 'first' e por que é um ponteiro."

**Resposta Ideal:**
> "`first` controla se devemos imprimir um espaço antes da próxima palavra:
>
> ```c
> void ft_putword(char *word, int *first, int print)
> {
>     if (*first == 0)
>         ft_putstr(' ');  // Espaço antes de palavras subsequentes
>     ft_putstr(word);
>     *first = 0;  // Próximas palavras não são mais 'first'
> }
> ```
>
> É um ponteiro porque **múltiplas funções precisam modificar o mesmo estado**:
> - `ft_putword()` seta `*first = 0` após imprimir
> - `process_solve()` reseta `first = 1` entre passagens
>
> Se passássemos `int first` por valor, cada função teria sua própria cópia e as modificações não seriam visíveis às outras."

---

# Parte 3: Análise de Edge Cases e Tratamento de Erros

## 3.1 Mapeamento de Erros

```
┌─────────────────────────────────────────────────────────────────────────┐
│                        FLUXO DE TRATAMENTO DE ERROS                     │
└─────────────────────────────────────────────────────────────────────────┘

┌─────────────────┬───────────────────────────────────────┬───────────────┐
│ CONDIÇÃO        │ ONDE É DETECTADO                      │ OUTPUT        │
├─────────────────┼───────────────────────────────────────┼───────────────┤
│ argc != 2 && 3  │ main.c: linha 77                      │ "Error\n"     │
│ num não é dígito│ main.c: !is_digit(num)                │ "Error\n"     │
│ num é vazio ""  │ dict_parser.c: is_digit() retorna 0   │ "Error\n"     │
│ num tem letras  │ dict_parser.c: is_digit() retorna 0   │ "Error\n"     │
├─────────────────┼───────────────────────────────────────┼───────────────┤
│ Arquivo não abre│ dict_parser.c: open() == -1           │ "Dict Error\n"│
│ malloc falha    │ Vários locais                         │ "Dict Error\n"│
│ Linha sem ':'   │ dict_parser.c: fill_struct()          │ "Dict Error\n"│
│ Key vazia/inval │ dict_parser.c: fill_struct()          │ "Dict Error\n"│
│ Palavra faltando│ solver.c: get_word() == NULL          │ "Dict Error\n"│
└─────────────────┴───────────────────────────────────────┴───────────────┘
```

## 3.2 Casos de Teste Críticos

### Input Numérico
| Input | Esperado | Observação |
|-------|----------|------------|
| `42` | `forty two` | Caso básico |
| `0` | `zero` | Zero isolado |
| `00042` | `forty two` | Zeros à esquerda |
| `1000` | `one thousand` | Magnitude simples |
| `1000000` | `one million` | Magnitude sem unidades |
| `1001001` | `one million one thousand one` | Zeros no meio |
| `4294967295` | `four billion...` | Maior unsigned int |
| `999999999999` | `nine hundred ninety nine billion...` | 12 dígitos |

### Input Inválido → "Error"
| Input | Razão |
|-------|-------|
| (nenhum arg) | argc < 2 |
| `abc` | Não é dígito |
| `12.5` | Ponto não é dígito |
| `-42` | Negativo rejeitado |
| `12 34` | Espaço não é dígito |
| `""` | String vazia |

### Dicionário Inválido → "Dict Error"
| Situação | Razão |
|----------|-------|
| Arquivo não existe | `open()` falha |
| Linha sem `:` | `fill_struct()` retorna 0 |
| Key não numérica | `is_digit(trimmed_key)` falha |
| Falta entrada para `20` | `get_word("20")` retorna NULL |

## 3.3 Análise de Robustez

### Pontos Fortes
1. **Validação em duas passagens**: Nunca imprime output parcial
2. **Números como strings**: Sem limite de tamanho
3. **Liberação de memória**: `free_dictionary()` + `free(dict)` + `free(file_str)`
4. **Tratamento de espaços**: `ft_trim()` remove whitespace do dicionário

### Pontos de Atenção (para discussão)
1. **ft_trim() bug potencial**: Na linha 24 de `ft_utils.c`, a condição `*string >= 9 && *string <= 13` deveria ser `string[i] >= 9 && string[i] <= 13` para o trim final
2. **Linhas sem \n final**: Se o arquivo não termina com `\n`, a última linha pode não ser processada
3. **Dicionário com entradas duplicadas**: A primeira entrada encontrada é usada (comportamento de `get_word()`)

## 3.4 Comandos para Testar

```bash
# Testes básicos
./rush-02 42
./rush-02 0
./rush-02 1000000

# Edge cases
./rush-02 00000
./rush-02 999999999999999999999999999999999999

# Erros de input
./rush-02
./rush-02 abc
./rush-02 -1
./rush-02 12.5

# Dicionário customizado
./rush-02 custom.dict 42

# Verificação de memória (Linux)
valgrind --leak-check=full ./rush-02 42
```

---

# Parte 4: Glossário de Funções

| Função | Arquivo | Responsabilidade |
|--------|---------|------------------|
| `main` | main.c | Entry point, validação de args, orquestra fluxo |
| `parse_dict` | main.c | Coordena parsing: read → count → fill |
| `process_solve` | main.c | Executa solver em 2 passagens |
| `read_file` | dict_parser.c | Lê arquivo inteiro para string |
| `get_lines` | dict_parser.c | Conta linhas para dimensionar array |
| `fill_dict` | dict_parser.c | Itera linhas, chama fill_struct |
| `fill_struct` | dict_parser.c | Extrai key:value de uma linha |
| `is_digit` | dict_parser.c | Valida se string é número positivo |
| `ft_solve` | solver_2.c | Recursão principal: divide em chunks |
| `solve_chunk` | solver_2.c | Processa um chunk + magnitude |
| `print_3_digits` | solver.c | Decompõe trio em centenas/dezenas/unidades |
| `print_hundreds` | solver.c | Imprime parte das centenas |
| `print_magnitude` | solver.c | Imprime thousand/million/etc |
| `itokey` | solver.c | Converte int para string (chave) |
| `get_word` | solver.c | Busca palavra no dicionário |
| `search_and_print` | ft_utils2.c | Busca e imprime (wrapper) |
| `free_dictionary` | ft_utils2.c | Libera keys e words alocados |
| `ft_trim` | ft_utils.c | Remove espaços das bordas |
| `ft_strdup` | ft_utils.c | Duplica string com malloc |
| `ft_strcmp` | ft_utils.c | Compara duas strings |
| `ft_atoi` | ft_utils.c | String para int (até 3 dígitos) |
| `ft_putword` | main_utils.c | Imprime palavra com espaço |
| `ft_putstr` | main_utils.c | Imprime string |
| `bad_input` | main_utils.c | Imprime erro apropriado |

---

# Parte 5: Dicas Finais para a Defesa

## O que demonstrar domínio:

1. **Saber explicar o fluxo completo** do main até o output
2. **Entender por que duas passagens** (validação + impressão)
3. **Explicar a recursão** em `ft_solve()` com um exemplo numérico
4. **Justificar as estruturas** `t_dict` e `t_solver`
5. **Saber onde cada tipo de erro é tratado**
6. **Explicar por que key é string** (números maiores que unsigned int)

## Frases-chave para usar:

- "O número nunca é convertido para inteiro completo, apenas chunks de 3 dígitos"
- "A primeira passagem valida, a segunda imprime - isso garante output atômico"
- "A struct t_solver agrupa o contexto para respeitar o limite de 4 parâmetros"
- "ft_strdup() cria cópias porque liberamos file_str após o parse"
- "A magnitude é calculada dinamicamente: '1' + N zeros"

---

> "O segredo não é apenas o código funcionar, mas demonstrar domínio sobre *por que* ele foi feito dessa forma."
