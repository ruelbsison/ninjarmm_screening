#include <Job.h>
#include <iostream>

using namespace std;
using namespace step2;

Job::Job(string _name, string _description, uint16_t _requiredNumberOfHours) 
    : name(_name), description(_description), requiredNumberOfHours(_requiredNumberOfHours)  {}


string Job::getName() const {
    return  name;
}

string Job::getDescription() const {
    return  description;
}

uint16_t Job::getRequiredNumberOfHours() const {
    return  requiredNumberOfHours;
}

void Job::DoWork() const {
  cout << "My Work involves " << getDescription() << " for " << getRequiredNumberOfHours() << " hours per day." << endl;
}