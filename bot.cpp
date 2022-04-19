#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// struct for holding a coordinate
struct coordinate {
    int x;
    int y;
};

// struct for holding a vector tarting from 0,0
struct vector2D {
    double x;
    double y;
    double magnitude;
};

// function for finding distnce betweentwo objects
double distance(coordinate a, coordinate b)
{
    int x = (a.x-b.x);
    int y = (a.y-b.y);
    return(sqrt((x*x+y*y)));
}

// function for finding vector from one object to another
vector2D vec(coordinate from, coordinate to)
{
    float angle = atan2(to.y - from.y, to.x-from.x);
    vector2D vector = {(cos(angle)), (sin(angle)), distance(from, to)};

    return(vector);
}

// function for adding a vector to a coordinate.
coordinate cord_from_vec(coordinate from, vector2D vec)
{
    from.x += int (vec.x * vec.magnitude);
    from.y += int (vec.y * vec.magnitude);
    return from;
}

int main()
{
    vector<int> power_angls = {85, 100};
    vector<int> thrust_levels = {40, 0};
    int minimum_boost_distance = 5500;
    int minimum_boost_angle = 2;

    const coordinate center_of_map = {8000, 4500};
    coordinate player;
    coordinate last_player_position;
    coordinate last_opponent_position;
    coordinate opponent;
    coordinate next_checkpoint;
    coordinate last_checkpoint;
    vector2D tgt_vector;
    vector2D player_velocity_vector;
    vector2D opponent_velocity_vector;
    vector2D target_velocity_vector;
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

        //if checkpoint has changed, increase passed checkpoints
        if (last_checkpoint.x != next_checkpoint.x || last_checkpoint.y != next_checkpoint.y)
        {
            checkpoints_passed++;
        }

        // calculate point between center of the play area and checkpoint thats 500 units away from checkpoint and set it as target
        if (checkpoints_passed > 0)
        {
            tgt_vector = vec(center_of_map, next_checkpoint);
            tgt_vector.magnitude = max(0.0, tgt_vector.magnitude-500);
            next_checkpoint = cord_from_vec(center_of_map, tgt_vector);
        }

        //calculate momentum and target vectors
        player_velocity_vector = vec(last_player_position, player);
        opponent_velocity_vector = vec(last_opponent_position, opponent);
        target_velocity_vector = vec(last_player_position, next_checkpoint);

        // lower thrust when pointing away from target
        for (int i = 0; i < power_angls.size(); i++)
        {
            if (abs(next_checkpoint_angle) >= power_angls.at(i))
            {
                thrust = thrust_levels.at(i);
            }
        }

        // lower thrust if near a checkpoint and speed is high
        if(player_velocity_vector.magnitude>400 && next_checkpoint_dist < 1000 && true)
        {
            thrust = 30;
        }

        // print out speed
        cerr << "speed: " << player_velocity_vector.magnitude << endl;

        //determine mode of movement for the round
        if (boosts > 0 && next_checkpoint_dist >= minimum_boost_distance && abs(next_checkpoint_angle) <= minimum_boost_angle && round >= 0)
        {
            // if pointed toward next cp and boosts are available, boost
            cout << next_checkpoint.x << " " << next_checkpoint.y << " " << "BOOST" << endl;
            boosts --;
        }
        else if (round == 1)
        {
            //if its the first round move to next checkpoint
            cout << next_checkpoint.x << " " << next_checkpoint.y << " " << thrust << endl;
        }
        
        else
        {
            // if no special cases apply point the movement vector toward the next checkpoint
            //cout << next_checkpoint.x << " " << next_checkpoint.y << " " << thrust << endl;   // always steer toward target
            cout <<  player.x + int((target_velocity_vector.x + (target_velocity_vector.x - player_velocity_vector.x))*next_checkpoint_dist) << " " << player.y + int((target_velocity_vector.y + (target_velocity_vector.y - player_velocity_vector.y))*next_checkpoint_dist) << " " << thrust << endl; // point movement vector toward target
        }

        //end of round actions
        round++;
        last_player_position = player;
        last_opponent_position = opponent;
        last_checkpoint = next_checkpoint;
    }
}
