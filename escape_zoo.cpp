#include "escape_zoo.h"
#include <iostream>
#include <queue>
#include <deque>
#include <string>



using namespace std;

bool is_edge(grid const &M, coordinate C)
{

    int rows = M.size();
    int cols = M[0].size();

    vector<pair<int, int>> edgeArray;

    for (int i = 0; i < cols; i++)
    {
        if (M[0][i] == 0) //if the top row (one of the secape routes) is open
        {
            edgeArray.push_back(make_pair(0, i)); //add the index to the vector of paris
        }
        else if (M[rows - 1][i] == 0) //bottom row
        {
            edgeArray.push_back(make_pair(rows - 1, i)); //add index to vector of pairs
        }
    }
    for (int j = 0; j < rows; j++)
    {
        if (M[j][0] == 0)
        {
            edgeArray.push_back(make_pair(j, 0));
        }
        else if (M[j][cols - 1] == 0)
        {
            edgeArray.push_back(make_pair(j, cols - 1));
        }
    }

    for (int i = 0; i < edgeArray.size(); i++)
    {
        if (C.first == edgeArray[i].first && C.second == edgeArray[i].second)
        {
            //cout << "Coordinate: (" << C.first << "," << C.second << " ) is an escapable edge" << endl;
            return true;
        }
    }
    //cout << "Coordinate: (" << C.first << "," << C.second << " ) is not an escapable edge" << endl;
    return false;
}

