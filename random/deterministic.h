//
//  deterministic.h
//  random
//
//  Created by Bowen Li on 6/17/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef deterministic_h
#define deterministic_h

#include "random_generator.h"

void deterministic(std::string file_name,double lambda,double time_period);

void deterministic(std::string file_name,double lambda,double time_period)
{
    
    std::ofstream fp;

    double   det_rv;              // Deterministic random variable
    double   sum_time;            // Sum of time up to now
    
    std::cout<<"-->Generate deterministically distributed     "<<std::endl;
    std::cout<<gen_random::sample_banner<<std::endl;
    gen_random::open_file(fp, file_name);


  // Generate and output interarrival times
    sum_time = 0.0;
    while(1){
        det_rv = 1.0 / lambda;
        fp<<det_rv;
        fp<<"\n";
        sum_time = sum_time + det_rv;
        if (sum_time >= time_period) break;
    }

  //Output message and close the output file
    std::cout<<gen_random::done_banner<<std::endl;
    fp.close();
}




#endif /* deterministic_h */
