#ifndef AUTOMAT_H
#define AUTOMAT_H
#include <bits/stdc++.h>
using namespace std;
class Automat
{
    public:
        Automat();
        virtual ~Automat();
        struct Node{
            unordered_map<char,vector<Node*>> muchie; //caracterul e cheie si nodurile in care ma duc cu caracterul c
        };
        Node* start; //nodul de start
        vector<Node*> finale; //noduri finale
        Automat & operator *(); //operatia de stelare
        void printEndStart(); // pentru debug
        void add(char); // automat cu un caracter - adaugare
        Automat  operator |(const Automat &); // adunare
        Automat  operator ^(const Automat &); // inmultire
        void toTxt(); // imi fac fisierul txt pe care sa il trimit in scriptul de python

};

#endif // AUTOMAT_H
