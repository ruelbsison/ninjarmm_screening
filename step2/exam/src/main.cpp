#include <cstdlib>
#include <vector>
#include <iostream>

#include <Programmer.h>
#include <Pilot.h>

using namespace std;
using namespace step2;

template <typename T>
T IsInBounds(T httpResonseCode, T responseCodeFrom, T responseCodeTo) {
    cout << httpResonseCode << " is ";
    if (httpResonseCode >= responseCodeFrom && httpResonseCode <= responseCodeTo) 
        cout << "In Range" << endl;
    else
        cout << "Not In Range" << endl;
   return (httpResonseCode >= responseCodeFrom && httpResonseCode <= responseCodeTo);
}

// i. Create a function that will take a vector of strings and a test function
void ContainsTheString(const vector<string> &n, const string& tested)
{

    for (int j = 0; j < n.size(); j++ )
    {
        cout << "n[" << j << "] = " << n[j] << endl;
    }

}

// j. how to use the ellipsis (...) with C++ variadic templates
template <typename T> void print(const T& t) {
    //cout << __PRETTY_FUNCTION__ << "\n";
    cout << t << endl;
}

template <typename First, typename... Rest> void print(const First& first, const Rest&... rest) {
    //cout << __PRETTY_FUNCTION__ << "\n";
    cout << first << ", ";
    print(rest...); // recursive call using pack expansion syntax
}

int main(int argc, char** argv) {
    // e. Dynamically allocate each type of job.
    Programmer *programmer = new Programmer();
    Pilot *pilot = new Pilot();

    // f. Store each instance in a collection.
    vector<Job*> jobs;
    jobs.push_back(programmer);
    jobs.push_back(pilot);


    // g. Iterate the collection and call each of the available interface functions.
    for (size_t i = 0; i < jobs.size(); i++) {
        const Job *job = jobs[i];
        // cout << "Name: " << job->getName() << endl;
        // cout << "Description: " << job->getDescription() << endl;
        // cout << "RequiredNumberOfHours: " << job->getRequiredNumberOfHours() << endl;
        job->getName();
        job->getDescription();
        job->getRequiredNumberOfHours();
        job->DoWork();
    }

    jobs.clear();
    delete pilot;
    delete programmer;

    // h. Create a template function that will test if the provided values are within a range.
    uint32_t httpResonseCode = 400;
    IsInBounds<uint32_t>(httpResonseCode, 500, 599);
    httpResonseCode = 600;
    IsInBounds<uint32_t>(httpResonseCode, 500, 599);
    httpResonseCode = 500;
    IsInBounds<uint32_t>(httpResonseCode, 500, 599);
    httpResonseCode = 599;
    IsInBounds<uint32_t>(httpResonseCode, 500, 599);
    httpResonseCode = 503;
    IsInBounds<uint32_t>(httpResonseCode, 500, 599);

    //auto theStrings = vector<string> { "one", "two",  "test"};
    //ContainsTheString();

    // j. how to use the ellipsis (...) with C++ variadic templates
    //print(); // calls first overload, outputting only a newline
    print(1); // calls second overload

    // these call the third overload, the variadic template,
    // which uses recursion as needed.
    print(10, 20);
    print(100, 200, 300);
    print("first", 2, "third", 3.14159);

    return EXIT_SUCCESS;
}