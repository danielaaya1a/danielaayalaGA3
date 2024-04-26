#ifndef POPULATION_H
#define POPULATION_H

#include "genome.h" // Include the Genome class

class Population {
private:
    genome* individuals; // Array of individuals in the population
    int nIndividuals; // Number of individuals in the population
    Pixel* targetGenome; // Target fitness image
    int imageSize; // Size of the image
    genome* p1; // Pointer to parent 1
    genome* p2; // Pointer to parent 2
    int nCrossover; // Number of crossover points
    double mutationRate; // Mutation rate

public:
    Population(); // Default constructor
    ~Population(); // Destructor

    void generate_population(int popSize, int nGenes); // Generate a population
    void set_target(Pixel* target, int imageSize); // Set the target fitness image
    void select_parents(); // Select the parents based on relative fitness
    void roulette_wheel_selection(genome* newIndividuals); // Perform roulette wheel selection

    // Utility methods
    genome crossover(genome* parent1, genome* parent2); // Perform crossover between two parents
    void set_nCrossover(int nCrossover); // Set the number of crossover points
    int get_nCrossover(); // Get the number of crossover points
    void set_mutation(double mRate); // Set the mutation rate
    void generate_new_population(int useRoulette, genome* newIndividuals, genome* parent1, genome* parent2); // Generate the next population
    double calculate_overall_fitness(); // Calculate the average fitness of the population
    void print_parents(); // Print the parents used to create the next generation
    void print_population(); // Print the population
};

#endif