struct info
{
    vector<Action> MP;
    coordinate X;
    int distance;
    Heading H;
    info() {}
    info(coordinate X, int distance, Heading H, vector<Action> MP) //constructor
    {
        this->MP = {};
        this->X = X;
        this->distance = distance;
        this->H = H;
    }
};
/*
motion_plan escape_route(grid const &M, coordinate init_coordinate, Heading init_heading)
{
    coordinate curr = init_coordinate;
    int rows = M.size();
    int cols = M[0].size();

    //setting all locations to not visited (0)
    bool visited[rows][cols];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            visited[i][j] = {0};
        }
    }
    motion_plan MP = {};
    visited[init_coordinate.second][init_coordinate.first] = 1;

    info start(init_coordinate, 0, init_heading, MP);
    queue<info> q;
    q.push(start);
    vector<queue<info>> Actions = {};

    Actions.push_back(q);

    if (is_edge(M, init_coordinate))
    {
        cout << "escaped before loop" << endl;
        return Actions.front().front().MP;
    }

    while (!Actions.empty()) //might need to keep track of the heading each time we move b/c if we end up in the same node with the same heading that means we are in a loop
    {

        if (is_edge(M, Actions.front().front().X))
        {
            cout << "escaped weird !!" << endl;
            //cout<<"size of MP: "<<MP.size()<<endl;
            //for (int i = 0; i < Actions.front().front().MP.size(); i++)
            //{
            //    cout<<Actions.front().front().MP[i]<<endl;
            //}
            motion_plan Action_MP = Actions.front().front().MP;
            for (int i = 0; i < Action_MP.size(); i++)
            {
                cout << "movements are: " << Action_MP[i] << endl;
            }
            return Actions.front().front().MP;
            //break;
        }

        //cout<<"queue size at beging of while loop is: "<<q.size()<<endl<<endl;
        //cout << "in while " << endl;
        if (Actions.front().front().H == North) //if pointed north
        {
            if (M[Actions.front().front().X.first - 1][Actions.front().front().X.second] == 0 && visited[Actions.front().front().X.first - 1][Actions.front().front().X.second] == 0) //if forward neigboor is open
            {
                if (is_edge(M, Actions.front().front().X))
                {
                    cout << "escaped 2 !!" << endl;
                    return Actions.front().front().MP;
                    //break;
                }

                int distacne = Actions.front().front().distance; //get the distacne of current node)

                coordinate N;
                N.first = Actions.front().front().X.first - 1;
                N.second = Actions.front().front().X.second;

                motion_plan new_MP = Actions.front().front().MP;

                new_MP.push_back(go_straight);
                //new_MP.push_back(go_straight);
                //new_MP.push_back(go_left);

                cout<<"size of MP after push is: "<<new_MP.size()<<endl;

                info curr(N, distacne + 1, North, new_MP);
                visited[Actions.front().front().X.first - 1][Actions.front().front().X.second] = 1;
                queue<info> new_q;
                new_q.push(curr);
                Actions.push_back(new_q);
                cout << "facing north moving forward" << endl;
                
                motion_plan Action_MP = Actions.front().front().MP;
                //cout<<"size of MP in north is: "<<Action_MP.size()<<endl;
                for (int i = 0; i < new_MP.size(); i++)
                {
                    cout << "movements are: " << new_MP[i] << endl;
                }

            }
            if (M[Actions.front().front().X.first][Actions.front().front().X.second - 1] == 0 && visited[Actions.front().front().X.first][Actions.front().front().X.second - 1] == 0) //if left neighboor is open
            {
                if (is_edge(M, Actions.front().front().X))
                {
                    cout << "escaped 3!!" << endl;
                    return Actions.front().front().MP;
                    //break;
                }
                int distance = Actions.front().front().distance;

                coordinate N;

                N.first = Actions.front().front().X.first;
                N.second = Actions.front().front().X.second - 1;

                motion_plan new_MP = Actions.front().front().MP;

                new_MP.push_back(go_left);
                info curr(N, distance + 1, West, new_MP);
                visited[Actions.front().front().X.first][Actions.front().front().X.second - 1] = 1;

                queue<info> new_q;
                new_q.push(curr);
                Actions.push_back(new_q);
                cout << "facing North moving left" << endl;
            }
                
                for (int i = 0; i < Actions.size(); i++)
                {
                    cout << "movements before pop are: " << Actions[i].front().distance << endl;
                }
                
            //cout<<"size of actions before pop: "<<Actions.size()<<endl;

            Actions.erase(Actions.begin());
                /*
                for (int i = 0; i < Actions.size(); i++)
                {
                    cout << "movements after pop are: " << Actions[i].front().MP.size() << endl;
                }
                
            //cout<<"size of actions after pop: "<<Actions.size()<<endl;

        }

        else if (Actions.front().front().H == West) //if pointed west
        {
            //visit neighboor north and west
            if (M[Actions.front().front().X.first][Actions.front().front().X.second - 1] == 0 && visited[Actions.front().front().X.first][Actions.front().front().X.second - 1] == 0) //if forward neighboor is open (moving west)
            {
                if (is_edge(M, Actions.front().front().X))
                {
                    cout << "escaped 4 !!" << endl;
                    return Actions.front().front().MP;
                    //break;
                }
                int distance = Actions.front().front().distance;
                coordinate N;
                N.first = Actions.front().front().X.first;
                N.second = Actions.front().front().X.second - 1;
                motion_plan new_MP = Actions.front().front().MP;
                new_MP.push_back(go_straight);
                info curr(N, distance + 1, West, new_MP);
                visited[Actions.front().front().X.first][Actions.front().front().X.second - 1] = 1;

                queue<info> new_q;
                new_q.push(curr);
                Actions.push_back(new_q);

                cout << "facing west moving forward" << endl;
            }
            if (M[Actions.front().front().X.first + 1][Actions.front().front().X.second] == 0 && visited[Actions.front().front().X.first + 1][Actions.front().front().X.second] == 0) //if Left neighboor is open (south)
            {
                if (is_edge(M, Actions.front().front().X))
                {
                    cout << "escaped 5 !!" << endl;
                    return Actions.front().front().MP;
                    //break;
                }
                int distance = Actions.front().front().distance;
                coordinate N;
                N.first = Actions.front().front().X.first + 1;
                N.second = Actions.front().front().X.second;
                motion_plan new_MP = Actions.front().front().MP;
                new_MP.push_back(go_left);
                info curr(N, distance + 1, South, new_MP);
                visited[Actions.front().front().X.first - 1][Actions.front().front().X.second] = 1;

                queue<info> new_q;
                new_q.push(curr);
                Actions.push_back(new_q);

                cout << "facing west moving left" << endl;
            }
            Actions.erase(Actions.begin());
        }

        else if (Actions.front().front().H == South)
        {
            if (M[Actions.front().front().X.first + 1][Actions.front().front().X.second] == 0 && visited[Actions.front().front().X.first + 1][Actions.front().front().X.second] == 0) //if south neigboor is open (go straight)
            {
                if (is_edge(M, Actions.front().front().X))
                {
                    cout << "escaped 6 !!" << endl;
                    return Actions.front().front().MP;
                    //break;
                }
                int distance = Actions.front().front().distance;
                coordinate N;
                N.first = Actions.front().front().X.first + 1;
                N.second = Actions.front().front().X.second;
                motion_plan new_MP = Actions.front().front().MP;
                new_MP.push_back(go_straight);
                info curr(N, distance + 1, South, new_MP);
                visited[Actions.front().front().X.first + 1][Actions.front().front().X.second] = 1;

                queue<info> new_q;
                new_q.push(curr);
                Actions.push_back(new_q);

                cout << "facing South moving forward" << endl;
            }

            if (M[Actions.front().front().X.first][Actions.front().front().X.second + 1] == 0 && visited[Actions.front().front().X.first][Actions.front().front().X.second + 1] == 0) //if East neighboor is open
            {
                if (is_edge(M, Actions.front().front().X))
                {
                    cout << "escaped 7 !!" << endl;
                    return Actions.front().front().MP;
                    //break;
                }
                int distance = Actions.front().front().distance;
                coordinate N;
                N.first = Actions.front().front().X.first;
                N.second = Actions.front().front().X.second + 1;
                motion_plan new_MP = Actions.front().front().MP;
                new_MP.push_back(go_left);
                info curr(N, distance + 1, East, new_MP);
                visited[Actions.front().front().X.first][Actions.front().front().X.second + 1] = 1;

                queue<info> new_q;
                new_q.push(curr);
                Actions.push_back(new_q);

                cout << "facing south moving left" << endl;
            }
            Actions.erase(Actions.begin());
        }
        else if (Actions.front().front().H == East)
        {
            if (M[Actions.front().front().X.first - 1][Actions.front().front().X.second] == 0 && visited[Actions.front().front().X.first - 1][Actions.front().front().X.second] == 0) //if North Neighboor is open (going up moving left)
            {
                if (is_edge(M, Actions.front().front().X))
                {
                    cout << "escaped 8 !!" << endl;
                    return Actions.front().front().MP;
                    //break;
                }
                int distance = Actions.front().front().distance;
                coordinate N;
                N.first = Actions.front().front().X.first - 1;
                N.second = Actions.front().front().X.second;
                motion_plan new_MP = Actions.front().front().MP;
                new_MP.push_back(go_left);
                info curr(N, distance + 1, North, new_MP);
                visited[Actions.front().front().X.first - 1][Actions.front().front().X.second] = 1;

                queue<info> new_q;
                new_q.push(curr);
                Actions.push_back(new_q);

                cout << "facing east moving left" << endl;
            }

            if (M[Actions.front().front().X.first][Actions.front().front().X.second + 1] == 0 && visited[Actions.front().front().X.first][Actions.front().front().X.second + 1] == 0) //if east neighboor is open (moving forward still east )
            {
                if (is_edge(M, Actions.front().front().X))
                {
                    cout << "escaped 9 !!" << endl;
                    return Actions.front().front().MP;
                    //break;
                }
                int distance = Actions.front().front().distance;
                coordinate N;
                N.first = Actions.front().front().X.first;
                N.second = Actions.front().front().X.second + 1;
                motion_plan new_MP = Actions.front().front().MP;
                new_MP.push_back(go_straight);
                info curr(N, distance + 1, East, new_MP);
                visited[Actions.front().front().X.first][Actions.front().front().X.second + 1] = 1;

                queue<info> new_q;
                new_q.push(curr);
                Actions.push_back(new_q);

                cout << "facing east moving forward" << endl;
                //direction East
            }
            Actions.erase(Actions.begin());
        }

        cout << "queue size before pop is: " << q.size() << endl;
    }

    //cout<<"end of function"<<endl;
    cout << "No path" << endl;
    motion_plan E = {};
    return E;
}

//idea find all places on the edge of the grid that are open and use dijkstras
//algorithm on all of them and see which one has the shortest path

bool legal_path_to_node(coordinate current_location, info node_info)
{
    if (node_info.MP.size() == 0)
        return 0;
    coordinate legal_straight;
    coordinate legal_left;
    if (node_info.H == North)
    {

        legal_straight.first = node_info.X.first - 1;
        legal_straight.second = node_info.X.second;

        legal_left.first = node_info.X.first;
        legal_left.second = node_info.X.second - 1;
    }
    else if (node_info.H == West)
    {
        legal_straight.first = node_info.X.first;
        legal_straight.second = node_info.X.second - 1;

        legal_left.first = node_info.X.first + 1;
        legal_left.second = node_info.X.second;
    }
    else if (node_info.H == South)
    {
        legal_straight.first = node_info.X.first + 1;
        legal_straight.second = node_info.X.second;

        legal_left.first = node_info.X.first;
        legal_left.second = node_info.X.second + 1;
    }
    else //East case
    {
        legal_straight.first = node_info.X.first;
        legal_straight.second = node_info.X.second + 1;

        legal_left.first = node_info.X.first - 1;
        legal_left.second = node_info.X.second;
    }
    bool straight_match = current_location.first == legal_straight.first && current_location.second == legal_straight.second;
    bool left_match = current_location.first == legal_left.first && current_location.second == legal_left.second;
    if (straight_match || left_match)
        return true;
    else
        return false;
}



*/
//matrix of integers



