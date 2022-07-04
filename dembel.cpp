#include <iostream>
#include <string>
#include <ctime>

class Date {
    bool is_a_leap_year(int year) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            return true;
        }
        return false;
    }

public:

    int day;
    int month;
    int year;

    Date() {
        day = 0;
        month = 0;
        year = 1900;
    }

    Date(const std::string &date) {
        if(date.size() != 10) {
            std::cerr << "Wrong date forman, please use dd-mm-yyyy" << std::endl;
            exit(-1);
        }

        std::string d(date.substr(0, 2));
        std::string m(date.substr(3, 2));
        std::string y(date.substr(6, 4));

        this->year = std::stoi(y);
        this->month = std::stoi(m);
        this->day = std::stoi(d);

        if(this->year < 2020) {
            std::cerr << "Year must be greater or equal to 2020" << std::endl;
            exit(1);
        }

        if(this->month < 1 || this->month > 12) {
            std::cerr << "Month must be between 1-12" << std::endl;
            exit(1);
        }

        if(this->day < 1) {
            std::cerr << "Day must be greater than 0" << std::endl;
            exit(1);
        }

        if(this->month <= 7) {
            if(this->month == 2 && this->day > (28 + is_a_leap_year(this->year))) {
                std::cerr << "Day must be lower or equal to " << 28 + is_a_leap_year(this->year) << std::endl;
                exit(1);
            }

            if(this->day > 30 + this->month % 2) {
                std::cerr << "Day must be lower or equal to " << 30 + this->month % 2 << std::endl;
                exit(1);
            }
        } else {
            if(this->day > 30 + (this->month - 1) % 2) {
                std::cerr << "Day must be lower or equal to " << 30 + (this->month- 1) % 2 << std::endl;
                exit(1);
            }
        }
    }

    std::string to_string() {
        return std::to_string(day) + '-' + std::to_string(month) + '-' + std::to_string(year);
    }

    int operator- (const Date &d) {
        struct std::tm a = {0,0,0, d.day, d.month, d.year - 1900};
        struct std::tm b = {0,0,0, day, month, year - 1900};
        std::time_t x = std::mktime(&a);
        std::time_t y = std::mktime(&b);
        int days;
        if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) )
        {
            double difference = std::difftime(y, x) / (60 * 60 * 24);
            days = difference;
        }
        return days;
    }
};

int main (int argc, char* argv[])
{

    if(argc == 1) {
        std::cout << "Please, enter date with dd-mm-yyyy format, and how many years lasts the service.\nFor example 01-01-2011 2" << std::endl;
        return 0;
    }

    if(argc != 3) {
        std::cerr << "Wrong argument count" << std::endl;
        return 1;
    }

    Date end_date(argv[1]);
    int length = atoi(argv[2]);

    Date start_date(end_date);
    start_date.year -= length;

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
    std::string str(buffer);

    Date now_date(str);

    int curr_days = end_date - now_date;
    int days = end_date - start_date;

    std::cout <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣤⣤⣤⣤⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n" <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣶⣿⡿⠿⠟⠛⠛⠛⠉⠉⠛⠿⣿⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⠟⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠛⠛⢻⡇⠀⠀⢿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⠟⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠘⣿⠀⠀⢸⡇⠀⠀⢸⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⠏⠀⠀⠀⠀⣰⡟⠀⠀⠀⠀⠀⠀⠀⠙⠷⠶⠟⠁⠀⢀⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << "\t\tStart time: " << start_date.to_string() << '\n' <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡟⠀⠀⠀⢀⣼⠿⠶⠶⠶⠶⠶⠶⠶⠶⠶⠶⠶⠶⠶⠶⣾⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << "\t\tEnd time: " << end_date.to_string() << '\n' <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣧⣄⣠⣴⠟⠛⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠓⠚⠚⢿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << "\t\tNow: " << now_date.to_string() << '\n' <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣶⣿⣿⠟⠋⠻⢷⣤⣀⠀⠀⢀⣠⣴⠟⠛⠻⢿⣿⣶⣦⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⠀⠀⠀⣀⣠⣤⣶⣿⠿⠛⠻⣏⠀⠹⣇⠀⠀⣀⣽⠟⢻⣿⡛⢿⣄⠀⠀⠀⣼⠏⠈⣿⠛⠻⢿⣷⣦⣤⣀⡀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⣤⣶⣿⣿⠟⠋⠁⠀⣀⣠⣴⠿⠂⠀⢹⣆⢠⣿⡁⢀⡿⠙⣧⠀⢙⣷⠀⣼⠏⠀⠸⢧⣤⣀⠀⠀⠉⠙⠻⣿⣷⣦⣄⠀⠀\n" <<
"⠀⠀⣸⣿⠋⠀⠹⣧⣤⠶⠟⠋⠉⠀⠀⠀⠀⠀⢻⣿⠙⢷⣾⠃⠀⢹⣦⡾⠻⣿⠏⠀⠀⠀⠀⠈⠙⠛⠶⣦⣄⣼⠃⠀⢹⣿⡄⠀\n" <<
"⠀⠀⣿⡟⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠈⢻⣆⠀⣴⠟⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠀⠀⠀⣿⣧⠀\n" <<
"⠀⢸⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⠃⠀⠀⣤⣀⣠⣀⣀⣀⣀⣀⣀⣀⣄⠀⠀⠀⠀⠀⠀⢿⣿⠀\n" <<
"⠀⣼⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⣿⣤⣬⣿⣤⣤⣼⣿⣤⣬⣿⠀⠀⠀⠀⠀⠀⢸⣿⠀\n" <<
"⠀⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡆\n" <<
"⢀⣿⣇⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣿⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣿⡇\n" <<
"⠈⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠃" << std::endl;


    int left = (float)curr_days/days * 100;

    std::cout << '[';
    for(int i = 0; i < 100; ++i) {
        if(i < 100 - left) {
            std::cout << "🎖";
        } else {
            std::cout << '.';
        }
    }
    float passed = 100 - (float)curr_days/days * 100;

    if(passed >= 100) {
        passed = 100;
        std::cout << "] " << passed << '%' << "\n\nCongratulations, you have successfully finished army servcie" << std::endl;
    } else if (passed < 0) {
        std::cout << "] You didn't start serving yet" << std::endl;   
    } else {
        std::cout << "] " << passed << '%' << std::endl;
    }

    return 0;
}
