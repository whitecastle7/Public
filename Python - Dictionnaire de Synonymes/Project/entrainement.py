
import numpy as np
import math
import lecteur as l


class Entrainement:
    def __init__(self, chemin, taille_fen, encodage):
        self.chemin = chemin
        self.rayon = math.floor(taille_fen/2)
        self.mots = []
        self.dict_mot = {}
        self.dict_index = {} #ajout d'un dictionnaire qui contient les donnees inverse de dic_mot
        self.matrice = np.zeros((1, 1))
        self.dict_cooc = {}
        self.lecteur = l.Lecteur(encodage)

    def traiter_texte(self):
        self.mots = self.lecteur.extraire_mots(self.chemin)
        self.__ajouter_au_dict()
        self.__calculer_cooc()
        return {"mots":self.dict_mot, "coocs":self.dict_cooc}

    def __ajouter_au_dict(self):
        for mot in self.mots:
            if mot not in self.dict_mot:
                self.dict_mot[mot] = len(self.dict_mot)
                self.dict_index[self.dict_mot[mot]] = mot #le remplissage du deuxieme dictionnaire

    def __calculer_cooc(self):
        # On itere au travers du texte / la liste de tous les mots
        for i in range(len(self.mots)):
            # On prend le id du premier mot
            id_mot_1 = self.dict_mot[self.mots[i]]
            # On regarde autour
            for j in range(1, self.rayon + 1):
                if i - j > 0:
                    # On prend le id du deuxieme mot
                    id_mot_2 = self.dict_mot[self.mots[i - j]]
                    # Si le id du premier mot est <= au id du deuxieme mot
                        # Pour ne prendre que la moitie de la "matrice"
                    if id_mot_1 <= id_mot_2:
                        # On prend la valeur des mots (string)
                        mot_1 = self.mots[i]
                        mot_2 = self.mots[i - j]
                        # On regarde si le couple de string est deja dans le dictionnaire
                        if (mot_1, mot_2) in self.dict_cooc:
                            self.dict_cooc[(mot_1, mot_2)] += 1
                        else:
                            self.dict_cooc[(mot_1, mot_2)] = 1
                if i + j < len(self.mots):
                    id_mot_2 = self.dict_mot[self.mots[i + j]]
                    if id_mot_1 <= id_mot_2:
                        mot_1 = self.mots[i]
                        mot_2 = self.mots[i + j]
                        if (mot_1, mot_2) in self.dict_cooc:
                            self.dict_cooc[(mot_1, mot_2)] += 1
                        else:
                            self.dict_cooc[(mot_1, mot_2)] = 1
