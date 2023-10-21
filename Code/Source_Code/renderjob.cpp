//
// Created by Devon Coates on 9/7/23.
//

#include "renderjob.h"
#include <iostream>

void RenderJob::Execute(){ // This job is just doing random stuff as an example
    int total = 0;

    std::vector< int >::iterator it = data.begin();

    for(; it != data.end(); ++it){
        total += *it;
    }

    data[0] = total;
    std::cout << "Render Job " << this->GetUniqueID() << " has been executed." << std::endl;
}

void RenderJob::JobCompleteCallback(){ // This just prints the sum after execute finds the sum
    std::cout << "Job " << this->GetUniqueID() << " calculated sum: " << this->data[0] << std::endl;
}