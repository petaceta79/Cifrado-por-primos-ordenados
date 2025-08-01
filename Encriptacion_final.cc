#include <iostream>
#include <vector>
#include <string>
#include "CodificarYDescodificar.cc"
#include "cifrado_descifrado_congruencias.cc"

using namespace std;

struct info_encriptada
{
    string mensaje;
    long long c;
    long long m;
};


// Aplica el cifrado de numeros primos y las congruencias
info_encriptada cifrarFinal(vector<Letra> Letras, int tam, string word) {
    string cifrado = cifradoPrimosOrden(Letras, 4, word);

    size_t posMenos = cifrado.find('-');

    std::string primeraParte = cifrado.substr(0, posMenos);

    std::string resto = cifrado.substr(posMenos + 1);

    std::vector<int> numeros;
    size_t start = 0, end;
    while ((end = resto.find('_', start)) != std::string::npos) {
        std::string numeroStr = resto.substr(start, end - start);
        if (!numeroStr.empty()) {
            numeros.push_back(std::stoi(numeroStr));
        }
        start = end + 1;
    }

    claves clavesCifrado = calcularClaves(99999999, 999999999);
    for (int i = 0; i < numeros.size(); i++) {
        numeros[i] = cifrarODescifrar(numeros[i], clavesCifrado.c_1, clavesCifrado.m);
    }

    std::string nuevoCodigo = primeraParte + "-";
    for (int n : numeros) {
        nuevoCodigo += std::to_string(n) + "_";
    }

    return {nuevoCodigo, clavesCifrado.c_2, clavesCifrado.m};
}

string descifrarFinal(vector<Letra> Letras, int tam, string word, long long c, long long m) {

    size_t posMenos = word.find('-');

    std::string primeraParte = word.substr(0, posMenos);

    std::string resto = word.substr(posMenos + 1);

    std::vector<int> numeros;
    size_t start = 0, end;
    while ((end = resto.find('_', start)) != std::string::npos) {
        std::string numeroStr = resto.substr(start, end - start);
        if (!numeroStr.empty()) {
            numeros.push_back(std::stoi(numeroStr));
        }
        start = end + 1;
    }

    for (int i = 0; i < numeros.size(); i++) {
        numeros[i] = cifrarODescifrar(numeros[i], c, m);
    }

    std::string nuevoCodigo = primeraParte + "-";
    for (int n : numeros) {
        nuevoCodigo += std::to_string(n) + "_";
    }


    return DescifradoPrimosOrden(Letras, 4, nuevoCodigo);
}



int main()
{
    // Codigo final
    vector<Letra> Letras = LetrasIprimos(); // Letras
    
    cout << "Escoge:" << endl;
    cout << "Encriptar: 0    Desencriptar: 1" << endl;
    int select; cin >> select;
    if (select == 0) {
        string word;
        cout << "Palabra a encriptar: " << endl;
        cin.ignore();
        getline(cin, word);
        info_encriptada cifrado = cifrarFinal(Letras, 4, word);

        cout << endl;
        cout << "Menaje cifrado: " << cifrado.mensaje << endl;
        cout << "Clave: " << cifrado.c << endl;
        cout << "Valor modular: " << cifrado.m << endl;
    }
    else if (select == 1) {
        string codigo;
        long long c;
        long long m;
        cout << "Palabra a desencriptar: " << endl;
        cin.ignore();
        getline(cin, codigo);
        cout << "Clave: " << endl;
        cin >> c;
        cout << "Numero modular: " << endl;
        cin >> m;
        string word = descifrarFinal(Letras, 4, codigo, c, m);

        cout << endl;
        cout << "Menaje descifrado: " << word << endl;
    }
    
    cout << endl;
}
