import os
from PIL import Image
import networkx as nx
from networkx.drawing.nx_agraph import to_agraph


class Automat:
    # input de forma:
    # numar de noduri, numar de muchii
    #nodurile
    #alfabetul acceptat
    # nod_inital
    # muchii nod1, nod2, caracter
    # muchii finale
    # sirul de caractere ce trebuie testat

    def __init__(self, file_name):
        #self.path = set() #calea in graf a cuvantului
        #self.accepted = 0
        file = open(file_name, "r")
        line = file.readline()
        self.n = int((line.split())[0])
        self.m = int((line.split())[1])
        self.nodes = {i for i in range(1,self.n+1)} #nodurile
        #self.sigma = {i for i in file.readline().split()} #limbajul
        #print(self.sigma)
        self.init_node = 1
        self.muchie = {} #dictionar de muchiii
        for i in range(self.m):
            line = file.readline()
            line = line.split()
            nod_1 = line[0]
            nod_2 = line[2]
            char = line[1]
            if((nod_1,char) in self.muchie.keys()):
                self.muchie[(nod_1, char)]+=[nod_2]  #de la nod1 se ajunge prin char la nod2
            else:
                self.muchie[(nod_1, char)]=[nod_2]
        self.final_nodes = {x for x in file.readline().split()}
        try:
            self.word = file.readline()  #cuvant de citit
        except:
            self.word = ""

    # def check(self):
    #
    #     stare_curenta = self.init_node
    #
    #     for i in self.word:
    #         if (stare_curenta, i) not in self.muchie: #daca nu e deloc din start nu e acceptata
    #             return 0
    #         self.path.add((i, stare_curenta, self.muchie[(stare_curenta, i)])) #adaug muchia ce leaga caracterul cu starea curenta si celalat nod
    #         stare_curenta = self.muchie[(stare_curenta, i)] #updatez
    #     self.accepted = stare_curenta in self.final_nodes
    #     return stare_curenta in self.final_nodes   #daca ma aflu in stare finala->true

    def drawGraph(self):
        G = nx.MultiDiGraph()

        # atribute care se refera la cum o sa fie desant graful
        G.graph['edge'] = {'arrowsize': '0.6', 'splines': 'curved'}
        G.graph['graph'] = {'scale': '3'}

        # pentru functionalitatea modulului
        f = open("path_to_bin.txt", "r")
        graph_path = f.readline().strip()
        if not graph_path in os.environ["PATH"]:
            os.environ["PATH"] += os.pathsep + graph_path

        # construiesc graful cu nodurile si muchiile pe care le am in automat
        # adaug toate nodurile din graf

        G.add_nodes_from(self.nodes)
        # nodul initial il colorez cu rosu, iar cele finale cu verde
        G.add_node(self.init_node, color='red')
        for final in self.final_nodes:
            G.add_node(final, color='green')
            #drumul se coloreaza cu mov daca automatul accepta cuvantul si albastru altfel
            #ni = nod initial
            #nf = nod final
        for ni, char in self.muchie: #daca tulplul e in dictionarul muchie
            nfv = self.muchie[(ni, char)]
            for nf in nfv:
                G.add_edge(ni, nf)
                G[ni][nf][len(G[ni][nf])-1]['label'] = char #pun pe muchie eticheta caracterului
        # converteste la obiectul care poate fi desenat
        A = to_agraph(G)
        A.layout('dot')
        A.draw('multi.png')
        # il deseneaza in multi.png
        # il afisez din multi.png
        imag = Image.open('multi.png')
        imag.show()


automat = Automat("dateGraf.txt")
# if (automat.check() == 1):
#     print("Cuvantul " + automat.word + " este accceptat.")
# else:
#     print("Cuvantul " + automat.word + " nu este acceptat.")

automat.drawGraph()