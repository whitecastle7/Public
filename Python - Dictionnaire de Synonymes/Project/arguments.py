
import argparse
import textwrap


class Args():

    def __init__(self):
        # creation du parser superieur
        self.parser = argparse.ArgumentParser(
            prog='parser',
            formatter_class = argparse.RawTextHelpFormatter,
            description=textwrap.dedent('''\
            TP2: Comparaison des contextes de mots
            ---------------------------------------
              Entrainement:       -e -t <taille fenetre> --enc <encodage> --chemin <chemins>
              Recherche:          -r -t <taille fenetre>
              Reinitialiser BD:   --bd

             '''))

        # obliger l'utilisation de la commande "-e", "-r" ou "--bd"
        self.group = self.parser.add_mutually_exclusive_group(required=True)
        self.group.add_argument('-e', action='store_true', help="demarrer l'entrainement")
        self.group.add_argument('-r', action='store_true', help='demarrer la recherche')
        self.group.add_argument('--bd', action='store_true', help='reinitiliser la base de donnees')

        # commandes additionnelles
        # MC : desactive DEFAULT pour les tests, ca va mieux
        self.parser.add_argument('-t', type=int, nargs=1, help='taille de la fenetre')#, default=5)
        self.parser.add_argument('--enc', nargs=1, help='encodage')#, default='utf-8')
        self.parser.add_argument('--chemin', type=str, nargs=1, help='lien vers le texte')


    def arguments(self):
        return self.parser.parse_args()


    # Fonction qui valide les entrees pour la recherche
    def valider_entree(self, entree, params, liste_calcul):
        liste_entrees = entree.split()
        if len(liste_entrees) != 3:
            return False
        else:
            try:
                int(liste_entrees[1])
            except expression as identifier:
                return False
            if liste_entrees[2] in liste_calcul:
                params["mot"] = liste_entrees[0]
                params["nb_syn"] = liste_entrees[1]
                params["num_calcul"] = liste_entrees[2]
                return True
            else:
                return False
