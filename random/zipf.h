//
//  zipf.h
//  random
//
//  Created by Bowen Li on 6/18/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef zipf_h
#define zipf_h

#include "random_generator.h"
#include <assert.h>
using namespace gen_random;

int zf(double alpha, int n);

int zf(double alpha, int n)
{
    
  static int first = 1;         // Static first time flag
  static double c = 0;          // Normalization constant
  double z;                     // Uniform random number (0 < z < 1)
  double sum_prob;              // Sum of probabilities
  double zipf_value=0;            // Computed exponential value to be returned                   // Loop counter

  // Compute normalization constant on first call only
  if (first == 1)
  {
    for (int i=1; i<=n; i++)
      c = c + (1.0 / pow((double) i, alpha));
    c = 1.0 / c;
    first = 0;
  }

  // Pull a uniform random number (0 < z < 1)
  do
  {
    z = rand_valc(0);
  }
  while ((z == 0) || (z == 1));

  // Map z to the value
  sum_prob = 0;
  for (int i=1; i<=n; i++)
  {
    sum_prob = sum_prob + c / pow((double) i, alpha);
    if (sum_prob >= z)
    {
      zipf_value = i;
      break;
    }
  }

  // Assert that zipf_value is between 1 and N
  assert((zipf_value >=1) && (zipf_value <= n));

  return(zipf_value);
}

void zipf(std::string file_name,int seed_num,double alpha,double n,int num_values)
{
    
    std::ofstream fp;                   // File pointer to output file
    int    zipf_rv;               // Zipf random variable


  // Output banner
    std::cout<<"-->Program to generate Zipf random variables\n";


  // Prompt for output filename and then create/open the file
    open_file(fp, file_name);

  // Prompt for random number seed and then use it
    rand_valc(seed_num);



  // Output "generating" message
    std::cout<<sample_banner<<std::endl;

  // Generate and output zipf random variables
  for (int i=0; i<num_values; i++){
      zipf_rv = zf(alpha, n);
      fp<<zipf_rv;
      fp<<"\n";
    
  }

  // Output "done" message and close the output file
    std::cout<<done_banner<<std::endl;
    fp.close();

}
#endif /* zipf_h */
