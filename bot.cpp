#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/


struct coordinate {
    int x;
    int y;
};

double distance(coordinate a, coordinate b)
{
    int x = (a.x-b.x);
    int y = (a.x-b.x);
    return(sqrt((x*x+y*y)));
}

int main()
{
    int min_boost_degrees = 5;
    double pmul = 0.06;
    int min_thrust_angle = 85;


    time_t timer;
    coordinate bot {0, 0};
    int next_checkpoint_x; // x position of the next check point
    int next_checkpoint_y; // y position of the next check point
    int next_checkpoint_dist; // distance to the next checkpoint
    int next_checkpoint_angle; // angle between your pod orientation and the direction of the next checkpoint

    int opponent_x;
    int opponent_y;


    int thrust;
    int last = 100;

    int longest_run_index = 0;
    double longest_run = 0;
    int current_index = 0;
    coordinate first_target;
    coordinate current_target;
    coordinate last_target;
    bool first_time = true;
    bool boost_enabled = false;

    int boosts = 1;

    // game loop
    while (1) {
        
        cin >> bot.x >> bot.y >> next_checkpoint_x >> next_checkpoint_y >> next_checkpoint_dist >> next_checkpoint_angle; cin.ignore();
        
        cin >> opponent_x >> opponent_y; cin.ignore();

        if (first_time)
        {
            first_target = {next_checkpoint_x, next_checkpoint_y};
            current_target = {next_checkpoint_x, next_checkpoint_y};
            last_target = {next_checkpoint_x, next_checkpoint_y};
            first_time = false;
        }
        current_target = {next_checkpoint_x, next_checkpoint_y};
        
        if (current_target.x != last_target.x || current_target.y != last_target.y)
        {
            current_index += 1;
            if (current_target.x == first_target.x || current_target.y == first_target.y) 
            {
                current_index = 0;
                boost_enabled = true;
            };
            if (distance(current_target, last_target) > longest_run)
            {
                longest_run_index = current_index;
                longest_run = distance(current_target, last_target);
            }
            last_target = current_target;
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        thrust = max(0, min(100 ,int(next_checkpoint_dist * pmul + 40))) * (cos(2*3.14*(next_checkpoint_angle/180)));
        if (abs(next_checkpoint_angle) > min_thrust_angle) thrust = 0;
        // You have to output the target position
        // followed by the power (0 <= thrust <= 100)
        // i.e.: "x y thrust"
        if (boost_enabled && boosts > 0 && abs(next_checkpoint_angle) < min_boost_degrees && current_index == longest_run_index)
        {
            cout << next_checkpoint_x << " " << next_checkpoint_y << " " << "BOOST" << endl;
            boosts -= 1;
        }
        else cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust << endl;
    }
}


