//
//  个\eometric.h
//  random
//
//  Created by Bowen Li on 6/17/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef __eometric_h
#define __eometric_h

#include "random_generator.h"

using namespace gen_random;

int geo(double p);

int geo(double p)
{
  double z;                     // Uniform random number (0 < z < 1)
  double geo_value;             // Computed geometric value to be returned

  // Pull a uniform random number (0 < z < 1)
  do
  {
    z = rand_valc(0);
  }
  while ((z == 0) || (z == 1));

  // Compute geometric random variable using inversion method
  geo_value = (int) (log(z) / log(1.0 - p)) + 1;

  return(geo_value);
}

void geometric(std::string file_name,int seed_num,double p,int num_values)
{
    std::ofstream fp;
    int    geo_rv;              // Geometric random variable

  
    // Output banner
    std::cout<<"-->Program to generate geometric random variables\n";
    open_file(fp, file_name);
    
    rand_valc(seed_num);

  // Output message and generate interarrival times

    std::cout<<sample_banner<<std::endl;

  // Generate and output geometric random variables
    for (int i=0; i<num_values; i++){
        geo_rv = geo(p);
        fp<<geo_rv;
        fp<<"\n";
    }
    
    std::cout<<done_banner<<std::endl;
    fp.close();
}



#endif /* __eometric_h */
