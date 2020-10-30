#pragma once
#ifndef REAL_H
#define REAL_H


#include "datum.h"


// La classe 'real' encapsule un 'double' dans une classe.
//
// Description : 
//  - un 'real' se manipule presque comme un 'double'
//  - la plupart des op�rateurs sont disponibles
//  - un panoplie de fonctions math�matiques sont disponibles � m�me l'objet
//
// Attention :
//  - le 'double' � l'int�rieur de la l'objet N'EST PAS ACCESSIBLE d'aucune 
//    fa�on
//  - 'real' est une classe 
//  - ce n'est pas un alias de type (pas un 'typedef' ou un 'using'), 
//    il est donc impossible de l'utiliser l� o� un 'double' est attendu
//
// Surveillance :
//  - toutes les op�rations permises par la classe sont sous surveillance
//  - la surveillance est globale et monitore tous les 'real' � la fois
// 
// Exemple :
//  real r1, r2(5.0), r3(r2);
//  r1 = r2 + r3;
//  r1 = 2.5;                           // le mutateur de double est implicite avec l'op�rateur =
//  bool test{ r1 <= r2 };
//  r1 = r2.round();
//  r1 = r2.square();
//  
//  // il EST IMPOSSIBLE de r�cup�rer le 'double'
//  // double val1{ r1 };                // impossible
//  // double val2{ r1.value() };        // impossible
//
//  // il est possible d'assigner un 'real' avec un 'integer'
//  r1 = integer(100);
//
//  // surveillance
//  std::cout << real::monitoring::measure().detailed_summary("Mon titre");
//  real::monitoring::measure().reset();
using real = datum<double, false>;


#endif // REAL_H

