//
//  PlayerProgress.cpp
//  FlatBuffers-Example
//
//  Created by Giorgi Abelashvili on 12/11/18.
//  Copyright © 2018 Giorgi Abelashvili. All rights reserved.
//

#include "PlayerProgress.h"

flatbuffers::FlatBufferBuilder builder(1024);

PlayerProgress::PlayerProgress()
{
    
    // we can have flatbuffers object here read from file, or recive over network
    // read / recieve data cod here
    // in this case just initialize with some test datas here
    auto yellow_zombie = LoadZombie(0, 5);
    auto blue_zombie = LoadZombie(1, 4);
    auto green_zombie = LoadZombie(2, 3);
    
    // create zombies vector
    std::vector<flatbuffers::Offset<PlayerProfile::Zombie>> zombies_vector;
    zombies_vector.push_back(yellow_zombie);
    zombies_vector.push_back(blue_zombie);
    zombies_vector.push_back(green_zombie);
    
    // yellow squeezer
    auto yellow_zombie_squeezer = LoadSqueezer(0, true);
    
    // blue squeezer
    auto blue_zombie_squeezer = LoadSqueezer( 1, false);
    
    // create zombies vector
    std::vector<flatbuffers::Offset<PlayerProfile::Squeezer>> squeezer_vector;
    squeezer_vector.push_back(yellow_zombie_squeezer);
    squeezer_vector.push_back(blue_zombie_squeezer);
    
    
    // initialize player id string
    flatbuffers::Offset<flatbuffers::String> playerIdString = builder.CreateString("someId");
    flatbuffers::Offset<flatbuffers::String> playerNameString = builder.CreateString("Giorgi Abelix Abelashvili");
    auto zombiesInventory = builder.CreateVector(zombies_vector);
    auto squeezersInventory = builder.CreateVector(squeezer_vector);
    //
    // create player progile
    PlayerProfile::PlayerProfileBuilder playerProfileBuilder(builder);
    playerProfileBuilder.add_id(playerIdString);
    playerProfileBuilder.add_name(playerNameString);
    playerProfileBuilder.add_plutonium(100);
    playerProfileBuilder.add_coin(123123);
    playerProfileBuilder.add_playerRank(34);
    playerProfileBuilder.add_playerLevel(56);
    playerProfileBuilder.add_zombies(zombiesInventory);
    playerProfileBuilder.add_squeezers(squeezersInventory);
    //
    // finish loading of player object
    currentPlayerProfile = playerProfileBuilder.Finish();
    //
    // finish the builder object writing
    builder.Finish(currentPlayerProfile);
    //
}
//

int PlayerProgress::GetCoinsAmount() const
{
    auto profile = PlayerProfile::GetPlayerProfile(builder.GetBufferPointer());
    int coinsAmount = profile->coin();
    return coinsAmount;
}
int PlayerProgress::GetPlutoniumAmount() const
{
    auto profile = PlayerProfile::GetPlayerProfile(builder.GetBufferPointer());
    int plutonium = profile->plutonium();
    return plutonium;
}
//
void PlayerProgress::SetCoinsAmount(int amount)
{
    PlayerProfile::PlayerProfileBuilder playerProfileBuilder(builder);
    playerProfileBuilder.add_coin(amount);
    currentPlayerProfile = playerProfileBuilder.Finish();
    builder.Finish(currentPlayerProfile);
}
//
void PlayerProgress::SetPlutoniumAmount(int amount)
{
    PlayerProfile::PlayerProfileBuilder playerProfileBuilder(builder);
    playerProfileBuilder.add_plutonium(amount);
    currentPlayerProfile = playerProfileBuilder.Finish();
    builder.Finish(currentPlayerProfile);
}

flatbuffers::Offset<PlayerProfile::Zombie> PlayerProgress::LoadZombie(int zombieId, int zombieCount)
{
    return PlayerProfile::CreateZombie(builder,zombieId, zombieCount);
}


flatbuffers::Offset<PlayerProfile::Squeezer>  PlayerProgress::LoadSqueezer(int squeezerId, bool unlocked)
{
    return PlayerProfile::CreateSqueezer(builder,squeezerId, unlocked);
}

//
PlayerProgress::~PlayerProgress()
{
    
}
//


