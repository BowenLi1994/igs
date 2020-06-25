//
//  interrupted_poisson_process.h
//  random
//
//  Created by Bowen Li on 6/18/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef interrupted_poisson_process_h
#define interrupted_poisson_process_h

#include "random_generator.h"
using namespace gen_random;

void interrupted_poisson_process(std::string file_name,int seed_num,double lambda,double alpha,double beta,double time_period){
    
    
  std::ofstream fp;
    // File pointer to output file
  double   ipp_rv;              // IPP random variable
  double   temp, temp1;         // Variables needed for IPP to H2 conversion
  double   lambda1, lambda2;    // Variables needed for IPP to H2 conversion
  double   pi1;                 // Variable needed for IPP to H2 conversion
  double   sum_time;            // Sum of time upto now

  //Output banner
    std::cout<<"-->Program to generate IPP interarrival times\n";


  // Prompt for output filename and then create/open the file
    open_file(fp, file_name);

  // Prompt for random number seed and then use it
 
    rand_valc(seed_num);





  // Conversion from IPP to H2
  temp = (lambda + alpha + beta);
  temp1 = (4.0 * lambda * beta);
  lambda1 = 0.5*(temp + sqrt(temp*temp - temp1));
  lambda2 = 0.5*(temp - sqrt(temp*temp - temp1));
  pi1 = (lambda - lambda2)/(lambda1 - lambda2);

  //Output message and generate samples
  printf("-------------------------------------------------------- \n");
  printf("-  Generating samples for %f seconds...   \n", time_period);
  printf("-    * lambda = %f customers per second   \n", lambda);
  printf("-    * alpha  = %f transitions per second \n", alpha);
  printf("-    * beta   = %f transations per second \n", beta);
  printf("-------------------------------------------------------- \n");
    
  sum_time = 0.0;
  while(1){
    if (rand_valc(0) < pi1)
      ipp_rv = expon(1.0 / lambda1);
    else
      ipp_rv = expon(1.0 / lambda2);

      fp<<ipp_rv;
      fp<<"\n";
      
      sum_time = sum_time + ipp_rv;
      if (sum_time >= time_period) break;
  }

  //Output message and close the outout file
    std::cout<<done_banner<<std::endl;
    fp.close();
}

#endif /* interrupted_poisson_process_h */
