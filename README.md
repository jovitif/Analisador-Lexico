# Analisador Léxico para Linguagem OWL2 (Manchester Syntax)


## Como executar o analisador
Entrar na pasta do projeto:
    ```bash
    cd projeto/
    ```
Compilar o analisador usando o makeFile:

    ```bash
    make
    ```
Executar o analisador gerado com o arquivo de entrada que contém o exemplo:

    ```bash
    ./analisador-lexico entrada.txt
    ```
Depois de executar, o arquivo saida.csv será gerado com as informações sobre a entrada 

## Descrição
Este projeto consiste na implementação de um analisador léxico para a linguagem Web Ontology Language (OWL2) no formato Manchester Syntax. A tarefa inclui a leitura de um subconjunto específico de elementos da linguagem, conforme descrito no arquivo anexo.

## Integrantes do Grupo
Rafael Lucas de Azevedo Nunes

João Vitor Fernandes de Sales

## Desafio
O desafio proposto é desenvolver um analisador léxico capaz de identificar e categorizar os seguintes elementos da linguagem OWL2:

## Palavras Reservadas
SOME, ALL, VALUE, MIN, MAX, EXACTLY, THAT
NOT
AND
OR

## Identificadores de Classes
Nomes começando com letra maiúscula (ex.: Pizza)
Nomes compostos concatenados e com iniciais maiúsculas (ex.: VegetarianPizza)
Nomes compostos separados por underline (ex.: Margherita_Pizza)

## Identificadores de Propriedades
Começando com "has", seguidos de uma string simples ou composta (ex.: hasSpiciness, hasTopping, hasBase)
Começando com "is", seguidos de qualquer coisa e terminados com "Of" (ex.: isBaseOf, isToppingOf)

## Cardinalidades
Representadas por números inteiros (ex.: hasTopping min 3)
O analisador léxico deve gerar tokens para cada elemento identificado, os quais serão registrados em uma tabela de símbolos.

## Ferramentas Utilizadas
Especificação manual, utilizando NFAs, DFAs, transformações NFA→DFA e expressões regulares.
Ambiente de desenvolvimento integrado, como VS Code.
Ambientes específicos de modelagem para compiladores, como Flex ou ANTLR.


