//
//  hyperexponential_lambdas_p1.h
//  random
//
//  Created by Bowen Li on 6/18/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef hyperexponential_lambdas_p1_h
#define hyperexponential_lambdas_p1_h

#include "random_generator.h"
using namespace gen_random;


void hyperexpon_p1_lambda(std::string file_name,int seed_num,double lambda1,double lambda2,double probability,double time_period){
    
  std::ofstream fp;              // File pointer to output file
 
  double   hyp_rv;              // Hyperxponential random variable
  double   sum_time;            // Sum of time up to now

  // Output banner
    std::cout<<"-->Program to generate hyperexponentially distributed\n";

  // Prompt for output filename and then create/open the file
    open_file(fp, file_name);
  // Prompt for random number seed and then use it
    rand_valc(seed_num);
    
    std::cout<<sample_banner<<std::endl;
    
  // Generate and output interarrival times
  sum_time = 0.0;
    
    while(1){
        if (rand_valc(0) <= probability)
            hyp_rv = expon(1.0 / lambda1);
        else
            hyp_rv = expon(1.0 / lambda2);
      
        fp<<hyp_rv;
        fp<<"\n";
        
        sum_time = sum_time + hyp_rv;
        if (sum_time >= time_period) break;
    }

    std::cout<<done_banner<<std::endl;
    fp.close();
}

#endif /* hyperexponential_lambdas_p1_h */
