
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

using namespace std;

// Restituisce un numero casuale nell'intervallo [a, b]
int numeroCasuale(int a, int b) {
    static random_device rd;
    static mt19937 gen(rd());

    uniform_int_distribution<int> dist(a, b);
    return dist(gen);
}

// Genera un vettore di n numeri casuali
vector<int> generaArrayCasuale(
    int n, int minVal = -100, int maxVal = 100
) {
    vector<int> A(n);

    for (int i = 0; i < n; i++) {
        A[i] = numeroCasuale(minVal, maxVal);
    }

    return A;
}

// Stampa il vettore
void printArray(const vector<int>& B) {
    for (auto x : B) {
        cout << x << " ";
    }
    cout << endl;
}

// Selection sort
void selectionSort(vector<int>& A) {
    for (size_t i = 0; i + 1 < A.size(); i++) {
        size_t indiceMinimo = i;

        for (size_t j = i + 1; j < A.size(); j++) {
            if (A[j] < A[indiceMinimo]) {
                indiceMinimo = j;
            }
        }

        if (indiceMinimo != i) {
            swap(A[i], A[indiceMinimo]);
        }
    }
}

// Insertion sort
void insertionSort(vector<int>& A) {
    for (size_t i = 1; i < A.size(); i++) {
        auto t = A[i];
        size_t j = i;

        while (j > 0 && A[j - 1] > t) {
            A[j] = A[j - 1];
            j--;
        }

        A[j] = t;
    }
}

int main() {
    constexpr int N = 100;

    vector<int> A = generaArrayCasuale(N);

    // Stampa il vettore iniziale solo se N < 100
    if (N < 100) {
        cout << "Vettore iniziale: ";
        printArray(A);
    }

    // Puntatore a una funzione di ordinamento
    using FuncPtr = void (*)(vector<int>&);

    const vector<FuncPtr> funzioni = {
        insertionSort,
        selectionSort
    };

    const vector<string> complessita = {
        "O(n^2) medio e pessimo, O(n) migliore",
        "O(n^2) in tutti i casi"
    };

    // Esegue e misura entrambi gli algoritmi
    for (size_t i = 0; i < funzioni.size(); i++) {
        vector<int> B = A;  // Copia il vettore originale

        const auto f = funzioni[i];
        const auto& costo = complessita[i];

        auto start = chrono::steady_clock::now();

        f(B);

        auto stop = chrono::steady_clock::now();

        auto durata = chrono::duration_cast<
            chrono::microseconds
        >(stop - start);

        cout << "Ordinamento (" << costo << "): "
             << durata.count()
             << " microsecondi" << endl;

        // Verifica che il vettore sia ordinato
        bool ordinato = true;

        for (size_t j = 1; j < B.size(); j++) {
            if (B[j - 1] > B[j]) {
                ordinato = false;
                break;
            }
        }

        cout << "Vettore ordinato correttamente: "
             << (ordinato ? "si" : "no") << endl;
    }

    return 0;
}