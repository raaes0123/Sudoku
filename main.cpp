#include <iostream>
#include <Windows.h>
#include <fstream>
#include "Digits.h"
#include "color.hpp"
#include <conio.h>
#include <iomanip>
using namespace std;

void banner()
{
    system("cls");
    cout<<hue::green;
    cout<<"********* W - E - L - C - O - M - E *********\n";
    cout<<"---------------------------------------------\n";
    cout<<" ***************** T - O ******************* \n";
    cout<<"---------------------------------------------\n";
    cout<<"  ********* S - U - D - O - K - U *********\n";
    cout<<"                                            \n";
    cout<<hue::reset;
}

void instruction()
{
    system("cls");
    banner();
    cout<<hue::aqua;
    cout<<"Instructions\n";
    cout<<hue::reset;
    cout<<"1. Sudoku grid consists of 9x9 spaces.\n";
    cout<<"2. You can use only numbers from 1 to 9.\n";
    cout<<"3. Each 3x3 block can only contain numbers from 1 to 9.\n";
    cout<<"4. Each vertical column can only contain numbers from 1 to 9.\n";
    cout<<"5. Each horizontal row can only contain numbers from 1 to 9.\n";
    cout<<"6. Each number in the 3x3 block, vertical column or horizontal row can be used only once.\n";
    cout<<"7. The game is over when the whole Sudoku grid is correctly filled with numbers.\n\n";
    cout<<"Press any key to return to main menu\n";
    getch();
}

char menu()
{
    banner();
    cout<<"             Press 1 to Start      "<<endl;
    cout<<"         Press 2 for Instructions  "<<endl;
    cout<<"            Press 3 for Scores     "<<endl;
    cout<<"             Press 4 to Exit      "<<endl;
    char choice = getch();
    return choice;
}

char gameOption()
{
    char choice;
    while(1)
    {
        system("cls");
        banner();
        cout<<hue::purple;
        cout<<"Game Options\n";
        cout<<hue::reset;
        cout<<"1. Easy\n";
        cout<<"2. Medium\n";
        cout<<"3. Hard\n";
        choice = getch();
        if (choice == '1' || choice == '2' || choice == '3')
            break;
    }
    return choice;
}

void readFile(Digits digit[][9], string file_name)
{
    fstream fstream_object;
    //fstream_object.open("./"+file_name);
    fstream_object.open(file_name); 
    if(!fstream_object.is_open())
    {
        int dummy;
        cout<<"Error opening file"<<endl;
        //cin>>dummy;
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fstream_object>>digit[i][j].num;
            // Set the flag to show that the number is from file
            if (digit[i][j].num != 0)
                digit[i][j].flag = 1;
        }
    }
    fstream_object.close();
}

void readSolnFile(int soln[][9], string file_name)
{
    fstream fstream_object;
    fstream_object.open("./"+file_name);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fstream_object >> soln[i][j];
        }
    }
    fstream_object.close();
}

void draw(Digits digit[][9],int soln[][9], int score)
{
    system("cls");
    // Print Digits
    for (int i = 0; i < 9; i++)
    {
        cout<<"             ";
        cout<<hue::yellow<<char('A'+ i)<<" "<<hue::reset;        //Row Lettering
        for (int j = 0; j < 9; j++)
        {
            // Set different colours for different types of digits
            if (digit[i][j].flag != 0)          //Numbers read from file
                cout<<digit[i][j].num<<" ";
            else                                //Numbers entered by player
            {
                if (digit[i][j].num == 0)       //Space is not filled yet
                    cout<<hue::aqua<<"_ ";
                else
                {
                    if(digit[i][j].num == soln[i][j])       // If number entered is correct
                        cout<<hue::aqua<<digit[i][j].num<<" ";
                    else
                        cout<<hue::red<<digit[i][j].num<<" ";
                }
                    
            }
            cout << hue::reset;
            if((j+1)%3 == 0 && j != 8)
                cout<<'|';
        }
        cout<<endl;
        if((i+1)%3 == 0)
        {
            cout<<"             ";
            cout<<"  -------------------"<<endl;
        }
    }
    cout<<"             ";
    cout<<hue::yellow<<"  1 2 3  4 5 6  7 8 9"<<hue::reset<<endl;
    cout<<hue::light_blue<<"                    Score: "<<score<<hue::reset<<endl;
}

