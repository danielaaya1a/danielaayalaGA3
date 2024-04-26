struct Pixel {
	int red;
	int green;
	int blue;
};
class genome {
public:
	genome();  // default constructor
	~genome();  // destructor
	void allocate(int numGenes);  // allocate space for the Pixels
	void deallocate();  // free up the space
	void randomize();  // set random values between 0 and 256
	// set new RGB values
	void set_red(int index, int value);
	void set_green(int index, int value);
	void set_blue(int index, int valuue);
	// get new RGB values
	int get_red(int index);
	int get_green(int index);
	int get_blue(int index);
	// print function
	void print();
	void set_mRate(double val);            // Set the mutation rate (0 <= val <= 1)
        double get_mRate();                    // Get the current mutation rate
        void mutate_gene(int index);           // Mutate the Pixel at index if conditions are met
        void mutate();                         // Mutate all Pixels in the genome
	double calculate_gene_fitness(int index, Pixel targetPixel);//Calculate fitness of Pixel at index
	double calculate_overall_fitness(Pixel*target, int nPixels); //Calculate overall fitness of genome
	void set_pixel(int index, Pixel newPixel); // Set the Pixel at index
	Pixel get_pixel(int index);  // Get the Pixel at index
        void testsetMRate();
        void testMutateGene();
        void testCalculateGeneFitness();
        void testSetAndGetPixel();
private:
	Pixel* genes; //Pointer to the array of Pixelso
	int nGenes; // Number of Pixels in the array
	double mRate; // Mutation rate (0 <= mRate <= 1)
};
