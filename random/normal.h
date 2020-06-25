//
//  normal.h
//  random
//
//  Created by Bowen Li on 6/17/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef normal_h
#define normal_h

#include "random_generator.h"

using namespace gen_random;

double norm(double mean, double std_dev);
void normal(std::string file_name,int seed_num,double mean,double std_dev,int num_values);


double norm(double mean, double std_dev){
  double   u, r, theta;           // Variables for Box-Muller method
  double   x;                     // Normal(0, 1) rv
  double   norm_rv;               // The adjusted normal rv

  // Generate u
  u = 0.0;
  while (u == 0.0)
    u = rand_valc(0);

  // Compute r
  r = sqrt(-2.0 * log(u));

  // Generate theta
  theta = 0.0;
  while (theta == 0.0)
    theta = 2.0 * PI * rand_valc(0);

  // Generate x value
  x = r * cos(theta);

  // Adjust x value for specified mean and variance
  norm_rv = (x * std_dev) + mean;

  // Return the normally distributed RV value
  return(norm_rv);
}

void normal(std::string file_name,int seed_num,double mean,double std_dev,int num_values){

    std::ofstream fp;
    double   norm_rv;               // The adjusted normal rv

  // Output banner
    printf("-->Program to generate normally distributed random\n");


  // Prompt for output filename and then create/open the file
    open_file(fp, file_name);

  // Prompt for random number seed and then use it
    rand_valc(seed_num);

    std::cout<<sample_banner<<std::endl;
    for (int i=0; i<num_values; i++){
        // Generate a normally distributed rv
        norm_rv = norm(mean, std_dev);

        // Output the norm_rv value
       fp<<norm_rv;
       fp<<"\n";
    }

    // Output message and close the distribution and output files
    std::cout<<done_banner<<std::endl;
    fp.close();
}

#endif /* normal_h */
