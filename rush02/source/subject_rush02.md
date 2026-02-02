# C Piscine

## Rush

_Preâmbulo: Este documento é o subject para o Rush02 da C Piscine na 42._

```
Versão: 11.
```

## Sumário

- II Instruções
- III Instruções de IA
- IV Subject
- V Bônus
- VI Entrega e avaliação por pares


# Capítulo II

# Instruções

- Você deve fazer o projeto com a equipe designada. Reunir-se com seus colegas
    de equipe faz parte de suas tarefas, utilizando qualquer meio apropriado (Slack,
    Discord, e-mail, telefone se disponível, ou diretamente pessoalmente).
- Se você já tentou tudopara entrar em contato um de seus colegas de equipe, mas
    eles ainda permanecem incomunicáveis, siga as instruções de sua equipe pedagógica,
    se fornecidas. O procedimento padrão é fazer o projeto com os colegas de equipe
    disponíveis e discutir a situação durante a avaliação. Mesmo que o líder do grupo
    esteja ausente, você ainda tem acesso ao repositório de submissão.
- Seu trabalho deve cumprir a Norma. Se você tiver arquivos/funções bônus, eles
    serão incluídos na verificação da norma, e você receberá uma pontuação de 0 se
    houver um erro de norma.
- Você deve lidar com erros de forma coerente. Você pode imprimir uma mensagem
    de erro ou simplesmente retornar o controle ao usuário.
- Seu projeto deve ser concluído e enviado ao repositório Git até o prazo exibido na
    página principal do projeto na intranet.
- Você deve seguir o procedimento de submissão descrito no final deste documento,
    se fornecido.
- Seu programa deve compilar usando cc com as seguintes flags: -Wall -Wextra -
    Werror. Se houver uma moulinette, ela usará o mesmo compilador e flags.
- Se seu programa não compilar, você receberá uma pontuação de 0.
- O grupo será automaticamente registrado para a defesa. Você deve comparecer à
    sua avaliação com todosos seus colegas de equipe. O objetivo da defesa é apresentar
    e explicar seu trabalho de forma abrangente.
- Não cancele sua avaliação; você não terá uma segunda.
- Cada membro do grupo deve estar totalmente ciente de todos os detalhes do pro-
    jeto. Se você optar por dividir a carga de trabalho, certifique-se de entender todas as partes concluídas por outros membros da equipe. Essa compreensão pode ser
verificada durante a avaliação.
- Você deve enviar um Makefile, que compilará seu projeto usando as regras $NAME, clean e fclean.


# Capítulo III

# Instruções de IA

## ● Contexto

A C Piscine é intensa. É seu primeiro grande desafio na 42 — um mergulho profundo na
resolução de problemas, autonomia e comunidade.

Durante essa fase, seu objetivo principal é construir sua base — através do esforço, da
repetição e, especialmente, da troca de **aprendizagem entre pares**.

Na era da IA, atalhos são fáceis de encontrar. No entanto, é importante considerar se
o uso da IA está realmente ajudando você a crescer — ou simplesmente atrapalhando o
desenvolvimento de habilidades reais.

A Piscine também é uma experiência humana — e, por enquanto, nada pode substituí-la.
Nem mesmo a IA.

Para uma visão mais completa de nossa posição sobre a IA — como ferramenta de apren-
dizagem, como parte do currículo de TIC e como uma expectativa crescente no mercado
de trabalho — consulte as perguntas frequentes disponíveis na intranet.

## ● Mensagem principal

```
☛ Construa bases sólidas sem atalhos.
```
```
☛ Desenvolva realmente habilidades técnicas e de poder.
```
```
☛ Experimente a verdadeira aprendizagem entre pares, comece a aprender como apren-
der e resolver novos problemas.
```
```
☛ A jornada de aprendizagem é mais importante que o resultado.
```
```
☛ Aprenda sobre os riscos associados à IA e desenvolva práticas de controle eficazes
e contramedidas para evitar armadilhas comuns.
```

● **Regras para o aluno:**

- Você deve aplicar o raciocínio às tarefas atribuídas, especialmente antes de recorrer à IA.
- Você não deve pedir respostas diretas à IA.
- Você deve aprender sobre a abordagem global da 42 em relação à IA.

● **Resultados da fase:**

Dentro desta fase fundamental, você obterá os seguintes resultados:

- Obter bases adequadas em tecnologia e codificação.
- Saber por que e como a IA pode ser perigosa durante esta fase.

● **Comentários e exemplo:**

- Sim, sabemos que a IA existe — e sim, ela pode resolver seus projetos. Mas você
    está aqui para aprender, não para provar que a IA aprendeu. Não perca seu tempo
    (nem o nosso) apenas para demonstrar que a IA pode resolver o problema proposto.
- Aprender na 42 não é sobre saber a resposta — é sobre desenvolver a capacidade
    de encontrá-la. A IA lhe dá a resposta diretamente, mas isso impede você de
    construir seu próprio raciocínio. E o raciocínio leva tempo, esforço e envolve falhas.
    O caminho para o sucesso não deve ser fácil.
