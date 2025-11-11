#include <iostream>

// Data struct
#include <vector>
#include <map>
#include <tuple>

// for random
#include <algorithm>
#include <random>
#include <ctime>

// raising exception to catch
#include <stdexcept>

// cleaning user input
#include <algorithm>

// for clearing input
#include <cstdlib>

using namespace std;

vector<vector<int>> make_board(u_int row, u_int col); // making a 2d array board with adding as an input to the array

int excel_to_int(string s); // turning excel to int like A --> 1, or AA --> 27

string int_to_excel(int n); // turning int to excel like 1 --> A, or 27 --> AA

vector<int> add_bom(u_int bom, u_int sizes); // return an array of randomized set of 1's as bom, and 0 as not bom

vector<vector<int>> bom_board(u_int length, u_int width, u_int BOMS); // making a board of boms

tuple<int,int> seperating(string cords, u_int length, u_int width); // parse user input and return a tuple containing the row, and col and raise an exception when the input is wrong

vector<vector<int>> update_board(vector<vector<int>>& ans, vector<vector<int>>& board, int row, int col); // updating the board

bool check_is_equal(vector<vector<int>>& ans, vector<vector<int>>& board); // checking if both board are equal

tuple<u_int, u_int, u_int> custom_board(); // custom checker for size

void print_board(vector<vector<int>>& board); // print to stout


