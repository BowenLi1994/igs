//
//  uniform _continuous.h
//  random
//
//  Created by Bowen Li on 6/17/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef uniform__continuous_h
#define uniform__continuous_h

#include "random_generator.h"

double unifc(double min, double max);
void uniform_c(std::string file_name,int seed_num,double min,double max,int num_values);

double unifc(double min, double max)
{
  double z;                     // Uniform random number (0 < z < 1)
  double unif_value;            // Computed uniform value to be returned

  // Pull a uniform random value (0 < z < 1)
  z = gen_random::rand_valc(0);

  // Compute uniform continuous random variable using inversion method
  unif_value = z * (max - min) + min;

  return(unif_value);
}

void uniform_c(std::string file_name,int seed_num,double min,double max,int num_values){
    
    std::ofstream fp;  // File pointer to output file
    double   unif_rv;             // Uniformly random variable

    std::cout<<"-->Generate continuous uniform                "<<std::endl;
    gen_random::open_file(fp, file_name);
    gen_random::rand_valc(seed_num);
    
    std::cout<<gen_random::sample_banner<<std::endl;


  // Generate and output interarrival times
    for (int i=0; i<num_values; i++){
        unif_rv = unifc(min, max);
        fp<<unif_rv;
        fp<<"\n";
    }
    
    std::cout<<gen_random::done_banner<<std::endl;
    fp.close();
    
}


#endif /* uniform__continuous_h */
