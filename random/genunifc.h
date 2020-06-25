#include <string>
#include <fstream>

//----- Function prototypes -------------------------------------------------
double unifc(double min, double max);  // Returns a continuous uniform RV
double rand_valc(int seed);            // Jain's RNG to return 0 < z < 1


//===== Main program ========================================================
void uniform_c(std::string file_name,int seed_num,double min,double max,int num_values)
{
  std::ofstream fp;  // File pointer to output file

    
  
  double   unif_rv;             // Uniformly random variable
  int      i;                   // Loop counter

    std::cout<<"----------------------------------------------"<<std::endl;
    std::cout<<"-  Generate continuous uniform                "<<std::endl;
    std::cout<<"----------------------------------------------"<<std::endl;

  // Output banner
 

  // Prompt for output filename and then create/open the file

    fp.open("/Users/brandonli/Desktop/random/"+file_name);
    if(!fp.is_open()){
        std::cout<<"Cannot creat output file: "<<file_name<<"!"<<std::endl;
        return;
    }
    

  rand_valc(seed_num);




  std::cout<<"----------------------------------------------"<<std::endl;
  std::cout<<"-  Generating samples to file                 "<<std::endl;
  std::cout<<"----------------------------------------------"<<std::endl;

  // Generate and output interarrival times
  for (i=0; i<num_values; i++)
  {
    unif_rv = unifc(min, max);
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
double unifc(double min, double max)
{
  double z;                     // Uniform random number (0 < z < 1)
  double unif_value;            // Computed uniform value to be returned

  // Pull a uniform random value (0 < z < 1)
  z = rand_valc(0);

  // Compute uniform continuous random variable using inversion method
  unif_value = z * (max - min) + min;

  return(unif_value);
}

//=========================================================================
//= Multiplicative LCG for generating uniform(0.0, 1.0) random numbers    =
//=   - From R. Jain, "The Art of Computer Systems Performance Analysis," =
//=     John Wiley & Sons, 1991. (Page 443, Figure 26.2)                  =
//=========================================================================
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
