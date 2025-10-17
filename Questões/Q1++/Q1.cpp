#include <bits/stdc++.h>
using namespace std;

static inline long long mul_mod(long long a, long long b, long long mod)
{
  __int128 x = (__int128)a * b;
  x %= mod;
  return (long long)x;
}

void print_sep(const string &title)
{
  cout << "\n= " << title << " =\n";
}

long long mdc_verbose(long long a, long long b)
{
  cout << "1.1. Calculando mdc(" << a << "," << b << ") - Algoritmo de Euclides:\n";
  while (b != 0)
  {
    long long q = a / b;
    long long r = a % b;
    cout << "  " << a << " = " << b << " * " << q << " + " << r << " - Divisao Euclidiana\n";
    a = b;
    b = r;
  }
  cout << "mdc = " << a << "\n";
  return a;
}

long long extgcd_verbose(long long a, long long b, long long &x, long long &y)
{
  cout << "2.1. Algoritmo de Euclides Estendido (EE(" << a << "," << b << ")):\n";
  long long old_r = a, r = b;
  long long old_s = 1, s = 0;
  long long old_t = 0, t = 1;

  cout << "  q\tr\told_r\ts\told_s\tt\told_t\n";
  int iter = 0;
  while (r != 0)
  {
    long long q = old_r / r;
    long long tmp;

    cout << "  " << q << "\t" << r << "\t" << old_r << "\t" << s << "\t" << old_s << "\t" << t << "\t" << old_t << " (Iter " << (++iter) << ")\n";

    tmp = old_r - q * r;
    old_r = r;
    r = tmp;
    tmp = old_s - q * s;
    old_s = s;
    s = tmp;
    tmp = old_t - q * t;
    old_t = t;
    t = tmp;
  }
  x = old_s;
  y = old_t;
  cout << "2.2. Resultado: mdc=" << old_r << ", x=" << x << ", y=" << y << " (mdc=a*x + b*y)\n";
  return old_r;
}

bool mod_inverse_verbose(long long E, long long mod, long long &inv)
{
  print_sep("3. Inverso Modular - Chave Privada D");
  long long x, y;
  long long g = extgcd_verbose(E, mod, x, y);
  if (g != 1)
  {
    cout << "3.2. Sem inverso: mdc(E,mod)!=1. O inverso existe sse mdc(E, mod) = 1.\n";
    return false;
  }
  inv = (x % mod + mod) % mod;
  cout << "3.3. Inverso modular D: inv(" << E << "," << mod << ") = " << inv << " (onde E*D cong 1 mod mod)\n";
  return true;
}

bool is_prime_bruteforce(long long n)
{
  if (n < 2)
    return false;
  if (n % 2 == 0)
    return (n == 2);
  for (long long d = 3; d * d <= n; d += 2)
    if (n % d == 0)
      return false;
  return true;
}

long long f_iter(long long x, long long mod)
{
  return (mul_mod(x, x, mod) + 1) % mod;
}

long long pollard_rho_verbose(long long N)
{
  print_sep(string("4. Fatoracao com Pollard Rho (N=") + to_string(N) + ")");
  if (N % 2 == 0)
  {
    cout << "4.1. N par, fator trivial: 2\n";
    return 2;
  }
  long long x = 2, y = 2, d = 1;
  int iter = 0;
  cout << "it\tx\ty\t|x-y|\tmdc\n";
  while (d == 1)
  {
    x = f_iter(x, N);
    y = f_iter(f_iter(y, N), N);
    long long diff = x > y ? x - y : y - x;
    cout << "4.3. Calculo do mdc para encontrar fator:\n";
    d = mdc_verbose(diff, N);
    cout << setw(3) << ++iter << "\t" << x << "\t" << y << "\t" << diff << "\t" << d << "\n";
    if (iter > 100000)
    {
      cout << "4.4. Limite de iteracoes atingido. Falha na fatoracao.\n";
      break;
    }
  }
  if (d == N)
  {
    cout << "4.4. Falha: mdc=N - Ciclo degenerado\n";
    return -1;
  }
  if (d == 1)
     
    {
      cout << "4.4. Sem fator - Loop quebrou por limite\n";
      return -1;
    }
  cout << "4.5. Fator encontrado: " << d << "\n";
  return d;
}

struct PowResult
{
  long long value;
};

static string to_binary(unsigned long long e)
{
  if (e == 0)
    return "0";
  string s;
  while (e)
  {
    s.push_back((e & 1) ? '1' : '0');
    e >>= 1;
  }
  reverse(s.begin(), s.end());
  return s;
}

