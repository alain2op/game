#include<iostream>
#include <dlfcn.h>
#include <set>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include<cstring>
#include "newlibGameLogic.h"
#include<unistd.h>

using namespace std;


// bool a=false;
void World::Tick(float f){
    ClientWorld* world = *((ClientWorld**)(dlsym(RTLD_NEXT, "GameWorld")));
    GameAPI* game=*((GameAPI**)(dlsym(RTLD_NEXT,"Game")));
    IPlayer* iplayer = world->m_activePlayer.m_object;
    Player* player = ((Player*)(iplayer));
    Actor* actor = ((Actor*)(iplayer));
    player->m_walkingSpeed = 99999;
    player->m_jumpSpeed = 999;
    player->m_jumpHoldTime = 99999;
    // player->SetPosition(Vector3(10000,10000,10000));
    // if(a){
    //     float x=-7894;
    //     float y=64482;
    //     float z=2463;
    //     player->SetPosition(Vector3(x,y,z));
    // }
}

void Player::Chat(const char* message){
    char buffer[256];
    strncpy(buffer, message, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';
    char* words[5];
    int word_count = 0;
    char* token = strtok(buffer, " ");
    while (token != NULL && word_count < 5) {
        words[word_count++] = token;
        token = strtok(NULL, " ");
    }
     if (word_count == 4 && strcmp(words[0], "tpr") == 0) {
        Vector3 pos = this->GetPosition();
        float x = strtof(words[1], NULL);
        float y = strtof(words[2], NULL);
        float z = strtof(words[3], NULL);
        this->SetPosition(pos + Vector3(x, y, z));
        cout<<pos.x+x<<' '<<pos.y+y<<' '<<pos.z+z<<endl;
    } 
    else if (word_count == 4 && strcmp(words[0], "tp") == 0) {
        float x = strtof(words[1], NULL);
        float y = strtof(words[2], NULL);
        float z = strtof(words[3], NULL);
        this->SetPosition(Vector3(x, y, z));
        cout<<x<<' '<<y<<' '<<z<<endl;
    }
    else if(word_count==1 && strcmp(words[0],"a")==0){
        ClientWorld* world = *((ClientWorld**)(dlsym(RTLD_NEXT, "GameWorld")));
        for(ActorRef<IActor> actor_s:world->m_actors){
            Vector3 position=actor_s.m_object->GetLookPosition();
            printf("%s\n",actor_s.m_object->GetDisplayName());
            std::cout<<position.x<<'\t'<<position.y<<'\t'<<position.z<<endl;
        }
        std::cout<<endl<<endl;
    }
    else if(word_count==1 && strcmp(words[0],"q")==0){
        // if(a==false){a=true;}
        // else{a=false;}
        // BearChest* bearchest;
        // cout<<"in";
        // for(ActorRef<IActor> actor_s:world->m_actors){
        //     Vector3 position=actor_s.m_object->GetLookPosition();
        //     if(abs(position.z-2663)<=5){
        //         bearchest=(BearChest*)actor_s.m_object;
        //         cout<<position.z;
        //         std::map<ActorRef<IPlayer>, float> m_playerTimeLeft=bearchest->m_playerTimeLeft;
        //         for (auto& pair : m_playerTimeLeft) {
        //             pair.second = 1;
        //         }
        //     }
        // }
        
    }   
    else if(word_count==1 && strcmp(words[0],"mb")==0){
        ClientWorld* world = *((ClientWorld**)(dlsym(RTLD_NEXT, "GameWorld")));
        for(ActorRef<IActor> actor_s:world->m_actors){
            Vector3 position=actor_s.m_object->GetLookPosition();
            if(strcmp(actor_s.m_object->GetDisplayName(),"Bear")==0){
                Actor* actor=(Actor*)actor_s.m_object;
                actor->SetPosition(Vector3(position.x+100000,position.y+100000,position.z+1000000));
            }
            // printf("%s\n",actor_s.m_object->GetDisplayName());
            // std::cout<<position.x<<'\t'<<position.y<<'\t'<<position.z<<endl;
        }
        // usleep(5*1000000);
    }
}