int main()
{
    /*
    TODO:
    1. Validate User Input (Done)
    2. Make the update func (Done)
    3. Back up this file (Done)
    4. Update all string placement to be a number and in the print statement only put map (string compare is expensive) (Done)
    5. Make it so that if you type 1a and there is a number already, but surrounding it has no flag, not explode (Done)
    6. check if complete (Done)
    7. change it so that by the user input, length_size, width_size, and bom (Done)
    */

   // var of size of minesweeper
   u_int length, width, boms;

   // what mode
   string mode;

   // clear stout
   system("clear");
   // beginning of text
   cout<< "Welcome To Minesweeper!\nMade by Nickson\n\n";
   cout<< "Choose What Board do you want!\n";
   cout<< "1. Beginner : 22 x 12 with 12 boms"<<endl;
   cout<< "2. Easy     : 10 x 7 with 10 boms"<<endl;
   cout<< "3. Medium   : 22 x 12 with 40 boms"<<endl;
   cout<< "4. Hard     : 32 x 18 with 100 boms"<<endl;
   cout<< "5. Huge     : 48 x 28 with 220 boms"<<endl;
   cout<< "6. Extreme  : 32 x 18 with 150 boms"<<endl;
   cout<< "7. Custom"<<endl;
   cout<< "Pick one of the numbers or the category"<<endl;
   while (true)
   {
        // input

        string s;
        // get input
        getline(cin, s);

        // clean up input 
        s.resize(distance(s.begin(), remove_if(s.begin(), s.end(), [](u_char c){return c == ' ';})));
        transform(s.begin(), s.end(), s.begin(), [](u_char c){return tolower(c);});
        
        // checking input & putting length
        if (s == "1" || s == "beginner")
        {
            length = 22;
            width = 12;
            boms = 10;
            mode = "Beginner";
        }
        else if (s == "2" || s == "easy")
        {
            length = 10;
            width = 7;
            boms = 10;
            mode = "Easy";
        }
        else if (s == "3" || s == "medium")
        {
            length = 22;
            width = 12;
            boms = 40;
            mode = "Medium";
        }
        else if (s == "4" || s == "hard")
        {
            length = 32;
            width = 18;
            boms = 100;
            mode = "Hard";
        }
        else if (s == "5" || s == "huge")
        {
            length = 48;
            width = 28;
            boms = 220;
            mode = "Huge";
        }
        else if (s == "6" || s == "extreme")
        {
            length = 32;
            width = 18;
            boms = 150;
            mode = "Extreme";
        }
        else if (s == "7" || s == "custom")
        {
            tie(length, width, boms) = custom_board();
            mode = "Custom";
        }
        // not accepted value
        else
        {
            // clear stout to make it clean
            system("clear");
            // reprompt
            cout<< "Choose What Board do you want!\n";
            cout<< "1. Beginner : 22 x 12 with 12 boms"<<endl;
            cout<< "2. Easy     : 10 x 7 with 10 boms"<<endl;
            cout<< "3. Medium   : 22 x 12 with 40 boms"<<endl;
            cout<< "4. Hard     : 32 x 18 with 100 boms"<<endl;
            cout<< "5. Huge     : 48 x 28 with 220 boms"<<endl;
            cout<< "6. Extreme  : 32 x 18 with 150 boms"<<endl;
            cout<< "7. Custom"<<endl;
            cout<< "Pick one of the numbers or the category"<<endl;
            cout<<"Wrong Input, please put number between 1-7 or through Beginner - Custom !\n";
            continue;
        }
        break;
    }
    
    // clearing the screen
    
    // making the answer sheets
    auto answer = bom_board(length, width, boms);
    
    // making the board
    auto board = make_board(length, width);
    
    // flag mode
    bool Flag = false;
    while (true)
    {
        // validate answer
        string cords;
        int row, col;
        
        // clear the stout
        system("clear");
        // print current mode
        cout<< "\nMode: "<< mode<<endl;
        printf("Type \"Flag\" if you want flag mode, Type \"Dig\" if you want dig mode.");
        printf("\n");

        // print current Board
        print_board(board);
        
        // validate user input
        while(true)
        {
            if (Flag)
            {
                printf("Flag mode\n");
            }
            else
            {
                printf("Dig mode\n");
            }
            try
            {
                printf("Cords: ");
                // get user input
                getline(cin, cords);

                // clean up user input
                cords.resize(distance(cords.begin(), remove_if(cords.begin(), cords.end(), [](u_char c){return c == ' ';})));
                transform(cords.begin(), cords.end(), cords.begin(), [](u_char c){return toupper(c);});

                // if its a flag or dig & reprompt board  
                if (cords == "FLAG")
                {
                    Flag = true;
                    system("clear");
                    cout<< "\nMode: "<< mode<<endl;
                    printf("Type \"Flag\" if you want flag mode, Type \"Dig\" if you want dig mode.");
                    printf("\n");
                    // print current Board
                    print_board(board);
                    continue;
                }
                else if (cords == "DIG")
                {
                    Flag = false;
                    system("clear");
                    cout<< "\nMode: "<< mode<<endl;
                    printf("Type \"Flag\" if you want flag mode, Type \"Dig\" if you want dig mode.");
                    printf("\n");
                    // print current Board
                    print_board(board);
    
                    continue;
                }

                // seperating the val
                tie(row, col) = seperating(cords, length, width);
                break;
            }
            catch(const invalid_argument)
            {
                system("clear");
                cout<< "\nMode: "<< mode<<endl;
                printf("Type \"Flag\" if you want flag mode, Type \"Dig\" if you want dig mode.");
                printf("\n");
                // print current Board
                print_board(board);

                // not accepted value
                printf("Wrong Input, please try again. Use the format number then alphabet. (example: 1A, 11AA)\n");
                continue;
            }
        }

        // variable to hold values for rechecking
        int var = board.at(row - 1).at(col - 1);
        int vars = answer.at(row - 1).at(col - 1);

        // check if flag is turn on
        if (Flag)
        {
            // if its not occupied
            if (var == -2)
            {
                board.at(row - 1).at(col - 1) = -3;
                continue;
            }
            // if its a flag
            else if (var == -3)
            {
                board.at(row - 1).at(col - 1) = -2;
                continue;
            }
        }

        // updating the board
        try 
        {
            if (var == -2)
            {
                board = update_board(answer, board, row - 1, col - 1);
            }
            else
            {
                // check if the surrounding has a flag
                // count how many flag surrounding it
                int count = 0;

                // iterating through surrounding array
                for(int i = -1; i < 2; i++)
                {
                    for(int j = -1; j < 2; j++)
                    {
                        if (row  - 1 + i < 0 || row - 1 + i >= length)
                        {
                            break; // because the entire iteration is useless 
                        }
                        if (col - 1 + j < 0 || col - 1 + j >= width)
                        {
                            continue;
                        }
                        if (board.at(row - 1 + i).at(col - 1 + j) == -3)
                        {
                            count += 1;
                        }
                    }
                }
                if (var <= count)
                {
                    // faking a blank to check surroundings
                    answer.at(row - 1).at(col - 1) = 0;
                    board.at(row - 1).at(col - 1) = -2;
                    board = update_board(answer, board, row - 1, col - 1);
                    board.at(row - 1).at(col - 1) = var;
                    answer.at(row - 1).at(col - 1) = vars;
                }
            }
        }
        // cathing the bom exception
        catch(const std::exception& e)
        {
            // lose
            answer.at(row - 1).at(col - 1) = vars;
            system("clear");
            print_board(answer);
            cout<<"\nYou Lose"<<endl;
            return 1;
        }

        // checking if board == answer but skip on the bomb part
        if (check_is_equal(answer, board) == true)
        {
            // win
            system("clear");
            print_board(board);
            printf("\nYOU WON!!!\n");
            return 0;
        }
    }
}

