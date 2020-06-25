#include <string>
#include <fstream>


//----- Function prototypes -------------------------------------------------
int    peak(int N, int K);      // Returns a peaked RV
double rand_valp(int seed);     // Jain's RNG to return 0 < z < 1

//===== Main program ========================================================
void peaked(std::string file_name,int num_seeds,int N,int K,int num_values)
{
   
  std::ofstream fp;            // File pointer to output file
                   
  int      peak_rv;             // Peaked random variable                 // Loop counter

  // Output banner
  std::cout<<"----------------------------------------------"<<std::endl;
  std::cout<<"-  Generate peaked distribution               "<<std::endl;
  std::cout<<"----------------------------------------------"<<std::endl;

  // Prompt for output filename and then create/open the file
  fp.open("/Users/brandonli/Desktop/random/"+file_name);
  if(!fp.is_open()){
      std::cout<<"Cannot creat output file: "<<file_name<<"!"<<std::endl;
      return;
  }


  // Prompt for random number seed and then use it
  rand_valc(num_seeds);


  //Output message and generate interarrival times
  std::cout<<"----------------------------------------------"<<std::endl;
  std::cout<<"-  Generating samples to file                 "<<std::endl;
  std::cout<<"----------------------------------------------"<<std::endl;

  // Generate and output interarrival times
  for (int i=0; i<num_values; i++)
  {
    peak_rv = peak(N, K);
    fp<<peak_rv;
    fp<<"\n";
  }

  //Output message and close the output file
    std::cout<<"----------------------------------------------"<<std::endl;
    std::cout<<"-  Done                                       "<<std::endl;
    std::cout<<"----------------------------------------------"<<std::endl;
    fp.close();
}

//===========================================================================
//=  Function to generate peak distributed random variables                 =
//=    - Input:  N and K values                                             =
//=    - Output: Returns with peak distributed random variable              =
//===========================================================================
int peak(int N, int K)
{
  double z;                     // Uniform random number (0 < z < 1)
  int    peak_value=0;            // Computed peaked value to be returned

  // Pull a uniform random value (0 < z < 1)
  z = rand_valp(0);

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

//=========================================================================
//= Multiplicative LCG for generating uniform(0.0, 1.0) random numbers    =
//=   - From R. Jain, "The Art of Computer Systems Performance Analysis," =
//=     John Wiley & Sons, 1991. (Page 443, Figure 26.2)                  =
//=========================================================================

double rand_valp(int seed)
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
