#include <bits/stdc++.h>
using namespace std;

long long mdc_verbose(long long a, long long b)
{
  cout << "\n1.1. Calculando mdc(" << a << "," << b << ") (Euclides):\n";
  long long oa = a, ob = b;
  int step = 1;
  while (b)
  {
    long long q = a / b;
    long long r = a % b;
    cout << " Passo " << (step++) << ": " << a << " = " << b << " * " << q << " + " << r << "\n";
    a = b;
    b = r;
  }
  cout << " mdc(" << oa << "," << ob << ") = " << a << "\n";
  return a;
}

long long extgcd_verbose(long long a, long long b, long long &x, long long &y)
{
  cout << "\n1.2. Algoritmo de Euclides Estendido (EE):\n";
  long long x0 = 1, y0 = 0, x1 = 0, y1 = 1;
  cout << " q\t r\t x0\t x1\t y0\t y1\n";
  while (b)
  {
    long long q = a / b, r = a - q * b;
    a = b;
    b = r;
    long long nx = x0 - q * x1, ny = y0 - q * y1;

    cout << " " << q << "\t " << r << "\t " << x0 << "\t " << x1 << "\t " << y0 << "\t " << y1 << "\n";

    x0 = x1;
    y0 = y1;
    x1 = nx;
    y1 = ny;
  }
  x = x0;
  y = y0;
  cout << " Resultado EE: mdc=" << a << ", x=" << x << ", y=" << y << " (a*x + b*y = mdc)\n";
  return a;
}

long long invmod_verbose(long long a, long long m)
{
  cout << "\n1.3. Inverso Modular para G^-1 mod Zn:\n";
  long long x, y;
  long long g = extgcd_verbose(a, m, x, y);
  if (g != 1)
  {
    cout << " Sem Inverso: mdc(" << a << "," << m << ") = " << g << " != 1\n";
    return -1;
  }
  long long inv = (x % m + m) % m;
  cout << " Inverso: " << a << "^-1 mod " << m << " = " << inv << "\n";
  return inv;
}

long long powmod_verbose(long long base, long long exp, long long mod, const string &method)
{
  cout << "\n2.4. Exponenciacao Modular (" << base << "^" << exp << " mod " << mod << ") - Metodo: Square-and-Multiply (" << method << ")\n";
  long long res = 1 % mod;
  base %= mod;
  long long exp_orig = exp;
  int step = 0;
  while (exp)
  {
    cout << " Passo " << (++step) << ": exp=" << exp << ", bit=" << (exp & 1) << " | res=" << res << ", base=" << base << "\n";
    if (exp & 1)
    {
      res = (res * base) % mod;
    }
    base = (base * base) % mod;
    exp >>= 1;
  }
  cout << " Resultado: " << res << "\n";
  return res;
}

bool is_prime_verbose(long long n)
{
  cout << "\n2.1. Teste de Primalidade para n1=" << n << " (Divisao por Tentativa):\n";
  if (n < 2)
    return false;
  if (n % 2 == 0)
    return n == 2;
  for (long long d = 3; d * d <= n; d += 2)
  {
    if (n % d == 0)
    {
      cout << " Nao primo: divisivel por " << d << "\n";
      return false;
    }
  }
  cout << " Primo: Nao divisivel ate raiz quadrada\n";
  return true;
}

long long phi_euler_verbose(long long n)
{
  cout << "\n2.2. Calculo de phi(" << n << ") (Totiente de Euler):\n";
  long long r = n;
  long long temp_n = n;
  int step = 1;
  for (long long p = 2; p * p <= temp_n; ++p)
  {
    if (temp_n % p == 0)
    {
      cout << " Passo " << (step++) << ": Fator primo " << p << " encontrado. phi -= phi/" << p << "\n";
      while (temp_n % p == 0)
        temp_n /= p;
      r -= r / p;
    }
  }
  if (temp_n > 1)
  {
    cout << " Passo " << (step++) << ": Fator restante " << temp_n << ". phi -= phi/" << temp_n << "\n";
    r -= r / temp_n;
  }
  cout << " phi(" << n << ") = " << r << "\n";
  return r;
}

void print_sep(const string &title)
{
  cout << "\n================ " << title << " ================\n";
}

int main()
{
  long long H = 7, G = 3, Zn = 11, x = 10, n1 = 13;

  cout << "0. Valores Iniciais da Questão\n";
  cout << " H=" << H << " G=" << G << " Zn=" << Zn << " x=" << x << " n1=" << n1 << "\n";

  cout << "1. Operacoes Modulares - Parte Base) \n";

  long long invG = invmod_verbose(G, Zn);
  if (invG == -1)
  {
    cout << " Sem solucao valida: Inverso G^-1 mod Zn nao existe.\n";
    return 0;
  }

  long long divHG = (H * invG) % Zn;
  cout << "\n1.4. Calculo da Base (H/G mod Zn):\n";
  cout << " Base A = (H * invG) mod Zn = (" << H << " * " << invG << ") mod " << Zn << " = " << divHG << "\n";

  cout << " 2. Reducao de Expoente - Teoremas \n";

  long long a = divHG, r;

  bool n1_is_prime = is_prime_verbose(n1);

  if (n1_is_prime && (a % n1 != 0))
  {
    cout << "\n2.3. Aplicacao do Teorema de Fermat:\n";
    cout << " Condicao: n1=" << n1 << " e primo E mdc(A, n1)=1\n";
    long long red = x % (n1 - 1);
    cout << " Reducao: x mod (n1-1) = " << x << " mod " << (n1 - 1) << " = " << red << "\n";
    r = powmod_verbose(a, red, n1, "Fermat");
    cout << " Resultado Fermat: " << r << "\n";
  }
  else
  {
    long long g = mdc_verbose(a, n1);
    if (g == 1)
    {
      long long phi = phi_euler_verbose(n1);
      cout << "\n2.3. Aplicacao do Teorema de Euler:\n";
      cout << " Condicao: mdc(A, n1) = " << g << " = 1\n";
      long long red = x % phi;
      cout << " Reducao: x mod phi(n1) = " << x << " mod " << phi << " = " << red << "\n";
      r = powmod_verbose(a, red, n1, "Euler");
      cout << " Resultado Euler: " << r << "\n";
    }
    else
    {
      cout << "\n2.3. Sem Reducao de Expoente (mdc(A, n1) = " << g << " != 1)\n";
      r = powmod_verbose(a, x, n1, "Base");
      cout << " Resultado Base: " << r << "\n";
    }
  }

  cout << "\n 3. Confirmacao - Base \n";
  long long r_base = powmod_verbose(a, x, n1, "Confirmacao (Base)");

  cout << "\n3.1. Comparacao:\n";
  if (r == r_base)
  {
    cout << " OK. O resultado com reducao (" << r << ") e igual ao resultado da base sem reducao.\n";
  }
  else
  {
    cout << " FALHA. Resultado com reducao (" << r << ") difere do resultado da base (" << r_base << ").\n";
  }

  return 0;
}