//
//  random_generator.h
//  random
//
//  Created by Bowen Li on 6/16/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef random_generator_h
#define random_generator_h

#include <string>
#include <fstream>
#include <cmath>
namespace gen_random{


const std::string file_path="/Users/brandonli/Desktop/";
const std::string sample_banner="-->Generating samples to file                 ";
const std::string done_banner="-->Done                                       ";
const double PI=3.14159265;
const int MAX_STAGES=500;


void open_file(std::ofstream &fp, std::string file_name);
double rand_valc(int seed);
long rand_vald(int seed);









void open_file(std::ofstream &fp, std::string file_name){
    fp.open(file_path+file_name,std::ios_base::app);
    if(!fp.is_open()){
      std::cout<<"Cannot creat output file: "<<file_name<<"!"<<std::endl;
      return;
    }
}



double rand_valc(int seed)
{
  const long  a =      16807;  // Multiplier
  const long  m = 2147483647;  // Modulus
  const long  q =     127773;  // m div a
  const long  r =       2836;  // m mod a
  static long x;               // Random int value
  long        x_div_q;         // x divided by q
  long        x_mod_q;         // x modulo q
  long        x_new;           // New x value

  // Set the seed if argument is non-zero and then return zero
  if (seed > 0)
  {
    x = seed;
    return(0.0);
  }

  // RNG using integer arithmetic
  x_div_q = x / q;
  x_mod_q = x % q;
  x_new = (a * x_mod_q) - (r * x_div_q);
  if (x_new > 0)
    x = x_new;
  else
    x = x_new + m;

  // Return a random value between 0.0 and 1.0
  return((double) x / m);
}


long rand_vald(int seed){
  const long  a =      16807;  // Multiplier
  const long  m = 2147483647;  // Modulus
  const long  q =     127773;  // m div a
  const long  r =       2836;  // m mod a
  static long x;               // Random int value
  long        x_div_q;         // x divided by q
  long        x_mod_q;         // x modulo q
  long        x_new;           // New x value

  // Set the seed if argument is non-zero and then return zero
  if (seed > 0)
  {
    x = seed;
    return(0.0);
  }

  // RNG using integer arithmetic
  x_div_q = x / q;
  x_mod_q = x % q;
  x_new = (a * x_mod_q) - (r * x_div_q);
  if (x_new > 0)
    x = x_new;
  else
    x = x_new + m;

  // Return a random integer number
  return(x);
}



    
}




#endif /* random_generator_h */
