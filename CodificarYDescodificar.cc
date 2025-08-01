#include <vector>
#include <iostream>
#include <string>
using namespace std;

struct Letra {
    int primo;
    char letra;
};

// Cifrado
// Devuelve un vector con los numeros primos hasta n
vector<int> Garbell(int n) {
    vector<bool> G(n + 1, true);
    G[0] = false;
    G[1] = false;

    int k = 0;

    for (int i = 2; i <= n; ++i) {
        if (G[i]) {
            for (int e = i + i; e <= n; e += i) {
                G[e] = false;
            }
            ++k;
        }
    }

    vector<int> Result(k);
    k = 0;
    for (int i = 0; i <= n; ++i) {
        if (G[i]) {
            Result[k] = i;
            ++k;
        }
    }

    return Result;
}
// Devuelve un vector de Letras con todas las letras con su primo asignado
vector<Letra> LetrasIprimos() {
    // Vector dinámico con los caracteres que se usarán
    vector<char> caracteres = {
        ' ', 'e', 'a', 'o', 'i', 's', 'r', 'n', 'l', 'd',
        'c', 't', 'u', 'p', 'm', 'g', 'b', 'v', 'f', 'q',
        'j', 'y', 'h', 'z', 'x', 'k', 'w'
    };

    int numeroDeLetras = caracteres.size();
    int MaxNumeroPrimoPos = 10000;

    // Obtener los primeros primos necesarios
    vector<int> P = Garbell(MaxNumeroPrimoPos);
    if ((int)P.size() < numeroDeLetras) {
        cerr << "Error: No se encontraron suficientes números primos." << endl;
        exit(1);
    }

    // Asignar cada caracter a su primo
    vector<Letra> ABC(numeroDeLetras);
    for (int i = 0; i < numeroDeLetras; ++i) {
        ABC[i].letra = caracteres[i];
        ABC[i].primo = P[i];
    }

    return ABC;
}


// Devuelve el numero al cual corresponde una letra
int CharToInt(char c, vector<Letra> &Letras) {
    int i = 0;
    while (c != Letras[i].letra) ++i;
    return Letras[i].primo;
}
// Devuelve un vector donde cada letra es su int 
vector<int> WordToInt(string &Words, vector<Letra> &Letras) {
    int wordN = Words.size();
    vector<int> Num(wordN);

    for (int i = 0; i < wordN; ++i) {
        Num[i] = CharToInt(Words[i], Letras);
    }

    return Num;
}
// Ordena de menor a mayor y eliminarepetidos
vector<int> ordenarIeliminarRepe(vector<int> Numeros) {
    // Algoritmo insertion
    int n = Numeros.size();
    for (int i = 1; i < n; ++i) {
        int aux = Numeros[i];
        int e = i;
        while (e > 0 && Numeros[e - 1] > aux) {
            Numeros[e] = Numeros[e - 1];
            --e;
        }
        Numeros[e] = aux;
    }

    // eliminar repetidos
    vector<int> result(1);
    result[0] = Numeros[0];
    for (int i = 1; i < n; ++i) {
        if (Numeros[i - 1] != Numeros[i]) result.push_back(Numeros[i]);
    }

    return result;
}
// funcion que devuelve la posicon en el vector del numero
int posicion(vector<int> &Primos, int num) {
    int left = 0;
    int right = Primos.size() - 1;

    int result = -1;
    while (result == -1 && left <= right) {
        int mid = (right + left) / 2;
        if (Primos[mid] < num) left = mid + 1;
        else if (Primos[mid] > num) right = mid - 1;
        else result = mid;
    }
    return result + 2;
}

// traduce la palabra Word, devolviendo code y la key 
void stringToInt(string &Words, long long &code, long long &key, vector<Letra> &Letras) {
    vector<int> Numeros = WordToInt(Words, Letras);
    vector<int> NumerosOrdenados = ordenarIeliminarRepe(Numeros);

    code = 1;
    key = 0;
    int n = Numeros.size();
    for (int i = 0; i < n; ++i) {
        code *= Numeros[i];  // Aquí la multiplicación puede ser muy grande
        key *= 10; ++key; key *= 10;
        key += posicion(NumerosOrdenados, Numeros[i]);
    }

}

