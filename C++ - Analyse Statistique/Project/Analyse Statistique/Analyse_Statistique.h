#pragma once
#ifndef ANALYSE_H
#define ANALYSE_H

#include <string>
#include <vector>

#include "..\dev\header\data_statistics.h"


class Analyse_Statistique :	public data_statistics
{
public:
	// Constructeur(s) et destructeur
	Analyse_Statistique();
	~Analyse_Statistique() = default;

	// Les fonctions contenant les static strings
	std::string const & process_description() override;
	std::string const & implementation_description() override;
	std::string const & implementation_id() override;
	std::string const & author_name() override;
	std::string const & author_id() override;

protected:
	// La fonction principale qui s'occupe de tout
	void do_process(data const & d) override;

private:
	// Les fonctions qui calculent les valeurs � retourner
	// Les autres valeurs � retourn�es sont calcul�es en une ligne dans la fonction do_process

	// Fonction quick-sort r�cursive
	void quickSort(int low, int high);
	// Fonction qui set la m�diane 
	void median();
	// Fonction qui set le mode
	void mode(data const & d);
	// Fonction qui set la somme
	void sum();
	// Fonction qui set la variance
	void variance();

	// Le vecteur de real tri�
	data mSorted;
	// Les variables utilis�es pour le tri du vecteur
	int l;
	int h;
	real pivot;
	real temp;

	// Le vecteur de paires et les variables utilis�s pour le mode
	std::vector<std::pair<integer, int>> mModeList;
	integer mI;
	bool mFound;
	int mRepeat;

	// Les variables d'instances qui contiendront les valeurs � retourner
	real mMin;
	real mMax;
	real mSpan;
	real mMedian;
	integer mMode;
	integer mCount;
	real mSum;
	real mAverage;
	real mVariance;
	real mDeviation;

};

#endif