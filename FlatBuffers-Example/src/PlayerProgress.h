//
//  PlayerProgress.hpp
//  FlatBuffers-Example
//
//  Created by Giorgi Abelashvili on 12/11/18.
//  Copyright © 2018 Giorgi Abelashvili. All rights reserved.
//

#ifndef PlayerProgress_hpp
#define PlayerProgress_hpp

#include <stdio.h>
#include "../flatbuffers/include/zc_player_profile_schema_generated.h"
#include "../flatbuffers/util.h"

using namespace ZombieCatchers;

class PlayerProgress
{
public:
    PlayerProgress();
    ~PlayerProgress();
    
    // currency properties
    int GetCoinsAmount() const;
    int GetPlutoniumAmount() const;
    
    void SetCoinsAmount(int amount);
    void SetPlutoniumAmount(int amount);
    
private:

    char *profileDataBuffer;
    
    flatbuffers::Offset<PlayerProfile::PlayerProfile> currentPlayerProfile;
    
    // load zombie object
    flatbuffers::Offset<PlayerProfile::Zombie> LoadZombie(int zombieId, int zombieCount);
    
    // load squeezer object
    flatbuffers::Offset<PlayerProfile::Squeezer> LoadSqueezer(int squeezerId, bool unlocked);

    bool SaveProgress(char* buffer);
    
    bool LoadProgress(std::string &buffer);
    
};

#endif /* PlayerProgress_h */
