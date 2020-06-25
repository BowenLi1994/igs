//
//  peaked.h
//  random
//
//  Created by Bowen Li on 6/17/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef peaked_h
#define peaked_h

#include "random_generator.h"

int peak(int N, int K);
void peaked(std::string file_name,int num_seeds,int N,int K,int num_values);


int peak(int N, int K){
  double z;                     // Uniform random number (0 < z < 1)
  int    peak_value=0;            // Computed peaked value to be returned

  // Pull a uniform random value (0 < z < 1)
  z = gen_random::rand_valc(0);

  // Generate peak RV -- similar approach to an empirical distribution
  if (z < ((double) K / (N + K - 1)))
    peak_value = 1;
  else
  {
    for (int i=1; i<N; i++)
      if (z < ((double) (K + i) / (N + K - 1)))
      {
        peak_value = i + 1;
        break;
      }
  }

  return(peak_value);
}

void peaked(std::string file_name,int num_seeds,int N,int K,int num_values){
   
    std::ofstream fp;            // File pointer to output file
    int      peak_rv;             // Peaked random variable

    std::cout<<"-->Generate peaked distribution               "<<std::endl;
    gen_random::open_file(fp, file_name);
    gen_random::rand_valc(num_seeds);

    std::cout<<gen_random::sample_banner<<std::endl;

  // Generate and output interarrival times
    for (int i=0; i<num_values; i++){
        peak_rv = peak(N, K);
        fp<<peak_rv;
        fp<<"\n";
    }
    
    std::cout<<gen_random::done_banner<<std::endl;
    fp.close();
}


#endif /* peaked_h */
