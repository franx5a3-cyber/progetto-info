// compila con:  g++ -std=c++17 sortalg.cpp -o sortalg
#include <iostream>
#include <vector>
#include <string>

// per creare numeri casuali
#include <random>
// per misurare i tempi di esecuzione
#include <chrono>

using namespace std;

int random(int a, int b){ // restituisce un numero random in [a..b]
    static random_device rd;  // per inizializzare il generatore
    static mt19937 gen(rd()); // static evita di creare ogni volta il generatore a ogni chiamata 
    uniform_int_distribution<int> dist(a, b);

    return dist(gen);
}

vector<int> generaArrayCasuale(int n, int minVal = -100, int maxVal = 100){  // accetta solo n > 0 oppure tutti gli argomenti
    vector<int> A(n); // vettore di n interi da riempire
    for (auto i = 0; i < n; i++){
        A[i] = random(minVal,maxVal);
    }
    return A;  // non fa la copia!
}

void printArray(const vector<int>& B){
    for (auto x : B){
        cout << x << " ";
    }
    cout << endl;
}

void selectionSort(vector<int>& A){
}

void insertionSort(vector<int>& A){
}

int main()
{
    constexpr auto N = 100;                // dimensione = numero di interi random
    vector<int> A = generaArrayCasuale(N); // vector<int> A = {4, -6, 3, 5, -2, 1, -4, 6, -3};
    if (N < 100)
        printArray(A); // questa chiamata ignorata se N è grande

    // array di puntatori a funzioni, evita di scrivere tre volte il codice per misurare i tempi
    using FuncPtr = void (*)(vector<int> &);
    const vector<FuncPtr> funzioni = {
        insertionSort,
        selectionSort
    };
    const vector<string> complessita = {
        "quadratica al caso pessimo",
        "quadratica sempre"
    };

    for (int i = 0; i < funzioni.size(); ++i) {
        auto B = A; // copia del vettore originale

        const auto f = funzioni[i]; // sort
        const auto & costo = complessita[i]; // usa il riferimento, evitiamo la copia della stringa con: auto costo = complessita[i]

        auto start = chrono::steady_clock::now();  // tempo d'inizio

        f(B); // eseguiamo uno dei sort a turno sulla copia (perché?)

        auto stop = chrono::steady_clock::now();    // tempo di fine
        auto durata = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout << "Ordinamento (tempo " << costo << "): " << " [" << durata.count() << " microsecondi]" << endl;
    }
   
    return 0;
}