//return the value in tuple form
tuple<int,int> seperating(string cords, u_int length, u_int width)
{
    int row = 0;
    int col = 0;
    if (cords == "")
        {
            throw invalid_argument("String is Blank");
        }
        else if (isdigit(cords[0]) == false)
        {
            throw invalid_argument("There is no int on the first section of the string");
        }
        for (int i = 0; i < cords.size();i++)
        {
            if(isdigit(cords[i]))
            {
                col = col*10 + cords[i] - '0';
            }
            else
            {
                cords = cords.substr(i, cords.size() - 1);
                break;
            }
        }
    
    row = excel_to_int(cords);
    if (row < 1 || row > length)
    {
        throw invalid_argument("There is no int on the first section of the string");
    }
    if (col < 1 || col > width)
    {
        throw invalid_argument("There is no int on the first section of the string");
    }

    return make_tuple(row,col);
}


vector<vector<int>> bom_board(u_int length, u_int width, u_int BOMS)
{   
    
    // initiation of board
    vector<vector<int>> board = make_board(length, width);
    // add an array of boms
    auto boms = add_bom(BOMS, length*width);
    
    // filling the board per items
    int index_row,index_col;
    for (int i= 0; i < boms.size(); i++)
    {
        if (boms[i] == 1)
        {
            index_col = i/length; // getting the index for col
            index_row = i%length; // getting the index for row
            board.at(index_row).at(index_col) = -1; 
        }
    }
    
    // adding the numbers surrounding the boms
    for (int row=0; row < length; row++)
    {
        for (int col=0; col< width; col++)
        {
            if (board.at(row).at(col) == -1)
            {
                continue;
            }
            // count how many boms surrounding it
            int count = 0;

            // iterating through surrounding array
            for(int i = -1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if (row + i < 0 || row + i >= length)
                    {
                        break; // because the entire iteration is useless 
                    }
                    if (col + j < 0 || col + j >= width)
                    {
                        continue;
                    }
                    if (board.at(row + i).at(col + j) == -1)
                    {
                        count += 1;
                    }
                }
            }
            board.at(row).at(col) = count; 
        }
    }
    return board;
}


void print_board(vector<vector<int>>& board)
{
    cout<<"[";
    string s = " ";
    // dict to make the board more readable
    map<int, string> int_to_emoji = {{1," 1️⃣ "}, {2," 2️⃣ "}, {0, "️️ 🔳"}, {3, " 3️⃣ "}, {4, " 4️⃣ "}, {5, " 5️⃣ "}, {6, " 6️⃣ "}, {7, " 7️⃣ "}, {8, " 8️⃣ "}, {-1, " 💣"}, {-2, " ☐ "}, {-3, " 🚩"}};

    int width = board.at(0).size();
    // formating the numbers stout
    for (int i = 1; i < width + 1; i++)
    {
        string j = to_string(i); 
        if (j.size() > 1)
        {
            s += j + ",";
            
        }
        else
        {
            s += j + ", ";
        }
    }
    s.pop_back();
    if (!(isdigit(s.back())))
    {
        s.pop_back();
    }
    cout<< s <<" ]\n";
    
    int k = 1; // remember what index it is
    for (vector<int> row : board)
    {
        cout<<"[";
        s = "";
        for (int str : row)
        {
            s += int_to_emoji[str];
        }
        
        cout<< s <<" ]["<< int_to_excel(k) <<"]\n";
        k ++;
    }

}


vector<int> add_bom(u_int bom, u_int sizes)
{
    // initializing the ret array
    vector<int> bom_arr;

    // inserting boms 
    for (int i=0;i<bom;i++)
    {
        bom_arr.push_back(1);
    }

    // inserting the rest of the value
    int res = sizes - bom;
    for (int i=0 ;i < res;i++)
    {
        bom_arr.push_back(0);
    }

    // randomized with time
    auto rng = default_random_engine {};
    rng.seed(time(0));

    // shuffling the array
    shuffle(bom_arr.begin(), bom_arr.end(), rng);

    return bom_arr;
}


