
import dao as d
import entrainement as e
import recherche as r

import time as time


class Model:
    entrainement = "entrainement"
    recherche = "recherche"
    reinitialiser = "reinitialiser"
    liste_calcul = r.Recherche.num_calculs

    def __init__(self, args):
        # Pour l'instant on ne fait que garder les arguments dans une variable
        self.arguments = args
        # Un dictionnaire de fonctions
        self.fonctions = {"entrainement":self.__entrainement,
                            "recherche":self.__recherche,
                            "reinitialiser":self.__reinitialiser}

        # Le DAO est utilise peu importe la fonctionalite en ce moment, on peut le laisser ici
        self.dao = d.DAO()
        self.dao.connecter_dao()

        self.dict_mots_bd = {}
        self.dict_coocs_bd = {}
        self.liste_nouv_mots = []
        self.liste_nouv_coocs = []
        self.liste_nouv_freqs = []


    def fermer_connexion(self):
        self.dao.deconnecter_dao()

    # Le pseudo-switch du model, le main call du controlleur
    def demarrer_modele(self, cle_fonction):
        self.fonctions[cle_fonction]()

    # Met la liste de mots de la BD dans un dictionnaire
    def __charger_dict_mots_bd(self):
        self.dao.charger_table_mots(self.dict_mots_bd)

    # Met la liste de coocs de la BD dans un dictionnaire, selon la taille de fenetre specifiee
    def __charger_dict_coocs_bd(self):
        self.dao.charger_table_cooc(self.dict_coocs_bd, self.taille_fenetre)


# Reinitialisation de la BD ---------------------------------------------
    # L'option --bd
    def __reinitialiser(self):
        self.dao.init_tables_dao()
# -----------------------------------------------------------------------


# Recherche -------------------------------------------------------------
    # La fonction qui prend les donnees de la BD et les met en memoire
    # aussi genere l'objet de recherche
    def preparer_recherche(self):
        self.taille_fenetre = self.arguments.t[0]
        self.recherche = r.Recherche()
        donnees_dao = self.dao.charger_table_cooc_recherche(self.taille_fenetre)
        self.recherche.traiter_donnees(donnees_dao)

    # La fonction qui set le input de l'utilisateur pour la recherche
    def obtenir_parametres(self, params):
        self.recherche.obtenir_parametres(params["mot"], params["nb_syn"], params["num_calcul"])

    def __recherche(self):
        self.resultat = self.recherche.obtenir_resultats()

    # On ne veut pas que les fonctions de self.fonctions retourne des valeurs, donc un pseudo-get
    def resultats_recherche(self):
        return self.resultat

# -----------------------------------------------------------------------


# Entrainement ----------------------------------------------------------
    # La fonction de base pour l'entrainement
    def __entrainement(self):
        self.chemin_txt = ""
        # Si le chemin contient des espaces, il est diviser -il faut donc le re-assembler
        for i in range(len(self.arguments.chemin)):
            self.chemin_txt += self.arguments.chemin[i]
            self.chemin_txt += " "
        self.enc = self.arguments.enc[0]
        self.taille_fenetre = self.arguments.t[0]

        # On charge en avance les mots et les occurences de la BD
        self.__charger_dict_mots_bd()
        self.__charger_dict_coocs_bd()

        # On est pret pour l'entrainement
        self.__demarrer_entrainement()

    def __demarrer_entrainement(self):
        # Creation d'une instance de l'entrainement et un pseudo-get pour obtenir les resultats
        self.entrain = e.Entrainement(self.chemin_txt, self.taille_fenetre, self.enc)
        resultat = self.entrain.traiter_texte()

        # On gere les nouveaux mots
        self.__lister_nouv_mots(resultat["mots"]) #Ca remplit self.liste_nouv_mots
        self.dao.inserer_mots(self.liste_nouv_mots) #Inserer les nouveaux mots
        self.__charger_dict_mots_bd() #Recharger apres insertion, pour etre a jour lorsqu'on check les coocc

        # Par la suite on gere les nouvelles coocs et freqs
        # On commence par les trouvees
        self.__lister_nouv_freqs_coocs(resultat["coocs"])

        # S'il y a des nouvelles coocs, on les rajoute
        if len(self.liste_nouv_coocs) > 0:
            self.dao.inserer_coocs(self.liste_nouv_coocs)

        # S'il y a des frequences a mettre a jour, on le fait
        if len(self.liste_nouv_freqs) > 0:
            self.dao.mettre_a_jour_freqs(self.liste_nouv_freqs)

        # L'entrainement est terminer rendu ici
        # -------------------------------------

    def __lister_nouv_mots(self, dict_mots_nouv_texte):
        for nom in dict_mots_nouv_texte:
            if nom not in self.dict_mots_bd:
                self.liste_nouv_mots.append(nom)

    def __lister_nouv_freqs_coocs(self, donnees):
        for (mot_1, mot_2), freq in donnees.items():
            mot_1_id = self.dict_mots_bd[mot_1]
            mot_2_id = self.dict_mots_bd[mot_2]
            if (mot_1, mot_2) in self.dict_coocs_bd:
                nouvelle_freq = self.dict_coocs_bd[(mot_1, mot_2)] + freq
                self.liste_nouv_freqs.append( (mot_1_id, mot_2_id, self.taille_fenetre, nouvelle_freq) )
            elif (mot_2, mot_1) in self.dict_coocs_bd:
                nouvelle_freq = self.dict_coocs_bd[(mot_2, mot_1)] + freq
                self.liste_nouv_freqs.append( (mot_2_id, mot_1_id, self.taille_fenetre, nouvelle_freq) )
            else:
                self.liste_nouv_coocs.append( (mot_1_id, mot_2_id, self.taille_fenetre, freq) )

# -----------------------------------------------------------------------
