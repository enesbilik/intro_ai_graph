/*
    These functions are compulsory for search algorithms but they are specific
    to problems. More clearly, you must must update their blocks but do not change
    their input and output parameters.

    Also, you can add new functions at the end of file by declaring them in GRAPH_SEARCH.h
*/

#include "graph_search.h"
#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>

int FindTargetRodIndex(int rod[]);
int FindDiskToMoveIndex(int rod[]);
int IsValidMove(const State *const state, const enum ACTIONS action, int disk, int target_rod_index);
void MoveDisk(State *state, const enum ACTIONS action, int disk, int target_rod_index);


//______________________________________________________________________________
State *Create_State()
{
    State *state = (State *)malloc(sizeof(State));
    if (state == NULL)
        Warning_Memory_Allocation();

    for (int i = 0; i < DISK_NUMBER; i++) {
        state->rodA[i] = DISK_NUMBER - i;
        state->rodB[i] = 0;
        state->rodC[i] = 0;
    }

    return state;
}

void Print_State(const State *const state)
{
    printf("A: ");
    for (int i = 0; i < DISK_NUMBER; i++) {
        if (state->rodA[i] != 0) {
            printf("%d ", state->rodA[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");

    printf("B: ");
    for (int i = 0; i < DISK_NUMBER; i++) {
        if (state->rodB[i] != 0) {
            printf("%d ", state->rodB[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");

    printf("C: ");
    for (int i = 0; i < DISK_NUMBER; i++) {
        if (state->rodC[i] != 0) {
            printf("%d ", state->rodC[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

void Print_Action(const enum ACTIONS action)
{
    switch (action)
    {
        case Move_A_to_B:
            printf("Move disk from A to B\n");
        break;
        case Move_A_to_C:
            printf("Move disk from A to C\n");
        break;
        case Move_B_to_A:
            printf("Move disk from B to A\n");
        break;
        case Move_B_to_C:
            printf("Move disk from B to C\n");
        break;
        case Move_C_to_A:
            printf("Move disk from C to A\n");
        break;
        case Move_C_to_B:
            printf("Move disk from C to B\n");
        break;
    }
}
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model) {
    State new_state = *parent_state;
    int disk_to_move_index = -1;
    int target_rod_index = -1;

    switch (action) {
        case Move_A_to_B:
            disk_to_move_index = FindDiskToMoveIndex(new_state.rodA);
            target_rod_index = FindTargetRodIndex(new_state.rodB);
            break;
        case Move_A_to_C:
            disk_to_move_index = FindDiskToMoveIndex(new_state.rodA);

            target_rod_index = FindTargetRodIndex(new_state.rodC);
            break;
        case Move_B_to_A:
            disk_to_move_index = FindDiskToMoveIndex(new_state.rodB);

            target_rod_index = FindTargetRodIndex(new_state.rodA);
            break;
        case Move_B_to_C:
            disk_to_move_index = FindDiskToMoveIndex(new_state.rodB);

            target_rod_index = FindTargetRodIndex(new_state.rodC);

            break;
        case Move_C_to_A:
            disk_to_move_index = FindDiskToMoveIndex(new_state.rodC);

            target_rod_index = FindTargetRodIndex(new_state.rodA);
            break;
        case Move_C_to_B:
            disk_to_move_index = FindDiskToMoveIndex(new_state.rodC);

            target_rod_index = FindTargetRodIndex(new_state.rodB);
            break;
    }

    // Hareket geçerli mi kontrol et
    int isValidMove = IsValidMove(parent_state, action, disk_to_move_index, target_rod_index);

    if (!isValidMove) {
        return FALSE;
    }

    // Diski taşı
    MoveDisk(&new_state, action, disk_to_move_index, target_rod_index);

    trans_model->new_state = new_state;
    trans_model->step_cost = 1;

    return TRUE;
}

int FindTargetRodIndex(int rod[]) {
    for (int i =0; i < DISK_NUMBER; i++) {
        if (rod[i] == 0) {
            return i;
        }
    }
    return -1;
}
int FindDiskToMoveIndex(int rod[]) {
    for (int i = DISK_NUMBER - 1; i >=0 ; i--) {
        if (rod[i] != 0) {
            return i;
        }
    }
    return -1;
}
// Hareketin geçerli olup olmadığını kontrol et
int IsValidMove(const State *const state, const enum ACTIONS action, int disk_to_move_index, int target_rod_index) {
    if (disk_to_move_index == -1 || target_rod_index == -1)
        return 0;

    if (target_rod_index == 0) {
        return 1;
    }

    switch (action) {
        case Move_A_to_B:


            if (state->rodB[target_rod_index - 1] < state->rodA[disk_to_move_index]) {
                return 0; // Geçersiz hareket, büyük disk üzerine küçük disk
            }
            break;
        case Move_A_to_C:

            if (state->rodC[target_rod_index - 1] < state->rodA[disk_to_move_index]) {
                return 0;
            }
            break;
        case Move_B_to_A:

            if (state->rodA[target_rod_index  - 1 ] < state->rodB[disk_to_move_index]) {
                return 0;
            }
            break;
        case Move_B_to_C:
            if (state->rodC[target_rod_index - 1] < state->rodB[disk_to_move_index]) {
                return 0;
            }
            break;
        case Move_C_to_A:
            if (state->rodA[target_rod_index - 1] < state->rodC[disk_to_move_index]) {
                return 0;
            }
            break;
        case Move_C_to_B:
            if (state->rodB[target_rod_index - 1] < state->rodC[disk_to_move_index]) {
                return 0;
            }
            break;
    }
    return 1; // Geçerli hareket
}


/// Diski taşı
void MoveDisk(State *state, const enum ACTIONS action, int disk_to_move_index, int target_rod_index) {
    switch (action) {
        case Move_A_to_B:
            state->rodB[target_rod_index] = state->rodA[disk_to_move_index];
            state->rodA[disk_to_move_index] = 0;
        break;

        case Move_A_to_C:
            state->rodC[target_rod_index] = state->rodA[disk_to_move_index];
            state->rodA[disk_to_move_index] = 0;
        break;

        case Move_B_to_A:
            state->rodA[target_rod_index] = state->rodB[disk_to_move_index];
            state->rodB[disk_to_move_index] = 0;
        break;

        case Move_B_to_C:
            state->rodC[target_rod_index] = state->rodB[disk_to_move_index];
            state->rodB[disk_to_move_index] = 0;
        break;

        case Move_C_to_A:
            state->rodA[target_rod_index] = state->rodC[disk_to_move_index];
            state->rodC[disk_to_move_index] = 0;
        break;

        case Move_C_to_B:
            state->rodB[target_rod_index] = state->rodC[disk_to_move_index];
            state->rodC[disk_to_move_index] = 0;
        break;
    }
}


//______________________________________________________________________________
float Compute_Heuristic_Function(const State *const state, const State *const goal)
{
    // 2^n - 1 adım gerekir, n disk sayısı.
    // En fazla adım sayısını hesapladık.

    return (float)((1 << DISK_NUMBER) - 1);
}

//_______________ Update if your goal state is not determined initially ___________________________________
int Goal_Test(const State *const state, const State *const goal_state)
{
    if (PREDETERMINED_GOAL_STATE)
        return Compare_States(state, goal_state);
    else
        return 1;
}

// ==================== WRITE YOUR OPTIONAL FUNCTIONS (IF REQUIRED) ==========================
