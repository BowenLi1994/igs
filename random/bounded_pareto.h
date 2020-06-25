//
//  bounded_pareto.h
//  random
//
//  Created by Bowen Li on 6/18/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef bounded_pareto_h
#define bounded_pareto_h

#include "random_generator.h"
using namespace gen_random;

double bpareto(double a, double k, double p);

double bpareto(double a, double k, double p)
{
  double z;     // Uniform random number from 0 to 1
  double rv;    // RV to be returned

  // Pull a uniform RV (0 < z < 1)
  do
  {
    z = rand_valc(0);
  }
  while ((z == 0) || (z == 1));

  // Generate the bounded Pareto rv using the inversion method
  rv = pow((pow(k, a) / (z*pow((k/p), a) - z + 1)), (1.0/a));

  return(rv);
}

void bounded_pareto(std::string file_name,int seed_num,double alpha,double k, double p,int num_values){
               
    std::ofstream fp;
    double pareto_rv;           // Pareto random variable


    std::cout<<"-->Program to generate bounded Pareto random variables with lower bound value of k and upper bound of p\n";
    open_file(fp, file_name);
    
  // Prompt for random number seed and then use it
    rand_valc(seed_num);

;

  //Output message and generate samples
  printf("-------------------------------------------------------- \n");
  printf("-  Generating samples to file                    \n");
  printf("-    * alpha = %f                                \n", alpha);
  printf("-    * k     = %f                                \n", k);
  printf("-    * p     = %f                                \n", p);
  printf("-------------------------------------------------------- \n");
    
  for (int i=0; i<num_values; i++){
    pareto_rv = bpareto(alpha, k, p);
    fp<<pareto_rv;
      fp<<"\n";
  }

  //Output message and close the outout file
  std::cout<<done_banner<<std::endl;
  fp.close();
}

#endif /* bounded_pareto_h */
