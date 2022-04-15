#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
struct coordinate {
    int x;
    int y;
};

struct vector2D {
    float x;
    float y;
};

double distance(coordinate a, coordinate b)
{
    int x = (a.x-b.x);
    int y = (a.x-b.x);
    return(sqrt((x*x+y*y)));
}

vector2D vec(coordinate from, coordinate to)
{
    float angle = atan2(to.y - from.y, to.x-from.x);
    vector2D vector = {(cos(angle)), (sin(angle))};
    return(vector);
}


int main()
{
    int minimum_power_angle = 55;
    int minimum_boost_distance = 6000;
    int minimum_boost_angle = 2;
    int low_thrust = 30;

    coordinate player;
    coordinate last_player_position;
    coordinate opponent;
    coordinate next_checkpoint;
    coordinate last_checkpoint;
    int next_checkpoint_dist; // distance to the next checkpoint
    int next_checkpoint_angle; // angle between your pod orientation and the direction of the next checkpoint

    int thrust;
    int boosts = 1;

    // game loop
    while (1) {
        // set thrust to maximum
        thrust = 100;
        
        //take input
        cin >> player.x >> player.y >> next_checkpoint.x >> next_checkpoint.y >> next_checkpoint_dist >> next_checkpoint_angle; cin.ignore();

        cin >> opponent.x >> opponent.y; cin.ignore();

        // lower thrust when pointing away from target
        if (abs(next_checkpoint_angle) >= minimum_power_angle)
        {
            thrust = low_thrust;
        }
        
        //calculate momentum and target vectors
        vector2D v = vec(last_player_position, player);
        vector2D r = vec(last_player_position, next_checkpoint);
        last_player_position = player;

        // debug outbut
        cerr << "current: " << v.x << " " << v.y << " target: " << r.x << " " << r.y << " predicted: " << r.x + (r.x - v.x) << " " << r.y + (r.y -v.x)<< endl;
        if (boosts > 0 && next_checkpoint_dist >= minimum_boost_distance && abs(next_checkpoint_angle) <= minimum_boost_angle)
        {
            cout << next_checkpoint.x << " " << next_checkpoint.y << " " << "BOOST" << endl;
            boosts --;
        }
        else
        {
            //cout << next_checkpoint.x << " " << next_checkpoint.y << " " << thrust << endl;   // always steer toward target
            cout <<  player.x + int((r.x + (r.x - v.x))*next_checkpoint_dist) << " " << player.y + int((r.y + (r.y - v.y))*next_checkpoint_dist) << " " << thrust << endl; // point movement vector toward target
        }
    }
}
