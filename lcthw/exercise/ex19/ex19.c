#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "ex19.h"
void free_function(void *self);

void free_function(void *self){
    Map *game = self;
    if(game) free(game);
    if(game->proto.description) free(game->proto.description);
    if(game->start) free(game->start);
    if(game->start->proto.description) free(game->start->proto.description);
    if(game->start->north) free(game->start->north);
    if(game->start->north->proto.description) free(game->start->north->proto.description);
    if(game->start->north->east) free(game->start->north->east);
    if(game->start->north->east->proto.description) free(game->start->north->east->proto.description);
    if(game->start->north->west) free(game->start->north->west);
    if(game->start->north->west->proto.description) free(game->start->north->west->proto.description);
    if(game->start->north->west->bad_guy) free(game->start->north->west->bad_guy);
    if(game->start->north->west->bad_guy->proto.description) free(game->start->north->west->bad_guy->proto.description);
    if(game->start->north->west->good_guy) free(game->start->north->west->good_guy);
    if(game->start->north->west->good_guy->proto.description) free(game->start->north->west->good_guy->proto.description);    
}

int Monster_attack(void *self, void *self_c, int damage, int back_damage)
{
    Monster *monster = self;
    Monster *monster_c = self_c;

    printf("%s attack %s!\n", monster_c->_(description), monster->_(description));

    monster->hit_points -= damage;
    monster_c->hit_points -= back_damage;
    printf("monster left hit_points:%d.\n",monster->hit_points);
    printf("challenger left hit_points:%d.\n",monster_c->hit_points);

    if((monster->hit_points > 0)&&(monster_c->hit_points > 0)) {
        printf("It is still alive, please go attack\n");
        return 1;
    } else if((monster->hit_points > 0)&&(monster_c->hit_points <= 0)) {
        printf("you die!\n");
        return 0;
    } else if((monster->hit_points <= 0)&&(monster_c->hit_points <= 0)) {
        printf("game over, You're all dead!\n");
	return 0;
    } else{ //if((monster->hit_points <= 0)&&(monster_c->hit_points > 0)) {
	printf("It is dead! You win, and become the new one monster\n");
	return 0;
    }
}

int Monster_init(void *self)
{
    Monster *monster = self;
    monster->hit_points = 10;
    return 1;
}

Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};


void *Room_move(void *self, Direction direction)
{
    Room *room = self;
    Room *next = NULL;

    if(direction == NORTH && room->north) {
        printf("You go north, into:\n");
        next = room->north;
    } else if(direction == SOUTH && room->south) {
        printf("You go south, into:\n");
        next = room->south;
    } else if(direction == EAST && room->east) {
        printf("You go east, into:\n");
        next = room->east;
    } else if(direction == WEST && room->west) {
        printf("You go west, into:\n");
        next = room->west;
    } else {
        printf("You can't go that direction.");
        next = NULL;
    }

    if(next) {
        next->_(describe)(next);
    }

    return next;
}


int Room_attack(void *self, void *self_c, int damage, int back_damage)
{
    Room *room = self;
    Monster *monster = room->bad_guy;
    Monster *monster_c = room->good_guy;// challenger

    if(monster&&monster_c) {
        return monster->_(attack)(monster, monster_c, damage, back_damage);
    } else {
        printf("You flail in the air at nothing. Idiot.\n");
        return 1;
    }
}


Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack
};


void *Map_move(void *self, Direction direction)
{
    Map *map = self;
    Room *location = map->location;
    Room *next = NULL;

    next = location->_(move)(location, direction);

    if(next) {
        map->location = next;
    }

    return next;
}

int Map_attack(void *self, void *self_c, int damage, int back_damage)
{
    Map* map = self;
    Room *location = map->location;

    return location->_(attack)(location, self_c, damage, back_damage);
}


int Map_init(void *self)
{
    Map *map = self;

    // make some rooms for a small map
    Room *hall = NEW(Room, "The great Hall");
    Room *throne = NEW(Room, "The throne room");
    Room *arena = NEW(Room, "The arena, with the minotaur");
    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");

    // put the bad guy and challenger in the arena
    arena->bad_guy = NEW(Monster, "The evil minotaur");
    arena->good_guy = NEW(Monster, "The challenger");

    // setup the map rooms
    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->east = throne;
    kitchen->west = throne;

    // start the map and the character off in the hall
    map->start = hall;
    map->location = hall;

    return 1;
}

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

int process_input(Map *game)
{
    printf("\n> ");

    char ch = getchar();
    int m = 1;
    assert(getchar()==10); // eat ENTER

    int damage = rand() % 4;
    int back_damage = rand() % 4;

    switch(ch) {
        case -1:
            printf("Giving up? You suck.\n");
            return 0;
            break;

        case 'n':
            game->_(move)(game, NORTH);
            break;

        case 's':
            game->_(move)(game, SOUTH);
            break;

        case 'e':
            game->_(move)(game, EAST);
            break;

        case 'w':
            game->_(move)(game, WEST);
            break;

        case 'a':

            m = game->_(attack)(game, NULL, damage, back_damage);
            break;
        case 'l':
            printf("You can go:\n");
            if(game->location->north) printf("NORTH\n");
            if(game->location->south) printf("SOUTH\n");
            if(game->location->east) printf("EAST\n");
            if(game->location->west) printf("WEST\n");
            break;

        default:
            printf("What?: %d\n", ch);
    }

    return m;
}

int main(int argc, char *argv[])
{
    // simple way to setup the randomness
    srand(time(NULL));

    // make our map to work with
    Map *game = NEW(Map, "The Hall of the Minotaur.");

    printf("You enter the ");
    game->location->_(describe)(game->location);

    while(process_input(game)) {
    }
    free_function(game);
    return 0;
}
