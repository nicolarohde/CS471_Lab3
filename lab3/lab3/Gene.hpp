#pragma once

#ifndef _GENE_H
#define _GENE_H

#include <vector>
#include <iostream>       // ostream
#include <functional>     // function
#include "utility.hpp"    // RNG
#include "Containers.hpp" // Offspring, Mutation_Info, Bounds

/// <summary>Typedef to make fitness function type a bit more readable.</summary>
typedef std::function<double(const std::vector<double>*)> fitnessFunction;

///<summary>Stores the genetic information of one member of the population.</summary>
class Gene
{
public:
	// Public Methods:
	// Constructors:
	/// <summary>Constructs a new randomly generated gene.</summary>
	/// <param name="ui_SIZE">The length of the gene.</param>
	/// <param name="BOUNDS">The min/max value that may be stored in the gene.</param>
	Gene(const std::size_t ui_SIZE, const Bounds BOUNDS);

	/// <summary>Constructs a new gene that is a copy of the gene <paramref name="other"/>.</summary>
	/// <param name="other">The gene to copy.</param>
	Gene(const Gene& other);

	// Destructor:
	/// <summary>Releases all dynamic memory owned by this object.</summary>
	~Gene(void) {}

	// Operations:
	/// <summary>Creates a random mutation in this gene.</summary>
	/// <param name="MUT_INFO">Structure containing the chance, range, and precision of a mutation.</param>
	void mutate(const Mutation_Info MUT_INFO);

	// Getters:
	/// <summary>Getter for the length of the gene.</summary>
	/// <returns>The length of this gene.</returns>
	inline std::size_t length(void) const;

	/// <summary>Getter for the fitness of the gene.</summary>
	/// <returns>The fitness of this gene.</returns>
	inline double fitness(void) const;
	
	// Setters:
	///<summary>Determines the fitness of this gene for the fitness function <paramref name="f"/> and stores it in <see cref="d_fitness"/>.</summary>
	///<param name="f">The fitness function.</param>
	inline void evaluate(fitnessFunction f);

	// Operators:
	/// <summary>Accessor for the component at index <paramref name="i"/>.</summary>
	/// <param name="i">The 0-based index to access.</param>
	/// <returns>A reference to the component located at index i.</returns>
	/// <exception name="std::out_of_range">Thrown if <paramref name="i"/> is larger than the length of the gene.</exception>
	double& operator[](const size_t i);

	/// <summary>Accessor for the component at index <paramref name="i"/>.</summary>
	/// <param name="i">The 0-based index to access.</param>
	/// <returns>The value of the component located at index i.</returns>
	/// <exception name="std::out_of_range">Thrown if <paramref name="i"/> is larger than the length of the gene.</exception>
	double operator[](const size_t i) const;

	/// <summary>Compares the fitness of this gene to the fitness of <paramref name="other"/>.</summary>
	/// <param name="other">The gene to compare this gene to.</param>
	/// <returns>True iff the fitness of this gene is greater than that of the gene <paramref name="other"/>, otherwise false.</returns>
	/// <remarks>This operator establishes a natural ordering for <see cref="std::sort"/>.</remarks>
	inline bool operator>(const Gene& other);

	// Friend declarations:
	/// <summary>Inserts the contents of <paramref name="gene"/> into the <paramref name="stream"/>.</summary>
	/// <param name="stream">The stream to insert this gene into.</param>
	/// <param name="geme">The gene to be inserted.</param>
	/// <returns>The stream with the contents of <paramref name="gene"/> added to the end.</returns>
	friend std::ostream& operator<<(std::ostream& stream, const Gene& gene);

	/// <summary>Determines if crossing over will occur based on the CO rate in <paramref name="CO_INFO"/>, if not, the parents are returned, otherwise, the following process wil occur:
	///			 Splits the genes of <paramref name="PARENT_A"/> and <paramref name="PARENT_B"/> in the specified number of spots, and then recombines the pieces to generate a specified 
	///			 number of offsprings.
	/// </summary>
	/// <param name="PARENT_A">The first parent.</param>
	/// <param name="PARENT_B">The second parent.</param>
	/// <param name="CO_INFO">Structure containing # of cuts to make, chance of crossing over occurring, and number of offspring to create.</param>
	/// <returns>An Offspring object containing the specified number of offspring genes.</returns>
	friend Offspring* crossingOver(const Gene& PARENT_A, const Gene& PARENT_B, const Crossing_Over_Info& CO_INFO);

private:
	// Private Data Members:
	/// <summary>Min/max value that a component of the gene can have.</summary>
	Bounds bounds;

	/// <summary>Container for the gene.</summary>
	std::vector<double> gene;

	/// <summary>Length of the gene.</summary>
	std::size_t	ui_length;

	/// <summary>The solution to the cost function being optimized with this gene as input.</summary>
	double d_fitness;

	// Private Methods:
	// Constructor:
	/// <summary>Crossing-over Constructor.</summary>
	/// <param name="PARENT_A">The first parent.</param>
	/// <param name="PARENT_B">The second parent.</param>
	/// <param name="ui_CO_POINTS">The number of pieces to cut the parents' genes into.</param>
	Gene(const Gene& PARENT_A, const Gene& PARENT_B, std::size_t ui_CO_POINTS);

	/// <summary>Recombines the Genes of <paramref name="PARENT_A"/> and <paramref name="PARENT_B"/> to create a new gene.</summary>
	/// <param name="PARENT_A">The first parent.</param>
	/// <param name="PARENT_B">The second parent.</param>
	/// <param name="indeces">The indeces at which recombination can occur.</param>
	void recombine(const Gene & PARENT_A, const Gene & PARENT_B, const std::vector<size_t>* indeces);


}; // end Class Gene


#endif // !_GENE_H