// Descifrado 
// Factoriza el numero dado y devuelve le numero de factores que tiene 
vector<int> Factorizar(long long num, vector<Letra> &Letras) {
    int nLetra = Letras.size();

    vector<int> Result;

    int i = 0;
    while (num > 1) {
        if (num % Letras[i].primo == 0) {
            Result.push_back(Letras[i].primo);
            num /= Letras[i].primo;
        }
        while (num % Letras[i].primo == 0) num /= Letras[i].primo;

        ++i;
    }

    return Result;
}
// Devuelve el char correspondiente al int
char IntToChar(int num, vector<Letra> &Letras) {
    int i = 0;
    while (num != Letras[i].primo) ++i;
    return Letras[i].letra;
}
// Canvia dos ints de un vector
void swap(int &a, int &b) {
    int bag = a;
    a = b;
    b = bag;
}
// Invierne el orden del vector
void voltearVector(vector<int> &V) {
    int n = V.size() - 1;
    int nHalf = n / 2;

    for (int i = 0; i <= nHalf; ++i) {
        swap(V[i], V[n - i]);
    }
}
// Devuelve un vector con los numeros en ordenar
vector<int> KeyToVector(long long key) {
    vector<int> Orden;

    while (key > 1) {
        long long keyCopy = key;
        long long Potencia = 1;
        while (key % 10 != 1) {
            Potencia *= 10;
            key /= 10;
        } key /= 10;

        Orden.push_back((keyCopy % Potencia) - 2);
    }

    voltearVector(Orden);

    return Orden;
}
// Obtiene le string cifrado, apartir del code y la key
void IntToString(string &Words, long long &code, long long &key, vector<Letra> &Letras) {
    vector<int> Primos = Factorizar(code, Letras); // se obtienen los factores primos
    Words = "";

    // Obtener el orden
    vector<int> Orden = KeyToVector(key);

    int n = Orden.size();
    for (int i = 0; i < n; ++i) {
        Words.push_back(IntToChar(Primos[Orden[i]], Letras));
    }

}

// Funciones finales 
// Añade lo que toque a result y un _ al final
void annadeResult(string &resultadoCode, string &resultadoKey, string &bloque, vector<Letra> &Letras) {
    long long code, key;  // Cambiado a long long
    stringToInt(bloque, code, key, Letras);

    // Agregar code convertido a string y un separador al resultadoCode
    resultadoCode += to_string(code);
    resultadoCode += '_';

    // Agregar key convertido a string y un separador al resultadoKey
    resultadoKey += to_string(key);
    resultadoKey += '_';
}
// Devuelve el string resultante de juntar el code y el key 
string fusionarCodeKey(string &resultadoCode, string &resultadoKey) {
    string result = resultadoCode + "-" + resultadoKey;

    return result;
}
// Devuelve dos strings que son el resultado de separar el code y el key
void desfusionarCodeKey(string &code, string &key, string &Resultado) {
    int n = Resultado.size();
    code = "";
    key = "";

    int i = 0;
    while (i < n && Resultado[i] != '-') {
        code += Resultado[i];
        ++i;
    }++i;
    while (i < n) {
        key += Resultado[i];
        ++i;
    }++i;

}
// Dado un formato num_num_ devuelve un vector de ints [num, num]
vector<int> separarString(string &w){
    vector<int> V;
    int n = w.size();

    int num = 0;
    int i = 0;
    while (i < n) {
        if (w[i] != '_') {
            num *= 10;
            num += int(w[i] - '0');
        }
        else {
            V.push_back(num);
            num = 0;
        }

        ++i;
    }

    return V;
}
// Dado un string te devuelve el cifrado en formato "code1_code2_...-key1_key2_"
// Letras son las letras con su primo respectivo
// NumBloques es el numeor de letras que tiene cada bloque 
string cifradoPrimosOrden(vector<Letra> &Letras, int NumBloques, string &Word) {
    string resultadoCode = "";
    string resultadoKey = "";

    string bloque = string(NumBloques, ' ');
    int n = Word.length();
    int i = 0;
    while (i < n) {
        if (i % NumBloques == 0 && i != 0) {
            annadeResult(resultadoCode, resultadoKey, bloque, Letras);
            bloque = string(NumBloques, ' ');
        }

        bloque[i % NumBloques] = Word[i];
        ++i;
    }
    annadeResult(resultadoCode, resultadoKey, bloque, Letras);

    return fusionarCodeKey(resultadoCode,resultadoKey);
}
// Dado un string con el cifrado en formato "code1_code2...-key1_key2", te devuelve le texto original
// Letras son las letras con su primo respectivo
// NumBloques es el numeor de letras que tiene cada bloque 
string DescifradoPrimosOrden(vector<Letra> &Letras, int NumBloques, string &Code) {
    string code;
    string key;
    desfusionarCodeKey(code, key, Code);

    vector<int> codes = separarString(code);
    vector<int> keys = separarString(key);

    int n = codes.size(); // |codes| == |keys|
    string result = "";
    for (int i = 0; i < n; ++i) {
        string word;
        // Conversión de int a long long
        long long codeLL = (long long) codes[i];
        long long keyLL = (long long) keys[i];
        IntToString(word, codeLL, keyLL, Letras);
        result += word;
    }

    return result;
}
