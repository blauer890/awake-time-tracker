/*
Author: Brian Lauer
Date: April 24, 2020

Program for keeping track of the number of
times I awake before a given time. The default is
9:00 am. Right now 9:00 am is hardcoded in as that
is my current goal. However, down the road a feature 
could be implemented to set the time
either with a command line argument or standard
input.
*/

#include <iostream>
#include <string>
#include <fstream>

#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_MINUTE 60

using namespace std;

int findHour(string time) {
    int i = 0;
    size_t colPos = 0;
    string hourString = "";
    colPos = time.find(":");
    hourString = time.substr(0, colPos);
    return stoi(hourString);
}

int findMinute(string time) {
    int i = 0;
    size_t colPos = 0;
    size_t len = 0;
    string minuteString = "";
    colPos = time.find(":");
    if(colPos != string::npos) {
        minuteString = time.substr(colPos+1);
    }
    return stoi(minuteString);
}

int main(int argc, char **argv) {
    // User variables
    ifstream timeInFile;
    ofstream timeOutFile;
    int timesBeforeBenchmark = 0;
    int awakeHours = 0;
    int awakeMinutes = 0;
    int awakeSeconds = 0;
    int benchmarkHours = 0;
    int benchmarkMinutes = 0;
    int benchmarkSeconds = 0;
    string awakeTime = "";
    string benchmarkTime = "";
    string strTimesBeforeBenchmark = "";

    // Read the number of times awoken before benchmark
    timeInFile.open("awake_time.txt");
    if(timeInFile.is_open()) {
        getline(timeInFile, strTimesBeforeBenchmark);
    }
    timesBeforeBenchmark = stoi(strTimesBeforeBenchmark);
    timeInFile.close();

    // Prompt for the awake time (military time)
    cout << "Enter an awake time: ";
    cin >> awakeTime;
    cout << "Enter a benchmark time: ";
    cin >> benchmarkTime;

    // Convert the time awoken to seconds from 00:00
    awakeHours = findHour(awakeTime);
    awakeMinutes = findMinute(awakeTime);
    awakeSeconds = awakeHours * SECONDS_PER_HOUR +
        awakeMinutes * SECONDS_PER_MINUTE;

    // Convert the benchmark time to seconds from 00:00
    benchmarkHours = findHour(benchmarkTime);
    benchmarkMinutes = findMinute(benchmarkTime);
    benchmarkSeconds = benchmarkHours * SECONDS_PER_HOUR +
        benchmarkMinutes * SECONDS_PER_MINUTE;

    // Write to the file the number of times
    // the user has woken before benchmark
    timeOutFile.open("awake_time.txt");
    if(awakeSeconds < benchmarkSeconds) {
        timesBeforeBenchmark++;
        cout << "Total streak is: " << timesBeforeBenchmark << endl;
        timeOutFile << timesBeforeBenchmark;
    } else {
        timesBeforeBenchmark = 0;
        cout << "Streak ended, streak set to " << timesBeforeBenchmark << endl;
        timeOutFile << timesBeforeBenchmark;
    }
    timeOutFile.close();

    return 0;
}
