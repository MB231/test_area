// -------------------------------------------------------------------------------------------------------------------
// SECURITY CLASSIFICATION: UNCLASSIFIED CUI//SP-CTI//SP-PROPIN
// -------------------------------------------------------------------------------------------------------------------
// Distribution Statement D: Distribution authorized to the DoD and U.S. DoD contractors only (Critical Technologies),
// 11 June 2014.  Other requests for this document will be referred to COMNAVAIRSYSCOM (PEO(T) PMA265).
// -------------------------------------------------------------------------------------------------------------------
// WARNING: This document contains technical data whose export is restricted by the Arms Export Control Act (Title 22,
// U.S.C., sec 2751, et seq.) or the Export Administration Act of 1979, as amended, Title 50, U.S.C., App. 2401 e seq.
// Violation of these export laws are subject to severe criminal penalties. Disseminate in accordance with the
// provisions of DoD directive 5230.25
// -------------------------------------------------------------------------------------------------------------------
// Restricted Data Rights
// Contract No. N/A
// Fuse Integration, Inc.
// 4863 Shawline Street #D San Diego, CA 92111
// The Government's rights to use, modify, reproduce, release, perform, display, or disclose this software
// are restricted by paragraph (b)(3) of the Rights in Noncommercial Technical Data and Computer Software -
// Small Business Innovation Research (SBIR) Program clause contained in the above identified contract.
// Any reproduction of computer software or portions thereof marked with this legend must also reproduce
// the markings. Any person, other than the Government, who has been provided access to such data must
// promptly notify the above named Contractor.
// -------------------------------------------------------------------------------------------------------------------

/*!
    \file Timer.hpp
    \brief File to define the api and class structure for a Timer class
*/

#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <cstdint>

/*!
    \brief Wraps up a timer to track a specific timeout
*/
class Timer {
    public:
        using Ms = std::chrono::duration<int, std::milli>; /// typedef for milliseconds

        explicit Timer();
        explicit Timer(const Ms& interval);
        ~Timer();

        Ms getInterval() const;
        bool isActive() const;
        Ms timeRemaining() const;

        bool hasTimedOut() const;

        void setInterval(const Ms& value);

        void start();
        void start(const Ms& value);

        void stop();

    private:
    std::chrono::time_point<std::chrono::steady_clock> startTime; /// Time point to represent the time the timer starts
    std::chrono::duration<int, std::milli> timeoutInterval; /// The timeout interval in milliseconds
    bool active; /// flag to check the activity of the Timer
};

#endif // TIMER_HPP
