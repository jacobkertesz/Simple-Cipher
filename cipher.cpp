#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
using namespace std;

class Cipher 
{
    private:
        vector<char> characters = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0',' ','-'};
        string setting = "-";

    public:
        void setSetting(string s) //setter
        {
            setting = s;
        }
        string getSetting() //getter
        {
            return setting;
        }

        //methods
        string encryptText(string text)
        {
            string encryption = "";

            for (int i = 0; i < text.length(); i++)
            {
                if (text[i] == '\n')
                {
                    encryption += text[i];
                }
                else
                {
                    char c = tolower(text.at(i));

                    int baseI = findIndex(c);
                    int settingI = findIndex(setting.at(i % setting.size())) + 1;

                    int encryptI = (baseI + settingI) % characters.size();
                    encryption += characters[encryptI];
                }
            }
            return encryption;
        }

        string decryptText(string text)
        {
            string decryption =  "";

            for (int i = 0; i < text.length(); i++)
            {
                if (text[i] == '\n')
                {
                    decryption += text[i];
                }
                else
                {
                    int baseI = findIndex(text.at(i));
                    int settingI = findIndex(setting.at(i % setting.size())) + 1;

                    int decryptI = (baseI - settingI + characters.size()) % characters.size();
                    decryption += characters[decryptI];
                }
            }
            return decryption;
        }

        int findIndex(char target)
        {
            int output = 37;
            for (int i = 0; i < characters.size(); i++)
            {
                if (target == characters[i])
                {
                    output = i;
                }
            }
            return output;
        }
};

int main()
{
    //Classes
    Cipher cipher;
    ifstream inputFile("cipherInput.txt");
    
    //Variables
    string input;
    string command;
    char ch;
    string output;

    //Read File
    while (inputFile.get(ch)) //reads only the first line
    {
        if (ch == '\n') break;
        command += ch;
    }

    while (inputFile.get(ch)) //reads the rest of the file
    {
        input += ch;
    }
    inputFile.close();

    //Run decrypt or encrypt
    if (command[0] == 'd')
    {
        command.erase(0, 1);
        cipher.setSetting(command);
        output = cipher.decryptText(input);
    }
    else if (command[0] == 'e')
    {
        command.erase(0, 1);
        cipher.setSetting(command);
        output = cipher.encryptText(input);
    }
    else
    {
        output = "FAILED";
    }

    //Write to a file
    ofstream outputFile("cipherOutput.txt");
    outputFile.clear();
    outputFile << command << endl;
    outputFile << output;
    outputFile.close();

    return 0;
}