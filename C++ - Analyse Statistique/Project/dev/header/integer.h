#pragma once
#ifndef INTEGER_H
#define INTEGER_H


#include "datum.h"
#include <cstdint>


// La classe 'integer' encapsule un 'int' (32-bits) dans une classe.
//
// Description : 
//  - un 'integer' se manipule presque comme un 'int'
//  - la plupart des op�rateurs sont disponibles
//  - un panoplie de fonctions math�matiques sont disponibles � m�me l'objet
//
// Attention :
//  - le 'int' � l'int�rieur de l'objet EST ACCESSIBLE via son accesseur 
//    (value) ou par conversion de type
//  - 'real' est une classe 
//  - ce n'est pas un alias de type (pas un 'typedef' ou un 'using'), 
//    il est donc impossible de l'utiliser l� o� un 'double' est attendu
//
// Surveillance :
//  - toutes les op�rations permises par la classe sont sous surveillance
//  - la surveillance est globale et monitore tous les 'integer' � la fois
// 
// Exemple :
//  integer i1, i2(5), i3(i2);
//  i1 = i2 + i3;
//  i1 = 50;                           // le mutateur de double est implicite avec l'op�rateur =
//  bool test{ i1 <= i2 };
//  i1 = i2.round();
//  i1 = i2.square();
//  
//  // il EST POSSIBLE de r�cup�rer le 'int'
//  int val1{ i1 };                     // possible via une conversion implicite
//  int val2{ i1.value() };             // possible via une conversion explicite, un accesseur
//
//  // il est possible d'assigner un 'integer' avec un 'real'
//  i1 = real(100.0);
//
//  // surveillance
//  std::cout << integer::monitoring::measure().detailed_summary("Mon titre");
//  integer::monitoring::measure().reset();
using integer = datum<int32_t, true>;


#endif // REAL_H