PowResult powmod_verbose(long long m, long long k, long long mod, long long phi_of_mod, const string &contexto)
{
  print_sep("5. Exp. Modular (Square-and-Multiply) - " + contexto);
  cout << "5.1. Calculando: " << m << "^" << k << " mod " << mod << "\n";

  long long g = mdc_verbose(m % mod, mod);

  bool mod_is_prime = is_prime_bruteforce(mod);
  if (mod_is_prime && (m % mod != 0))
  {
    cout << "5.2. Teorema de Fermat: Como " << mod << " e primo, reduzimos k mod (" << mod << "-1).\n";
    k = k % (mod - 1);
  }
  else if (g == 1)
  {
    cout << "5.2. Teorema de Euler: Como mdc(base, mod)=1, reduzimos k mod phi(" << mod << "). phi=" << phi_of_mod << ".\n";
    k = k % phi_of_mod;
  }
  else
  {
    cout << "5.2. Reducao de expoente nao aplicavel. Usando k original.\n";
  }

  cout << "5.3. Expoente efetivo: k' = " << k << " (binario: " << to_binary((unsigned long long)k) << "). Metodo: Square-and-Multiply.\n";
  long long base = m % mod;
  long long res = 1 % mod;

  unsigned long long e = (unsigned long long)k;
  int step = 0;
  while (e > 0)
  {
    cout << "passo " << (++step) << ": e=" << e << ", bit=" << (e & 1) << " - Analise do bit menos significativo \n";
    if (e & 1)
    {
      cout << "  (Bit=1) res=(" << res << " * " << base << ")% " << mod << " = ";
      res = mul_mod(res, base, mod);
      cout << res << "\n";
    }
    cout << "  (Square) base=(" << base << " * " << base << ")% " << mod << " = ";
    base = mul_mod(base, base, mod);
    cout << base << "\n";
    e >>= 1;
  }
  cout << "5.5. Resultado final da exponenciacao modular: " << res << "\n";
  return {res};
}

int char_to_code(char c)
{
  if (c == ' ')
    return 0;
  if ('A' <= c && c <= 'Z')
    return 11 + (c - 'A');
  return -1;
}

char code_to_char(int code)
{
  if (code == 0)
    return ' ';
  if (11 <= code && code <= 36)
    return char('A' + (code - 11));
  return '?';
}

vector<int> encode_message(const string &msg)
{
  cout << "\n6. Codificacao da Mensagem (Letra -> Numero):\n";
  vector<int> v;
  int step = 1;
  for (char c : msg)
  {
    char u = toupper((unsigned char)c);
    int code = char_to_code(u);
    if (code >= 0)
    {
      v.push_back(code);
      cout << "  " << (step++) << ". '" << c << "' -> " << setw(2) << setfill('0') << code << "\n";
    }
    else
    {
      cout << "  Ignorado: '" << c << "' (nao e letra/espaco)\n";
    }
  }
  return v;
}

