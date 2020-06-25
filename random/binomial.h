//
//  binomial.h
//  random
//
//  Created by Bowen Li on 6/18/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef binomial_h
#define binomial_h

#include "random_generator.h"
using namespace gen_random;

int bin(double p, int n);

int bin(double p, int n)
{
  int    bin_value;             // Computed Poisson value to be returned
  int    i;                     // Loop counter

  // Generate a binomial random variate
  bin_value = 0;
  for (i=0; i<n; i++)
    if (rand_valc(0) < p) bin_value++;

  return(bin_value);
}

void binomial(std::string file_name,int seed_num,int num_trials,double probability,int num_values)
{
 
    std::ofstream fp;
    int      bin_rv;              // Binomial random variable

    // Output banner
    std::cout<<"-->Program to generate Poisson random variables\n";

    // Prompt for output filename and then create/open the file
    open_file(fp, file_name);


  // Prompt for random number seed and then use it
    rand_valc(seed_num);

    std::cout<<sample_banner<<std::endl;



  // Generate and output binomial random variables
  for (int i=0; i<num_values; i++)
  {
    bin_rv = bin(probability, num_trials);
    fp<<bin_rv;
    fp<<"\n";
  }

  //Output message and close the output file
    std::cout<<done_banner<<std::endl;
    fp.close();
}

#endif /* binomial_h */
