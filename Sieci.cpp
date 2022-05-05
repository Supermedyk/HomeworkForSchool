#include <bits/stdc++.h>

using namespace std;

int powOfTwo[8] = {
    1,2,4,8,16,32,64,128
};

unsigned long long int evilThing = 0;

string numToBin(int in)
{
    string binaryOut = "";
    for (int i = 7; i > -1; i--)
    {
        if (in >= powOfTwo[i])
        {
            binaryOut += '1';
            in -= powOfTwo[i];
        }
        else
        {
            binaryOut += '0';
        }
    }
    return binaryOut;
}
string ip_To_Binary(string IP)
{
    int buffNum = 0;
    string binOut = "";
    for (int i = 0; i < IP.length(); i++)
    {
        if (IP[i] == '.')
        {
            binOut += numToBin(buffNum);
            buffNum = 0;
        }
        else
        {
            buffNum*=10;
            buffNum+=IP[i]-'0';
        }
    }
    binOut += numToBin(buffNum);
    return binOut;
}
string bit_mask(int amount)
{
    string out = "";
    for (int i = 1; i <= 32; i++)
    {
        if (i <= amount)
        {
            out +='1';
        }
        else
        {
            out += '0';
        }
    }
    return out;
}
string network(string bin_IP, int amount)
{
    string out = "";
    for (int i = 0; i < amount; i++)
    {
        out += bin_IP[i];
    }
    for (int i = 0; i < 32-amount; i++)
    {
        out += '0';
    }
    return out;
}
string broadcast(string bin_IP, int amount)
{
    string out = "";
    for (int i = 0; i < amount; i++)
    {
        out += bin_IP[i];
    }
    for (int i = 0; i < 32-amount; i++)
    {
        out += '1';
    }
    return out;
}
string minHost(string nt)
{
    string out = nt;
    out[31] = '1';
    return out;
}
string maxHost(string br)
{
    string out = br;
    out[31] = '0';
    return out;
}
string binToDec(string bin)
{
    int buffNum = 0;
    string out = "";
    string conv;
    for (int i = 0; i < 32;)
    {
        buffNum = 0;
        for (int j = 7; j > -1; j--,i++)
        {
            if (bin[i] == '1')
            {
                buffNum += powOfTwo[j];
            }
        }
        conv = to_string(buffNum);
        out+=conv;
        if (i < 31)
        {
            out+='.';
        }
    }
    return out;
}
int main()
{
    int amountOfBits;
    string mask="";
    string ipFromInput;
    cout << "Podaj IP\n";
    cin >> ipFromInput;
    cout << "Podaj ilosc bitow\n";
    cin >> amountOfBits;
    evilThing = 32-amountOfBits;
    evilThing = pow(2,evilThing)-2;
    system("cls");
    cout <<"Adres IP: "<<binToDec(ip_To_Binary(ipFromInput)) << "\n";
    cout <<"Maska: "<<binToDec(bit_mask(amountOfBits)) << "\n";
    cout <<"Adres sieci: "<<binToDec(network(ip_To_Binary(ipFromInput),amountOfBits)) << "\n";
    cout <<"Adres rozgloszeniowy: " << binToDec(broadcast(ip_To_Binary(ipFromInput),amountOfBits)) << "\n";
    cout << "Ilosc hostow w sieci: "<< evilThing <<"\n";
    cout << "Host min: " << binToDec(minHost(network(ip_To_Binary(ipFromInput),amountOfBits))) << "\n";
    cout << "Host max: " << binToDec(maxHost(broadcast(ip_To_Binary(ipFromInput),amountOfBits))) << "\n";
}

