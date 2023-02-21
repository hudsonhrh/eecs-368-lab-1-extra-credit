#include <stdio.h>
#include <stdbool.h>

int Combat(int dep, int dep_combat, int program_pref[5]){
    int dep_num=dep+1;
    int dep_combat_num=dep_combat+1;
    int index_dep=0;
    int index_dep_combat=0;
    for(int i=0; i<5;i++){
        if(program_pref[i]==dep_num){
            index_dep=i;
        }
        if(program_pref[i]==dep_combat_num){
            index_dep_combat=i;
        }
    }
    if(index_dep<index_dep_combat){
        return dep;
    } else{
        return dep_combat;
    }
}

int main(){

    FILE *input_file = fopen("input_file.txt", "r");

    int matrix[10][5];

    // Read the input file and populate the matrix
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            fscanf(input_file, "%d", &matrix[i][j]);
        }
    }

    // Separate the matrix into two parts
    int top_matrix[5][5];
    int bottom_matrix[5][5];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            top_matrix[i][j] = matrix[i][j];
            bottom_matrix[i][j] = matrix[i+5][j];
        }
    }

    fclose(input_file);

    int program_pref[5][5];
    int dep_pref[5][5];
    for(int i=0; i<5; i++){
        for(int x=0; x<5;x++){
            dep_pref[i][x]=top_matrix[x][i];
            program_pref[i][x]=bottom_matrix[x][i];
        }
    }

    int prog_match[5]={-1,-1,-1,-1,-1};
    int dep_match[5]={-1,-1,-1,-1,-1};

    while(true){
        bool flag=true;
        for(int i=0; i<5;i++){
            if(dep_match[i]==-1){
                flag=false;
                break;
            }
        }
        if(flag==true){
            break;
        }

        for(int i=0; i<5; i++){
            int dep=i;
            if(dep_match[dep]!=-1){
                continue;
            }
            bool flag_match=false;
            for(int x=0; x<5; x++){
                if(flag_match==true){
                    break;
                }
                int dep_prefernce=dep_pref[dep][x];
                int check_index=dep_prefernce-1;
                if(prog_match[check_index]==-1){
                    prog_match[check_index]=dep;
                    flag_match=true;
                    dep_match[dep]=check_index;
                } else{
                    int dep_combat=prog_match[check_index];
                    int winner=Combat(dep, dep_combat, program_pref[check_index]);
                    if(winner==dep){
                        flag_match=true;
                        dep_match[dep]=check_index;
                        dep_match[dep_combat]=-1;
                    }
                    prog_match[check_index]=winner;
                }
            }
        } 
    }

    for(int i=0; i<5; i++){
        printf("Department %d gets Programmer %d\n", i+1, dep_match[i]+1);
    }

    return 0;
}
