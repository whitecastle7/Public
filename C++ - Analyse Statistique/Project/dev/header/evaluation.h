#pragma once
#ifndef EVALUATION_H
#define EVALUATION_H


#include "data_statistics.h"


// Cette classe repr�sente une �valuation sp�cifique.
// 
// Elle est destin�e � �tre h�rit�e. La classe enfant doit �tre en mesure de 
// d�finir ces trois param�tres � m�me son constructeur :
//  - _data : 
//          - les donn�es � traiter
//          - il est attendu que le vecteur de 'real' soit mis � la taille 
//            d�sir�e et que le contenu soit ad�quatement d�termin�
//  - _title : 
//          - titre de l'�valuation
//          - le titre doit �tre unique parmi toutes les �valuations
//          - le titre sera tronqu� � 32 caract�res
//  - _objective :
//          - une description de l'�valuation
// 
// Il est tr�s facile de faire sa propre classe de test. Voici un exemple :
// 
// class mon_evaluation : public evaluation
// {
// public:
//      mon_evaluation();
// };
//
//
// mon_evaluation::mon_evaluation()
//      : evaluation(100, "mon titre", "mon objectif")      // 100 correspond � la taille du tableau pour les tests
// {
//      // on rempli le tableau de valeurs al�atoires born�es entre -1000 et 1000
//      for (real & value : _data) {
//          value.randomize(real(-1000.0), real(1000.0));
//      }
//      
//      // on m�lange les donn�es
//      std::shuffle(_data.begin(), _data.end(), std::default_random_engine());
// }
class evaluation
{
public:
    ~evaluation() = default;

protected:
    evaluation(std::string const & title, std::string const & objective = "");
    evaluation(std::size_t size, std::string const & title, std::string const & objective = "");
    evaluation(data const & d, std::string const & title, std::string const & objective = "");
    evaluation(evaluation const &) = delete;
    evaluation(evaluation &&) = delete;
    evaluation& operator=(evaluation const &) = delete;
    evaluation& operator=(evaluation &&) = delete;

    data _data;

    static constexpr std::size_t title_max_length{ 32 };

private:
    std::string _title;
    std::string _objective;
    std::string conform_title(std::string const & title);

    friend class evaluator;
};






class easy_evaluation : public evaluation
{
public:
    enum class ordering { none, sort_ascending, sort_descending, shuffle };
    easy_evaluation(std::size_t n, real const & value, std::string const & title, std::string const & objective = "");
    easy_evaluation(std::size_t n, real const & from, real const & increment, ordering order, std::string const & title, std::string const & objective = "");
    easy_evaluation(std::size_t n, ordering order, real const & random_min_value, real const & random_max_value, std::string const & title, std::string const & objective = "");

private:
    void apply_ordering(ordering order);
};



class empty_data        : public evaluation { public: empty_data(); };

class one_zero          : public easy_evaluation { public: one_zero(); };
class one_random        : public easy_evaluation { public: one_random(); };








#endif // EVALUATION_H