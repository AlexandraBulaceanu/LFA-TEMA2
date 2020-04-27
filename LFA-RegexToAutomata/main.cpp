#include <iostream>
#include <Automat.h>
#include <fstream>
#include <string>
using namespace std;
ifstream fin("date.in");
//)sdadw
Automat parsare(string reg, int st, int dr)
{
    Automat ans;
    int semn = 0; // concat
    for (int p = st; p <= dr; p++)
    {
        if (reg[p] == '(')//daca dau de ( ->incep sa evaluez ce e in paranteza
        {
            if (p > 0)
            {
                if (reg[p - 1] == '|')
                    semn = 1;//daca rezultatul ce iese  sau ii dau sau trb concatenat
                else
                    semn = 0;
            }
            // unde se termina paranteza deschisa
            int cont = 1; // cate paranteze deschise - paranteze inchise am
            int poz = p + 1;// ma mut in regex pe urmatoarea pozitie
            while (cont !=0 )
            {
                if (reg[poz] =='(')
                    cont ++;
                if (reg[poz] == ')')
                    cont --;
                poz ++;//deplasare
            }
            poz --;//ma pun pe ultima paranteza inchisa
            Automat temp = parsare(reg, p + 1, poz - 1);//scot continutul ()
            p = poz;
            if (poz + 1 < reg.size())
                if (reg[poz + 1] == '*')//aici vad daca nu cumva am stelare
                    *temp, p = poz + 1;
            if (semn == 0)
                ans = ans ^ temp; //fac concatenare
            else
                ans = ans | temp; //sau pun sau
            semn = 0;
        }
        else
        {
            if (reg[p] == '|') // fac sau
                semn = 1;
            else
            {
                Automat temp;
                int poz = p;
                //cand am secventa de caractere faraoperatori
                while(poz<reg.size()&&reg[poz]!='('&&reg[poz]!=')'&&reg[poz]!='|'&&reg[poz]!='*')
                {
                    temp.add(reg[poz]);
                    poz++;
                }
                //vad acum ce fac cu secventa aia de caractere
                if (semn == 0)
                    ans = ans ^ temp;
                else
                    ans = ans | temp;
                poz --;
                p = poz;
            }

        }
    }
    return ans;

}

int main()
{
    Automat a;
    //*a;
    //a.printEndStart();
    //cout<<(a.start)->muchie['~'][0];
   // a.add('b');
    /* Automat d;
     d.add('s');
     a=a|d;*/
    //cout<<a.start->muchie['~'].size();
    //a.printEndStart();
    string exprRegulata;
    fin>>exprRegulata;
    Automat b;
    a.add('a');
    b.add('b');
    //a = parsare(exprRegulata, 0);
    a = parsare(exprRegulata, 0, exprRegulata.size() - 1);
    a.toTxt();
    return 0;
}