- Lembre-se de que durante os exames, a IA não está disponível — sem internet,
    sem smartphones, etc. Você perceberá rapidamente se confiou muito na IA em seu
    processo de aprendizagem.
- A aprendizagem entre pares o expõe a diferentes ideias e abordagens, melhorando
    suas habilidades interpessoais e sua capacidade de pensar de forma divergente. Isso
    é muito mais valioso do que apenas conversar com um bot. Portanto, não seja
    tímido — converse, faça perguntas e aprenda juntos!
- Sim, a IA fará parte do currículo — tanto como ferramenta de aprendizagem quanto
    como tópico em si. Você terá até a chance de construir seu próprio software de
    IA. Para saber mais sobre nossa abordagem crescente, consulte a documentação
    disponível na intranet.


C Piscine Rush

```
✓ Boa prática:
```
```
Estou travado em um novo conceito. Pergunto a alguém próximo como ele abordou
isso. Conversamos por 10 minutos — e de repente, clica. Entendi.
```
```
✗ Má prática:
```
```
Usei secretamente a IA, copiei um código que parece certo. Durante a avaliação entre
pares, não consigo explicar nada. Eu falho. Durante o exame — sem IA — estou
travado novamente. Eu falho.
```

# Capítulo IV

# Subject

```
Exercício : 00
```
```
rush-
Pasta de entrega : ex 00 /
Arquivos para entregar : Makefile e todos os arquivos necessários
Funções ou bibliotecas autorizadas : write, malloc, free, open, read, close
```
- Crie um programa que receba um número como argumento e o converta para seu
    valor escrito por extenso.
- Nome do executável: rush-
- Seu código-fonte será compilado da seguinte forma:

```
make fclean
make
```
- Seu programa pode receber até 2 argumentos:

```
◦ Se houver apenas um argumento, ele é o número que você precisa converter.
```
```
◦ Se houver dois argumentos, o primeiro argumento é o novo dicionário de refe-
rência e o segundo argumento é o número que você precisa converter.
```
- Se o argumento que representa o número não for um inteiro válido e positivo, seu
    programa deve imprimir "Error"seguido de uma nova linha.

```
Seu programa deve lidar com números além do intervalo de um unsigned int.
```

- Seu programa deve analisar o dicionário fornecido como recurso ao projeto. Os
    valores contidos nele devem ser usados para imprimir o resultado. Esses valores
    podem ser modificados.
- Qualquer memória alocada na heap (com malloc(3)) deve ser liberada corretamente.
    Isso será verificado durante a avaliação.
- O dicionário terá as seguintes regras:
    ```
    [um número][0 a n espaços]:[0 a n espaços][quaisquer caracteres imprimíveis]\n
    ```

◦ Você irá remover os espaços antes e depois dos valores no dicionário.


◦ O dicionário sempre terá pelo menos as chaves contidas no dicionário de refe-
rência. Seus valores podem ser modificados, mais entradas podem ser adicio-
nadas, mas as chaves iniciais não podem ser removidas.


◦ As entradas do dicionário podem ser armazenadas em qualquer ordem.
◦ Pode haver linhas vazias no dicionário.
◦ Se houver algum erro na análise do dicionário, seu programa deve imprimir
"Dict Error\n".
◦ Se o dicionário não permitir que você realize a conversão do número fornecido,
seu programa deve imprimir "Dict Error\n".

```
- Exemplo:

$> ./rush-02 42 | cat -e
forty two$
$> ./rush-02 0 | cat -e
zero$
$> ./rush-02 10.4 | cat -e
Error$
$> ./rush-02 100000 | cat -e
one hundred thousand$
$> grep "20" numbers.dict | cat -e
20 : hey everybody ! $
$> ./rush-02 20 | cat -e
hey everybody !$

```

# Capítulo V

# Bônus

Você pode completar os seguintes bônus:

- Usar “-”, “,”, “e” para se aproximar da sintaxe escrita correta.
- Fazer o mesmo exercício em um idioma diferente, usando outro dicionário que con-
    terá as entradas traduzidas.
- Usar read para ler números da entrada padrão (um por linha) quando o argumento
    da linha de comando para o número for “-”.
```
Exemplo:
$> ./rush-02 -
42
forty two
0
zero
^D
$>


```

# Capítulo VI

# Entrega e avaliação por pares

Envie seu trabalho para seu repositório Git como de costume. Apenas o trabalho dentro
do seu repositório será avaliado durante a defesa. Não hesite em verificar novamente os
nomes de seus arquivos para garantir que estejam corretos.

Este trabalho não é verificado por um programa. Você está livre para organizar seus
arquivos como desejar, desde que envie os arquivos obrigatórios e cumpra os requisitos.

```
Envie apenas os arquivos solicitados pelo subject deste projeto.
```