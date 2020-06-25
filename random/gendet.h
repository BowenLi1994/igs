#include <string>
#include <fstream>

void deterministic(std::string file_name,double lambda,double time_period)
{
    
    std::ofstream fp;


    double   det_rv;              // Deterministic random variable
    double   sum_time;            // Sum of time up to now
    

    std::cout<<"----------------------------------------------"<<std::endl;
    std::cout<<"-  Generate deterministically distributed     "<<std::endl;
    std::cout<<"----------------------------------------------"<<std::endl;

    fp.open("/Users/brandonli/Desktop/random/"+file_name);
    if(!fp.is_open()){
      std::cout<<"Cannot creat output file: "<<file_name<<"!"<<std::endl;
      return;
    }
    
    
   

    
    std::cout<<"----------------------------------------------"<<std::endl;
    std::cout<<"-  Generating samples to file                 "<<std::endl;
    std::cout<<"----------------------------------------------"<<std::endl;

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
  std::cout<<"----------------------------------------------"<<std::endl;
  std::cout<<"-  Done                                       "<<std::endl;
  std::cout<<"----------------------------------------------"<<std::endl;
  fp.close();
}
