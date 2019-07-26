//
//  main.cpp
//  EE299-lab3
//
//  Created by 朴世豪 on 2019/7/26.
//  Copyright © 2019年 朴世豪. All rights reserved.
//

#include <iostream>
using namespace std;

int board[4][4]={{9,1,0,1},
                 {5,5,5,5},
                 {0,0,1,2},
                 {0,0,0,10},
};
int life=1;
int player_psn[2]={3,2};

void display(int board[4][4],int plyer_psn[2])
{
    int flag;
    board[player_psn[0]][player_psn[1]]=-1;
    for(int j=0;j<4;++j)
    {//cout<<"--------------\n";
    for(int i=0;i<4;++i)
    {
        flag=board[j][i];
        
        switch (flag) {
            case 0:{
                cout<<' '<<' ';
                break;
            }
            case 1:{
                cout<<'*'<<' ';
                break;
            }
            case 2:{
                cout<<'X'<<' ';
                break;
            }
            case 5:{
                cout<<'.'<<' ';
                break;
            }
            case 9:{
                cout<<'>'<<' ';
                break;
            }
            case 10:{
                cout<<'>'<<' ';
                break;
            }
            case -1:{
                cout<<'@'<<' ';
                break;
            }
                
            default:
                break;
        }
        
        if(3==i)
            cout<<'\n';
       }
    }
    //cout<<"--------------\n";
    cout<<"LIFE: "<<life<<endl;
}
int main(int argc, const char * argv[]) {
    
    display(board,player_psn);
    
    return 0;
}