vector<vector<int>> make_board(u_int row, u_int col)
{
    // initializazing the 2d array
    vector<vector<int>> ret;
    for (int j = 0; j < row; j++)
    {
        // initialization row
        vector<int> add;
        for (int i = 0; i < col; i++)
        {
            // adding the string
            add.push_back(-2);
        }
        // adding the array to array
        ret.push_back(add);
    }
    return ret;
}


vector<vector<int>> update_board(vector<vector<int>>& ans, vector<vector<int>>& board, int row, int col)
{
    // variable for non repetition
    int var = board.at(row).at(col);
    int vars = ans.at(row).at(col);
    
    // var for non repetition
    // if not new or board is blank
    // check if board is the special char, and act surrounding it
    if (var == -3)
    {
        return board;
    }
    if (vars == -1)
    {
        throw invalid_argument("BOM");
    }
    else if (vars == 1)
    {
        board.at(row).at(col) = 1;
        return board;
    }
    else if (vars == 2)
    {
        board.at(row).at(col) = 2;
        return board;
    }
    else if (vars == 3)
    {
        board.at(row).at(col) = 3;
        return board;
    }
    else if (vars == 4)
    {
        board.at(row).at(col) = 4;
        return board;
    }
    else if (vars == 5)
    {
        board.at(row).at(col) = 5;
        return board;
    }
    else if (vars == 6)
    {
        board.at(row).at(col) = 6;
        return board;
    }
    else if (vars == 7)
    {
        board.at(row).at(col) = 7;
        return board;
    }
    else if (vars == 8)
    {
        board.at(row).at(col) = 8;
        return board;
    }
    else if (board.at(row).at(col) == -2)
    {
        board.at(row).at(col) = 0;
        
        for (int i = -1; i < 2; i++)
        {
            for(int j = -1; j < 2; j++)
            {
                if (i == 0 && j == 0)
                {
                    continue;
                }
                if (row + i > ans.size() - 1 || row + i < 0)
                {
                    break;
                }
                if (col + j > ans.at(0).size() - 1 || col + j < 0)
                {
                    continue;
                }
                // print_board(board);
                board = update_board(ans, board, row + i, col + j);
            }
        }
    }
    
    return board;
}

// turning int to excel
string int_to_excel(int columnNumber)
{
    // initialization of string
    string s = "";
    // iterating columnNumber
    while (columnNumber > 0)
    {
        columnNumber -= 1;
        s = char(columnNumber % 26 + 65) + s;
        columnNumber /= 26;
    }
    return s;
}

// turning excel to int
int excel_to_int(string s)
{
    int val = 0;
    for (char c : s) // "Hello" --> ['H', 'e', ...] --> c = 'H', 'e'
    {
        if (isupper(c))
        {
            val = val*26 + (c - 65 + 1);
        }
        else
        {
            throw invalid_argument("The content should be Upper Character!\n");
        }
    }
    return val;
}


bool check_is_equal(vector<vector<int>>& ans, vector<vector<int>>& board)
{

    int length = ans.size();
    int width = ans.at(0).size();
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int s = ans.at(i).at(j);
            if (s == -1)
            {
                continue;
            }
            
            int c = board.at(i).at(j);
            
            if (c != s)
            {
                return false;
            }
        }
    }
    return true;
}


tuple<u_int, u_int, u_int> custom_board()
{
    // Variables
   int length, width, boms;

   // getting length
   while(true)
   {
       cout<< "Length of the board: ";
        try
        {
            string s;
            getline(cin, s);
            length = stoi(s);
            if (length > 0)
            {
                break;
            }
        }
        catch(const invalid_argument){}
        system("clear");
        cout <<"Length must be greater than 0 and is a number." << '\n';
   }

   // getting width
   while(true)
   {
       try
       {
            cout<< "Width of the board: ";
            string s;
            getline(cin, s);
            width = stoi(s);
            if (width > 0)
            {
                break;
            }
        }
        catch(const invalid_argument){}
        system("clear");
        cout <<"Width must be greater than 0 and is a number." << '\n';
   }
   
   // getting boms
   while(true)
   {
       try
       {
            cout<< "How many Boms: ";
            string s;
            getline(cin, s);
            boms = stoi(s);
            if (boms > 0 && boms <= length*width)
            {
                break;
            }
        }
        catch(const invalid_argument){}
        system("clear");
        cout <<"Boms must be greater than 0 and less than "<< length*width <<" is a number." << '\n';
   }

   return make_tuple(length, width, boms);
}
