
#include <b52_project2_evaluator.h>
#include "Analyse_Statistique.h"


int main()
{
	b52_project2_evaluator evaluator;
	evaluator.prepare();
	evaluator.add_processor<Analyse_Statistique, Analyse_Statistique>();
	evaluator.evaluate();

	//std::cout << real::monitoring::measure().detailed_summary();
	//std::cout << integer::monitoring::measure().detailed_summary();

	return 0;
}