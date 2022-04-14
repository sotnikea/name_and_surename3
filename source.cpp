#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>





using namespace std;

class Person {
public:
    Person(const string&name, const string&lName, int year) {
        birthName = name;
        birthLastName = lName;
        birthYear = year;
        data[year] = { name,lName };
    }

    void ChangeFirstName(int year, const string& first_name) {
        //Проверка попадания в диапазон первоначальной даты рождения
        if (year < birthYear) {
            return;
        }

        // добавить факт изменения имени на first_name в год year
        if (data.count(year) == 0) {
            data[year].resize(2);
        }
        data[year][0] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        //Проверка попадания в диапазон первоначальной даты рождения
        if (year < birthYear) {
            return;
        }
        
        // добавить факт изменения фамилии на last_name в год year
        if (data.count(year) == 0) {
            data[year].resize(2);
        }
        data[year][1] = last_name;
    }

    string GetFullName(int year) const{

        //Проверка попадания в диапазон первоначальной даты рождения
        if (year < birthYear) {
            return "No person";
        }

        string name, fam, res;
        for (const auto& n : data) {

            if (n.first > year) {
                break;
            }

            if (!n.second[0].empty()) {
                name = n.second[0];
            }
            if (!n.second[1].empty()) {
                fam = n.second[1];
            }
        }

        if (name.empty() && fam.empty()) {
            res = "Incognito";
        }
        else if (!name.empty() && !fam.empty()) {
            res = name + " " + fam;
        }
        else if (name.empty()) {
            res = fam + " with unknown first name";
        }
        else {
            res = name + " with unknown last name";
        }

        return res;
    }

    string GetFullNameWithHistory(int year) const {
        //Проверка попадания в диапазон первоначальной даты рождения
        if (year < birthYear) {
            return "No person";
        }               

        // получить все имена и фамилии по состоянию на конец года year
        vector<string> names;
        vector<string> fams;

        string name, fam, res;
        for (const auto& n : data) {

            if (n.first > year) {
                break;
            }

            if (!n.second[0].empty()) {
                name = n.second[0];
                               

                if (names.size() == 0) {
                    names.push_back(n.second[0]);
                }

                else if (names[names.size() - 1] != n.second[0]) {
                    names.push_back(n.second[0]);
                }

            }
            if (!n.second[1].empty()) {
                fam = n.second[1];
                                
                if (fams.size() == 0) {
                    fams.push_back(n.second[1]);
                }
                else if (fams[fams.size() - 1] != n.second[1]) {
                    fams.push_back(n.second[1]);
                }
            }
        }
                

        if (!names.empty())
            names.pop_back();
        if (!fams.empty())
            fams.pop_back();

        //Реверсируем вектор
        reverse(names.begin(), names.end());
        reverse(fams.begin(), fams.end());


        //Формируем строки из векторов
        string strName = " (", strFam = " (";

        for (auto& n : names) {
            if (n.empty()) continue;
            strName += n;
            strName += ", ";
        }
        strName.erase(strName.length() - 1);
        strName[strName.length() - 1] = ')';

        for (auto& f : fams) {
            strFam += f;
            strFam += ", ";
        }
        strFam.erase(strFam.length() - 1);
        strFam[strFam.length() - 1] = ')';

        if (strName.length() < 3)
            strName = "";
        if (strFam.length() < 3)
            strFam = "";

        if (name.empty() && fam.empty()) {
            res = "Incognito";
        }
        else if (!name.empty() && !fam.empty()) {
            res = name + strName + " " + fam + strFam;
        }
        else if (name.empty()) {
            res = fam + strFam + " with unknown first name";
        }
        else {
            res = name + strName + " with unknown last name";
        }

        return res;

    }

private:
    // приватные поля
    map<int, vector<string>> data;
    string birthName, birthLastName;
    int birthYear;
};


int main() {
    Person person("-1_first", "-1_last", -1);

    int year = -3;
    person.ChangeFirstName(year, std::to_string(year) + "_first");
    person.ChangeLastName(year, std::to_string(year) + "_last");

    year = 7;
    std::cout << "year: " << year << '\n';
    std::cout << person.GetFullNameWithHistory(year) << '\n';
    std::cout << person.GetFullName(year) << '\n';

    return 0;
}
