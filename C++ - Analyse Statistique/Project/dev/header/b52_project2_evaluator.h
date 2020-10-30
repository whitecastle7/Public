#pragma once
#ifndef B52_PROJECT2_EVALUATOR_H
#define B52_PROJECT2_EVALUATOR_H


#include "evaluator.h"


// Cette classe est le moteur de test.
// 
// Il suffit de l'instancier, de lui ajouter vos classes et de partir l'
// �valuation pour voir les r�sultats.
// 
// Il est possible de cr�er trois type d'�valuateur :
//  - les tests pr�d�termin�s : en utilisant le constructeur par d�faut
//  - un test d�fini par l'usager : en utilisant le constructeur avec 'eval'
//  - plusieurs tests d�finis par l'usager : avec le constructeur utilisant 'evals'
// 
// Voici un exemple comment utiliser cette classe :
// 
// int main() 
// {
//      // inclu tous les tests pr�d�termin�s qui serviront � l'�valuation.        
//      b52_project2_evaluator evaluateur_1();
//
//      // inclu un test d�fini par l'usager
//      b52_project2_evaluator evaluateur_2(new ma_class_evaluation_1);  // voir la classe 'evaluation'
//
//      // inclu plusieurs tests d�finis par l'usager - voir la classe 'evaluation'
//      b52_project2_evaluator evaluateur_3({   new ma_class_evaluation_1, 
//                                              new ma_class_evaluation_2,
//                                              new ma_class_evaluation_3 } );
//
//      // les tests �tant d�finis, il est possible de pr�parer l'engin de test imm�diatement
//      evaluateur_1.prepare();
//
//      // maintenant, on ajoute les 2 classes r�alisant l'analyse statistique demand�e. 
//      evaluateur_1.add_processor<ma_solution_implementation_1, ma_solution_implementation_2>();
// 
//      // finalement, on r�alise l'�valuation
//      evaluateur_1.evaluate();
// 
//      return 0;
// }
class b52_project2_evaluator : public evaluator
{
public:
    b52_project2_evaluator();
    b52_project2_evaluator(evaluation * eval);
    b52_project2_evaluator(std::vector<evaluation*> evals);
};


#endif // B52_PROJECT2_EVALUATOR_H