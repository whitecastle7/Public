
#include <b52_project2_evaluator.h>
#include "b52p2_RoyVincent_1.h"

int main()
{

	b52_project2_evaluator evaluator;
	evaluator.prepare();
	evaluator.add_processor<b52p2_RoyVincent_1, b52p2_RoyVincent_1>();
	evaluator.evaluate();


	//std::cout << real::monitoring::measure().detailed_summary();
	//std::cout << integer::monitoring::measure().detailed_summary();

	return 0;
}