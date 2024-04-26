#include "genome.h"   // this is assuming that the file has the same name as the
                      // class.
#include <iostream>   // this is so that the << redirect operators and
                      // cout works
#include <cstdlib>   // for random
#include <cassert>

using namespace std;  // we use this so that we do not have to have
                      // "std:" before cout and endl
// constructor
genome::genome(){
    genes = NULL;	// initialie the genes pointer to NULL
    nGenes = 0;		// initialize number of genes to 0
}
//destructor
genome::~genome(){
    deallocate();
}
// void function to allocate memory for the gene aray for RGB values
void genome::allocate(int numGenes){
   if (genes != NULL){ 		// check if array is null
       deallocate();		// if not NULL deallocate
   }
   genes = new Pixel[numGenes];		//allocate memory
   nGenes = numGenes;			// set number of nGenes
   for (int i = 0; i < nGenes; i++) {
      genes[i].red = 0;		// set red val to 0
      genes[i].green = 0;	// set  green val to 0
      genes[i].blue = 0;	// set blue val to 0
   }
}
//Function to deallocate memory
void genome:: deallocate(){
   if (genes != NULL){		//check if gene is not NULL
       delete[] genes;		//dealocate memory
       genes = NULL;		// set gene to NULL
       nGenes = 0;		//set nGenes to 0
   }
}
// function to randomize RGB values for pixels
void genome::randomize(){
    srand(time(NULL));
    for(int i=0; i < nGenes; i++){
       genes[i].red = rand() % 255;	//set random red values between 0 and 255
       genes[i].green = rand() % 255;	//set random green values between 0 and 255
       genes[i].blue = rand() %255;	//set random blue values between 0 and 255
    }
}
// Functions are to set a value of pixel based on the index for red green and blue
void genome::set_red(int index, int value){
   if (index >= 0 && index < nGenes){
       genes [index].red = value;	//set red value
   }
}
void genome::set_green(int index, int value){
   if (index >= 0 && index < nGenes){
       genes[index].green = value;	//set green value
   }
}
void genome::set_blue(int index, int value){
   if (index >= 0 && index < nGenes){
       genes[index].blue = value;	// set blue value
   }
}
// Function to get the a value of a given pixel for a certain value red, green and blue
int genome::get_red(int index){
    if (index >= 0 && index < nGenes){	//check  if index is a valid input
        return genes[index].red;	//returnt the red value
    }
    else{
        return -1;			// return -1 for invalid index (input)
    }
}
//reference the past comments for these next two functions
int genome::get_green(int index){
    if(index >= 0 && index < nGenes){
       return genes[index].green;
    }
    else {
       return -1;
   }
}
int genome::get_blue(int index){
    if(index >= 0 && index < nGenes){
       return genes[index].blue;
    }
    else{
       return -1;
    }
}
// Print Function to print the genes array with RGB values
void genome::print() {
    for(int i=0; i < nGenes; i++){
        cout << "Pixel:"<< i << " Red = " << genes[i].red << " Green = " << genes[i].green << " Blue = "<< genes[i].blue <<  endl;
    }
}
// Testing sets for genome.cpp
#ifdef UNIT_TEST_ENABLED
//ruining unit test
void genome::run_unit_tests() {	//testing all functions described in the  run_unit_test
    test_allocate_deallocate();
    test_randomize();
    test_set_get();
    test_print();
}
// function to test allocate and deallocate
void genome::test_allocate_deallocate() {
    genome g;				// set genome to g
    g.allocate(10);			// allocate memory to 10
    assert(g.get_num_genes() == 10);	// checking if num of gene is 10
    g.deallocate();			// deallocate memory
    assert(g.get_genes() == NULL);	//Check if the array is empty
    assert(g.get_num_genes() == 0);	//check if gene is 0 after deallocating
    cout << "allocate_deallocate functions test passed" << endl;	//print the message if it passes
}
// function to test the randomized function
void genome::test_randomize() {
    genome g;
    g.allocate(10);
    g.randomize();		// randomize RGB val
    bool allZero = true;	// checl of RGB values are 0
    for (int i = 0; i < 10; i++) {
        if (g.get_red(i) != 0 || g.get_green(i) != 0 || g.get_blue(i) != 0) {
            allZero = false;
            break;
        }
    }
    assert(!allZero);
    cout << "randomize function test passed"<< endl;	//print passed message
}
// function to test set and get functions
void genome::test_set_get() {
    genome g;
    g.allocate(3);		//allocate memory for 3 different genes
    g.set_red(0, 50);		// set red value of genes index from 0 to 50
    g.set_green(1,100);		//set green values of genes index from 2 to 100
    g.set_blue(2, 150);	// set blue values of gene index from 2 to 150
    assert(g.get_red(0) == 50);		//check of the red value is in the correct index
    assert(g.get_green(1) == 100);	//check if the green value is in the correct index
    assert(g.get_blue(2) == 150);	//check if the blue value is in the correct index
    cout << "set_getter functions test passed "<< endl;	//print messages if passed correctly
}
//function to test the print function
void genome::test_print() {
    genome g;
    g.allocate(2);
    g.set_red(0,100);  //set values
    g.set_green(1, 150); //set values
    cout << "Expected outpt for testing set:" << endl;	//print the expected output message
    cout << "Pixel 0: Red=100 Green=0 Blue=0"<< endl; // print the expected RGB values for pixel 0
    cout << "Pixel 1: Red=0 Green=150 Blue=150" << endl; //print the expected RGB values for pixel 1
    cout << "Actual output:" << endl;
    g.print();	//print
    cout << "print function test passed" << endl; //print  message if  passed
}
#endif // UNIT_TESTS_ENABLED
void genome::set_mRate(double val) {
	if (val > 0 && val < 1) {
		mRate = val;     // mRate = val if 0<val<1
	}
}
double genome::get_mRate() {
	return mRate;
}
void genome::mutate_gene(int index) {
	srand(time(nullptr));
	float ran_val = rand() % 1;
	if (ran_val < mRate) {
		genes[index].red = rand() % 256;
	}
	if (ran_val < mRate) {
		genes[index].green = rand() % 256;
	}
	if (ran_val < mRate) {
		genes[index].blue = rand() % 256;
	}
}
void genome::mutate() {
	for (int i = 0; i < nGenes; i++) {
		mutate_gene(i);
	}
}
double genome::calculate_gene_fitness(int index, Pixel targetPixel) {
	double red_diff = abs(targetPixel.red - genes[index].red) / 256.0;
	double green_diff = abs(targetPixel.green - genes[index].green) / 256.0;
	double blue_diff = abs(targetPixel.blue - genes[index].blue) / 256.0;
	double total_avg_diff = (red_diff + green_diff + blue_diff) / 3.0;
	return total_avg_diff;
}
double genome::calculate_overall_fitness(Pixel* target, int nPixels) {
    if (nPixels == nGenes) {
        double total_error = 0.0;
        for (int i = 0; i < nPixels; i++) {
            double red_error = abs(target[i].red - genes[i].red);
            double blue_error = abs(target[i].blue - genes[i].blue);
            double green_error = abs(target[i].green - genes[i].green);
            total_error += red_error + blue_error + green_error;
        }
        double avg_error = total_error / (3.0 * nPixels);
        return avg_error;
    }
    // Default return value if the condition is not met
    return -1.0; // You can change this to a meaningful default value
}
void genome::set_pixel(int index, Pixel newPixel) {
	if (index >= 0 && index < nGenes) {
		if (newPixel.red >= 0 && newPixel.red <= 255) {
			genes[index].red = newPixel.red;
		}
		if (newPixel.green >= 0 && newPixel.green <= 255) {
			genes[index].green = newPixel.green;
		}
		if (newPixel.blue >= 0 && newPixel.blue <= 255) {
			genes[index].blue = newPixel.blue;
		}
	}
}
Pixel genome::get_pixel(int index) {
	return genes[index];
}
void testsetMRate(){
	genome g;
        g.set_mRate(0.5);
        assert(g.get_mRate() == 0.5); // Check if mRate is correctly set

        g.set_mRate(-0.1);
        assert(g.get_mRate() == 0.5); // mRate should not change as -0.1 is invalid

        g.set_mRate(1.5);
        assert(g.get_mRate() == 0.5); // mRate should not change as 1.5 is invalid

        std::cout << "testSetMRate passed." << std::endl;
}
void testMutateGene() {
        genome g;
        g.set_mRate(1); // Ensure mutation happens
        Pixel original = g.get_pixel(0); // Assume get_pixel() gives you the original state
        g.mutate_gene(0);
        Pixel mutated = g.get_pixel(0);
        assert(original.red != mutated.red || original.green != mutated.green || original.blue != mutated.blue); // At least one color should change


        std::cout << "testMutateGene passed." << std::endl;
}
void testCalculateGeneFitness() {
        genome g;
        Pixel target = {255, 0, 0}; // Target pixel
        g.set_pixel(0, {0, 0, 0}); // Set gene pixel to a known value
        double fitness = g.calculate_gene_fitness(0, target);
        assert(fitness == 1.0); // Fitness should be 1.0 as the colors are completely off

        std::cout << "testCalculateGeneFitness passed." << std::endl;
}
void testSetAndGetPixel() {
        genome g;
        Pixel p = {123, 45, 67};
        g.set_pixel(0, p); // Assume valid index 0
        Pixel retrieved = g.get_pixel(0);
        assert(p.red == retrieved.red && p.green == retrieved.green && p.blue == retrieved.blue);

        std::cout << "testSetAndGetPixel passed." << std::endl;
}
