#--------------------------------------
# TP2 : Coocurrences
# Auteurs:  Makraphone Phouttama
#           Roy, Vincent
#           Chavez-Campos, Melissa
# Remise: 8 mai 2020
#--------------------------------------

import arguments
import affichage
import model



def main():
    a = arguments.Args()
    args = a.arguments()
    v = affichage.Vue(args)
    m = model.Model(args)

    # Entrainement
    if args.e:
        # Un simple check ici permet de valider l'existence de bon arguments (la classe Args fait le reste)
        if args.t and args.enc and args.chemin:
            m.demarrer_modele(model.Model.entrainement)
            v.afficher_entrainement()
        else:
            v.erreur_entrainement()
    # Recherche
    elif args.r:
        if args.t:
            if not args.enc and not args.chemin:
                fin_recherche = False
                m.preparer_recherche()
                # La boucle de la recherche
                while fin_recherche is not True:
                    v.afficher_recherche()
                    entree = input("Faites votre choix: ")
                    if entree == 'q':
                        fin_recherche = True
                    else:
                        params = {}
                        # On valide les parametres hors du modele
                        valide_params = a.valider_entree(entree, params, model.Model.liste_calcul)

                        if valide_params is True:
                            # On envoit les parametres au model
                            m.obtenir_parametres(params)
                            # On demarre la recherche
                            m.demarrer_modele(model.Model.recherche)
                            # On prend les resultats
                            resultats = m.resultats_recherche()
                            # Un resultat a False signifie que le mot n'a pas ete trouve (aucun resultats)
                            if (resultats is False):
                                a.mot_pas_dans_dict()
                            else:
                                v.afficher_resultats(params, resultats)
                        else:
                            v.entree_non_valide()
                v.au_revoir()
        else:
            v.erreur_recherche()
    # Reinitiliaser BD
    elif args.bd:
        m.demarrer_modele(model.Model.reinitialiser)
        v.afficher_reinit_bd()

    m.fermer_connexion()

    return 0


if __name__ == '__main__':
    quit(main())
