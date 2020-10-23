
# -*- coding: iso-8859-1 -*-
import os


clear = lambda: os.system('cls')


class Vue:
    def __init__(self, args):
        self.arguments = args


    def afficher_entrainement(self):
        #clear()
        print('''
          ______       _             _                                 _
         |  ____|     | |           /_\                               | |
         | |__   _ __ | |_ _ __ __ _ _ _ __   ___ _ __ ___   ___ _ __ | |_
         |  __| | '_ \| __| '__/ _` | | '_ \ / _ \ '_ ` _ \ / _ \ '_ \| __|
         | |____| | | | |_| | | (_| | | | | |  __/ | | | | |  __/ | | | |_
         |______|_| |_|\__|_|  \__,_|_|_| |_|\___|_| |_| |_|\___|_| |_|\__|
                                    _   __ _    __
           ___ ___  _ __ ___  _ __ | | /_/| |_ /_/
          / __/ _ \| '_ ` _ \| '_ \| |/ _ \ __/ _ \\
         | (_| (_) | | | | | | |_) | |  __/ ||  __/
          \___\___/|_| |_| |_| .__/|_|\___|\__\___|
                             |_|
        ''')
        print("Taille de la fenetre: " + str(self.arguments.t[0]))
        print("Encodage: " + str(self.arguments.enc[0]))
        print("Chemin: " + str(self.arguments.chemin[0]))
        print("\n")


    def afficher_recherche(self):
        #clear()
        print('''
          _____           _                   _
         |  __ \         | |                 | |
         | |__) |___  ___| |__   ___ _ __ ___| |__   ___
         |  _  // _ \/ __| '_ \ / _ \ '__/ __| '_ \ / _ \\
         | | \ \  __/ (__| | | |  __/ | | (__| | | |  __/
         |_|  \_\___|\___|_| |_|\___|_|  \___|_| |_|\___|
         ''')
        print("Taille de la fenetre: " + str(self.arguments.t[0]))

        self.__afficher_menu()


    def __afficher_menu(self):
        print('''
        -------------------------------------------------------------------------------
        Entrez un mot, le nombre de synonymes que vous voulez et la methode de calcul,
        i.e. produit scalaire -> 0, least-squares -> 1, city-block -> 2

        Tapez 'q' pour quitter
        --------------------------------------------------------------------------------
        ''')


    def afficher_reinit_bd(self):
        #clear()
        print('''
          ____  ____          __ _       _ _   _       _ _       __
         | __ )|  _ \   _ __ /_/(_)_ __ (_) |_(_) __ _| (_)___  /_/  ___
         |  _ \| | | | | '__/ _ \ | '_ \| | __| |/ _` | | / __|/ _ \/ _ \\
         | |_) | |_| | | | |  __/ | | | | | |_| | (_| | | \__ \  __/  __/
         |____/|____/  |_|  \___|_|_| |_|_|\__|_|\__,_|_|_|___/\___|\___|
        ''')


    def erreur_entrainement(self):
        print("Les commandes '-t', '--enc' et '--chemin' sont necessaires pour l'entrainement.")


    def erreur_recherche(self):
        print("Que la commande '-t' est necessaire pour la recherche.")


    def type_de_recherche(self, no_calcul):
        if (no_calcul == '0'):
            return "0. Produit scalaire"
        elif (no_calcul == '1'):
            return "1. Least square"
        else:
            return "2. City block"

    def afficher_resultats(self, params, pointage):
        #clear()
        print("====================================================================================")
        print(self.type_de_recherche(params["num_calcul"]))
        print("-----------------------------------")
        print("Ceci est la recherche pour: " + params["mot"])
        print(str(len(pointage)) + " resultats\n")

        for i in range(len(pointage)):
            print(f'{i+1}. {pointage[i][1]}  -->  {pointage[i][0]}')

        print("====================================================================================")


    def mot_pas_dans_dict(self):
        #clear()
        print('''
====================================================================================
     Le mot ne se trouve pas dans le dictionnaire, veuillez en choisir un autre.
====================================================================================
''')

    def entree_non_valide(self):
        #clear()
        print('''
=========================================================================================
     Veuillez entrer selon cet ordre: mot nombre_synonymes type_calcul(0, 1 ou 2)
=========================================================================================
''')

    def au_revoir(self):
        #clear()
        print('''
                                  _   _
          _ __ ___   ___ _ __ ___(_) | |
         | '_ ` _ \ / _ \ '__/ __| | | |
         | | | | | |  __/ | | (__| | |_|
         |_| |_| |_|\___|_|  \___|_| (_)
        ''')
