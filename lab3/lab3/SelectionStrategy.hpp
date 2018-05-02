#pragma once

#ifndef _SELECTION_STRAT_H
#define _SELECTION_STRAT_H

#include "Population.hpp"

/// <summary>Wrapper class for selection strategies.</summary>
class SelectionStrategy
{
public:
	/// <summary>Types of selection strategies.</summary>
	enum StrategyType
	{
		Tournament,
		Roulette,
		Proportionate,
		Rank,
		SteadyState
	}; // end enum Type

	/// <summary>Selects two parents from the population <paramref name="pop"/> using strategy <paramref name="t"/>.</summary>
	/// <param name="pop">The population to select parents from.</param>
	/// <param name="t">(Optional) The strategy to use. DEFAULT: Roulette</param>
	/// <returns>A parent structure with two pointers to two genes in the population <paramref name="pop"/>.</returns>
	static Parents* selectParents(const Population& pop, StrategyType t = StrategyType::Roulette);

private:
	/// <summary>Selects a parent from the population <paramref name="pop"/> using the tournament selection strategy.</summary>
	/// <param name="pop">The population to select parents from.</param>
	/// <returns>A pointer to a gene in the population <paramref name="pop"/> that is the selected parent.</returns>
	static Gene* tournament(const Population& pop);

	/// <summary>Selects a parent from the population <paramref name="pop"/> using the roulette selection strategy.</summary>
	/// <param name="pop">The population to select an individual from.</param>
	/// <returns>A pointer to a gene in the population <paramref name="pop"/> that is the selected parent.</returns>
	static Gene* roulette(const Population& pop);

	/// <summary>Selects a parent from the population <paramref name="pop"/> using the proportionate selection strategy.</summary>
	/// <param name="pop">The population to select an individual from.</param>
	/// <returns>A pointer to a gene in the population <paramref name="pop"/> that is the selected parent.</returns>
	static Gene* proportionate(const Population& pop);

	/// <summary>Selects a parent from the population <paramref name="pop"/> using the rank selection strategy.</summary>
	/// <param name="pop">The population to select an individual from.</param>
	/// <returns>A pointer to a gene in the population <paramref name="pop"/> that is the selected parent.</returns>
	static Gene* rank(const Population& pop);

	/// <summary>Selects a parent from the population <paramref name="pop"/> using the steady-state selection strategy.</summary>
	/// <param name="pop">The population to select an individual from.</param>
	/// <returns>A pointer to a gene in the population <paramref name="pop"/> that is the selected parent.</returns>
	static Gene* steadyState(const Population& pop);

	/// <summary>Determines the propability distribution for the given population by mapping the fitness values into the positive reals.</summary>
	/// <param name="pop">The population to map.</param>
	/// <returns>A pointer to a vector containing the probability distribution.</returns>
	/// <remarks>It is assumed that the population <paramref name="pop"/> is sorted, and all fitness values have already been calculated.</remarks>
	static vector<double>* findProbabilities(const Population& pop);

}; // end Class SelectionStrategy

#endif // !_SELECTION_STRAT_H
