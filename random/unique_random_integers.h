//
//  unique_random_integers.h
//  random
//
//  Created by Bowen Li on 6/18/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef unique_random_integers_h
#define unique_random_integers_h


#include "random_generator.h"
using namespace gen_random;

int randInt(int seed);         // LCG RNG with x_n = 7^5*x_(n-1)mod(2^31 - 1)
int Generator31(void);


int randInt(int seed)
{
  const long  a =      16807;  // Multiplier
  const long  m = 2147483647;  // Modulus
  const long  q =     127773;  // m div a
  const long  r =       2836;  // m mod a
  static long x;               // Random int value (seed is set to 1)
  long        x_div_q;         // x divided by q
  long        x_mod_q;         // x modulo q
  long        x_new;           // New x value

  // Seed the RNG
  if (seed > 0) x = seed;

  // RNG using integer arithmetic
  x_div_q = x / q;
  x_mod_q = x % q;
  x_new = (a * x_mod_q) - (r * x_div_q);
  if (x_new > 0)
    x = x_new;
  else
    x = x_new + m;

  // Return a random integer value
  return (int)x;
}

int Generator31(void)
{
  static int n = 1;            // Start with n = 1

  // Generate the unique random value
  n = n >> 1 | ((n^n >> 3) & 1) << 30;

  // Return the unique random value
  return n;
}


void unique_random_integers(std::string file_name,int seed_num,int num_values){
    
  std::ofstream   fp;                  // File pointer to output file
                // Number of values to generate
  int    *z;                   // Array of shuffled unique integers
  int     temp;                // Temporary value
  int     i, j;                // Indexes

  // Output banner

  std::cout<<"-->Program to generate unique random integers\n";


  // Prompt for output filename and then create/open the file
    open_file(fp, file_name);

  // Prompt for random number seed and then use it
  randInt(seed_num);



  // Malloc space for an array of num integers
  z = (int *) malloc(num_values * sizeof(int));
  if (z == NULL)
  {
    printf("*** ERROR - could not malloc space for array \n");
    exit(1);
  }

  // Create an array of num unique integers
  for (i=0; i<num_values; i++)
    z[i] = Generator31();

  // Shuffle the array of unique integers
  for (i=0; i<num_values; i++)
  {
    j = randInt(0) % num_values;
    temp = z[i];
    z[i] = z[j];
    z[j] = temp;
  }

  // Output message and generate values
    std::cout<<sample_banner<<std::endl;


  // Output the values to the file
  for (i=0; i<num_values; i++){
      fp<<z[i];
      fp<<"\n";
  }
   

  // Output message and close the output file
    std::cout<<done_banner<<std::endl;
    fp.close();
}
#endif /* unique_random_integers_h */
