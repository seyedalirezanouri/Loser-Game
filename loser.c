#include <stdio.h>
#include <clui.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
   char UserName[30];
   char password[30];
   int score;
   int code; //starting from 100
} client;
typedef struct{
    char word[21];
    int score;
} words;
void BeautifulPrinting(int R, int G, int B, char text[], int milisec){
    change_color_rgb(R, G, B);
    for(int i = 0; ; i++){
        delay(milisec);
        if(text[i] != '\0'){
            printf("%c", text[i]);
        }
        else{
            break;
        }

    }
    reset_color();
}

int CheckUsername(FILE* fptr, char username[]){
    client temp = {"","",0,0};
    rewind(fptr);
    int result = 1;
    while(!feof(fptr)){
        fread(&temp,sizeof(client), 1,fptr);
        result = strcmp(username,temp.UserName);
        if(result == 0){
            return 1;
        }
   }
   return 0;
}

void GetUsername(char username[]){
    int result = 2;
    printf("please enter your user name :\n");
    change_color_rgb(255, 0, 0);
    printf("user name should be less than 30 character\n");
    reset_color();
    scanf("%29s", username);    
    FILE * fptr = fopen("acount.dat", "r");
    result = CheckUsername(fptr, username);
    fclose(fptr);
    if(result == 1){
        char text2[40] = "This username has already taken!";
        BeautifulPrinting(255, 0, 0, text2, 100);
        delay(100);
        system("cls");
        GetUsername(username);

    }
}

int CheckWordExist(FILE* fptr, char word[]){
    words temp = {"",0};
    rewind(fptr);
    int result = 1;
    while(!feof(fptr)){
        fread(&temp,sizeof(words), 1,fptr);
        result = strcmp(word,temp.word);
        if(result == 0){
            return 1;
        }
   }
   return 0;
}

void GetPassword( char password[]){
    int a = 0, b = 0, c = 0, i = 0, d = 0;
    printf("please enter your password :\n");
    change_color_rgb(255, 0, 0);
    printf("password should be at least 8 character\n");
    reset_color();
    change_color_rgb(255, 0, 0);
    printf("password should have A-Z , a-z , 0-9 , special characters(! . ? @ #) \n");
    reset_color();
    scanf("%29s", password);
    if(strlen(password) < 8){
        system("cls");
        GetPassword(password);
    }
    while(password[i]){
        if(password[i] >= 48 && password[i] <= 57){
            a = 1;
        }
        else if(password[i] >= 65 && password[i] <= 90){
            b = 1;
        }
        else if(password[i] >= 97 && password[i] <= 122){
            c = 1;
        }
        else if(password[i] == 33 || password[i] == 46 || password[i] == 63 || password[i] == 64 || password[i] == 35 ){
            d = 1;
        }
        i++;
    }
    if(a + b + c + d != 4){
        system("cls");
        GetPassword(password);
    }
}

int login(char username[], char password[], FILE * fptr){
    client temp = {"","",0,0};
    int usernameCheck = 1;
    int passwordCheck = 1;
    rewind(fptr);
    while(!feof(fptr)){
        fread(&temp,sizeof(client), 1,fptr);
        usernameCheck = strcmp(username,temp.UserName);
        if(usernameCheck == 0){
            passwordCheck = strcmp(password,temp.password);
            if(passwordCheck == 0){
                return temp.code;
            }
            else {
                return -1;
            }
        }
    }
    return 0;
}
client GetLogin(FILE* fPtr){
    int check = 0;
    client person;
    char text1[40];
    printf("Please enter your username:\n");
    scanf("%s",person.UserName);
    system("cls");
    printf("Please enter your password:\n");
    scanf("%s",person.password);
    system("cls");
    check = login(person.UserName,person.password,fPtr);
    if(check == 0){
        strcpy(text1 , "This username doesn't exist!");
        BeautifulPrinting(255, 0, 0, text1, 100);
        delay(500);
        system("cls");
        
        person = GetLogin(fPtr);
    }
    else if(check <= 0){
        strcpy(text1 , "username or password is wrong!");
        BeautifulPrinting(255, 0, 0, text1, 100);
        delay(500);
        system("cls");
        
        person = GetLogin(fPtr);
    }
    else{
        fseek(fPtr, (check-100)*sizeof(client), SEEK_SET);
        fread(&person,sizeof(client), 1,fPtr);
    }
    return person;

}
void swap(client* x, client* y){
    client temp = *x;
    *x = *y;
    *y = temp;
}

