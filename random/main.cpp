//
//  main.cpp
//  random
//
//  Created by Bowen Li on 6/16/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#include <iostream>
#include "random_header.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    
    //gen_random::deterministic("dis.txt", 1.0, 15.0);
    //gen_random::uniform_d("unifd.txt", 1, 1, 2, 5);
    //gen_random::peaked("peak.txt", 1, 10, 10, 10);
    //gen_random::normal("normal.txt", 1, 0, 1, 10);
    //expontial("exp.txt", 1, 10, 5);
    //geometric("geo.txt", 1, 0.25, 5);
    //poisson("poi.txt", 1, 10.0, 5);
    //binomial("bin.txt", 1, 20, 0.1, 6);
    //erlang("erl.txt", 1, 2, 1.0, 100);
    //hyperexpon_p1_lambda("hyp1.txt", 1, 10.0, 1.0, 0.25, 10.0);
    //hyperexpon_mean_cov("hyp2.txt", 1, 1.0, 2.0, 20);
    //interrupted_poisson_process("ipp.txt", 1, 2.0, 1.0, 1.0, 15.0);
    //pareto("par1.txt", 1, 1.5, 1.0, 5);
    //bounded_pareto("par2.txt", 1, 1.5, 1.0, 100.0, 5);
    //zipf("zipf.txt", 1, 1.0, 1000, 5);
    unique_random_integers("uni.txt", 1, 10);

    return 0;
}
