#include <fstream>
#include <cstdlib>
#include <string>
#include<bits/stdc++.h>

using namespace std;

const int MAX_PARTIES = 6;
const int MAX_VOTERS = 50;

struct Voter
{
    int NIDnumber;
    int vote;
    string name;
};

struct PoliticalParty
{
    int partyNumber;
    string partyName;
};PoliticalParty parties[MAX_PARTIES];
Voter voters[MAX_VOTERS];

int votes[MAX_PARTIES] = {0};
int spoiltVotes = 0;
int voterCount = 0;

void saveVoters()
{
    ofstream file("voters.txt");
    for (int i = 0; i < voterCount; i++)
    {
        file << voters[i].NIDnumber << " " << voters[i].name << " " << voters[i].vote << endl;
    }
    file.close();
}

void loadVoters()
{
    ifstream file("voters.txt");
    if (!file)
        return;

    while (file >> voters[voterCount].NIDnumber >> voters[voterCount].name >> voters[voterCount].vote)
    {
        if (voters[voterCount].vote >= 1 && voters[voterCount].vote <= MAX_PARTIES)
        {
            votes[voters[voterCount].vote - 1]++;
        }
        else
        {
            spoiltVotes++;
        }
        voterCount++;
    }
    file.close();
}

void saveParties()
{
    ofstream file("parties.txt");
    for (int i = 0; i < MAX_PARTIES; i++)
    {
        file << parties[i].partyNumber << " " << parties[i].partyName << endl;
    }
    file.close();
}

void loadParties()
{
    ifstream file("parties.txt");
    if (!file)
        return;

    for (int i = 0; i < MAX_PARTIES; i++)
    {
        file >> parties[i].partyNumber >> parties[i].partyName;
    }
    file.close();
}

Voter* createVoter(int NIDnumber, string name, int vote)
{
    Voter* newVoter = nullptr;

    if (voterCount < MAX_VOTERS && vote >= 1 && vote <= MAX_PARTIES)
    {
        newVoter = &voters[voterCount++];
        newVoter->NIDnumber = NIDnumber;
        newVoter->name = name;
        newVoter->vote = vote;

        votes[vote - 1]++;
        saveVoters();
    }
    else
    {
        spoiltVotes++;
    }

    return newVoter;
}

void addVoter(int NIDnumber, string name)
{
    if (voterCount < MAX_VOTERS)
    {
        Voter* newVoter = &voters[voterCount++];
        newVoter->NIDnumber = NIDnumber;
        newVoter->name = name;
        newVoter->vote = 0;
        saveVoters();
    }
    else
    {
        cout << "Max voters reached. Cannot add more voters." << endl;
    }
}

void castVote(int vote)
{
    if (vote >= 1 && vote <= 3)
    {
        votes[vote - 1]++;
        saveVoters();
    }
    else
    {
        spoiltVotes++;
    }
}

void viewVotersNoVotes()
{
    cout << "List of Voters (without votes):" << endl;
    for (int i = 0; i < voterCount; i++)
    {
        cout << "NID: " << voters[i].NIDnumber << ", Name: " << voters[i].name << endl;
    }
}
void announceWinner()
{
    int maxVotesIndex = 0;
    for (int i = 1; i < 3; i++)
    {
        if (votes[i] > votes[maxVotesIndex])
        {
            maxVotesIndex = i;
        }
    }

    cout << "The winner is: ";
    switch (maxVotesIndex)
    {
    case 0:
        cout << "TIGER";
        break;
    case 1:
        cout << "LION";
        break;
    case 2:
        cout << "BLACK CAT";
        break;
    default:
        cout << "No winner";
    }
    cout << " with " << votes[maxVotesIndex] << " votes." << endl;
}

void addParty(int partyNumber, string partyName)
{
    if (partyNumber >= 1 && partyNumber <= MAX_PARTIES)
    {
        parties[partyNumber - 1].partyNumber = partyNumber;
        parties[partyNumber - 1].partyName = partyName;
        saveParties();
    }
    else
    {
        cout << "Invalid party number." << endl;
    }
}

void viewParties()
{
    cout << "List of Political Parties:" << endl;
    cout << "1.TIGER" << endl;
    cout << "2.LION" << endl;
    cout << "3.BLACK CAT" << endl;

    for (int i = 3; i < MAX_PARTIES; i++)
    {
        cout << parties[i].partyNumber << ". " << parties[i].partyName << endl;
    }
}

void viewVoters()
{
    cout << "List of Voters:" << endl;
    for (int i = 0; i < voterCount; i++)
    {
        cout << "NID: " << voters[i].NIDnumber << ", Name: " << voters[i].name << ", Voted for: ";
        switch (voters[i].vote)
        {
        case 1:
            cout << "TIGER";
            break;
        case 2:
            cout << "LION";
            break;
        case 3:
            cout << "BLACK CAT";
            break;
        default:
            cout << "Spoilt vote";
        }
        cout << endl;
    }
}
int main()
{
    loadVoters();
    loadParties();

    string userName;
    string userPassword;
    int loginAttempt = 0;

    while (loginAttempt < 5)
    {
        cout << "Admin user name: ";
        cin >> userName;
        cout << "Please enter your user password: ";
        cin >> userPassword;

        if (userName == "Shapla" && userPassword == "Shakib75")
        {
            cout << "Welcome Admin!\n";
            break;
        }

        else
        {
            cout << "Invalid login attempt. Please try again.\n" << '\n';
            loginAttempt++;
        }
    }
    if (loginAttempt == 5)
    {
        cout << "Too many login attempts! The program will now terminate.";
        return 0;
    }

    cout << "Thank you for logging in.\n";

    int adminChoice;
    do
    {
        cout << "\nAdmin Panel:\n1. Add Political\n2. Add Voter\n3. View Political Parties\n"
             << "4. View Voters\n5. Search Voter\n6. Delete Voter\n"
             << "7. Announce Winner\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> adminChoice;

        switch (adminChoice)
        {
        case 1:
        {
            int partyNumber;
            string partyName;
            cout << "Enter the party number (4-6): ";
            cin >> partyNumber;
            cout << "Enter the name of the political party: ";
            cin >> partyName;
            addParty(partyNumber, partyName);
            break;
        }

        case 2:
        {
            int NIDnumber;
            string name;
            cout << "Enter NIDnumber for the new voter: ";
            cin >> NIDnumber;
            cout << "Enter name: ";
            cin >> name;
            addVoter(NIDnumber, name);
            break;
        }

        case 3:
            viewParties();
            break;
        case 4:
            viewVotersNoVotes();
            break;
         case 0:
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    while (adminChoice != 0);
    return 0;
}
