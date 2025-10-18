# AtividadeMD2_2025_2.
Atividade da P2 de MD2.

# Informações do Aluno.

Nome: Pedro Victor Lima Torreão.  
Matricula: 190036761.

# Intruções de Execução.
## Para as Questões 1, 2 e 3.
### Para compilar o codigo em C++:

```bash
g++ Q1.cpp -o nomedoprograma
```
### Para a execução do codigo:

```bash
./nomedoprograma
```

## Para a Questão 4
### Para compilar o codigo em C:

```bash
gcc Q4.c -o nomedoprograma
```
### Para executar o codigo:

```bash
./nomedoprograma
```
# Respostas para a Questão 4:
## Questão 4.1:

Ao executar o codigo utilizando as seguintes entradas:  
H: 7, G: 3, Zn: 11, x: 10, n1: 13  

Obtemos a seguinte Saida:  
Algoritmo de Euclides: 3 mod 11 = 3  
Algoritmo de Euclides: 11 mod 3 = 2  
Algoritmo de Euclides: 3 mod 2 = 1  
Algoritmo de Euclides: 2 mod 1 = 0  
MDC(3, 11) = 1

Substituindo, temos que o inverso de 3 em 11 é 4.

Fazendo a multiplicação modular: 7 * 4 mod 11 cong 6
Sendo 4 o inverso de 3  
Valor final da congruencia: 4

## Questão 4.2:

a. (V) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.

Explicação - A função inversoModular implementa claramente o algoritmo de Euclides estendido, que é usado para calcular inversos modulares.

b. (F) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.

Explicação - O inverso modular só existe se mdc(G, Zn) = 1. Se mdc(G, Zn) ≠ 1, o algoritmo não funcionará corretamente e não retornará um inverso válido.

c. (V) A operação (H * inverso) % Zn representa a divisão modular de H por G.

Explicação - Em aritmética modular, dividir H por G é equivalente a multiplicar H pelo inverso modular de G, ou seja: H ÷ G ≡ H × G⁻¹ (mod Zn).

d. (F) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1.

Explicação - A função powMod mostrada implementa exponenciação modular por quadrados (método eficiente), mas não há nenhuma aplicação explícita do Pequeno Teorema de Fermat no código.

e. (F) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização.

Explicação - Pelo código anterior, a função powMod usa o método de exponenciação por quadrados (exponenciação binária), que é uma otimização eficiente, não multiplicações diretas.

f. (V) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.

Explicação - O código claramente faz: if (x1 < 0) x1 += m0; para garantir que o inverso modular seja um número positivo no intervalo [0, m0-1].

g. (F) O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.

Explicação - O código não calcula a função totiente de Euler (φ(n1)) em nenhum momento, nem para n1 primo nem para n1 composto.