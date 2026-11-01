#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <chrono>
#include <string>

using namespace std;

// Algoritmo 1: Cubico O(N^3)
int SommaMassima1(const vector<int>& B) {
    auto maxs = 0;
    auto n = B.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i; j < n; ++j) {
            auto somma = 0;
            for (size_t k = i; k <= j; ++k)
                somma += B[k];
            if (somma > maxs)
                maxs = somma;
        }
    }
    return maxs;
}

// Algoritmo 2: Quadratico O(N^2)
int SommaMassima2(const vector<int>& B) {
    auto maxs = 0;
    auto n = B.size();
    for (size_t i = 0; i < n; ++i) {
        auto somma = 0;
        for (size_t j = i; j < n; ++j) {
            somma += B[j];
            if (somma > maxs)
                maxs = somma;
        }
    }
    return maxs;
}

// Algoritmo 3: Lineare O(N) - Algoritmo di Kadane
int SommaMassima3(const vector<int>& B) {
    auto maxs = 0;
    auto somma = 0;
    for (size_t j = 0; j < B.size(); j++) {
        if (somma > 0)
            somma += B[j];
        else
            somma = B[j];
        if (somma > maxs)
            maxs = somma;
    }
    return maxs;
}

// Generazione numero casuale
int random(int a, int b) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(a, b);
    return dist(gen);
}

// Generazione array casuale
vector<int> generaArrayCasuale(int n, int minVal = -100, int maxVal = 100) {
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        A[i] = random(minVal, maxVal);
    }
    return A;
}

// Stampa dell'array (passato per riferimento costante per evitare copie)
void printArray(const vector<int>& A) {
    for (auto x : A) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    // Impostiamo N a 1000 per permettere all'algoritmo O(N^3) di terminare rapidamente
    constexpr int N = 1000;
    vector<int> A = generaArrayCasuale(N);

    A[0] = 1;
    A[N - 1] = -1;

    if (N < 100) {
        printArray(A);
    }

    using _se_translator_function = int (*)(const vector<int>&);

    _se_translator_function funzioni[] = {
        SommaMassima3,
        SommaMassima2,
        SommaMassima1
    };

    string complessita[] = {
        "lineare O(N)",
        "quadratica O(N^2)",
        "cubica O(N^3)"
    };

    cout << "=== Test di Performance con N = " << N << " ===\n\n";

    for (int i = 0; i < 3; ++i) {
        auto f = funzioni[i];
        auto costo = complessita[i];

        auto start = chrono::high_resolution_clock::now();
        auto risultato = f(A);
        auto stop = chrono::high_resolution_clock::now();

        auto durata = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout << "Algoritmo " << costo
            << " -> Risultato: " << risultato
            << " | Tempo: " << durata.count() << " us" << endl;
    }

    return 0;
}