#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int mdc_verbose(int a, int b)
{
  std::cout << "\n= Inicio MDC(" << a << ", " << b << ") =\n";
  int original_a = a;
  int original_b = b;
  int step = 1;
  while (b != 0)
  {
    int q = a / b;
    int r = a % b;
    std::cout << " Passo " << (step++) << ": " << a << " = " << b << " * " << q << " + " << r << " - Divisao Euclidiana\n";
    a = b;
    b = r;
  }
  std::cout << " MDC(" << original_a << ", " << original_b << ") = " << a << "\n";
  std::cout << "--- Fim MDC ---\n";
  return a;
}

int mmc_verbose(int a, int b)
{
  std::cout << "\n--- Inicio MMC(" << a << ", " << b << ") ---\n";
  int g = mdc_verbose(a, b);

  long long num = (long long)a / g * b;

  if (num > 2147483647)
  {
    std::cout << " Aviso: Resultado do MMC excede o limite int.\n";
    return 51;
  }

  int result = (int)num;
  std::cout << " Formula MMC: (" << a << " * " << b << ") / " << g << " = " << result << "\n";
  std::cout << "--- Fim MMC ---\n";
  return result;
}

int main()
{
  std::ios::sync_with_stdio(false);

  std::cout << " SINCRONIZACAO DE CICLOS (MMC) \n";
  
  std::cout << "1. Digite o numero de ciclos - N, max 50:\n" << std::flush;
  int N;
  if (!(std::cin >> N) || N < 1 || N > 50)
  {
    std::cout << " Erro: N deve estar entre 1 e 50.\n";
    return 0;
  }

  std::cout << "2. Digite os " << N << " periodos - C[i], cada um max 50:\n" << std::flush;
  std::vector<int> C(N);
  for (int i = 0; i < N; ++i)
  {
    if (!(std::cin >> C[i]) || C[i] < 1 || C[i] > 50)
    {
      std::cout << " Erro: Periodo C[" << i + 1 << "] deve estar entre 1 e 50.\n";
      return 0;
    }
  }

  std::cout << "\n 2. CALCULO DE MMC ITERATIVO \n";

  int l = 1;

  std::cout << " Passo 2.1: L_0 = " << C[0] << "\n";
  l = C[0];

  for (int i = 1; i < N; ++i)
  {
    std::cout << "\n--- Iteracao " << i << " (MMC(" << l << ", " << C[i] << ")) ---\n";
    int novo_l = mmc_verbose(l, C[i]);

    l = novo_l;

    if (l > 50)
    {
      std::cout << "Parada antecipada: MMC (" << l << ") excedeu o limite de 50.\n";
      break;
    }
    std::cout << " Resultado parcial L_" << i << " = " << l << "\n";
  }

  std::cout << "\n 3. RESULTADO FINAL \n";
  if (l >= 1 && l <= 50)
  {
    std::cout << "Sincronizacao possivel. O periodo e:\n";
    std::cout << l << "\n";
  }
  else
  {
    std::cout << "Nao e possivel sincronizar no intervalo [1, 50].\n";
  }

  return 0;
}