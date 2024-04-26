#include "genome.h"
int main (){
  genome myGenome; // this line will declare a variable called MyGenome that is of type
		  // genome the default constructor will be called.
  myGenome.print(); //this function will output nothing because genome is null
  myGenome.allocate(4); //this line will allocate an array of 4 pixels in myGenome, all the GRB
			// values will be zeroed.
  myGenome.print(); // this function would output to the console
  myGenome.randomize(); // this line will assign random values to the pizels in myGenome
  myGenome.print(); //this function would output to the console genes with random values.
  myGenome.set_blue(0,226); //this line will assign 226 to the blue value of pixe;s in myGenom @ pos 0
  myGenome.print(); // this function would output to the console the RGB values
		   // and assuming you decide to output the value in RGB it would be.
  return 0;
}
