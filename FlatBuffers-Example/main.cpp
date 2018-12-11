//
//  main.cpp
//  FlatBuffers-Example
//
//  Created by Giorgi Abelashvili on 12/10/18.
//  Copyright © 2018 Giorgi Abelashvili. All rights reserved.
//

#include <iostream>
#include "src/PlayerProgress.h"

int main(int argc, const char * argv[])
{
    std::unique_ptr<PlayerProgress> currentProgress(new PlayerProgress());
    //
    std::cout<<"coins amount = " << currentProgress->GetCoinsAmount()<<std::endl;
    //
    // set new coins amount
    currentProgress->SetCoinsAmount(200);
    // print new coins amount
    std::cout<<"new coins amount = " << currentProgress->GetCoinsAmount()<<std::endl;
    //
    return 0;
}
