//
//  main.cpp
//  FlatBuffers-Example
//
//  Created by Giorgi Abelashvili on 12/10/18.
//  Copyright © 2018 Giorgi Abelashvili. All rights reserved.
//

#include <iostream>
#include "flatbuffers/include/zc_player_profile_schema_generated.h"

using namespace ZombieCatchers;

// declare flatbufferbuilder
flatbuffers::FlatBufferBuilder builder(1024);

auto CreateZombie(int zombieId, int zombieCount)
{
    return PlayerProfile::CreateZombie(builder,zombieId, zombieCount);
}

auto CreateSqueezer(int squeezerId, bool unlocked)
{
    return PlayerProfile::CreateSqueezer(builder,squeezerId, unlocked);
}

auto CreatePlayer()
{
    // create yellow zombie
    auto yellow_zombie = CreateZombie(0,3);
    
    // create yellow zombie
    auto blue_zombie = CreateZombie(1,6);
    
    
    // create zombies vector
    std::vector<flatbuffers::Offset<PlayerProfile::Zombie>> zombies_vector;
    zombies_vector.push_back(yellow_zombie);
    zombies_vector.push_back(blue_zombie);
    
    
    // yellow squeezer
    auto yellow_zombie_squeezer = CreateSqueezer(0, true);
    

    // blue squeezer
    auto blue_zombie_squeezer = CreateSqueezer(1, false);

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
    PlayerProfile::PlayerProfileBuilder playerProfileBuilder (builder);
    playerProfileBuilder.add_id(playerIdString);
    playerProfileBuilder.add_name(playerNameString);
    playerProfileBuilder.add_plutonium(100);
    playerProfileBuilder.add_coin(123123);
    playerProfileBuilder.add_playerRank(34);
    playerProfileBuilder.add_playerLevel(56);
    playerProfileBuilder.add_zombies(zombiesInventory);
    playerProfileBuilder.add_squeezers(squeezersInventory);
    //
    auto finishedPlayer = playerProfileBuilder.Finish();
    //
    return finishedPlayer;
    //
}

int main(int argc, const char * argv[])
{
    // create player
    auto playerToWrite = CreatePlayer();
    //
    // serialize the root of the object
    builder.Finish(playerToWrite);

    // we can send Builder directly over the network or save to Disk
    
    // save / send code goes here
    
    // here we are just reading the Player profile again
    auto playerToRead = PlayerProfile::GetPlayerProfile(builder.GetBufferPointer());
    //
    // print some player data here
    std::cout<<"Player Level = "<<playerToRead->playerLevel()<<std::endl;
    std::cout<<"Coins Count = "<<playerToRead->coin()<<std::endl;
    std::cout<<"Plutonium Count = "<<playerToRead->plutonium()<<std::endl;
    //
    return 0;
}
