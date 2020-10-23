
import numpy as np


class Recherche:
	# La liste statique pour les types de calculs
	num_calculs = ["0", "1", "2"]

	def __init__(self):
		# On a besoin d'une structure similaire a l'entrainement pour re-utiliser la structure du TP 1
		self.mots = {}
		self.matrice = np.zeros( (1,1) )
		# Le dictionnaire pour les differents types de calculs
		self.calcul_list = {"0": self.__produit_scalaire,
							"1": self.__least_squares,
							"2": self.__city_block}
		self.reverse_sort = ["0"]
		self.stop_list = ["a", "c", "d", "j", "l", "m", "n", "s", "t", "y", "mais","et", "que", "en",
						"pas", "le", "la", "les", "on", "me", "meme", "je", "tu", "il", "elle", "nous",
						"vous", "ils", "elles", "eux", "par", "ce", "ceci", "cela", "ceux", "celle",
						"celles", "cette", "donc", "dans", "ne", "ou", "ou", "de", "des", "votre",
						"notre", "sur", "une", "un", "qui", "si", "que", "quoi", "qu", "son", "sa",
						"ses", "se", "du", "dit", "lui", "pour", "afin", "est", "au", "plus", "tout",
						"tous", "avec", "comme", "avait", "ainsi", "vos", "nos", "leurs", "leur"]


	# Fonction pour faire plusieurs recherches, on donne de nouvelles valeurs aux variables
	def obtenir_parametres(self, mot, nb_syn, num_calcul):
		self.mot = mot
		self.nb_syn = nb_syn
		self.num_calcul = num_calcul


	def traiter_donnees(self, donnees_dao):
		dict_mot = donnees_dao["dao_mots"]
		liste_coocs = donnees_dao["dao_coocs"]
		# On recre le dictionnaire de mots similaire a l'entrainement, ou [mot] = index
		for index1, index2, _fen, _freq in liste_coocs:
			if dict_mot[index1] not in self.mots:
				self.mots[dict_mot[index1]] = len(self.mots)
			if dict_mot[index2] not in self.mots:
				self.mots[dict_mot[index2]] = len(self.mots)

		self.matrice = np.zeros((len(self.mots), len(self.mots)), dtype = np.int32)

		# On met les valeurs dans la matrice
		for index1, index2, _fen, freq in liste_coocs:
			mot1_index = self.mots[dict_mot[index1]] -1
			mot2_index = self.mots[dict_mot[index2]] -1
			self.matrice[mot1_index][mot2_index] = freq
			self.matrice[mot2_index][mot1_index] = freq


	# La fonction qui fait le calcul avec un pseudo-commutateur (le dictionnaire de fonctions de calcul, calcul_list)
	def obtenir_resultats(self):
		if self.mot in self.mots.keys():
			resultats = []
			self.__commutateur(resultats)
			# la fonction .sort() ne retourne pas le tableau mais le trie directement
			if self.num_calcul in self.reverse_sort:
				resultats.sort(reverse = True)
			else:
				resultats.sort()
			return resultats[:int(self.nb_syn)]
		else:
			#aucun resultat : mot pas dans le dictionnaire
			return False


	def __commutateur(self, resultats):
		# On prend l'index et le vecteur du mot
		index_mot = self.mots[self.mot]
		vect_mot = self.matrice[index_mot -1]

		# On prend tout du dictionnaire self.mots
		for autre_mot, autre_index in self.mots.items():
			# On s'assure que le mot du dictionnaire (l'autre mot) n'est pas celui selectionne, ou dans la stoplist
			if autre_index is not index_mot and autre_mot not in self.stop_list:
				# On prend le vecteur de l'autre mot dans la matrice
				autre_vect = self.matrice[autre_index -1]
				# On appel la fonction via le dictionnaire de fonctions de calcul (le commutateur)
				resultats.append((self.calcul_list[self.num_calcul](vect_mot, autre_vect), autre_mot))


	def __produit_scalaire(self, vect_mot, autre_vect):
		return np.dot(vect_mot, autre_vect)

	def __least_squares(self, vect_mot, autre_vect):
		return np.sum(np.power((vect_mot - autre_vect), 2))

	def __city_block(self, vect_mot, autre_vect):
		return np.sum(np.absolute(vect_mot - autre_vect))
