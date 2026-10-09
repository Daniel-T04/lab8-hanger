#include "roster_io.h"
#include <fstream>
#include <sstream>

// TODO (Checkpoint 1): implement save_roster.
bool save_roster( const std::vector<Mech>& roster, const std::string& path) {
    std::ofstream file(path);
    if(!file.is_open()) {
    return false;

  }

    for (const auto& mech : roster) {
        file << mech.name() << ","
            << mech.hp() << ","
            << mech.attack() << ","
            << mech.armor() << "\n";
    

    }
     return true;

 }


// TODO (Checkpoints 2 and 3): implement load roster
bool load_roster(const std::string& path,
 std::vector<Mech>& roster,  int& skipped_lines) {

    std::ifstream in(path);
    if(!in.is_open()){
    return false;
}

    std::vector<Mech> temp_roster;
    skipped_lines = 0;
    std::string line;

    while(std::getline(in, line)){
    std::istringstream line_stream(line);
    std::string name_ss, hp_ss, attack_ss, armor_ss;

    if(!std::getline(line_stream, name_ss, ',' ) ||
    !std::getline(line_stream, hp_ss, ',' ) ||
    !std::getline(line_stream, attack_ss, ',' ) ||
    !std::getline(line_stream, armor_ss)) {
    skipped_lines++; 
    continue;
 }

    if(name_ss.empty()){
       skipped_lines++;
       continue;
    }

    auto parse_int = [](const std::string& ss, int& value) -> bool{
        std::istringstream iss(ss);
        if(!(iss >> value)) {
        return false;

    }

    iss >> std::ws;
    return iss.eof();
    };

    int hp = 0, attack = 0, armor = 0;
    if(!parse_int(hp_ss, hp) ||
       !parse_int(attack_ss, attack) ||
       !parse_int(armor_ss, armor)) {
        skipped_lines++;
        continue;
    }


    if(hp < 1 || attack < 0 || armor < 0){
       skipped_lines++;
       continue;
    }

    temp_roster.emplace_back(name_ss, hp, attack, armor);
 
  }

  roster = std::move(temp_roster);
  return true;

}

// TODO (Checkpoint 4): implement append_line.
bool append_line(const std::string& path,
const std::string& text) {
    std::ofstream file(path,std::ios::app);
    if(!file.is_open()){
        return false;
    }
    file << text << "\n";
    return true;
}