string decode_message(const vector<int> &codes)
{
  cout << "\n8. Decodificacao da Mensagem (Numero -> Letra):\n";
  string s;
  int step = 1;
  for (int code : codes)
  {
    cout << "  " << (step++) << ". " << setw(2) << setfill('0') << code << " -> '" << code_to_char(code) << "'\n";
    s.push_back(code_to_char(code));
  }
  return s;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  print_sep("0. Criptografia RSA - Inicializacao");
  cout << "0.1. Validacao de Entrada - N1 e N2 de 3 a 4 digitos.\n";
  long long N1, N2;
  cout << "N1 [100..9999]: ";
  if (!(cin >> N1))
    return 0;
  cout << "N2 [100..9999]: ";
  if (!(cin >> N2))
    return 0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  if (N1 < 100 || N1 > 9999 || N2 < 100 || N2 > 9999)
  {
    cout << "0.2. Erro: N1 e N2 devem estar no intervalo [100..9999].\n";
    return 0;
  }

  print_sep("1. Fatoracao para Primos RSA");
  cout << "1.1. Objetivo: Encontrar p e q tais que N1=p*q1 e N2=q*p2. Os primos RSA serao p e q.\n";

  long long p_found = pollard_rho_verbose(N1);
  if (p_found <= 1 || p_found == N1)
  {
    cout << "1.2. Falha na fatoracao de N1.\n";
    return 0;
  }
  long long q1 = N1 / p_found;
  cout << "N1 = " << N1 << " = " << p_found << " * " << q1 << " - Divisao Euclidiana inversa\n";

  long long q_found = pollard_rho_verbose(N2);
  if (q_found <= 1 || q_found == N2)
  {
    cout << "1.3. Falha na fatoracao de N2.\n";
    return 0;
  }
  long long p2 = N2 / q_found;
  cout << "N2 = " << N2 << " = " << q_found << " * " << p2 << " - Divisao Euclidiana inversa\n";

  long long p = p_found;
  long long q = q_found;
  if (!is_prime_bruteforce(p))
    swap(p, q1);
  if (!is_prime_bruteforce(q))
    swap(q, p2);

  cout << "\n1.4. Primos RSA Selecionados (p, q):\n";
  cout << "  p=" << p << "\n";
  cout << "  q=" << q << "\n";

  print_sep("2. Geracao das Chaves RSA");
  long long n = p * q;
  long long phi = (p - 1) * (q - 1);
  cout << "2.1. Modulo: n = p * q = " << n << "\n";
  cout << "2.2. Totiente de Euler: phi(n) = (p-1) * (q-1) = " << phi << "\n";

  cout << "\n2.3. Escolha do Expoente Publico E (menor E > 1 tal que mdc(E,phi)=1):\n";
  long long E = 0;
  for (long long cand = 2; cand < n; ++cand)
  {
    if (mdc_verbose(cand, phi) == 1)
    {
      E = cand;
      break;
    }
  }
  if (E == 0)
  {
    cout << "2.4. Falha ao escolher E valido. Sem solucao valida.\n";
    return 0;
  }
  cout << "2.4. E escolhido: E = " << E << "\n";

  long long D;
  if (!mod_inverse_verbose(E, phi, D))
  {
    cout << "2.6. Falha ao calcular D. Sem solucao valida.\n";
    return 0;
  }

  cout << "\n2.6. Chaves Finais:\n";
  cout << "  Chave Publica: (n,e)=(" << n << "," << E << ")\n";
  cout << "  Chave Privada: (n,d)=(" << n << "," << D << ")\n";

  print_sep("3. Criptografia e Decriptografia RSA");
  cout << "3.1. Digite a mensagem - letras A-Z e espaco:\n";
  string msg;
  getline(cin, msg);

  vector<int> plain_codes = encode_message(msg);
  if (plain_codes.empty())
  {
    cout << "3.2. Nada para codificar. Fim.\n";
    return 0;
  }

  cout << "\n7. Criptografando: C = M^E mod n (Square-and-Multiply com E)\n";
  vector<long long> ciphertext;
  for (size_t i = 0; i < plain_codes.size(); ++i)
  {
    long long M = plain_codes[i];
    cout << "\nBloco " << (i + 1) << ":\n";
    cout << "Massa de texto M=" << M << "\n";
    PowResult r = powmod_verbose(M, E, n, phi, "Criptografia");
    long long C = r.value;
    ciphertext.push_back(C);
    cout << "Cifrado C=" << C << "\n";
  }

  cout << "\n9. Decriptando: M = C^D mod n - Square-and-Multiply com D\n";
  vector<int> recovered_codes;
  for (size_t i = 0; i < ciphertext.size(); ++i)
  {
    long long C = ciphertext[i];
    cout << "\nBloco " << (i + 1) << ":\n";
    cout << "Cifrado C=" << C << "\n";
    PowResult r = powmod_verbose(C, D, n, phi, "Decodificacao");
    long long M = r.value;
    cout << "Texto Plano M=" << M << " - Resultado mod n\n";

    if (M < 0 || M > 99)
    {
      cout << "Ajuste mod 100 - Requisito de Decodificacao-\n";
      M = ((M % 100) + 100) % 100;
    }
    recovered_codes.push_back((int)M);
  }

  string recovered = decode_message(recovered_codes);
  cout << "\n10. Mensagem Decifrada: \"" << recovered << "\"\n";

  string norm;
  for (char c : msg)
  {
    if (c == ' ')
      norm.push_back(' ');
    else if (isalpha((unsigned char)c))
      norm.push_back(toupper((unsigned char)c));
  }

  print_sep("4. Integridade e Confirmacao");
  cout << "4.1. Comparacao com a mensagem original  - normalizada apenas letras e espacos:\n";
  cout << "Original Normalizada: \"" << norm << "\"\n";
  cout << "Decifrada:          \"" << recovered << "\"\n";

  if (norm == recovered)
  {
    cout << "4.2. CONFIRMACAO Mensagem decifrada coincide com a original.\n";
  }
  else
  {
    cout << "4.2. CONFIRMACAO: Mensagem decifrada NAO coincide com a original.\n";
  }

  print_sep("Fim do Processo RSA");
  return 0;
}