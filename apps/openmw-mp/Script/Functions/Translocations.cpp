//
// Created by koncord on 29.02.16.
//

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>
#include <apps/openmw-mp/Player.hpp>
#include <apps/openmw-mp/Networking.hpp>

#include <iostream>
using namespace std;

void ScriptFunctions::GetPos(unsigned short pid, float *x, float *y, float *z) noexcept
{
    *x = 0.00;
    *y = 0.00;
    *z = 0.00;

    Player *player;
    GET_PLAYER(pid, player,);

    *x = player->Position()->pos[0];
    *y = player->Position()->pos[1];
    *z = player->Position()->pos[2];
}

void ScriptFunctions::SetPos(unsigned short pid, float x, float y, float z) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->Position()->pos[0] = x;
    player->Position()->pos[1] = y;
    player->Position()->pos[2] = z;

    mwmp::Networking::Get().GetController()->GetPacket(ID_GAME_UPDATE_POS)->Send(player, false);
    mwmp::Networking::Get().GetController()->GetPacket(ID_GAME_UPDATE_POS)->Send(player, true);
}

void ScriptFunctions::SetCell(unsigned short pid, const char *name) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    /*if(player->GetCell()->mName == name)
        return;*/

    cout << "attempt to move player (pid: " << pid << " name: " << player->Npc()->mName << ") from ";
    if(!player->GetCell()->isExterior())
        cout << "\"" << player->GetCell()->mName << "\"";
    else
        cout << "exterior";

    player->GetCell()->mName = name;

    cout << " in to cell \"" << player->GetCell()->mName << "\"" << endl;

    player->GetCell()->mData.mFlags |=  1;

    mwmp::Networking::Get().GetController()->GetPacket(ID_GAME_CELL)->Send(player, false);
    mwmp::Networking::Get().GetController()->GetPacket(ID_GAME_CELL)->Send(player, true);
}

const char* ScriptFunctions::GetCell(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);


    return player->GetCell()->mName.c_str();
}

bool ScriptFunctions::IsInInterior(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, false);

    return !player->GetCell()->isExterior();
}

void ScriptFunctions::GetAngle(unsigned short pid, float *x, float *y, float *z) noexcept
{
    *x = 0.00;
    *y = 0.00;
    *z = 0.00;

    Player *player;
    GET_PLAYER(pid, player,);

    *x = player->Position()->rot[0];
    *y = player->Position()->rot[1];
    *z = player->Position()->rot[2];
}

void ScriptFunctions::SetAngle(unsigned short pid, float x, float y, float z) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->Position()->rot[0] = x;
    player->Position()->rot[1] = y;
    player->Position()->rot[2] = z;

    mwmp::Networking::Get().GetController()->GetPacket(ID_GAME_UPDATE_POS)->Send(player, false);
    mwmp::Networking::Get().GetController()->GetPacket(ID_GAME_UPDATE_POS)->Send(player, true);
}
