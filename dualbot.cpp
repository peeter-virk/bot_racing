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
    int laps;
    cin >> laps; cin.ignore();
    int checkpoint_count;
    cin >> checkpoint_count; cin.ignore();

    coordinate tmp;
    vector<coordinate> targets = {};
    vector<coordinate> last_postitons = {tmp, tmp};
    for (int i = 0; i < checkpoint_count; i++) {
        cin >> tmp.x >> tmp.y; cin.ignore();
        targets.push_back(tmp);
    }

    // game loop
    while (1) {
        for (int i = 0; i < 2; i++) {
            coordinate player;
            int vx; // x speed of your pod
            int vy; // y speed of your pod
            int angle; // angle of your pod
            int next_check_point_id; // next check point id of your pod
            cin >> player.x >> player.y >> vx >> vy >> angle >> next_check_point_id; cin.ignore();

            vector2D v = vec(last_postitons.at(i), player);
            vector2D r = vec(last_postitons.at(i), targets.at(next_check_point_id));
            

            cout << player.x + int((r.x + (r.x - v.x))*distance(last_postitons.at(i), targets.at(next_check_point_id))) << " " << player.y + int((r.y + (r.y - v.y))*distance(last_postitons.at(i), targets.at(next_check_point_id))) << " " << 100 << endl;
            last_postitons.at(i) = player;
        }
        for (int i = 0; i < 2; i++) {
            int x_2; // x position of the opponent's pod
            int y_2; // y position of the opponent's pod
            int vx_2; // x speed of the opponent's pod
            int vy_2; // y speed of the opponent's pod
            int angle_2; // angle of the opponent's pod
            int next_check_point_id_2; // next check point id of the opponent's pod
            cin >> x_2 >> y_2 >> vx_2 >> vy_2 >> angle_2 >> next_check_point_id_2; cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // You have to output the target position
        // followed by the power (0 <= thrust <= 100)
        // i.e.: "x y thrust"
    }
}