void BubbleSort(client * personPtr, int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(personPtr[j].score < personPtr[j + 1].score){
                swap(&personPtr[j] , &personPtr[j + 1]);
            }
        }
    }
}

void GetWord(char word[]){
    int i = 0;
    char text3[50];
    system("cls");
    printf("Please enter the word :\n");
    change_color_rgb(255, 0, 0);
    printf("The word should be less than 20 character!\n");
    printf("please use a-z.\n");
    reset_color();
    scanf("%s", word);
    if(strlen(word) > 20){
        system("cls");
        change_color_rgb(255, 0, 0);
        printf("This word has more than 20 character!\n");
        reset_color();
        delay(1000);
        GetWord(word);
    }
    else{
        while(word[i]){
            if(word[i] >= 97 && word[i] <= 122){
            }
            else{
                system("cls");
                strcpy(text3 , "Please just use a-z!");
                BeautifulPrinting(255, 0, 0, text3, 100);
                delay(1000);
                GetWord(word);
            }
            i++;
        }
    }    
                        
}

void ASCIIPrint_o(){
    change_color_rgb(255, 204, 92);
    cursor_to_pos(8 , 21);
    printf("  ___");
    cursor_to_pos(9 , 21);
    printf(" / _ \\");
    cursor_to_pos(10 , 21);
    printf("| (_) |");
    cursor_to_pos(11 , 21);
    printf(" \\___/");
    reset_color();
} 

void ASCIIPrint_r(){
    change_color_rgb(255, 204, 92);
    cursor_to_pos(8 , 43);
    printf(" _ __");
    cursor_to_pos(9 , 43);
    printf("| '__|");
    cursor_to_pos(10 , 43);
    printf("| |");
    cursor_to_pos(11 , 43);
    printf("|_|");
    reset_color();
}

void ASCIIPrint_e(){
    change_color_rgb(255, 204, 92);
    cursor_to_pos(8 , 35);
    printf("  ___");
    cursor_to_pos(9 , 35);
    printf(" / _ \\");
    cursor_to_pos(10 , 35);
    printf("|  __/");
    cursor_to_pos(11 , 35);
    printf(" \\___|");
    reset_color();
}


void ASCIIPrint_s(){
    change_color_rgb(255, 204, 92);
    cursor_to_pos(8 , 29);
    printf(" ___");
    cursor_to_pos(9 , 29);
    printf("/ __|");
    cursor_to_pos(10 , 29);
    printf("\\__ \\");
    cursor_to_pos(11 , 29);
    printf("|___/"); 
    reset_color();
}

void ASCIIPrint_L(){
    change_color_rgb(255, 204, 92);
    cursor_to_pos(7 , 12);
    printf(" _");
    cursor_to_pos(8 , 12);
    printf("| |");
    cursor_to_pos(9 , 12);
    printf("| |");
    cursor_to_pos(10 , 12);
    printf("| |____");
    cursor_to_pos(11 , 12);
    printf("|______|");
    reset_color();
}

void ASCIIPrint(){
    change_color_rgb(255, 204, 92);
    printf("      _\n      \\ \\\n ______\\ \\\n|______/ /\n      /_/\n");
    reset_color();
}

void FindChar(char word[] , int charPosition[] , char check){
    int i = 0;
    int j = 0;
    charPosition[j] = 0;
    while(word[i]){
        if(word[i] == check){
            charPosition[j] = (i + 1);
            j++;
            charPosition[j] = 0;
        }
        i++;
    }
    
}

int checkChar(char used[] , char check){
    for(int i = 0; i < 11; i++){
        if(used[i] == check){
            return 1;
        }
    }
    return 0;
}

void Print(int a){
    if(a == 4){
        ASCIIPrint_L();
    }
    else if(a == 3){
        ASCIIPrint_o();
    }
    else if(a == 2){
        ASCIIPrint_s();
    }
    else if(a == 1){
        ASCIIPrint_e();
    }
    else if(a == 0){
        ASCIIPrint_r();
    }
}

