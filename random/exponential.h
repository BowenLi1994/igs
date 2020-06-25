//
//  exponential.h
//  random
//
//  Created by Bowen Li on 6/17/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef exponential_h
#define exponential_h

#include "random_generator.h"

using namespace gen_random;


double expon(double x);



double expon(double x){
  double z;                     // Uniform random number (0 < z < 1)
  double exp_value;             // Computed exponential value to be returned

  // Pull a uniform random number (0 < z < 1)
  do{
    z = rand_valc(0);
  }while ((z == 0) || (z == 1));

  // Compute exponential random variable using inversion method
  exp_value = -x * log(z);

  return(exp_value);
}


void expontial(std::string file_name,int seed_num,double lambda,int num_values){

  
    std::ofstream fp;
    double exp_rv;              // Exponential random variable

    open_file(fp, file_name);

    std::cout<<"-->Program to generate exponential random variables"<<std::endl;

    rand_valc(seed_num);

    std::cout<<sample_banner<<std::endl;

  // Generate and output exponential random variables
    for (int i=0; i<num_values; i++){
        exp_rv = expon(1.0 / lambda);
        fp<<exp_rv;
        fp<<"\n";
    }

  // Output message and close the output file

    std::cout<<done_banner<<std::endl;
    fp.close();
}


#endif /* exponential_h */
