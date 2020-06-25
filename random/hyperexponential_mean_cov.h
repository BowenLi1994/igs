//
//  hyperexponential_mean_cov.h
//  random
//
//  Created by Bowen Li on 6/18/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef hyperexponential_mean_cov_h
#define hyperexponential_mean_cov_h

#include "random_generator.h"
using namespace gen_random;

double hyper(double x, double cov);

double hyper(double x, double cov)
{
  double p;                     // Probability value for Morse's method
  double z1, z2;                // Uniform random numbers from 0 to 1
  double hyp_value;             // Computed exponential value to be returned
  double temp;                  // Temporary double value

  // Pull a uniform random number (0 < z1 < 1)
  do
  {
    z1 = rand_valc(0);
  }
  while ((z1 == 0) || (z1 == 1));

  // Pull another uniform random number (0 < z2 < 1)
  do
  {
    z2 = rand_valc(0);
  }
  while ((z2 == 0) || (z2 == 1));

  // Compute hyperexponential random variable using Morse's method
  temp = cov*cov;
  p = 0.5 * (1.0 - sqrt((temp - 1.0) / (temp + 1.0)));
  if (z1 > p)
    temp = x / (1.0 - p);
  else
    temp = x / p;
  hyp_value = -0.5 * temp * log(z2);

  return(hyp_value);
}


void hyperexpon_mean_cov(std::string file_name,int seed_num,double lambda,double cov,double time_period)
{
    
    std::ofstream fp;                 // File pointer to output file
    double   hyp_rv;              // Hyperxponential random variable
    double   sum_time;            // Sum of time up to now

  // Output banner
    std::cout<<"-->Program to generate hyperexponentially distributed with interarrival times for a given CoV\n";
  // Prompt for output filename and then create/open the file
    open_file(fp, file_name);

  // Prompt for random number seed and then use it
    rand_valc(seed_num);


  //Output message and generate interarrival times
    std::cout<<sample_banner<<std::endl;

  // Generate and output interarrival times
  sum_time = 0.0;
    while(1){
        hyp_rv = hyper((1.0 / lambda), cov);
        fp<<hyp_rv;
        fp<<"\n";
        sum_time = sum_time + hyp_rv;
        if (sum_time >= time_period) break;
    }

  //Output message and close the output file
    std::cout<<done_banner<<std::endl;
    fp.close();

}
#endif /* hyperexponential_mean_cov_h */
