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

    // Kulelerin başlangıç durumunu oluşturalım
    for (int i = 0; i < DISK_NUMBER; i++) {
        state->rodA[i] = DISK_NUMBER - i; // Büyük diskler altta, küçük diskler üstte
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
/*
//______________________________________________________________________________
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model)
{
    State new_state = *parent_state;

    // Hareketi gerçekleştirelim
    int disk;
    switch (action) {
        case Move_A_to_B:
            for (disk = 0; disk < DISK_NUMBER; disk++) {
                if (parent_state->rodA[disk] != 0) {
                    break;
                }
            }
            if (disk == DISK_NUMBER) return FALSE; // A'da disk yok
            for (int i = DISK_NUMBER - 1; i >= 0; i--) {
                if (new_state.rodB[i] == 0) {
                    new_state.rodB[i] = parent_state->rodA[disk];
                    new_state.rodA[disk] = 0;
                    break;
                }
            }
            break;
        case Move_A_to_C:
            for (disk = 0; disk < DISK_NUMBER; disk++) {
                if (parent_state->rodA[disk] != 0) {
                    break;
                }
            }
            if (disk == DISK_NUMBER) return FALSE; // A'da disk yok
            for (int i = DISK_NUMBER - 1; i >= 0; i--) {
                if (new_state.rodC[i] == 0) {
                    new_state.rodC[i] = parent_state->rodA[disk];
                    new_state.rodA[disk] = 0;
                    break;
                }
            }
            break;
        case Move_B_to_A:
            for (disk = 0; disk < DISK_NUMBER; disk++) {
                if (parent_state->rodB[disk] != 0) {
                    break;
                }
            }
            if (disk == DISK_NUMBER) return FALSE; // B'de disk yok
            for (int i = DISK_NUMBER - 1; i >= 0; i--) {
                if (new_state.rodA[i] == 0) {
                    new_state.rodA[i] = parent_state->rodB[disk];
                    new_state.rodB[disk] = 0;
                    break;
                }
            }
            break;
        case Move_B_to_C:
            for (disk = 0; disk < DISK_NUMBER; disk++) {
                if (parent_state->rodB[disk] != 0) {
                    break;
                }
            }
            if (disk == DISK_NUMBER) return FALSE; // B'de disk yok
            for (int i = DISK_NUMBER - 1; i >= 0; i--) {
                if (new_state.rodC[i] == 0) {
                    new_state.rodC[i] = parent_state->rodB[disk];
                    new_state.rodB[disk] = 0;
                    break;
                }
            }
            break;
        case Move_C_to_A:
            for (disk = 0; disk < DISK_NUMBER; disk++) {
                if (parent_state->rodC[disk] != 0) {
                    break;
                }
            }
            if (disk == DISK_NUMBER) return FALSE; // C'de disk yok
            for (int i = DISK_NUMBER - 1; i >= 0; i--) {
                if (new_state.rodA[i] == 0) {
                    new_state.rodA[i] = parent_state->rodC[disk];
                    new_state.rodC[disk] = 0;
                    break;
                }
            }
            break;
        case Move_C_to_B:
            for (disk = 0; disk < DISK_NUMBER; disk++) {
                if (parent_state->rodC[disk] != 0) {
                    break;
                }
            }
            if (disk == DISK_NUMBER) return FALSE; // C'de disk yok
            for (int i = DISK_NUMBER - 1; i >= 0; i--) {
                if (new_state.rodB[i] == 0) {
                    new_state.rodB[i] = parent_state->rodC[disk];
                    new_state.rodC[disk] = 0;
                    break;
                }
            }
            break;
    }

    trans_model->new_state = new_state;
    trans_model->step_cost = 1; // Her adımda maliyeti 1 olarak belirleyelim

    return TRUE;
}
*/
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model) {
    State new_state = *parent_state;
    // Hareketi gerçekleştirelim
    int disk_to_move_index = -1;
    int target_rod_index = -1;

    // Hedef çubuktaki en küçük diski bul
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
    trans_model->step_cost = 1; // Her adımda maliyeti 1 olarak belirleyelim

    return TRUE;
}

// Hedef çubuktaki en küçük boş indisi bul
int FindTargetRodIndex(int rod[]) {
    for (int i =0; i < DISK_NUMBER; i++) {
        if (rod[i] == 0) {
            return i;
        }
    }
    return -1; // Boş yer yok
}
int FindDiskToMoveIndex(int rod[]) {
    for (int i = DISK_NUMBER - 1; i >=0 ; i--) {
        if (rod[i] != 0) {
            return i;
        }
    }
    return -1; // Boş yer yok
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
            // Hedef çubuktaki en üst disk boyutunu kontrol et
            if (state->rodC[target_rod_index - 1] < state->rodA[disk_to_move_index]) {
                return 0; // Geçersiz hareket, büyük disk üzerine küçük disk
            }
            break;
        case Move_B_to_A:
            // Hedef çubuktaki en üst disk boyutunu kontrol et
            if (state->rodA[target_rod_index  - 1 ] < state->rodB[disk_to_move_index]) {
                return 0; // Geçersiz hareket, büyük disk üzerine küçük disk
            }
            break;
        case Move_B_to_C:
            // Hedef çubuktaki en üst disk boyutunu kontrol et
            if (state->rodC[target_rod_index - 1] < state->rodB[disk_to_move_index]) {
                return 0; // Geçersiz hareket, büyük disk üzerine küçük disk
            }
            break;
        case Move_C_to_A:
            // Hedef çubuktaki en üst disk boyutunu kontrol et
            if (state->rodA[target_rod_index - 1] < state->rodC[disk_to_move_index]) {
                return 0; // Geçersiz hareket, büyük disk üzerine küçük disk
            }
            break;
        case Move_C_to_B:
            // Hedef çubuktaki en üst disk boyutunu kontrol et
            if (state->rodB[target_rod_index - 1] < state->rodC[disk_to_move_index]) {
                return 0; // Geçersiz hareket, büyük disk üzerine küçük disk
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
    // Burada herhangi bir tutarlı bir sezgisel tahmin hesaplaması yapabilirsiniz.
    // Ancak, Hanoi kuleleri problemi için basit bir tahmin olarak hamle sayısını kullanabiliriz.
    // Çünkü her hamlede bir disk hareket ettiriliyor ve hedef duruma ulaşmak için en fazla
    // 2^n - 1 adım gerekir, n disk sayısı.
    // Bu tahminin admissible olduğu ve herhangi bir durumu asla aşırı tahmin etmeyeceği garanti edilir.

    // En fazla adım sayısını döndürelim
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
