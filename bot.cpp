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

int main()
{
    time_t timer;
    coordinate bot {0, 0};
    int next_checkpoint_x; // x position of the next check point
    int next_checkpoint_y; // y position of the next check point
    int next_checkpoint_dist; // distance to the next checkpoint
    int next_checkpoint_angle; // angle between your pod orientation and the direction of the next checkpoint

    int opponent_x;
    int opponent_y;


    int thrust;
    double pmul = 0.04;
    int last = 100;

    int last_time = time(&timer);
    int this_time;
    int delta;
    // game loop
    while (1) {
        
        cin >> bot.x >> bot.y >> next_checkpoint_x >> next_checkpoint_y >> next_checkpoint_dist >> next_checkpoint_angle; cin.ignore();
        
        cin >> opponent_x >> opponent_y; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        thrust = max(0, min(100 ,int(next_checkpoint_dist * pmul + 40))) * cos(2*3.14*(next_checkpoint_angle/180));
        // You have to output the target position
        // followed by the power (0 <= thrust <= 100)
        // i.e.: "x y thrust"
        cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust << endl;
    }
}
