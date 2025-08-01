#include <iostream>
#include <random> 
#include <chrono>

// Devuelve un numero aleatorio comprimido en [a, b]
// pre: a < b
int nuemroRandom(int a, int b) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generador(seed);

    std::uniform_int_distribution<int> distribucion(a, b);

    return distribucion(generador);
}

// Algoritmo de Euclides para gcd
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
// Busca un número coprimo con n en el rango [1, n-1]
int encontrarCoprimo(int n) {
    srand(time(nullptr));
    int candidato;
    do {
        candidato = rand() % (n - 1) + 1; 
    } while (gcd(candidato, n) != 1);
    return candidato;
}

struct  result_euclides
{
    int mcd;
    int x;
    int y;
};

// Algoritmo de Euclides extendido para resolver la ecuacion diofantica
result_euclides euclidesExtendido(int a, int b) {
    if (b == 0) return {a, 1, 0};
    
    result_euclides r = euclidesExtendido(b, a % b);
    int x = r.y;
    int y = r.x - (a / b) * r.y;
    return {r.mcd, x, y};
}
// Devuelve le inverso modular 
// pre: mcd(x,m) = 1
int calcularInversoModular(int x, int m) {
    result_euclides r = euclidesExtendido(x, m);

    return (r.x % m + m) % m;
}

struct claves
{
    long long m;
    long long c_1;
    long long c_2;
};
// Devuelve un struct con la clave publica, privada y con el numero modular 
claves calcularClaves(int a, int b) {
    long long m = nuemroRandom(a, b);

    long long x = encontrarCoprimo(m);

    long long x_inv = calcularInversoModular(x, m);

    return {m, x, x_inv};
}

long long cifrarODescifrar(long long x, long long c, long long m) {
    return ((x * c)%m + m)%m;
}


