//
//  uniform_discrete.h
//  random
//
//  Created by Bowen Li on 6/17/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef uniform_discrete_h
#define uniform_discrete_h

#include "random_generator.h"

double unifd(int min, int max);
void uniform_d(std::string file_name,int seed_num,double min,double max,int num_values);

double unifd(int min, int max)
{
  int    z;                     // Uniform random integer number
  int    unif_value;            // Computed uniform value to be returned

  // Pull a uniform random integer
  z = (int)gen_random::rand_vald(0);

  unif_value = z % (max - min + 1) + min;

  return(unif_value);
}


void uniform_d(std::string file_name,int seed_num,double min,double max,int num_values){
    
    std::ofstream fp;
    int      unif_rv;             // Uniformly random variable

    std::cout<<"-->Generate discrete uniform                  "<<std::endl;
    gen_random::open_file(fp, file_name);
    gen_random::rand_vald(seed_num);
    
    std::cout<<gen_random::sample_banner<<std::endl;


 
  // Generate and output interarrival times
    for (int i=0; i<num_values; i++){
        unif_rv = unifd(min, max);
        fp<<unif_rv;
        fp<<"\n";
    }

    
    std::cout<<gen_random::done_banner<<std::endl;
    fp.close();

}


#endif /* uniform_discrete_h */
