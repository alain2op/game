#include<iostream>
#include <dlfcn.h>
#include <set>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include<cstring>
#include "newlibGameLogic.h"

using namespace std;

void World::Tick(float f){
    ClientWorld* world = *((ClientWorld**)(dlsym(RTLD_NEXT, "GameWorld")));
    GameAPI* game=*((GameAPI**)(dlsym(RTLD_NEXT,"Game")));
    IPlayer* iplayer = world->m_activePlayer.m_object;
    Player* player = ((Player*)(iplayer));
    Actor* actor = ((Actor*)(iplayer));
    player->m_walkingSpeed = 99999;
    player->m_jumpSpeed = 999;
    player->m_jumpHoldTime = 99999;
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
        cout << "tpr" << endl;
        Vector3 pos = this->GetPosition();
        float x = strtof(words[1], NULL);
        float y = strtof(words[2], NULL);
        float z = strtof(words[3], NULL);
        this->SetPosition(pos + Vector3(x, y, z));
    } 
    else if (word_count == 4 && strcmp(words[0], "tp") == 0) {
        float x = strtof(words[1], NULL);
        float y = strtof(words[2], NULL);
        float z = strtof(words[3], NULL);
        this->SetPosition(Vector3(x, y, z));
        cout << "tp" << endl;
    }
    else if(word_count==1 && strcmp(words[0],"q")==0){
        cout<<"done";
        IQuest* iquest=this->m_currentQuest;
        this->CompleteQuest(iquest);
    }
    
}

