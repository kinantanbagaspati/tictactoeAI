#include<bits/stdc++.h>
using namespace std;

const int total = 19683;
int boardVal[total], bestMove[total], vis[total], pw3[9];

int isGameOver(int boardBit){
    int bit[9];
    int cek[8][3] = {
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6}};
    for(int i=0; i<9; i++){
        bit[i] = boardBit % 3;
        boardBit /= 3;
    }
    int result = 0;
    for(int i=0; i<8; i++){
        if(bit[cek[i][0]] == bit[cek[i][1]] && bit[cek[i][0]] == bit[cek[i][2]] && bit[cek[i][0]] > 0){
            result = bit[cek[i][0]];
        }
    }
    return result;
}

int nbMoves(int node){
    int cnt = 0;
    for(int i=0; i<9; i++){
        if(node%3>0){
            cnt++;
        }
        node /= 3;
    }
    return cnt;
}

void init(){
    for(int i=0; i<total; i++){
        boardVal[i] = 0;
        bestMove[i] = -1;
        vis[i] = false;
    }
    pw3[0] = 1;
    for(int i=1; i<9; i++){
        pw3[i] = pw3[i-1] * 3;
    }
}
int minimax(int node){
    int cnt = nbMoves(node);
    if(vis[node]){//Sudah pernah dihitung
        return boardVal[node];
    }
    vis[node] = true;
    //cek apabila leaf node
    if(isGameOver(node)>0){
        if(cnt%2 == 0){
            boardVal[node] = -10 +cnt;
        }else{
            boardVal[node] = 10 -cnt;
        }
        return boardVal[node];
    }
    if(cnt == 9){
        return 0;
    }
    //bukan leaf node
    int next, mul, cp = node;
    if(cnt%2==0){//Sekarang player 1 (maximize)
        boardVal[node] = -11;
        mul = 1;
        for(int i=0; i<9; i++){
            if(cp%3 == 0){
                if(minimax(node + mul) > boardVal[node]){
                    boardVal[node] = boardVal[node + mul];
                    bestMove[node] = i;
                }
            }
            cp /= 3;
            mul *= 3;
        }
    }else{ //Sekarang player 2 (minimize)
        boardVal[node] = 11;
        mul = 2;
        for(int i=0; i<9; i++){
            if(cp%3 == 0){
                if(minimax(node + mul) < boardVal[node]){
                    boardVal[node] = boardVal[node + mul];
                    bestMove[node] = i;
                }
            }
            cp /= 3;
            mul *= 3;
        }
    }
    return boardVal[node];
}

void print(int state){
    char square[3] = {' ','X','O'};
    for(int i=0; i<3; i++){
        if(i>0){
            for(int j=0; j<5; j++){
                cout << '-';
            }
            cout << endl;
        }
        for(int j=0; j<3; j++){
            if(j>0){
                cout << '|';
            }
            cout << square[state%3];
            state /= 3;
        }
        cout << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    init();
    minimax(0);
    int player, mv, state = 0;
    cout << "Pick player (1/2):" << endl;
    cin >> player;
    for(int i=0; i<9 && isGameOver(state)==0; i++){
        cout << state << endl;
        print(state);
        if(i%2 +1 == player){//Player Move
            cout << "Pick an empty square (0-8):" << endl;
            cin >> mv;
            state += player * pw3[mv];
        }else{
            cout << "Bot move: " << bestMove[state] << endl;
            state += (player%2 + 1)*pw3[bestMove[state]];
        }
    }

}

