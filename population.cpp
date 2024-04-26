#include "population.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Population::Population() {
    individuals = nullptr; // Initialize individuals to nullptr
    nIndividuals = 0; // Initialize number of individuals to 0
    nCrossover = 1; // Set default number of crossover points to 1
    mutationRate = 0.0; // Initialize mutation rate to 0.0
}

Population::~Population() {
    if (individuals != nullptr) { // Check if individuals array is not nullptr
        delete[] individuals; // Delete the individuals array
        individuals = nullptr; // Set individuals to nullptr
    }
    nIndividuals = 0; // Reset number of individuals to 0
}

void Population::generate_population(int popSize, int nGenes) {
    // Allocate memory for individuals array
    individuals = new genome[popSize];
    nIndividuals = popSize; // Set the number of individuals

    // Initialize each genome in the population
    for (int i = 0; i < popSize; ++i) {
        individuals[i].allocate(nGenes); // Allocate memory for genome
        individuals[i].randomize(); // Randomize the genome
    }
}

void Population::set_target(Pixel* target, int imageSize) {
    targetGenome = target; // Set the target fitness image
    this->imageSize = imageSize; // Set the size of the image
}

void Population::select_parents() {
    // Initialize the best two individuals to the first two individuals in the population
    p1 = &individuals[0];
    p2 = &individuals[1];

    // Iterate through the rest of the individuals to find the best two
    for (int i = 2; i < nIndividuals; ++i) {
        if (individuals[i].calculate_overall_fitness(targetGenome, imageSize) > p1->calculate_overall_fitness(targetGenome, imageSize)) {
            p2 = p1; // Move the current p1 to p2
            p1 = &individuals[i]; // Set the new p1
        } else if (individuals[i].calculate_overall_fitness(targetGenome, imageSize) > p2->calculate_overall_fitness(targetGenome, imageSize)) {
            p2 = &individuals[i]; // Set the new p2
        }
    }
}

void Population::set_nCrossover(int n) {
    // Set the number of crossover points to a positive integer
    if (n > 0) {
        nCrossover = n;
    } else {
        nCrossover = 1; // Set to 1 if n is not positive
    }
}

int Population::get_nCrossover() {
    return nCrossover; // Return the number of crossover points
}

void Population::set_mutation(double mRate) {
    // Set the mutation rate
    if (mRate >= 0 && mRate <= 1) {
        mutationRate = mRate;
    } else {
        mutationRate = 0.0; // Set to 0.0 if mRate is not within the valid range
    }
}

void Population::generate_new_population(int useRoulette,genome* newIndividuals,genome* parent1, genome* parent2) {
    // Create a temporary array to hold the new population
    genome* newIndividuals = new genome[nIndividuals];
    // Roulette wheel selection
    if (useRoulette == 1) {
        roulette_wheel_selection(newIndividuals);
    } else {
        // Simple top two selection
        select_parents();

        // Perform crossover and mutation on the selected parents
        for (int i = 0; i < nIndividuals; ++i) {
            // Select parents for crossover
            genome child = crossover(p1,p2); // Perform crossover between parents
            newIndividuals[i] = child; // Add child to the new population
        }
    }

    // Replace the old population with the new one
    delete[] individuals; // Delete the old population
    individuals = newIndividuals; // Assign the new population
}

double Population::calculate_overall_fitness() {
    double totalFitness = 0.0;

    // Calculate the fitness of each individual and sum them up
    for (int i = 0; i < nIndividuals; ++i) {
        totalFitness += individuals[i].calculate_overall_fitness(targetGenome, imageSize); // Calculate individual fitness
    }

    // Return the average fitness
    return totalFitness / nIndividuals;
}

void Population::print_parents() {
    if (p1 == nullptr || p2 == nullptr) {
        cout << "No parents yet set." << endl;
    } else {
        cout << "Parent 1:" << endl;
        p1->print(); // Print parent 1
        cout << "Parent 2:" << endl;
        p2->print(); // Print parent 2
    }
}

void Population::print_population() {
    cout << "Number of crossover points: " << nCrossover << endl;
    cout << "Mutation rate: " << mutationRate << endl;
    cout << "Population:" << endl;
    for (int i = 0; i < nIndividuals; ++i) {
        cout << "Individual " << i+1 << ":" << endl;
        individuals[i].print(); // Print each individual in the population
        cout << endl;
    }
}
