#include <iostream>
#include <vector>
#include <string>
#include <random>

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
