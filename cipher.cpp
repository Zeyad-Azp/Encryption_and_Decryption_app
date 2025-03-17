#include <iostream>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

void main_menu(){
    cout << "What do you like to do?\n";
    cout << "1- Cipher a message\n";
    cout << "2- Decipher a message\n";
    cout << "3- Exit\n";
}

void cipher_menu(){
    cout << "Which Cipher do you like to choose?\n";
    cout << "1- Affine Cipher\n";
    cout << "2- Vignere Cipher\n";
    cout << "3- Morse Code\n";
    cout << "4- Return\n";
}

int mOdeLsInvers(int a, int m) {
    for (int x = 1; x < m; x++) {
        if (((a % m) * (x % m) % m == 1)) {
            return x;
        }
    }
     // If no inverse found
    return -1;
}

string enCryptCipher(string enCrypt, int a, int b) {
    string meSSage = "";
    for (int i = 0; i < enCrypt.length(); i++) {
        if (enCrypt[i] != ' ' && !(isdigit(enCrypt[i]))) {
            int x = toupper(enCrypt[i]) - 'A';
            int enCryptedChar = (a * x + b) % 26;
            if (enCryptedChar < 0)
                // Handle negative values
                enCryptedChar = 26 + enCryptedChar;
            // Convert back to character
            meSSage += char('A' + enCryptedChar);
        } else {
            // check If it's a space to keep it .
            meSSage += enCrypt[i];
        }
    }
    return meSSage;
}