bool checkGrid(Digits digit[][9],int soln[][9])
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if(digit[i][j].num != soln[i][j])
                return false;
    return true;
}

int gamePlay(string file_name)
{
    Digits digit[9][9];         // Digits object
    int soln_array[9][9];       // Grid Solution array
    int score = 0;              // Score
    const int POINTS = 10;
    // Read data from file and display
    readFile(digit, file_name);
    //Read data from solution file to a int[9][9]
    int pos = file_name.find(".");
    string soln_file_name = file_name.substr(0,pos);
    soln_file_name += "_soln.txt";
    readSolnFile(soln_array,soln_file_name);
    // Display digits
    draw(digit,soln_array,score);
    // Get into the play loop
    while(1)
    {
        // Flag to indicate the game is over ie all spaces are filled
        bool game_over = true;
        string s;           // To store the position
        cout<<"Enter the position. (Eg A1 for 1st row 1st column) ";
        cin>>s;
        int x,y,val;
        //Check if the position is within range
        if(int(s[0] - 'A') >= 0 && int(s[0] - 'I') >= 0 && int(s[1] - '1') >= 0 && int(s[1] - '9') >= 0)
            cout<<"The position you entered is incorrect"<<endl;
        else
        {
            int n;
            x = int(s[0] - 'A');
            y = int(s[1] - '1');
            //Check if the position is already filled
            if(digit[x][y].flag != 0)
            {
                cout<<"The position you entered is invalid"<<endl;
                continue;
            }
            cout<<"Enter the number ";
            cin>>n;
            if (n>=1 && n <= 9)         // Valid Case
            {
                digit[x][y].num = n;
                // Keep score
                if(n == soln_array[x][y])
                    score += POINTS;
                else
                    score -= POINTS;

            }
            else
                cout<<"The number you entered is not in range."<<endl;
            draw(digit,soln_array,score);
        }
        // Check if the grid is filled ie if the game is complete
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if(digit[i][j].num == 0)
                {
                    game_over = false;
                    break;
                }    
        // If every space is filled match with the solution and if everything matches get out of the loop
        bool check = false;
        if(game_over)
            check = checkGrid(digit,soln_array);
        if(check)
            break;
    }
    cout<<hue::green<<"Congratulations!\nYou have completed the game.\n";
    cout<<hue::reset;
    return score;   
}

void getScores(string file)
{
    fstream fstream_object;
    fstream_object.open("./"+file);
    string name;
    string score;
    system("cls");
    banner();
    cout<<hue::aqua;
    cout<<setw(25)<<"Player Name"<<setw(8)<<"Score"<<endl;
    cout<<hue::reset;
    while(fstream_object>>name>>score)
    {
        cout<<setw(25)<<name<<setw(8)<<score<<endl;
    }
    fstream_object.close();
}

int main()
{
    // Clear the screen
    system("cls");
    string file_name;
    string score_file = "score.txt";
    string player;
    int score;
    while(1)
    {
        char choice = menu();
        // If choice is to exit
        if(choice == '4')
        {
            system("cls");
            exit(0);
        }
        // If choice to display scores
        else if (choice == '3')
        {
            getScores(score_file);
            cout<<"Press any key to return to main menu"<<endl;
            getch();
        }
        // If choice is to view instruction
        else if (choice == '2')
            instruction();
        // Choice to start the game
        else if(choice == '1')
        {
            // Read User name
            system("cls");
            banner();
            cout<<"Enter player"<<endl;
            cin>>player;
            //Game options
            int level = gameOption();
            if (level == '1')
                file_name = "easy.txt";
            else if (level == '2')
                file_name = "medium.txt";
            else if (level == '3')
                file_name = "hard.txt";
            break;
        }
    }
    score = gamePlay(file_name);
    ofstream fstream_object;
    fstream_object.open("./"+score_file,ios::app);       //Apppend mode
    fstream_object<<player<<" "<<to_string(score)<<endl;
    fstream_object.close();
    return 0;
}