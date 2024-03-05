#include <iostream>
#include <fstream>
#include "Leaderboard.h"

void Leaderboard::insert_new_entry(LeaderboardEntry * new_entry) {
    // TODO: Insert a new LeaderboardEntry instance into the leaderboard, such that the order of the high-scores
    //       is maintained, and the leaderboard size does not exceed 10 entries at any given time (only the
    //       top 10 all-time high-scores should be kept in descending order by the score).
    if (head_leaderboard_entry == nullptr) {
        head_leaderboard_entry = new_entry;
    } else {
        LeaderboardEntry *temp = head_leaderboard_entry;
        LeaderboardEntry *prev = nullptr;

        while (temp != nullptr && temp->score >= new_entry->score) {
            prev = temp;
            temp = temp->next_leaderboard_entry;
        }
        if (prev == nullptr) {
            new_entry->next_leaderboard_entry = head_leaderboard_entry;
            head_leaderboard_entry = new_entry;
        } else {
            prev->next_leaderboard_entry = new_entry;
            new_entry->next_leaderboard_entry = temp;
        }
        std::cout << "\n";
        int size = 0;
        temp = head_leaderboard_entry;
        while (temp != nullptr && size < 10) {
            std::cout<<temp->score<<" ";
            prev = temp;
            temp = temp->next_leaderboard_entry;
            size++;
        }
        delete temp;
        prev->next_leaderboard_entry= nullptr;

    }
}


void Leaderboard::write_to_file(const string& filename) {
    // TODO: Write the latest leaderboard status to the given file in the format specified in the PA instructions
    ofstream file(filename);
    LeaderboardEntry *temp = head_leaderboard_entry;
    if(file.is_open()){
        while (temp!= nullptr){
            file<<temp->score<<" "<<temp->last_played<<" "<<temp->player_name<<"\n";
            temp=temp->next_leaderboard_entry;
        }
    }
}


void Leaderboard::read_from_file(const string& filename) {
    // TODO: Read the stored leaderboard status from the given file such that the "head_leaderboard_entry" member
    //       variable will point to the highest all-times score, and all other scores will be reachable from it
    //       via the "next_leaderboard_entry" member variable pointer.
}


void Leaderboard::print_leaderboard() {
    // TODO: Print the current leaderboard status to the standard output in the format specified in the PA instructions
}

Leaderboard::~Leaderboard() {
    // TODO: Free dynamically allocated memory used for storing leaderboard entries
}
