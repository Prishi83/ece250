#ifndef FIELDMAP_H
#define FIELDMAP_H

// Class declaration
class FieldMap {
public:
    FieldMap();   // constructor
    ~FieldMap();  // Destructor (frees up dynamically allocated memory)

    void potential_value_calculator();
    void create_field(int N, int M);
    bool insert_point(char T, int X, int Y);
    void move_robot(int X, int Y);
    bool clear();
    bool update(double new_K);

private:
    int N_rows;            // Number of rows in grid
    int M_columns;         // Number of columns in grid
    double** grid_array;   // Dynamically allocated 2D array
    double K;              // Constant value used in potential value formula
    int** goals_array;     // (X,Y) coordinates for goals
    int** obstacles_array; // (X,Y) coordinates for obstacles
    int goal_count;        // Number of goals
    int obstacle_count;    // Number of obstacles
};

#endif