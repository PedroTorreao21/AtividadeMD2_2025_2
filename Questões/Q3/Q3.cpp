#include <bits/stdc++.h>
using namespace std;

long long pow_verbose(long long base, int exp)
{
  long long res = 1;
  long long b = base;
  unsigned int e = (unsigned int)exp;
  int step = 0;

  cout << "\n5.1. Calculando potencia (" << base << "^" << exp << ") via Square-and-Multiply:\n";
  cout << " Exp Binario: " << bitset<32>(e) << "\n";

  while (e > 0)
  {
    cout << "  Passo " << (++step) << ": bit=" << (e & 1) << " | res=" << res << ", base=" << b << "\n";
    if (e & 1)
    {
      res *= b;
    }
    b *= b;
    e >>= 1;
  }
  cout << "5.2. Resultado da potencia: " << res << "\n";
  return res;
}

void print_sep(const string &title)
{
  cout << "\n=" << title << " =\n";
}

int main()
{
  ios::sync_with_stdio(false);

  print_sep("1. Entrada e Validacao");
  long long N;
  cout << "1.1. Digite o numero N (maximo 9 digitos para seguranca de long long):\n" << flush;
  if (!(cin >> N))
    return 0;

  if (N < 2 || N > 1000000000)
  {
    cout << "1.2. Erro: N deve estar entre 2 e 1.000.000.000.\n";
    return 0;
  }

  cout << " N = " << N << "\n";

  print_sep("2. Fatoracao Prima - Divisao por Tentativa");

  vector<pair<long long, int>> fac;
  long long x = N;
  long long original_N = N;
  int step = 1;

  if (x % 2 == 0)
  {
    int c = 0;
    cout << "2." << (step++) << ". Testando p=2:\n";
    while (x % 2 == 0)
    {
      x /= 2;
      c++;
    }
    fac.push_back(make_pair(2, c));
    cout << "  Fator 2^" << c << " encontrado. N restante: " << x << "\n";
  }

  for (long long p = 3; p * p <= x; p += 2)
  {
    if (x % p == 0)
    {
      int c = 0;
      cout << "2." << (step++) << ". Testando p=" << p << ":\n";
      while (x % p == 0)
      {
        x /= p;
        c++;
      }
      fac.push_back(make_pair(p, c));
      cout << "  Fator " << p << "^" << c << " encontrado. N restante: " << x << "\n";
    }
  }
  if (x > 1)
  {
    cout << "2." << (step++) << ". Fator restante: " << x << "\n";
    fac.push_back(make_pair(x, 1));
  }

  cout << "\n2.F. Fatoracao Completa - Teorema Fund. da Aritmetica:\n";
  cout << " N = " << original_N << " = ";
  for (size_t i = 0; i < fac.size(); ++i)
  {
    cout << fac[i].first << "^" << fac[i].second;
    if (i + 1 < fac.size())
      cout << " * ";
  }
  cout << "\n";

  print_sep("3. Calculo de tau(N) e sigma(N)");

  long long tau = 1;
  cout << "3.1. Calculo de tau(N) - Numero de divisores:\n";
  cout << " tau(N) = ";
  for (size_t i = 0; i < fac.size(); ++i)
  {
    int a = fac[i].second;
    tau *= (a + 1);
    cout << "(" << a << "+1)";
    if (i + 1 < fac.size())
      cout << " * ";
  }
  cout << " = " << tau << "\n";

  long long sigma = 1;
  cout << "3.2. Calculo de sigma(N) - Soma dos divisores:\n";
  cout << " sigma(N) = ";
  for (size_t i = 0; i < fac.size(); ++i)
  {
    long long p = fac[i].first;
    int a = fac[i].second;

    long long p_aplus1 = pow_verbose(p, a + 1);

    long long term = (p_aplus1 - 1) / (p - 1);

    cout << "((" << p << "^" << (a + 1) << ") - 1)/(" << p << " - 1) [" << term << "]";
    if (i + 1 < fac.size())
      cout << " * ";

    sigma *= term;
  }
  cout << " = " << sigma << "\n";

  print_sep("4. Resultados Finais");

  double razao = (double)sigma / (double)tau;

  cout << "4.1. Razao de Eficiencia = sigma(N) / tau(N):\n";
  cout << " razao = " << sigma << " / " << tau << " = ";

  cout << fixed << setprecision(2);
  cout << razao << "\n";

  cout << "4.2. Confirmacao - Verificacao :\n";
  if (sigma == 2 * original_N)
  {
    cout << " N e um numero PERFEITO (sigma(N) = 2*N).\n";
  }
  else if (sigma < 2 * original_N)
  {
    cout << " N e um numero DEFICIENTE (sigma(N) < 2*N).\n";
  }
  else
  {
    cout << " N e um numero ABUNDANTE (sigma(N) > 2*N).\n";
  }
}