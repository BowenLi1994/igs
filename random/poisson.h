//
//  poisson.h
//  random
//
//  Created by Bowen Li on 6/17/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef poisson_h
#define poisson_h

#include "random_generator.h"
using namespace gen_random;

int    poisson(double x);

int poisson(double x)
{
  int    poi_value;             // Computed Poisson value to be returned
  double t_sum;                 // Time sum value

  // Loop to generate Poisson values using exponential distribution
  poi_value = 0;
  t_sum = 0.0;
  while(1)
  {
    t_sum = t_sum + expon(x);
    if (t_sum >= 1.0) break;
    poi_value++;
  }

  return(poi_value);
}

void poisson(std::string file_name,int seed_num,double lambda,int num_values)
{
  std::ofstream fp;                 // File pointer to output file
  int      pois_rv;             // Poisson random variable

  // Output banner

    std::cout<<"-->Program to generate Poisson random variables\n";
    open_file(fp, file_name);


  // Prompt for output filename and then create/open the file

    rand_valc(seed_num);
    
    std::cout<<sample_banner<<std::endl;



  // Generate and output exponential random variables
  for (int i=0; i<num_values; i++){
    pois_rv = poisson(1.0 / lambda);
    fp<<pois_rv;
    fp<<"\n";
  }

  //Output message and close the output file
  printf("-------------------------------------------------------- \n");
  printf("-  Done! \n");
  printf("-------------------------------------------------------- \n");
  std::cout<<done_banner<<std::endl;
  fp.close();
}


#endif /* poisson_h */
