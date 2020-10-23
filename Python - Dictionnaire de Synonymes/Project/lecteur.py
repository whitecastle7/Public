import re

class Lecteur:
    def __init__(self, encodage):
        self.encodage = encodage

    def extraire_mots(self, chemin):
        texte = self.__lire(chemin)
        mots = self.__diviser_mots(texte)
        return mots

    def __lire(self, chemin):
        fichier = open(chemin, 'r', encoding = self.encodage)
        chaine = fichier.read().lower()
        fichier.close()
        return chaine

    def __diviser_mots(self, texte):
        mots = []
        mots += re.findall('\w+', texte)
        return mots
