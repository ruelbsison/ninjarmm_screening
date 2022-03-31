#pragma once

#include <string>
#include <cstdint>

using namespace std;

namespace step2 {
    class Job {
    protected:
        string name;
        string description;
        uint16_t requiredNumberOfHours;
    public:
        Job(string name, string description, uint16_t requiredNumberOfHours);

        string getName() const;
        string getDescription() const;
        uint16_t getRequiredNumberOfHours() const;

        void DoWork() const;
    };
} // namespace step2
