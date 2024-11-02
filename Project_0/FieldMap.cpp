#include "FieldMap.h"
#include <iostream>
#include <cmath>
using namespace std;


// Constructor definition
FieldMap::FieldMap() {
    N_rows = 0;
    M_columns = 0;
    grid_array = nullptr;
    K = 1.0;
    goals_array = nullptr;
    obstacles_array = nullptr;
    goal_count = 0;
    obstacle_count = 0;
}


// Destructor definition
FieldMap::~FieldMap() {
    if (grid_array) {
        for (int i = 0; i < N_rows; i++) {
            delete[] grid_array[i];   // Rows freed
        }
        delete[] grid_array;    // Pointers array freed and set to nullptr
        grid_array = nullptr;
    }

    if (goals_array) {
        for (int i = 0; i < N_rows * M_columns; i++) {
            delete[] goals_array[i];    // Coordinates freed
        }
        delete[] goals_array;      // Array of goals freed and set to nullptr
        goals_array = nullptr;
    }

    if (obstacles_array) {
        for (int i = 0; i < N_rows * M_columns; i++) {
            delete[] obstacles_array[i];    // Coordinates freed
        }
        delete[] obstacles_array;      // Array of obstacles freed and set to nullptr
        obstacles_array = nullptr;
    }
}


void FieldMap::potential_value_calculator() {   // Helper function
    double potential_value = 0.0;

    // Calculate potential value at all cells
    for (int i = 0; i < N_rows; i++) {
        for (int j = 0; j < M_columns; j++) {
            double potential_value = 0.0;   // Reset potential value for current cell

            // Effect from goals on potential
            for (int goal = 0; goal < goal_count; goal++) {
                double denominator = sqrt(pow(j - goals_array[goal][1], 2) + pow(i - goals_array[goal][0], 2));

                if (denominator != 0) {
                    potential_value -= K / denominator;
                }
            }
            
            // Effect from obstacles on potential
            for (int obstacle = 0; obstacle < obstacle_count; obstacle++) {
                double denominator = sqrt(pow(j - obstacles_array[obstacle][1], 2) + pow(i - obstacles_array[obstacle][0], 2));

                if (denominator != 0) {
                    potential_value += K / denominator;
                }
            }

            grid_array[i][j] = potential_value; // Current cell is set to newly calculated potential value
        }
    }
}


void FieldMap::create_field(int N, int M) {
    N_rows = N;
    M_columns = M;

    // Create grid as 2D array
    grid_array = new double*[N_rows];   // Array of pointers for each row

    for (int i = 0; i < N_rows; i++) {
        grid_array[i] = new double[M_columns];  // Each row is the length of the number of columns

        for (int j = 0; j < M_columns; j++) {
            grid_array[i][j] = 0.0;    // Set all potential vector values to 0.0
        }
    }

    // Create dynamic array for goals and obstacles
    goal_count = 0;
    obstacle_count = 0;
    goals_array = new int*[N_rows*M_columns];
    obstacles_array = new int*[N_rows*M_columns];

    for (int i = 0; i < (N_rows*M_columns); i++) {    // 2 elements per cell for coordinate (x,y)
        goals_array[i] = new int[2];
        obstacles_array[i] = new int[2];
    }
}


bool FieldMap::insert_point(char T, int X, int Y) {
    if ((X >= 0) && (X < N_rows) && (Y >= 0) && (Y < M_columns)) {  // insert the Goal/Obstacle if (X,Y) is in the bounds
        if (T == 'G') {
            grid_array[X][Y] = 1.0;         // G (goal) = 1.0
            goals_array[goal_count][0] = X;
            goals_array[goal_count][1] = Y;
            goal_count++;
            potential_value_calculator();   // Recalculate potential values for all other points
            return true;
        }
        else if (T == 'O') {
            grid_array[X][Y] = 2.0;         // O (obstacle)= 2.0
            obstacles_array[obstacle_count][0] = X;
            obstacles_array[obstacle_count][1] = Y;
            obstacle_count++;
            potential_value_calculator();   // Recalculate potential values for all other points
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;   // Coordinate out of bounds
    }
}


void FieldMap::move_robot(int X, int Y) {
    if ((X >= 0) && (X < N_rows) && (Y >= 0) && (Y < M_columns)) {  // (X,Y) is in the bounds then insert the Goal/Obstacle
        double current_potential_value = grid_array[X][Y];

        std::cout << current_potential_value << " " << current_potential_value << std::endl;
    }
    else {
        std::cout << "failure" << std::endl;
    }
}


bool FieldMap::clear() {
    if (grid_array) {
        for (int i = 0; i < N_rows; i++) {
            for (int j = 0; j < M_columns; j++){
                grid_array[i][j] = 0.0;
            }
        }

        goal_count = 0;
        obstacle_count = 0;

        return true;
    }
    else {
        return false;
    }
}


bool FieldMap::update(double new_K) {
    if (new_K > 0) {
        K = new_K;
        potential_value_calculator();
        return true;
    }
    else {
        return false;
    }
}
