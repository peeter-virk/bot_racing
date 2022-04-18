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

struct collision_coordinate {
    coordinate place;
    int estimated_turns;
};


struct vector2D {
    double x;
    double y;
    double magnitude;
};

double distance(coordinate a, coordinate b)
{
    int x = (a.x-b.x);
    int y = (a.y-b.y);
    return(sqrt((x*x+y*y)));
}

vector2D vec(coordinate from, coordinate to)
{
    float angle = atan2(to.y - from.y, to.x-from.x);
    vector2D vector = {(cos(angle)), (sin(angle)), distance(from, to)};

    return(vector);
}

coordinate cord_from_vec(coordinate from, vector2D vec)
{
    from.x += int (vec.x * vec.magnitude);
    from.y += int (vec.y * vec.magnitude);
    return from;
}

collision_coordinate time_to_collision(coordinate a, coordinate b, vector2D velocity_vector_a, vector2D velocity_vector_b, double speed_a, double speed_b, int range, int iterations)
{
    collision_coordinate cc;
    for (int i = 0; i<iterations+1; i++)
    {
        if (distance(a,b) <= range)
        {
            cc.estimated_turns = i;
            cc.place = a;
            return cc;
        }
        a.x = (int) a.x + velocity_vector_a.x * speed_a;
        a.y = (int) a.y + velocity_vector_a.y * speed_a;
        b.x = (int) b.x + velocity_vector_b.x * speed_b;
        b.y = (int) b.y + velocity_vector_b.y * speed_b;
        
    }
    cc.estimated_turns = -1;
    return cc;
}


int main()
{
    vector<int> power_angls = {80, 120};
    vector<int> thrust_levels = {70, 0};
    int minimum_boost_distance = 5000;
    int minimum_boost_angle = 2;

    const coordinate center_of_map = {8000, 4500};
    coordinate player;
    coordinate last_player_position;
    coordinate last_opponent_position;
    coordinate opponent;
    coordinate next_checkpoint;
    coordinate last_checkpoint;
    int next_checkpoint_dist; // distance to the next checkpoint
    int next_checkpoint_angle; // angle between your pod orientation and the direction of the next checkpoint

    int thrust;
    int boosts = 1;

    int round = 1;
    int checkpoints_passed = -1;

    // game loop
    while (1) {
        // set thrust to maximum
        thrust = 100;
        
        //take input
        cin >> player.x >> player.y >> next_checkpoint.x >> next_checkpoint.y >> next_checkpoint_dist >> next_checkpoint_angle; cin.ignore();

        cin >> opponent.x >> opponent.y; cin.ignore();

        if (last_checkpoint.x != next_checkpoint.x || last_checkpoint.y != next_checkpoint.y)
        {
            checkpoints_passed++;
        }
        last_checkpoint = next_checkpoint;
        // calculate point between center of the play area and checkpoint thats 500 units away from checkpoint and set it as target
        if (checkpoints_passed > 0)
        {
            vector2D tgt_vector = vec(center_of_map, next_checkpoint);
            tgt_vector.magnitude = max(0.0, tgt_vector.magnitude-500);
            next_checkpoint = cord_from_vec(center_of_map, tgt_vector);
        }
        // lower thrust when pointing away from target
        for (int i = 0; i < power_angls.size(); i++)
        {
            if (abs(next_checkpoint_angle) >= power_angls.at(i))
            {
                thrust = thrust_levels.at(i);
            }
        }
        //calculate momentum and target vectors
        vector2D player_velocity_vector = vec(last_player_position, player);
        vector2D opponent_velocity_vector = vec(last_opponent_position, opponent);
        vector2D target_velocity_vector = vec(last_player_position, next_checkpoint);

        if(player_velocity_vector.magnitude>400 && next_checkpoint_dist < 2500 && false)
        {
            thrust = 30;
        }

        cerr << player_velocity_vector.magnitude << endl;

        if (boosts > 0 && next_checkpoint_dist >= minimum_boost_distance && abs(next_checkpoint_angle) <= minimum_boost_angle && round >= 0)
        {
            cout << next_checkpoint.x << " " << next_checkpoint.y << " " << "BOOST" << endl;
            boosts --;
        }
        else if (round == 1)
        {
            cout << next_checkpoint.x << " " << next_checkpoint.y << " " << thrust << endl;
        }
        
        else
        {
            //cout << next_checkpoint.x << " " << next_checkpoint.y << " " << thrust << endl;   // always steer toward target
            cout <<  player.x + int((target_velocity_vector.x + (target_velocity_vector.x - player_velocity_vector.x))*next_checkpoint_dist) << " " << player.y + int((target_velocity_vector.y + (target_velocity_vector.y - player_velocity_vector.y))*next_checkpoint_dist) << " " << thrust << endl; // point movement vector toward target
        }
        //end of round constants
        round++;
        last_player_position = player;
        last_opponent_position = opponent;
    }
}
