//
//  pareto.h
//  random
//
//  Created by Bowen Li on 6/18/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef pareto_h
#define pareto_h

#include "random_generator.h"
using namespace gen_random;

double par(double a, double k);

double par(double a, double k)
{
  double z;     // Uniform random number from 0 to 1
  double rv;    // RV to be returned

  // Pull a uniform RV (0 < z < 1)
  do
  {
    z = rand_valc(0);
  }
  while ((z == 0) || (z == 1));

  // Generate Pareto rv using the inversion method
  rv = k / pow(z, (1.0 / a));

  return(rv);
}

void pareto(std::string file_name,int seed_num, double alpha, double k,int num_values){
    
  
  std::ofstream fp;            // File pointer to output file
  double pareto_rv;           // Pareto random variable

    //Output banner
    std::cout<<"-->Program to generate Pareto random variables with lower bound value of k\n";


  // Prompt for output filename and then create/open the file
    open_file(fp, file_name);

  // Prompt for random number seed and then use it
    rand_valc(seed_num);


  //Output message and generate samples
  printf("-------------------------------------------------------- \n");
  printf("-  Generating samples to file                    \n");
  printf("-    * alpha = %f                                \n", alpha);
  printf("-    * k     = %f                                \n", k);
  printf("-------------------------------------------------------- \n");
    
  for (int i=0; i<num_values; i++)
  {
    pareto_rv = par(alpha, k);
    fp<<pareto_rv;
      fp<<"\n";
  }

  //Output message and close the outout file
    std::cout<<done_banner<<std::endl;
    fp.close();

}

#endif /* pareto_h */