vector<vector<int>> make_matrix(grid const &M)
{
    std::vector<std::vector<int>> Matrix;
    int rows = M.size();
    int cols = M[0].size();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if ( M[i][j] == 1) //can't move there 
                Matrix[i][j] = -2;
            else if (M[i][j] == 0)
                Matrix[i][j] = 0;
        }
    }
}

coordinate Check_orientation(Heading orientation, coordinate Cord)
{
            coordinate C;
            if (orientation == North)
            {
                C.first = Cord.first - 1;
                C.second = Cord.second;
                return C;
            }
            else if (orientation == West)
            {
                C.first = Cord.first;
                C.second = Cord.second -1;
                return C;
            }
            else if (orientation == South)
            {
                C.first = Cord.first +1;
                C.second = Cord.second;
                return C;
            }
            else 
            {
                C.first = Cord.first;
                C.second = Cord.second + 1;
                return C;
            }
}

motion_plan escape(vector<vector<int>> matrix, coordinate Cord ,Heading orientation,motion_plan movement)
{

    int rows = matrix.size();
    int cols = matrix[0].size();
    

    if (matrix[Cord.first][Cord.second] == -1);
        return movement;
    if (matrix[Cord.first][Cord.second] == -2)
        return movement;

    if (matrix[Cord.first][Cord.second]!= 0);
        return movement;
    if (matrix[Cord.first][Cord.second] ==0);
        //check if up is going out //escape
    if (Cord.first +1  > rows || Cord.second +1 > cols || Cord.first -1 < 0 || Cord.second - 1 < 0)
             matrix[Cord.first][Cord.second] = 1;
        //else:escape(matrix,up_corid,up_heading,motion_plan)
     else 
        {
                //changing his code here 
            escape(matrix, Check_orientation(orientation, Cord) , orientation, movement);
        }

        coordinate straight = Check_orientation(orientation, Cord); // up = matrix[coordinate up]
        matrix[up cord ] = -1
//left

        //check if left going out:;
        if (Cord.first +1  > rows || Cord.second +1 > cols || Cord.first -1 < 0 || Cord.second - 1 < 0)
        {
        //matrx[coordinate] =1

        }
        else escape(matrix,left_corid,left_heading,motion_plan)
            left = matx[cordi]_-left]
        pick min from up and left and put it at matrix[Cord]
        add(direction in motion plan returned by the min value escape according to which one is minimum)
        return motion plan


}       
motion_plan escape_route(grid const &M, coordinate init_coordinate, Heading init_heading)
{
    vector<vector<int>> matrix = make_matrix(M);
    motion_plan init_motion_plan = {};
    escape(matrix, init_coordinate, init_heading, init_motion_plan);

}



int main()
{
    grid zoo = {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {1, 0, 0, 1}

    };
    //cout<<zoo[2][3]<<endl;
    coordinate C;
    C.first = 4;
    C.second = 2;

    Heading N = North;
    //cout<<zoo[1][0]<<endl;
    //cout<<C.first<<","<<C.second<<endl;
    //cout<<zoo[1].size()<<endl;
    //cout<<zoo[6][100]<<endl;
    //is_edge(zoo,C);
    motion_plan path;
    path = escape_route(zoo, C, North);
    //cout<<"size is: "<<path.size()<<endl;
    //path[0];
    //BFS(zoo, C, N);
}
