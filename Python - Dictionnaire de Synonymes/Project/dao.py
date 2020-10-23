
import sqlite3
import numpy as np


class DAO:
    def __init__(self):
        self.chemin_db = "testdb.db"
        self.connection = None
        self.curseur = None

        ###############################
        #ENONCES sqlite
        ###############################
        self.ENABLE_FK = 'PRAGMA foreign_keys = 1'
        self.DROP_TABLE_MOT = 'DROP TABLE IF EXISTS mot'
        self.DROP_TABLE_COOC = 'DROP TABLE IF EXISTS cooccurrence'
        self.CREER_TABLE_MOT = '''
CREATE TABLE IF NOT EXISTS mot
(
    id      INTEGER PRIMARY KEY,
    nom     CHAR(15) NOT NULL
)
'''
        self.CREER_TABLE_COOC = '''
CREATE TABLE IF NOT EXISTS cooccurrence
(
    id_mot1     INTEGER NOT NULL,
    id_mot2     INTEGER NOT NULL,
    taille_fen  INTEGER NOT NULL,
    frequence   INTEGER DEFAULT 1 NOT NULL,
    PRIMARY KEY (id_mot1, id_mot2, taille_fen),
    FOREIGN KEY (id_mot1) REFERENCES mot(id),
    FOREIGN KEY (id_mot2) REFERENCES mot(id)
)
'''
        self.INSERT_MOT = 'INSERT INTO mot(id, nom) VALUES (?, ?)'
        self.INSERT_COOC = 'INSERT INTO cooccurrence(id_mot1, id_mot2, taille_fen, frequence) VALUES(?, ?, ?, ?)'

        self.UPDATE_COOC = '''
UPDATE cooccurrence
SET frequence = ?
WHERE id_mot1 = ? AND id_mot2 = ? AND taille_fen = ?
'''
        self.CHERCHER_TOUS_MOTS = 'SELECT * FROM mot'
        #self.CHERCHER_MOT_PAR_NOM = 'SELECT * FROM mot WHERE nom = ?'
        #self.CHERCHER_IDMOT_PAR_NOM = 'SELECT id FROM mot WHERE nom = ?'
        #self.CHERCHER_MOT_PAR_ID = 'SELECT * FROM mot WHERE id = ?'

        #self.CHERCHER_TOUTES_COOCS = 'SELECT * FROM cooccurrence'
        self.CHERCHER_COOCS = 'SELECT * FROM cooccurrence WHERE taille_fen = ?'
#         self.CHERCHER_COOC = '''
# SELECT * FROM cooccurrence
# WHERE id_mot1 = ? AND id_mot2 = ? AND taille_fen = ?
# '''
#         self.CHERCHER_FREQ = '''
# SELECT frequence FROM cooccurrence
# WHERE id_mot1 = ? AND id_mot2 = ? AND taille_fen = ?
# '''
        ###########################
        ###########################

    def connecter_dao(self):
        self.connection = sqlite3.connect(self.chemin_db)
        self.curseur = self.connection.cursor()
        self.curseur.execute(self.ENABLE_FK)
        #return self.connection

    def deconnecter_dao(self):
        self.curseur.close()
        self.connection.close()

    def init_tables_dao(self):
        self.curseur.execute(self.DROP_TABLE_COOC)
        self.curseur.execute(self.DROP_TABLE_MOT)
        self.curseur.execute(self.CREER_TABLE_MOT)
        self.curseur.execute(self.CREER_TABLE_COOC)
        self.connection.commit()

    #def AFFICHER_BD(self): #fonction test
    #    print('''
    #    dao---AFFICHER_BD''')
    #    liste_mots = []
    #
    #    # Afficher la table MOT
    #    self.curseur.execute(self.CHERCHER_TOUS_MOTS)
    #    liste_mots = self.curseur.fetchall()
    #    if not len(liste_mots):
    #            print("IL Y A ZERO MOTS DS LA BD")
    #    else:
    #        print("LA TABLE MOT CONTIENT:", liste_mots)
    #
    #    # Afficher la table COOCCURRENCE
    #    self.curseur.execute(self.CHERCHER_TOUTES_COOCS)
    #    liste_freqs = self.curseur.fetchall()
    #    if not len(liste_freqs):
    #            print("IL Y A ZERO COOCCURRENCE DS LA BD")
    #    else:
    #        print("LA TABLE COOCCURRENCE CONTIENT: ", liste_freqs)

    # Insere des nouveaux mots dans la BD
    def inserer_mots(self, dict_nouv_mots):
        liste_nouv_mots = []
        for nom in dict_nouv_mots:
            liste_nouv_mots.append( (None, nom) )
        self.curseur.executemany(self.INSERT_MOT, liste_nouv_mots)
        self.connection.commit()

    # Insere les nouvelles cooccurrences
    def inserer_coocs(self, dict_nouv_coocs):
        self.curseur.executemany(self.INSERT_COOC, dict_nouv_coocs)
        self.connection.commit()

    # Mets a jour les frequences
    def mettre_a_jour_freqs(self, dict_nouv_freqs):
        self.curseur.executemany(self.UPDATE_COOC, dict_nouv_freqs)
        self.connection.commit()

    # Charge un dictionnaire de mot
    def charger_table_mots(self, dict_mots):
        self.curseur.execute(self.CHERCHER_TOUS_MOTS)
        liste_mots = self.curseur.fetchall()
        for index, nom in liste_mots:
            dict_mots[nom] = index

    # Rempli un dictionnaire pour l'entrainement
    def charger_table_cooc(self, model_dict_cooc, taille_fen):
        dict_mot = {}
        self.charger_table_mots(dict_mot)

        self.curseur.execute(self.CHERCHER_COOCS, (taille_fen,))
        liste_coocs = self.curseur.fetchall()
        for index1, index2, _fen, freq in liste_coocs:
            un_tuple = (dict_mot[index1], dict_mot[index2])
            model_dict_cooc[un_tuple] = freq

    # Renvoit des donnees pour la recherche
    def charger_table_cooc_recherche(self, taille_fen):
        donnees_dao = {}
        dict_mot = {}
        self.charger_table_mots(dict_mot)
        donnees_dao["dao_mots"] = dict_mot

        self.curseur.execute(self.CHERCHER_COOCS, (taille_fen,))
        liste_coocs = self.curseur.fetchall()
        donnees_dao["dao_coocs"] = liste_coocs

        # Le model / la recherche s'occupe de refaire la matrice, le dao ne fait que donner des donnees
        return donnees_dao
