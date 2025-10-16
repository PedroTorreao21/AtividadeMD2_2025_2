#include <stdio.h>

// Função para calcular o MDC (Máximo Divisor Comum)
int mdc(int a, int b)
{
  while (b != 0)
  {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// Função para calcular o MMC (Mínimo Múltiplo Comum)
int mmc(int a, int b)
{
  return (a * b) / mdc(a, b);
}

// Função para calcular o MMC de uma lista de números
int mmc_lista(int ciclos[], int n)
{
  int resultado = ciclos[0];

  for (int i = 1; i < n; i++)
  {
    resultado = mmc(resultado, ciclos[i]);
  }

  return resultado;
}

int main()
{
  int N;

  // Lê o número de chaves
  scanf("%d", &N);

  int ciclos[N];

  // Lê os ciclos das chaves
  for (int i = 0; i < N; i++)
  {
    scanf("%d", &ciclos[i]);
  }

  // Calcula o MMC de todos os ciclos
  int ano_sincronizado = mmc_lista(ciclos, N);

  // Verifica se o ano sincronizado está dentro do limite de 50 anos
  if (ano_sincronizado > 0 && ano_sincronizado <= 50)
  {
    printf("%d\n", ano_sincronizado);
  }
  else
  {
    printf("Nao ha ano sincronizado no limite de 50 anos.\n");
  }

  return 0;
}