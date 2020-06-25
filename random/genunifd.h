#include <string>
#include <fstream>

//----- Function prototypes -------------------------------------------------
double unifd(int min, int max); // Returns a discrete uniform RV
long   rand_vald(int seed);     // Jain's RNG to return a discrete number

//===== Main program ========================================================
void uniform_d(std::string file_name,int seed_num,double min,double max,int num_values)
{
    std::ofstream fp;
    // File pointer to output file
  int      unif_rv;             // Uniformly random variable

  // Output banner
    std::cout<<"----------------------------------------------"<<std::endl;
    std::cout<<"-  Generate discrete uniform                  "<<std::endl;
    std::cout<<"----------------------------------------------"<<std::endl;

    fp.open("/Users/brandonli/Desktop/random/"+file_name);
    if(!fp.is_open()){
        std::cout<<"Cannot creat output file: "<<file_name<<"!"<<std::endl;
        return;
    }


  // Prompt for random number seed and then use it
  rand_vald(seed_num);


  //Output message and generate interarrival times
  std::cout<<"----------------------------------------------"<<std::endl;
  std::cout<<"-  Generating samples to file                 "<<std::endl;
  std::cout<<"----------------------------------------------"<<std::endl;

  // Generate and output interarrival times
  for (int i=0; i<num_values; i++)
  {
    unif_rv = unifd(min, max);
    fp<<unif_rv;
    fp<<"\n";
  }

  //Output message and close the output file
    std::cout<<"----------------------------------------------"<<std::endl;
    std::cout<<"-  Done                                       "<<std::endl;
    std::cout<<"----------------------------------------------"<<std::endl;
    fp.close();

}

//===========================================================================
//=  Function to generate uniformly distributed random variables            =
//=    - Input:  Min and max values                                         =
//=    - Output: Returns with uniformly distributed random variable         =
//===========================================================================
double unifd(int min, int max)
{
  int    z;                     // Uniform random integer number
  int    unif_value;            // Computed uniform value to be returned

  // Pull a uniform random integer
  z = (int)rand_vald(0);

  unif_value = z % (max - min + 1) + min;

  return(unif_value);
}

//=========================================================================
//= Multiplicative LCG for generating uniform(0.0, 1.0) random numbers    =
//=   - From R. Jain, "The Art of Computer Systems Performance Analysis," =
//=     John Wiley & Sons, 1991. (Page 443, Figure 26.2)                  =
//=========================================================================
long rand_vald(int seed)
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

  // Return a random integer number
  return(x);
}
