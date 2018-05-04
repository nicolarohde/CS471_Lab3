#include "SelectionStrategy.hpp"

using namespace std;

typedef function<Gene*(const GA_Population&)> StrategyFunction;

Parents* SelectionStrategy::selectParents(const GA_Population& pop, StrategyType t)
{
	Parents* p = new Parents();
	StrategyFunction f;

	switch (t)
	{
	case SelectionStrategy::StrategyType::Roulette:
		f = roulette;
		break;
	case SelectionStrategy::StrategyType::Proportionate:
		f = proportionate;
		break;
	case SelectionStrategy::StrategyType::Rank:
		f = rank;
		break;	
	case SelectionStrategy::StrategyType::SteadyState:
		f = steadyState;
		break;
	case SelectionStrategy::StrategyType::Tournament:
		f = tournament;
		break;
	default:
		throw invalid_argument("Invalid type received by selectParents.");
	} // end switch

	p->parent_A = f(pop);
	p->parent_B = f(pop);

	// ensure parents are unique
	while (p->parent_A == p->parent_B)
	{
		p->parent_A = f(pop);
	} // end while

	return p;
} // end method selectParents


Gene* SelectionStrategy::tournament(const GA_Population & pop)
{
	throw not_implemented();
} // end method tournament


Gene* SelectionStrategy::roulette(const GA_Population & pop)
{
	// our random number is in the range [0, total_probabilities]
	double	d_rand = getRandomRealInRange<double>(0.0, vectorSum(&pop.probabilities));

	Gene* selected = &(pop[0]);

	for (size_t i = 0; i < pop.probabilities.size(); i++)
	{
		// if probability[i] <= rand < probability[i+1], the individual i was selected
		// if probability[size] <= rand <= sum_probabilities, the last individual was selected
		if (pop.probabilities.at(i) > d_rand)
		{
			break;
		} // end if

		selected = &(pop[i]);
	} // end for

	return selected;
} // end method roulette


Gene* SelectionStrategy::proportionate(const GA_Population & pop)
{
	throw not_implemented();
} // end method proportionate


Gene* SelectionStrategy::rank(const GA_Population & pop)
{
	throw not_implemented();
} // end method rank


Gene* SelectionStrategy::steadyState(const GA_Population & pop)
{
	throw not_implemented();
} // end method steadyState

