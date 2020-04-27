#include "Automat.h"
#include <bits/stdc++.h>
ofstream fout("dateGrafic.txt");
Automat::Automat()
{
    start = new Node;//fac un nod de start
}

Automat::~Automat()
{
    //dtor
}
Automat & Automat::operator *(){
    Node* temp = new Node;
    temp->muchie['~'].push_back(start); // am pus ca ma duc prin lambda de la noul start la vechiul start
    start = temp;
    for(auto &it:finale)
        {
            (*it).muchie['~'].push_back(start);//leg nodurile finale de start
        }
    finale.push_back(start);//ca il fac final si pe cel initial -> ca sa il accepte si pe vid
    return (*this);
}
void Automat::printEndStart(){
    //printez nodul initial si noduri finale
    for(auto &it:finale){
        cout<<it<<" ";
    }
    cout<<'\n';
    cout<<start;
}

void Automat::add(char cara){//.
    //creez un automat ce accepta doar caracterul cara primit ca parametru
    Node* n = new Node;
    if (finale.size() == 0) //daca automatul e gol
    {
        start->muchie[cara].push_back(n);//de la start duc muchie cu acel caracter la un nou nod
        finale.push_back(n);//il pun in noduri finale pe n
    }
    else
    {
        finale[0] -> muchie[cara].push_back(n); //pun o muchie de la final la nod
        finale[0] = n; //am un sg nod final si e cel nou introdus
    }
}

Automat  Automat::operator |(const Automat &altul){
    Automat temp;
    if (finale.size() == 0)
    {
        temp = altul;//nu am elemete in automat, returnez automatul param
        return temp;
    }
    if (altul.finale.size() == 0)
    {
        temp = (*this);//automatul primit e gol il returnez pe cel curent
        return temp;
    }
    temp.start->muchie['~'].push_back(start);//leg prin lambda temp cu curent
    temp.start->muchie['~'].push_back(altul.start);//leg prin lambda temp cu altul
    for(auto &it:finale){
        temp.finale.push_back(it); // pun nodurile finale ale curent
    }
    for(auto &it:altul.finale){
        temp.finale.push_back(it); // pun nodurile finale ale altul
    }
    return temp;
}

Automat  Automat::operator ^(const Automat &altul){//concatenez doua expresii
    if (finale.size() == 0)
        {
            (*this) = altul;
            return (*this);//daca this e gol -> altul
        }
    if (altul.finale.size() == 0)
    {
        return (*this);// daca altul e gol -> il returnez direct pe altul
    }
    for(auto &it:finale){
        (*it).muchie['~'].push_back(altul.start); //leg nodurile finale ale this de nodul de start al lui altul
    }
    finale.clear(); //sterg vechile noduri finae
    for(auto &it:altul.finale){
        finale.push_back(it);//le inlocuiesc cu cele finale noi ale lui altul
    }
    return (*this);
}

void Automat::toTxt(){
    //bfs
    int contor=0;
    unordered_map<Node*,int> mapper;//asociez fiecare nod cu un numar, pt a putea sa il fac
    unordered_set<Node*> vizitat; //set de noduri vizitate
    queue<Node*> coada; //coada
    vector<pair<int, int>> ans_n;
    vector<char> ans_c;
    coada.push(start);//prima pun start in coada
    while(!coada.empty()) // daca nu e goala coada
    {
        Node* frontul = coada.front();//primul nod din coada il sterg
        coada.pop();
        if(mapper.find(frontul)==mapper.end()){ //daca primul e si ultimul
            contor++; // contor
            mapper[frontul]=contor; // mapez numar nodului
        }
        vizitat.insert(frontul);//a fost vizitat
        for(auto &it:frontul->muchie){ //ma duc in toate muchiile ce pleaca din nodul curent
            for(auto &k:it.second){//
            if (vizitat.find(k) == vizitat.end())//nu e in vizitat
            {
                coada.push(k);//il bag in coada
            }
            if(mapper.find(k)==mapper.end()){//nu e in map
            contor++;
            mapper[k]=contor;//mapez valoare numerica

        }
            ans_n.push_back(make_pair(mapper[frontul], mapper[k]));//fac pereche intre aceste 2 noduri
            ans_c.push_back(it.first);//nodul
            //fout<<mapper[frontul]<<" "<<it.first<<" "<<mapper[k]<<'\n';
        }}
    }
    fout << contor <<" " <<ans_c.size()<<"\n";//nr de noduri, nr de muchii

    for (int i = 0; i < ans_c.size(); i++)
    {
        fout << ans_n[i].first <<" "<<ans_c[i] << " " << ans_n[i].second<<"\n"; // nod-caracter-nod
    }
    for (auto &it: finale)
        fout<< mapper[it] <<" "; //noduri finale lista

}

