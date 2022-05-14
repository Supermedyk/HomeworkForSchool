#include <bits/stdc++.h>
#include <conio.h>


using namespace std;


struct subNET
{
    string sub_bitMask;
    string sub_broadcast;
    string sub_network;
    string sub_maxHost;
    string sub_minHost;
    unsigned long long int sub_amountOfHosts;
};

struct Page
{
    unsigned long long int howMany;
    vector <subNET> OUT;
};

class IP
{
private:
    const int powOfTwo[8] =
    {
        1,2,4,8,16,32,64,128
    };
    string binAdd(string bin1, int val)
    {
        string bin2 = bitset<32>(val).to_string();
        int len = bin1.size();
        string addRes = "";
        int carry = 0;
        int i,re;
        for(i=(len-1); i>-1; i--)
        {
            re = carry;
            if(bin1[i] == '1')
                re = re+1;
            else
                re = re+0;
            if(bin2[i] == '1')
                re = re+1;
            else
                re = re+0;
            if(re%2==1)
                addRes = '1' + addRes;
            else
                addRes = '0' + addRes;
            if(re<2)
                carry = 0;
            else
                carry = 1;
        }
        if(carry!=0)
            addRes = '1' + addRes;
        return addRes;
    }
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
        for (size_t i = 0; i < IP.length(); i++)
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
    string classCheck(string bin_IP)
    {
        if (bin_IP[0] == '0')
            return "A";
        else if (bin_IP[1] == '0')
            return "B";
        else if (bin_IP[2] == '0')
            return "C";
        else if (bin_IP[3] == '0')
            return "D";
        else
            return "E";
    }
    void lookOut(Page *in, unsigned long long int am, string binM, string bin_IP, unsigned long long int ones)
    {
        string lastM = binM;
        string lastIP = bin_IP;
        subNET buff;
        buff.sub_network = bin_IP;
        unsigned long long int counter = 0;
        unsigned long long int amount = ones;
        for (unsigned long long int i = 1; i <= am && i < 13; i++)
        {
            in[i-1].howMany = pow(2,i);
        }
        for (unsigned long long i = 0; i < am && i < 12; i++)
        {
            lastM = binM;
            amount = ones;
            counter = i+1;
            for (size_t j = 0; j < lastM.length(); j++)
            {
                if (counter == 0)
                    break;
                if (lastM[j] == '0')
                {
                    lastM[j] = '1';
                    counter--;
                    amount++;
                }
            }

            buff.sub_amountOfHosts = pow(2,32-amount)-2;
            if (pow(2,32-amount) - 2 <= 0)
                buff.sub_amountOfHosts = 0;
            buff.sub_bitMask = lastM;
            buff.sub_broadcast = broadcast(lastIP,amount);
            buff.sub_network = bin_IP;
            buff.sub_minHost = minHost(buff.sub_network);
            buff.sub_maxHost = maxHost(buff.sub_broadcast);
            in[i].OUT.push_back(buff);
            for (int j = 1; j < in[i].howMany; j++)
            {
                buff.sub_network = binAdd(buff.sub_broadcast,1);
                buff.sub_broadcast = broadcast(buff.sub_network,amount);
                buff.sub_minHost = minHost(buff.sub_network);
                buff.sub_maxHost = maxHost(buff.sub_broadcast);
                in[i].OUT.push_back(buff);
            }
        }
    }
    void outputPage(Page a)
    {
        cout << "Ilosc podsieci: " << a.howMany << "\n";
        int counter = 1;
        for (auto i: a.OUT)
        {
            cout << counter << ". Maska: " << binToDec(i.sub_bitMask) << "\n";
            cout << counter << ". Adres podsieci: " << binToDec(i.sub_network) << "\n";
            cout << counter << ". Adres rozgloszeniowy: " << binToDec(i.sub_broadcast) << "\n";
            cout << counter << ". Host max: " << binToDec(i.sub_maxHost) << "\n";
            cout << counter << ". Host min: " << binToDec(i.sub_minHost) << "\n";
            cout << counter << ". Ilosc hostow w podsieci: " << i.sub_amountOfHosts << "\n";
            counter++;
        }
    }
    string IpFromInput;
    string binIP;
    string binMask;
    string binNetwork;
    string binBroadcast;
    string oldClass;
    string binMinHost;
    string binMaxHost;
    vector<Page> book;
    Page* amountOfPages;
    char c;
    unsigned long long int evilThing = 0;
    unsigned long long int amountOfBits;
    unsigned long long int amountOfSubNETS;
public:
    IP()
    {
        cout << "Podaj IP: \n";
        cin >> IpFromInput;
        cout << "Podaj ilosc bitow: \n";
        cin >> amountOfBits;
        evilThing = 32-amountOfBits;
        evilThing = pow(2,evilThing)-2;
        binIP = ip_To_Binary(IpFromInput);
        binMask = bit_mask(amountOfBits);
        binNetwork = network(binIP,amountOfBits);
        binBroadcast = broadcast(binIP,amountOfBits);
        binMinHost = minHost(binNetwork);
        binMaxHost = maxHost(binBroadcast);
        oldClass = classCheck(binIP);
        amountOfSubNETS = 32-amountOfBits;
        cout << "Adres IP:              " << IpFromInput            << "\n";
        cout << "Maska:                 " << binToDec(binMask)      << "\n";
        cout << "Adres sieci:           " << binToDec(binNetwork)   << "\n";
        cout << "Adres rozgloszeniowy:  " << binToDec(binBroadcast) << "\n";
        cout << "Ilosc hostow w sieci:  " << evilThing              << "\n";
        cout << "Host min:              " << binToDec(binMinHost)   << "\n";
        cout << "Host max:              " << binToDec(binMaxHost)   << "\n";
        cout << "Klasa:                 " << oldClass               << "\n";
        if (amountOfSubNETS != 0)
        {
            amountOfPages = new Page [amountOfSubNETS];
            lookOut(amountOfPages,amountOfSubNETS,binMask,binNetwork,amountOfBits);
            cout << "Kliknij D by wyswietlic podzial podsieci \n";
            cout << "Kliknij X by zakonczyc program \n";
            while(true)
            {
                c = _getch();
                if (c == 'd' || c == 'D' || c == 'x' || c == 'X')
                {
                    break;
                }
            }
            int counter = 0;
            if (c != 'x' && c != 'X')
            {
                do
                {
                    system("cls");
                    outputPage(amountOfPages[counter]);
                    if (counter != amountOfSubNETS-1 && counter != 12)
                        cout << "Kliknij D by wyswietlic nastepna strone \n";
                    cout << "Kliknij X by zakonczyc program \n";
                    if (counter != 0)
                        cout << "Kliknij A by wrocic do poprzedniej strony \n";
                    while(true)
                    {
                        c = _getch();
                        if ( c == 'x' || c == 'X')
                        {
                            break;
                        }
                        if ((c == 'd' || c == 'D') && counter != 12 && counter != amountOfSubNETS-1)
                        {
                            counter++;
                            break;
                        }
                        if (c == 'A' || c == 'a' && counter != 0)
                        {
                            counter -= 1;
                            break;
                        }
                    }
                    if (c == 'x' || c == 'X')
                        break;
                }
                while(true);
            }
            system("cls");
            delete [] amountOfPages;
            amountOfPages = nullptr;
        }
    }
};

int main()
{
    cout.tie(0);
    IP output;
    return 0;
}
