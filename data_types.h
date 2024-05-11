//
// Created by Enes Bilik on 11.05.2024.
//

#ifndef DATA_TYPES_H
#define DATA_TYPES_H



// ==================== WRITE YOUR OPTIONAL DATA TYPES IF YOU NEED =============

// ====== WRITE YOUR COMPULSORY (BUT SPECIFIC TO THE PROBLEM) DATA TYPES =======

enum ACTIONS // All possible actions
{
     Move_A_to_B,
     Move_A_to_C,
     Move_B_to_A,
     Move_B_to_C,
     Move_C_to_A,
     Move_C_to_B
};

typedef struct State
{
    int rodA[3]; //disk sayısı
     int rodB[3];
    int rodC[3];
    float h_n;

} State;

// ================== YOU DO NOT NEED TO CHANGE THIS PART ======================

enum METHODS
{
    BreastFirstSearch = 1,
    UniformCostSearch = 2,
    DepthFirstSearch = 3,
    DepthLimitedSearch = 4,
    IterativeDeepeningSearch = 5,
    GreedySearch = 6,
    AStarSearch = 7,
    GeneralizedAStarSearch = 8
};

// This struct is used to determine a new state and action in transition model
typedef struct Transition_Model
{
    State new_state;
    float step_cost;
} Transition_Model;

typedef struct Node
{
    State state;
    float path_cost;
    enum ACTIONS action; // The action applied to the parent to generate this node
    struct Node *parent;
    int Number_of_Child; // required for depth-first search algorithms
} Node;

typedef struct Queue // Used for frontier
{
    Node *node;
    struct Queue *next;
} Queue;



#endif //DATA_TYPES_H
