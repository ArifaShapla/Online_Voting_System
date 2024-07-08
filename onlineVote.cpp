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
Voter* searchVoterByNID(int NIDnumber)
{
    for (int i = 0; i < voterCount; i++)
    {
        if (voters[i].NIDnumber == NIDnumber)
        {
            return &voters[i];
        }
    }

    return nullptr;
}

void searchVoter(int NIDnumber)
{
    Voter* searchedVoter = searchVoterByNID(NIDnumber);

    if (searchedVoter != nullptr)
    {
        cout << "Voter found with NID number: " << searchedVoter->NIDnumber << endl;
        cout << "Name: " << searchedVoter->name << endl;
        cout << "Vote: ";
        switch (searchedVoter->vote)
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

     else
    {
        cout << "Voter not found with NID number: " << NIDnumber << endl;
    }
}

void deleteVoter(int index)
{
    if (voters[index].vote >= 1 && voters[index].vote <= MAX_PARTIES)
    {
        votes[voters[index].vote - 1]--;
    }

    for (int i = index; i < voterCount - 1; i++)
    {
        voters[i] = voters[i + 1];
    }

    voterCount--;
    saveVoters();
}

int findVoterIndexByNID(int NIDnumber)
{
    for (int i = 0; i < voterCount; i++)
    {
        if (voters[i].NIDnumber == NIDnumber)
        {
            return i;
        }
    }

    return -1;
}

void voterPanel()
{
    int voterNID;
    cout << "Enter your NID number to access the voter panel: ";
    cin >> voterNID;

    Voter* voter = searchVoterByNID(voterNID);

    if (voter != nullptr)
    {
        cout << "Welcome, " << voter->name << "!\n";
        cout << "Voter Panel:\n1. View Political Parties\n2. Vote\n0. Exit\n";
        int voterChoice;
        cin >> voterChoice;

        switch (voterChoice)
        {
        case 1:
            viewParties();
            break;
        case 2:
 {
            cout << "List of political parties:" << endl;
            viewParties();
            int vote;
            cout << "Select your political party (enter the party number): ";
            cin >> vote;

            if (vote >= 1 && vote <= MAX_PARTIES)
            {
                castVote(vote);
                voter->vote = vote;
                saveVoters();
                cout << "Vote cast successfully!\n";
            }
            else
            {
                spoiltVotes++;
                cout << "Invalid party number. Vote spoiled.\n";
            }
 break;
        }
        case 0:
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    else
    {
        cout << "Voter not found with NID number: " << voterNID << endl;
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
             case 5:
        {
            int NIDnumber;
            cout << "Enter NIDnumber of the voter to search: ";
            cin >> NIDnumber;
            searchVoter(NIDnumber);
            break;
        }
        case 6:
        {
            int NIDnumber;
            cout << "Enter NIDnumber of the voter to delete: ";
            cin >> NIDnumber;

            int voterIndex = findVoterIndexByNID(NIDnumber);

            if (voterIndex != -1)
            {
                char confirm;
                cout << "Do you want to delete this voter? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y')
 {
                    deleteVoter(voterIndex);
                    cout << "Voter deleted successfully!\n";
                }
                else
                {
                    cout << "Voter not deleted.\n";
                }
            }
            else
            {
                cout << "Voter not found with NID number: " << NIDnumber << endl;
            }
            break;
        }

        case 7:
            announceWinner();
            break;

         case 0:
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    while (adminChoice != 0);
     int voterPanelChoice;
    do
    {
        cout << "Voter Panel:\n1. View Political Parties\n2. Vote\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> voterPanelChoice;

        switch (voterPanelChoice)
        {
        case 1:
            voterPanel();
            break;
        case 2:
        {
            int NIDnumber;
            int vote;
            string name;


            cout << "Enter your NID number: ";
            cin >> NIDnumber;
            cout << "Enter your name: ";
            cin >> name;
cout << "List of political parties:" << endl;
            viewParties();
            cout << "Select your political party (enter the party number): ";
            cin >> vote;

            if (vote >= 1 && vote <= MAX_PARTIES)
            {
                castVote(vote);
                createVoter(NIDnumber, name, vote);
            }
            else
            {
                spoiltVotes++;
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (voterPanelChoice != 0);

    return 0;
}
