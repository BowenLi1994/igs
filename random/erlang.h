//
//  erlang.h
//  random
//
//  Created by Bowen Li on 6/18/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef erlang_h
#define erlang_h

#include "random_generator.h"

using namespace gen_random;

void erlang(std::string file_name,int seed_num,int num_stages,double rate,int num_values){
    
  std::ofstream fp;
    // File pointer to output file// Temporary string variable
  double   lambda[MAX_STAGES];  // Mean of rates for stages
  double   exp_rv;              // Exponential random variable
  double   erl_rv;              // Erlang random variable


  // Output banner
    std::cout<<"-->Program to generate Erlang random variables\n";
  

  // Prompt for output filename and then create/open the file
    open_file(fp, file_name);


  // Prompt for random number seed and then use it
  rand_valc(seed_num);


    
  if (num_stages > MAX_STAGES)
  {
    printf("ERROR - too many stages (max stages is %d) \n", MAX_STAGES);
    exit(1);
  }

  // Prompt for stage rate and assign the rates (lambda[])
    lambda[0] = rate;
    
    for (int i=1; i<num_stages; i++){
        lambda[i] = lambda[0];
    }



    std::cout<<sample_banner<<std::endl;

  // Generate and output Erlang random variables
  //  - Erlang random variable is a sum of exponential random variables
  for (int i=0; i<num_values; i++)
  {
    erl_rv = 0.0;
    for (int j=0; j<num_stages; j++)
    {
      exp_rv = expon(1.0 / lambda[j]);
      erl_rv = erl_rv + exp_rv;
    }
    fp<<erl_rv;
    fp<<"\n";
  }

  //Output message and close the output file
    std::cout<<done_banner<<std::endl;
    fp.close();
}


#endif /* erlang_h */
