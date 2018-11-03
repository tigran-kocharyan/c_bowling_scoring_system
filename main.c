#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <unistd.h> 
 
int main ()
{
    int players; //the number of players
    int current=0; //who currently throws a ball
    int frame=0; //which frame is currently selected
    printf(" Enter the number of players: ");
    scanf("%d", &players);
    bool strike_current[players]; //strike in the current frame
    bool strike_previous[players]; //strike in the previous frame
    bool strike_preprevious[players]; //strike in the frame before last
    bool spare_current[players]; //spare in the current frame
    bool spare_previous[players]; //spare in the previous frame
    bool last_strike[players]; //strike in the first roll of 10th frame
    bool last_spare[players]; //spare in the first or second roll of 10th frame
    bool draw=0; //the variable for defining the current status of DRAW
    int totalCount[players][9]; //total score counted for each frame from 1 to 9 frame
    int score[players]; //total score of the whole game
    int firstRoll[players][9]; //first roll from 1 to 9 frame of every player
    int secondRoll[players][9]; //second roll from 1 to 9 frame of every player
    int last_first[players]; //first roll in 10th frame for every player
    int last_second[players]; //second roll in 10th frame for every player
    int last_third[players]; //third roll in 10th frame for every player (if it is strike or spare)
    int last_total[players]; //total score counted of 10th frame for every player
    char name[players]; //initials (name) of players
    char surname[players]; //initials (surname) of players
    int max=-1; //variable for selecting the max score of the game (-1 is stated for avoiding DRAW if there is (are) player (s) with just 0 score) P.S at the end there is a calculation
    int maxplayer=0; //which player currently has the greatest score (at the end there is a calculation)
 
    for(int i=0;i<players;i++) //registration of players
    {
        printf(" Player %d enter your initals    (Name): ", i+1);
        scanf("%s",  &name[i]);
        printf(" Player %d enter your initals (Surname): ", i+1);
        scanf("%s",  &surname[i]);
    }
    clrscr(); //screen cleariing
    for(current=0;current<players;current++) //function to zero all the arrays
    {
        score[current]=0;
        last_first[current]=0;
        last_second[current]=0;
        last_third[current]=0;
        last_total[current]=0;
        strike_current[current]=0;
        strike_previous[current]=0;
        strike_preprevious[current]=0;
        spare_current[current]=0;
        spare_previous[current]=0;
        last_strike[current]=0;
        last_spare[current]=0;
    }
    for(frame=0;frame<9;frame++) //loop for frames
    {
        for(current=0;current<players;current++) //loop for players
        {
        label1: printf(" Enter 1 roll (player %c %c, frame %d): ", name[current], surname[current], frame+1);
        scanf("%d", &firstRoll[current][frame]); //first roll input
        if (firstRoll[current][frame]>10||firstRoll[current][frame]<0) //input validation
        {
            printf("⦾-----------------------------------⦾\n");
            printf("|    ►    OOPS!  TRY    AGAIN   ◄    |\n");
            printf("⦾-----------------------------------⦾\n");
            goto label1;
        }
        if(firstRoll[current][frame]==10) //in case of strike returns to the next frame
        {
            strike_current[current]=1;
            secondRoll[current][frame]=0;
            printf("⦾-----------------------------------⦾\n");
            printf("|    ►   STRIKE! KEEP BOWLING   ◄    |\n");
            printf("⦾-----------------------------------⦾\n");
        }
        if(!strike_current[current]) //goes to next roll
        {
            label2: printf(" Enter 2 roll (player %c %c, frame %d): ", name[current], surname[current], frame+1);
            scanf("%d", &secondRoll[current][frame]); //second roll input
            if (secondRoll[current][frame]>10 || secondRoll[current][frame]<0 || secondRoll[current][frame]+firstRoll[current][frame]>10) //nput validation
            {
                printf("⦾-----------------------------------⦾\n");
                printf("|    ►    OOPS!  TRY    AGAIN   ◄    |\n");
                printf("⦾-----------------------------------⦾\n");
                goto label2;
            }
        }
        if(firstRoll[current][frame]+secondRoll[current][frame]==10 && !strike_current[current]) //in case of spare
        {
            printf("⦾-----------------------------------⦾\n");
            printf("|    ►   SPARE! ALMOST STRIKE   ◄    |\n");
            printf("⦾-----------------------------------⦾\n");
            spare_current[current]=1;
        }
        if(!spare_current[current] && !strike_current[current])
        {
            totalCount[current][frame]=firstRoll[current][frame]+secondRoll[current][frame]; //counting scores wiyhour strike and spare
            printf("⦾-----------------------------------⦾\n");
            printf("|   ►   NOTHING! KEEP PLAYING   ◄    |\n");
            printf("⦾-----------------------------------⦾\n");
        }
        if(spare_previous[current]) //counting scores for previous frame in case of spare
        {
            totalCount[current][frame-1]=10+firstRoll[current][frame];
        }
        if(strike_previous[current]) //counting scores for prevous frame in case of strike
        {
            if(!strike_current[current])
            {
            totalCount[current][frame-1]=10+firstRoll[current][frame]+secondRoll[current][frame];
            strike_previous[current]=0;
            }
        }
        if(strike_preprevious[current]) //counting scores for prevous frame in case of two strikes in row
        {
            totalCount[current][frame-2]=10+10+firstRoll[current][frame];
        }
        spare_previous[current]=spare_current[current];  //shifting boolean variables
        spare_current[current]=0;
        strike_preprevious[current]=strike_previous[current];
        strike_previous[current]=strike_current[current];
        strike_current[current]=0;
        }
        sleep(1); //function to pause output before screen clearing
        clrscr(); //screen clearing for better perception
    }
    frame=10;
    for (current=0; current<players; current++)
    {
        label3: printf(" Enter 1 roll (player %c %c, frame %d): ", name[current], surname[current], frame);
        scanf("%d", &last_first[current]); //input first roll of last frame
        if (last_first[current]>10 || last_first[current]<0) //input validation
        {
            printf("⦾-----------------------------------⦾\n");
            printf("|    ►    OOPS!  TRY    AGAIN   ◄    |\n");
            printf("⦾-----------------------------------⦾\n");
            goto label3;
        }
        if(last_first[current]==10) //in case of srike
        {
            last_strike[current]=1;
            printf("⦾-----------------------------------⦾\n");
            printf("|    ►   STRIKE! +TWO   ROLLS   ◄    |\n");
            printf("⦾-----------------------------------⦾\n");
        }
        label4: printf(" Enter 2 roll (player %c %c, frame %d): ", name[current], surname[current], frame);
        scanf("%d", &last_second[current]); //input second roll of last frame
        if (last_second[current]+last_first[current]>10 && last_strike[current]!=1 || last_second[current]>10 || last_second[current]<0) //input validation
        {
 
                printf("⦾-----------------------------------⦾\n");
                printf("|    ►    OOPS!  TRY    AGAIN   ◄    |\n");
                printf("⦾-----------------------------------⦾\n");
                goto label4;
 
        }
        if((last_second[current]+last_first[current]==10) && (!last_strike[current])) //in case of spare
        {
            last_spare[current]=1;
            printf("⦾-----------------------------------⦾\n");
            printf("|    ►   SPARE!  +ONE    ROLL   ◄    |\n");
            printf("⦾-----------------------------------⦾\n");
        }
        if((last_strike[current])||(last_spare[current])) //third roll input in case of strike or spare
        {
            label5: printf(" Enter 3 roll (player %c %c, frame %d): ", name[current], surname[current], frame);
            scanf("%d",&last_third[current]);
            if (last_third[current]>10 || last_third[current]<0) //input validation
            {
                printf("⦾-----------------------------------⦾\n");
                printf("|    ►    OOPS!  TRY    AGAIN   ◄    |\n");
                printf("⦾-----------------------------------⦾\n");
                goto label5;
            }
            printf("⦾-----------------------------------⦾\n");
            printf("|    ►   FINISH! PERFECT GAME   ◄    |\n");
            printf("⦾-----------------------------------⦾\n");
        }
        if(last_strike[current]) //counting scores in last frame in case of strike
        {
            last_total[current]=10+last_second[current]+last_third[current];
        }
        if(last_spare[current]) //counting scores in last frame in case of spare
        {
            last_total[current]=10+last_third[current];
        }
        if(!last_strike[current] && !last_spare[current]) //counting scores in last frame without strike and spare
        {
            last_total[current]=last_first[current]+last_second[current];
            printf("⦾-----------------------------------⦾\n");
            printf("|    ►   FINISH!  NICE  GAME    ◄    |\n");
            printf("⦾-----------------------------------⦾\n");
        }
        if(spare_previous[current]) //counting scores in 9th frame in case of spare
        {
            totalCount[current][8]=10+last_first[current];
        }
        if(strike_previous[current]) //counting scores in 9th frame in case of strike
        {
            if(!strike_current[current])
            {
                totalCount[current][8]=10+last_first[current]+last_second[current];
                strike_previous[current]=0;
            }
        }
        if(strike_preprevious[current]) //counting scores in 8th frame in case two strikes in row
        {
            totalCount[current][7]=10+10+last_first[current];
        }
        spare_previous[current]=spare_current[current]; //shifting boolean variables
        spare_current[current]=0;
        strike_preprevious[current]=strike_previous[current];
        strike_previous[current]=strike_current[current];
        strike_current[current]=0;
    }
    sleep(1); //function to pause output before screen clearing
    clrscr(); //screen clearing for better perception
    for(current=0;current<players;current++) 
    {
        score[current]=0;
        for(frame=0;frame<9;frame++) //countig final results of each player
        {
            score[current]=score[current]+totalCount[current][frame];
        }
        printf("\nResult: %d | Player: %d | Name: %c | Surname: %c\n⦾", score[current]+last_total[current], current+1, name[current], surname[current]);
        for (int a=0; a<76; a++) //final score table
            printf("-");
        printf("⦾\n|  ");
        for(frame=0;frame<9;frame++) //frame number
        {
            printf(" %d\t", frame+1);
        }
        printf(" 10   |\n|  ");
        for(frame=0;frame<9;frame++) //scores for each roll
        {
            switch (firstRoll[current][frame])
            {
            case 0:
                printf("-|");
                break;
            case 10:
                printf("X|");
                break;
            default:
                printf("%d|", firstRoll[current][frame]);
                break;
            }
            switch (secondRoll[current][frame])
            {
            case 0:
                printf("-\t");
                break;
            default:
                if (secondRoll[current][frame]+firstRoll[current][frame]==10)
                    printf("/\t");
                else
                    printf("%d\t", secondRoll[current][frame]);
                break;
            }
        }
        switch (last_first[current])
        {
        case 0:
            printf("-|");
            break;
        case 10:
            printf("X|");
            break;
        default:
            printf("%d|", last_first[current]);
            break;
        }
        switch (last_second[current])
        {
        case 0:
            printf("-");
            break;
        case 10:
            printf("X");
            break;
        default:
            if (last_first[current]+last_second[current]==10)
            printf("/");
            else
            printf("%d", last_second[current]);
            break;
        }
        if (last_first[current]==10 || last_first[current]+last_second[current]==10)
        {
            switch (last_third[current])
            {
            case 0:
                printf("|- |\n|  ");
                break;
            case 10:
                printf("|X |\n|  ");
                break;
            default:
                printf("|%d |\n|  ", last_third[current]);
                break;
            }
        }
        else
        {
            printf("   |\n|  ");
        }
        score[current]=0;
        for(frame=0;frame<9;frame++) //cummulative scores for each frame
        {
            score[current]=score[current]+totalCount[current][frame];
            printf(" %d\t", score[current]);
        }
        if((score[current]+last_total[current])<=9)
        printf(" %d    |\n⦾", score[current]+last_total[current]);
        if((score[current]+last_total[current])<100 && (score[current]+last_total[current])>=10)
        printf(" %d   |\n⦾", score[current]+last_total[current]);
        if((score[current]+last_total[current])>=100)
        printf(" %d  |\n⦾", score[current]+last_total[current]);
        for (int a=0; a<76; a++)
            printf("-");
        printf("⦾\n\n");
 
        if (score[current]+last_total[current]>max) //defining of leader or draw
        {
            max=score[current]+last_total[current];
            maxplayer=current;
            draw=0;
        }
        else if (score[current]+last_total[current]==max)
        {
            draw=1;
        }
    }
    if (draw)
    {
       if(max<=9)
        {
            printf("\t\t     ⦾-----------------------------------⦾\n");
            printf("\t\t     |            ►   DRAW   ◄            |\n");
            printf("\t\t     |          Maximum score %d           |\n", max);
            printf("\t\t     ⦾-----------------------------------⦾\n");
            return 0;
        }
        if(max>=100)
        {
            printf("\t\t     ⦾-----------------------------------⦾\n");
            printf("\t\t     |            ►   DRAW   ◄            |\n");
            printf("\t\t     |          Maximum score %d         |\n", max);
            printf("\t\t     ⦾-----------------------------------⦾\n");
            return 0;
        }
        if(max>=10)
        {
            printf("\t\t     ⦾-----------------------------------⦾\n");
            printf("\t\t     |            ►   DRAW   ◄            |\n");
            printf("\t\t     |          Maximum score %d          |\n", max);
            printf("\t\t     ⦾-----------------------------------⦾\n");
            return 0;
        } 
    }
    if (!draw)
    {
        if(score[maxplayer]+last_total[maxplayer]<=9)
        {
            printf("\t\t     ⦾-----------------------------------⦾\n");
            printf("\t\t     |          ►   WINNER!!!   ◄         |\n");
            printf("\t\t     |          Player %c %c    (%d)         |\n", name[maxplayer], surname[maxplayer], score[maxplayer]+last_total[maxplayer]);
            printf("\t\t     ⦾-----------------------------------⦾\n");
            return 0;
        }
        if(score[maxplayer]+last_total[maxplayer]>=100)
        {
            printf("\t\t     ⦾-----------------------------------⦾\n");
            printf("\t\t     |          ►   WINNER!!!   ◄         |\n");
            printf("\t\t     |          Player %c %c   (%d)        |\n", name[maxplayer], surname[maxplayer], score[maxplayer]+last_total[maxplayer]);
            printf("\t\t     ⦾-----------------------------------⦾\n");
            return 0;
        }
        if(score[maxplayer]+last_total[maxplayer]<100 && score[maxplayer]+last_total[maxplayer]>=10)
        {
            printf("\t\t     ⦾-----------------------------------⦾\n");
            printf("\t\t     |          ►   WINNER!!!   ◄         |\n");
            printf("\t\t     |          Player %c %c   (%d)         |\n", name[maxplayer], surname[maxplayer], score[maxplayer]+last_total[maxplayer]);
            printf("\t\t     ⦾-----------------------------------⦾\n");
            return 0;
        } 
    }
}