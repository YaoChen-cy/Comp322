# include <iostream>
# include <cctype>
# include <string>
# include <stdio.h>
# include <ctype.h>
# include <cstdlib>
# include <time.h>
// include libraries will use in code

// declare the namespace std to use cin and cout without std ::
using namespace std;

// define the global constants rows and cols
const int rows = 5; 
const int cols = 5;

// declare functions before being used
void checkPassword();
void convertPhonetic();
void fillMatrix(int matrix[rows][cols]);
void printMatrix(int matrix[rows][cols]);
void multiplyMatrices(int matrix_left[rows][cols], int matrix_right[rows][cols],int matrix_result[rows][cols]);

//Question 1
void checkPassword(){
    // define a variable password eith type string
    string password;

    // define a variable with type int , used to count the occurrence
    // of each character in the password
    int count_occurrence=1;

    // ask user to input a password
    cout<<"Please enter a password: ";
    // store the input to the string password 
    cin>> password;

    // if the password does not contain at least 8 character, print message
    if(password.length()<8){
        cout<<"password should contain at least 8 characters"<<endl;
    }

    // if the password does not contain at least one special chars, print message
    if(password.find_first_of("*#$")==std::string::npos){
        cout<<"password should contain at least 1 of the following special characters #*$"<<endl;
    }

    // if the password does not containat least one number, print message
    if(password.find_first_of("0123456789")==std::string::npos){
        cout<<"password should contain at least 1 number"<<endl;
    }

    // check whether each character does not occur more than 2 times
    // itwerate each character in the password
    for(int i=0; i<password.length(); i++){
        // iterate the rest of the string
        for(int s=i+1; s<password.length(); s++){

            // if the character occur in the rest of the string
            // increase the occurrentce by one
            if(password[i]==password[s]){
                count_occurrence++;
            }

            // if the character occure more than two times, print message
            // get out of the double loop, execute the rest of the code
            if(count_occurrence>2){
                cout<<"each character should occur no more than 2 times"<<endl;
                goto afterLoop;
            }
        }
        // iterate the next character in the password
        count_occurrence=1;
    }

    // if get out of the double lopp in half way, get directly to this line of code
    afterLoop:

    // if all requirements of a password are satisfy, print message
    if((password.length()>=8)&& (password.find_first_of("*#$")!=std::string::npos)&&(password.find_first_of("0123456789")!=std::string::npos)&&(count_occurrence<=2)){
        cout<<"password has been accepted"<<endl;
    }
}

//Question 2
void convertPhonetic(){
    // define a variable word with type string
    string word;

    // ask user to input a word
    cout<<"Please enter a word: ";
    // store the input into word
    cin>>word;

    // deifne a constant stirng list to store 26 code words in NATO
    // phonetic alphabet 
    const char *phonetic[26] ={"Alfa","Bravo","Charlie","Delta","Echo","Foxtrot","Golf","Hotel","India","Juliett","Kilo","Lima","Mike","November","Oscar","Papa","Quebec","Romeo","Sierra","Tango","Uniform","victor","Whiskey","X-ray","Yankee","Zulu"};
    
    // iterate each character in the word
    for(int i=0; i<word.length(); i++){

        // change character into lowercase
        // translate character to ASCII value
        // subtract the ASCII by 97 to find the corresponding code word in the list 
        // print the word out followed by a blank
        cout<<phonetic[int(tolower(word[i]))-97]<<" ";
    }

    // get to a new line
    cout<<endl;
}

//Question 3-1
void fillMatrix(int matrix[rows][cols]){

    // define a static local variable x with type int
    static int x=1;

    // set a different seed in order to get different number everytime when calling the function
    srand(time(nullptr)+x);

    // fill the 5*5 matrix with randmly generated numbers
    // the numbers are positive integers ranging from 0 to 25
    for(int i=0; i<rows; i++){
        for(int s=0; s<cols; s++){
            matrix[i][s]=rand() % 26;
        }
    }
    // increase x everytime when call this function to set a random seed
    x++;
}

//Question 3-2
void printMatrix(int matrix[rows][cols]){

    for(int i=0; i<rows; i++){
        for(int s=0; s<cols; s++){
            // if reach to the end if a row, print the end number
            // followed by a separete line
            if(s==(cols-1)){
                cout<<matrix[i][s]<<endl;
                cout<<"----------------------"<<endl;
            }
            // print a number followed by a vertical line
            else{
                cout<<matrix[i][s]<<"|";
            }
        }
    }
    cout<<endl;
}

//Question 3-3
void multiplyMatrices(int matrix_left[rows][cols], int matrix_right[rows][cols],int matrix_result[rows][cols]){
   
   // define a static local variable a,b and c with type int
    static int a=0; // indicate the current column number for result matrix
    static int b=0; // indicate the current row number for result matrix
    static int c=0; // temporary row/column num
    
    // if the current column number greater than 5, multiply matraix computed
    // stop execute this function
    if(a>cols){
        return;
    }

    // if the current column number equal to 5, multiply matraix computed
    // stop execute this function
    if(a==cols){
        return;
    }

    // if the current row is smaller than 5
    if(b<cols){
        // if the tempotaty row/cols num samller than 5
        if(c<rows){
            //initialize the current position with value 0
            if(c==0){
                matrix_result[a][b]=0;
            }
            // compute the value of the current position by following the rule of
            // product of matrix
            matrix_result[a][b] += matrix_left[a][c]*matrix_right[c][b];
            // update the temporaray row/cols by 1
            c++;
            // recursion: computing the value of the current position
            multiplyMatrices(matrix_left, matrix_right, matrix_result);
        }
        // if the tempotaty row/cols num greater than 4
        // finish computing the current position of the result matrix
        // update the current row number by 1
        // update the temporary row/cols num to 1
        b++;
        c=0;
        // recursion: computing the next column of result matrix
        multiplyMatrices(matrix_left, matrix_right, matrix_result);
    }
    // if the current row is greater than 4
    // finish computing a column of the result matrix
    // update the current row number to 0
    // update the current column number by 1
    b=0;
    a++;
    // recusion
    multiplyMatrices(matrix_left, matrix_right, matrix_result);
}

int main(){
    checkPassword();
    convertPhonetic();
    int matrix[rows][cols];
    int matrix2[rows][cols];
    int matrix_result[rows][cols];
    fillMatrix(matrix);
    fillMatrix(matrix2);
    printMatrix(matrix);
    multiplyMatrices(matrix, matrix2, matrix_result);
    printMatrix(matrix_result);
    return 0;
}