int main(){
    system("cls");
    int col =  get_window_cols();
    int row = get_window_rows();
    int i = 0;
    int j = 0;
    int counter = 0;
    client person = {"","",0,0};
    client temp = {"","",0,0};
    client temp2 = {"", "", 0, 0};
    FILE* fPtr = NULL;
    fPtr = fopen("acount.dat" , "ab");
    fclose (fPtr);
    char text1[60] = "wellcome to LOSER game!";
    BeautifulPrinting(41, 168, 171, text1, 100);
    delay(500);
    system("cls");
    change_color_rgb(136, 116, 163);
    printf("1. Login\n2. Signup\n3. Exit\n");
    reset_color();
    fflush(stdin);
    char selected = getchar();
    if (selected != '1' && selected != '2' && selected != '3'){
        change_color_rgb(255, 0, 0); 
        printf("Please enter 1 or 2 or 3 !\n");
        reset_color();
        fflush(stdin);
        selected = getchar();
    }
    switch(selected){
        case '1':{
            system("cls");
            fPtr = fopen("acount.dat","rb");
            person = GetLogin(fPtr);
            fclose(fPtr);
            strcpy(text1 , "login succesful!");
            BeautifulPrinting(41, 168, 171, text1, 100);
            puts("");
            strcpy(text1 , "wellcome ");
            BeautifulPrinting(41, 168, 171, text1, 100);
            strcpy(text1 , person.UserName);
            BeautifulPrinting(41, 168, 171, text1, 100);
            delay(1000);
            system("cls");
            fPtr = fopen("words.dat" , "ab");
            fclose(fPtr);
            words myWord = {"",0};
            change_color_rgb(136, 116, 163);
            printf("1. Start game\n2. Show learderboard\n3. New word\n4. Change password\n5. Exit\n");
            reset_color();
            fflush(stdin);
            selected = getchar();
            while(selected != '5'){
                switch(selected){
                    case '1':{
                        system("cls");
                        fPtr = fopen("words.dat" , "rb+");
                        fseek (fPtr, 0, SEEK_END);
                        int size = ftell(fPtr);
                        fclose(fPtr);
                        if(size == 0){
                            change_color_rgb(255, 0, 0);
                            printf("Unfortunately we don't have any word :\\\n");
                            reset_color();
                            delay(2000);
                            system("cls");

                            break;
                        }
                        strcpy(text1 , "Are you ready!?\n");
                        BeautifulPrinting(254, 215, 102, text1, 100);
                        delay(1000);
                        system("cls");
                        counter = (rand() % (size / sizeof(words)));
                        fPtr = fopen("words.dat" , "rb+");
                        fseek(fPtr, counter * sizeof(words), SEEK_SET);
                        fread(&myWord, sizeof(words), 1, fPtr);
                        int mistake = 0;
                        if(myWord.score < 8){
                            strcpy(text1 , "You can make 5 mistakes!");
                            mistake = 5;
                            BeautifulPrinting(238, 64, 53, text1, 100);
                        }
                        else{
                            strcpy(text1 , "You can make 10 mistakes!");
                            mistake = 10;
                            BeautifulPrinting(238, 64, 53, text1, 100);
                        }
                        delay(1000);
                        system("cls");
                        cursor_to_pos(1, 1);
                        change_color_rgb(53, 167, 156);
                        printf("The word is: ");
                        reset_color();
                        for(i = 0; i < myWord.score; i++){
                            printf("-");
                        }
                        cursor_to_pos(6, 1);
                        for(i = 0; i < col; i++){
                            printf("-");
                        }
                        cursor_to_pos(7, 1);
                        ASCIIPrint();
                        cursor_to_pos(3, 1);
                        change_color_rgb(253, 244, 152);
                        printf("Your guess(es): \n");
                        change_color_rgb(238, 64, 53);
                        printf("remaining mistake(S): %d" , mistake);
                        reset_color();
                        char guess = 0;
                        int charPosition[21];
                        char UsedChar[11];
                        for(j = 0; j < 11; j++){
                            UsedChar[j] = 0;
                        }
                        j = 0;
                        char CompleteWord[21];
                        for(int k = 0; k < myWord.score; k++){
                            CompleteWord[k] = '1';
                        }
                        for(int k = myWord.score; k < 21; k++){
                            CompleteWord[k] = '\0';
                        }
                        while(1){
                            cursor_to_pos(3, (strlen("Your guess(es):  ") + j));
                            fflush(stdin);
                            guess = getchar();
                            if (guess <= 90 && guess >= 65){
                                guess += 32;
                            }
                            if(checkChar(UsedChar , guess) == 1){
                                cursor_to_pos(2,1);
                                strcpy(text1 , "You have used this character once!");
                                BeautifulPrinting(255, 0, 0, text1, 100);
                                delay(1000);
                                cursor_to_pos(2,1);
                                for(int k = 0; k <= strlen("You have used this character once!"); k++){
                                    printf(" ");
                                }
                            }
                            UsedChar[j] = guess;
                            FindChar(myWord.word, charPosition, guess);
                            i = 0;
                            if(charPosition[i] == 0){
                                cursor_to_pos(2,1);
                                strcpy(text1 , "wrong guess!");
                                BeautifulPrinting(255, 0, 0, text1, 100);
                                delay(1000);
                                cursor_to_pos(2,1);
                                for(int k = 0; k <= strlen("wrong guess!"); k++){
                                    printf(" ");
                                }
                                mistake--;
                                if(myWord.score < 8){
                                    Print(mistake);
                                    cursor_to_pos(4 , 1);
                                    change_color_rgb(238, 64, 53);
                                    printf("remaining mistake(S): %d" , mistake);
                                    reset_color();
                                    if(mistake == 0){
                                        delay(2000);
                                        system("cls");
                                        strcpy(text1 , "you lose :(");
                                        BeautifulPrinting(255, 167, 0, text1, 100);
                                        puts("");
                                        strcpy(text1 , "Your score is: ");
                                        BeautifulPrinting(255, 167, 0, text1, 100);
                                        char num[20];
                                        sprintf(num, "%d", person.score);
                                        strcpy(text1 , num);
                                        BeautifulPrinting(255, 167, 0, text1, 100);
                                        delay(1500);
                                        system("cls");
                                        break;
                                    }
                                }
                                else{
                                    if((mistake % 2) == 0){
                                        Print(mistake/2);
                                        cursor_to_pos(4 , 1);
                                        change_color_rgb(238, 64, 53);
                                        printf("remaining mistake(S): %d" , mistake);
                                        reset_color();
                                        if(mistake == 0){
                                            delay(2000);
                                            system("cls");
                                            strcpy(text1 , "you lose :(");
                                            BeautifulPrinting(255, 167, 0, text1, 100);
                                            puts("");
                                            strcpy(text1 , "Your score is: ");
                                            BeautifulPrinting(255, 167, 0, text1, 100);
                                            char num[20];
                                            sprintf(num, "%d", person.score);
                                            strcpy(text1 , num);
                                            BeautifulPrinting(255, 167, 0, text1, 100);
                                            delay(1500);
                                            system("cls");
                                            break;
                                        }
                                    }
                                    else{
                                        cursor_to_pos(4 , 1);
                                        change_color_rgb(238, 64, 53);
                                        printf("remaining mistake(S): %d" , mistake);
                                        reset_color();
                                    }
                                }

                               
                            }
                            while(charPosition[i]){
                                cursor_to_pos(1, (strlen("The word is: ") + charPosition[i]));
                                printf("%c", guess);
                                CompleteWord[(charPosition[i] - 1)] = guess;
                                i++;
                            }
                            j++;
                            if(strcmp(CompleteWord , myWord.word) == 0){
                            delay(1500);
                            system("cls");
                            strcpy(text1 , "you win :)");
                            BeautifulPrinting(255, 167, 0, text1, 100);
                            puts("");
                            person.score += myWord.score;
                            fPtr = fopen("acount.dat" , "rb+");
                            fseek(fPtr , (person.code - 100) * sizeof(client) , SEEK_SET);
                            fwrite(&person , sizeof(client) , 1 , fPtr);
                            fclose(fPtr);
                            strcpy(text1 , "Your score is: ");
                            BeautifulPrinting(255, 167, 0, text1, 100);
                            char num[20];
                            sprintf(num, "%d", person.score);
                            strcpy(text1 , num);
                            BeautifulPrinting(255, 167, 0, text1, 100);
                            delay(1500);
                            system("cls");
                            fflush(stdin);
                            break;
                            }
                        }
                
                        break;
                    }
                    case '2':{
                        client * personPtr = (client *) malloc(1000 * sizeof(client));
                        fPtr = fopen("acount.dat" , "rb+");
                        rewind(fPtr);
                        while(!feof(fPtr)){
                            fread(&personPtr[i], sizeof(client), 1, fPtr);
                            i++;
                        }
                        int a = sizeof(client);
                        fseek(fPtr, -1 * a, SEEK_END);
                        fread(&temp2, sizeof(client), 1, fPtr);
                        counter = temp2.code - 99;
                        BubbleSort(personPtr , counter);
                        for(i = 0; i < counter; i++){
                            printf("%s", personPtr[i].UserName);
                            for(int j = 0; j < (25 - strlen(personPtr[i].UserName)); j++){
                                printf("-");
                            }
                            printf("%d", personPtr[i].score);
                            puts("");
                        }
                        free(personPtr);
                        break;
                    }
                    case '3':{
                        GetWord(myWord.word);
                        fPtr = fopen("words.dat" , "rb+");
                        int result = CheckWordExist(fPtr , myWord.word);
                        if( result == 1){
                            system("cls");
                            strcpy(text1 , "This word has been added!");
                            BeautifulPrinting(214, 45, 32, text1, 100);
                            delay(1000);
                            system("cls");
                            break;
                        }
                        else{
                            myWord.score = strlen(myWord.word);
                            words temp3 = {"", 0};
                            fPtr = fopen("words.dat", "ab+");
                            fwrite(&myWord, sizeof(words),1,fPtr);
                            fclose(fPtr);
                            system("cls");
                            strcpy(text1 , "The word succesfully added.\nThanks for your coopration :)");
                            BeautifulPrinting(15, 193, 247, text1, 100);
                            delay(1000);
                            system("cls");
                            break;
                        }
                    }
                    case '4':{
                        system("cls");
                        printf("Please enter your old password:\n");
                        char pass[50];
                        scanf("%s",pass);
                        fPtr = fopen("acount.dat" , "rb+");
                        int checks = login(person.UserName,pass,fPtr);
                        fclose(fPtr);
                        if(checks <= 0){
                            strcpy(text1 , "password is wrong!");
                            BeautifulPrinting(255, 0, 0, text1, 100);
                            delay(500);
                            system("cls");
                            break;
                        }
                        else{
                            system("cls");
                            GetPassword(person.password);
                            fPtr = fopen("acount.dat" , "rb+");
                            fseek(fPtr , (person.code - 100) * sizeof(client) , SEEK_SET);
                            fwrite(&person , sizeof(client) , 1 , fPtr);
                            fclose(fPtr);
                            system("cls");
                            strcpy(text1 , "Your password succesfuly changed!");
                            BeautifulPrinting(0, 255, 0, text1, 100);
                            delay(1000);
                            system("cls");
                        }
                        break;
                    }
                    default :{
                        change_color_rgb(255, 0, 0); 
                        printf("Please enter 1 or 2 or 3 or 4 or 5 !\n");
                        reset_color();
                        delay(1000);
                        system("cls");
                        break;
                    }
                }
                strcpy(text1 , "What do you want to do now?\n");
                BeautifulPrinting(255, 255, 0, text1, 100);
                change_color_rgb(136, 116, 163);
                printf("1. Start game\n2. Show learderboard\n3. New word\n4. Change password\n5. Exit\n");
                reset_color();
                fflush(stdin);
                selected = getchar();
            }
            system("cls");
            change_color_rgb(255, 255, 51);
            printf("bye!");
            delay(1000);
            reset_color();
            quit();
        }
            break;
        case '2':{
            client temp = {"","",0,0};
            system("cls");
            GetUsername(person.UserName);
            system("cls");
            GetPassword(person.password);
            person.score = 0;
            person.code = 100;
            fPtr = fopen("acount.dat", "ab+");
            while(!feof(fPtr)){
                fread(&temp,sizeof(client), 1,fPtr);
            }
            if(temp.code == 0){
                fwrite(&person, sizeof(client),1,fPtr);
            }
            else{
                person.code = ++temp.code;
                fwrite(&person, sizeof(client),1,fPtr);
            }
            fclose(fPtr);
            system("cls");
            strcpy(text1 , "you signed up succesfuly!");
            BeautifulPrinting(0, 255, 0, text1, 100);
            puts("");
            strcpy(text1 , "see you soon! :)");
            BeautifulPrinting(0, 255, 0, text1, 100);
            delay(500);
            quit();
        }
                break;
        case '3':{
            system("cls");
            change_color_rgb(255, 255, 51);
            printf("bye!");
            delay(1000);
            reset_color();
            quit();
        }         
                break;
        default :{
            change_color_rgb(255, 255, 51);
            printf("Kiding me?\n");
            delay(200);
            printf("bye!");
            delay(1000);
            reset_color();
            quit();
        }
                break;
    }
    
    return 0;
}