void cipher_affine(string message ,int a ,int b , int c){
    do {
        cout << "** Please enter the first key (a):\n";
        while (!(cin >> a) || cin.peek() != '\n') {
            cout << "** Invalid input. please enter a integer number\n";
            cout << "** Please enter the first key (a):\n";
            // Clear the error state flags
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cout << "\n";
        c = mOdeLsInvers(a, 26);// Find modular inverse for 'a'
        if (c == -1)
            cout<< "**The entered value for 'a' does not have an integer inverse. Please enter another +ve integer number.\n\n";
        // Repeat until 'a' has an inverse
    } while (c == -1);

    cout << "** Please enter the second key (b):\n";
    while (!(cin >> b) || cin.peek() != '\n') {
        cout << "** Invalid input. please enter a integer number\n";
        cout << "** Please enter the first key (b):\n";
        cin.clear();
        // Discard invalid input from the buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }
    cout << "*The keys:\n";
    cout << "a = " << a << "\nb = " << b << "\nc = " << c << "\n\n";
    cout << "Please enter message for encryption:\n";
    cin.ignore();
    {
        string CipherText = enCryptCipher(message, a, b);
        cout << "The encrypted message is: " << CipherText << "\n\n";
    }

}


bool check_sAlpha(string k){
    for (int i = 0 ; i < size(k) ; i++)
    {
        if (!isalpha(k[i]))
        {
            return true;
        }
    }
    return false;
}

string cipher_vignere(string message){
    string keyword, result = "";
    int res;
    while (size(message) > 80)
    {
        cout << "Invalid message! Enter a message which its size don't bigger than 80 letters\n";
        getline(cin, message);
    }
    do {
        cout << "please Enter the keyword which its size don't bigger than 8 letters and olny alphabetic characters:\n";
        getline(cin, keyword);
    } while (size(keyword) > 8 || check_sAlpha(keyword));
    for (int i = 0 ; i < size(message) ;)
    {
        for (int j = 0 ; j < size(keyword) ; j++)
        {
            if(i == size(message))
            {
                break;
            }
            if (!isalpha(toupper(message[i])))
            {
                result += toupper(message[i]);
                i++;
                continue;
            }
            res = toupper(message[i]) + toupper(keyword[j]);
            i++;
            res %= 26;
            res += 65;
            result += char(res);
        }
    }
    result = "The encrypted message is: " + result;
    return result;
}

char chars[] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
        'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' , ' '
};
string morse[] =

        { ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
          "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
          "..-","...-",".--","-..-","-.--","--..","-----",".----",
          "..---","...--","....-",".....","-....","--...","---..","----." , " "
        };

string cipher_morse(string text) {
    string con;
    // Loop through each character in the input text
    for (char x : text) {
        // Check if the character is a letter, number, or space
        for (int i = 0; i < 38; i++) {
            if (isspace(x)) {
                continue;
            }
            if (chars[i] == tolower(x)) {
                // If the character matches, add its Morse code representation to the result string
                con += morse[i] + " ";
                break;
            }
        }
        // Add three spaces after every word
        if (isspace(x)) {
            continue;
        }
    }

    // Print the ciphered text
    cout << "Your ciphered text: \n\n" << con << endl;
    return con;
}

string deCryptCipher(string deCrypt, int b, int c) {
    string messaGe = "";
    for (int j = 0; j < deCrypt.length(); j++) {
        if (deCrypt[j] != ' ' && !(isdigit(deCrypt[j]))) {
            int y = toupper(deCrypt[j]) - 'A';
            int deCryptedChar = (c * (y - b)) % 26;
            if (deCryptedChar < 0)
                // Handle negative values
                deCryptedChar = 26 + deCryptedChar;
            // Convert back to character
            messaGe += char('A' + deCryptedChar);
        } else {
            // check If it's a space to keep it .
            messaGe += deCrypt[j];
        }
    }
    return messaGe;
}



void decipher_affine(string message ,int a ,int b , int c){
    do {
        cout << "** Please enter the first key (a):\n";
        while (!(cin >> a) || cin.peek() != '\n'){
            cout <<"** Invalid input. please enter a integer number\n";
            cout << "** Please enter the first key (a):\n";
            // Clear the error state flags
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cout <<"\n";
        c = mOdeLsInvers(a, 26); // Find modular inverse for 'a'
        if (c == -1)
            cout << "**The entered value for 'a' does not have an integer inverse. Please enter another +ve integer number.\n\n";

        // Repeat until 'a' has an inverse
    } while (c == -1);
    cout << "** Please enter the second key (b):\n";
    while (!(cin >> b) || cin.peek() != '\n'){
        cout <<"** Invalid input. please enter a nteger number\n";
        cout << "** Please enter the first key (b):\n";
        cin.clear();
        // Discard invalid input from the buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }
    cout << "*The keys:\n";
    cout << "a = " << a << "\nb = " << b << "\nc = " << c << "\n\n";
    cout << "Please enter message for decryption:\n";
    cin.ignore();
    {
        string unCipherText = deCryptCipher(message, b, c);
        cout << "The decrypted message is: " << unCipherText << "\n\n";
    }
}



string decipher_vignere(string message){
    string keyword , result = "";
    int res , riminder;
    while (size(message) > 80)
    {
        cout << "Invalid message! Enter a message which its size don't bigger than 80 letters\n";
        getline(cin, message);
    }

    do {
        cout << "please Enter the keyword which its size don't bigger than 8 letters and olny alphabetic characters:\n";
        getline(cin, keyword);
    } while (size(keyword) > 8 || check_sAlpha(keyword));
    for (int i = 0 ; i < size(message) ;)
    {
        for (int j = 0 ; j < size(keyword) ; j++)
        {
            if(i == size(message))
            {
                break;
            }
            if (!isalpha(toupper(message[i])))
            {
                result += message[i];
                i++;
                continue;
            }
            riminder = toupper(message[i]) - 65;
            for (int k = 4 ; k < 7 ; k++)
            {
                res = 26 * k + riminder - toupper(keyword[j]);
                if (res >= 65 && res <= 90)
                {
                    result += char(res);
                    i++;
                    break;
                }
            }
        }
    }
    return result;
}

string decipher_morse(string morse1) {

    for(char element : morse1)
    {
        if((element != '.' and element != '-' and element != ' '))
        {
            cout<<"please enter your morse code in ('.' / '-' )";
            break;
        }
    }

    string the_text = "";
    string decipher = "";
    // Loop through each character in the Morse code input
    for (char str : morse1) {
        // If the character is a space, decode the Morse sequence and add the corresponding character to the result string
        if (str == ' ') {
            if (decipher == "") {
                // If the decipher string is empty, add a space to the result string
                the_text += " ";
            } else {
                // Loop through the Morse code array to find the corresponding character
                for (int i = 0; i < 38; i++) {
                    if (decipher == morse[i]) {
                        the_text += chars[i];
                        break;
                    }
                }
                decipher = ""; // Reset decipher for the next Morse code sequence
            }
        } else {
            // If the character is not a space, accumulate Morse code sequence
            decipher += str;
        }
    }
    // Check if there's remaining Morse code at the end
    if (!decipher.empty()) {
        for (int i = 0; i < 38; i++) {
            if (decipher == morse[i]) {
                the_text += chars[i];
                break;
            }
        }
    }
    // Print the deciphered text
    cout << "Your text: " << the_text << endl;
    return the_text;
}


int main() {
    int choice1, choice2;
    int a , b ,c;
    string message;
    do{
        main_menu();
        while (!(cin >> choice1) || cin.peek() != '\n' || choice1 > 3)
        {
            cout <<"**Invalid choice. please enter a integer number between 1 and 3.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choice1 == 1)
        {
            cin.ignore();
            cout << "Please enter the message to cipher:\n";
            getline(cin, message);
            cipher_menu();
            while (!(cin >> choice2) || cin.peek() != '\n' || choice2 > 4)
            {
                cout << "**Invalid choice. please enter an integer number between 1 and 4.\n\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (choice2 == 1)
            {
                cin.ignore();
                cipher_affine(message ,a ,b ,c) ;

            }
            else if (choice2 == 2)
            {
                cin.ignore();
                cout << cipher_vignere(message) << '\n';
            }
            else if (choice2 == 3)
            {
                cin.ignore();
                cipher_morse(message);
            }
            else if (choice2 == 4)
            {
                cout << "thx to using this program";
                return 0;
            }
        }
        else if (choice1 == 2)
        {
            cin.ignore();
            cout << "Please enter the message to decipher:\n";
            getline(cin, message);
            cipher_menu();
            while (!(cin >> choice2) || cin.peek() != '\n' || choice2 > 4)
            {
                cout << "**Invalid choice. please enter an integer number between 1 and 4.\n\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (choice2 == 1)
            {
                cin.ignore();
                decipher_affine(message ,a ,b ,c) ;

            }
            else if (choice2 == 2)
            {
                cin.ignore();
                cout << decipher_vignere(message) << '\n';
            }
            else if (choice2 == 3)
            {
                cin.ignore();
                decipher_morse(message);
            }
            else if (choice2 == 4)
            {
                cout << "thx to using this program";
                return 0;
            }
        }
        else if (choice1 == 3)
        {
            cout << "thx to using this program";
            return 0;
        }
    } while (choice1 != 3);
}