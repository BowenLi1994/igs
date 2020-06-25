
#ifndef random_h
#define random_h

#include <string>
#include <fstream>

namespace new_random {

const std::string file_path="/Users/brandonli/Desktop/random/";
const std::string sample_banner="-->Generating samples to file            ";
const std::string done_banner=  "-->Done                                  ";

//declration
double rand_valc(int seed);
double unifc(double min, double max);
void deterministic(std::string file_name,double lambda,double time_period);


void deterministic(std::string file_name,double lambda,double time_period)
{
    
    std::ofstream fp;


    double   det_rv;              // Deterministic random variable
    double   sum_time;            // Sum of time up to now
    
    std::cout<<"-->Generate deterministically distributed"<<std::endl;
    fp.open("/Users/brandonli/Desktop/random/"+file_name);
    if(!fp.is_open()){
        std::cout<<"Cannot creat output file: "<<file_name<<"!"<<std::endl;
        return;
    }
    
    std::cout<<sample_banner<<std::endl;

  // Generate and output interarrival times
  sum_time = 0.0;
  while(1)
  {
    det_rv = 1.0 / lambda;
    fp<<det_rv;
    fp<<"\n";
    sum_time = sum_time + det_rv;
    if (sum_time >= time_period) break;
  }

  //Output message and close the output file
  std::cout<<done_banner<<std::endl;

    
  fp.close();
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
  return ((double) x / m);
}





}







#endif
