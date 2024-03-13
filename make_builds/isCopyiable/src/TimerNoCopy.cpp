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
    \file TimerNoCopy.cpp
    \brief File to provide implementation of the TimerNoCopy class
*/

#include "TimerNoCopy.hpp"

/*!
    \brief Default constructor for the TimerNoCopy class
*/
TimerNoCopy::TimerNoCopy() :
    startTime(std::chrono::steady_clock::now()),
    timeoutInterval(0),
    active(false) {
}

/*!
 * \brief TimerNoCopy::TimerNoCopy constructor that sends the timeout interval on creation
 * \param value - the Ms value for tiemout interval
 */
TimerNoCopy::TimerNoCopy(const TimerNoCopy::Ms& interval) :
    startTime(std::chrono::steady_clock::now()),
    timeoutInterval(interval),
    active(false) {

}

/*!
    \brief Default destructor for the TimerNoCopy class
*/
TimerNoCopy::~TimerNoCopy() {

}

/*!
    \brief Interval the timer is set for
    \return The timer's timeout interval in milliseconds
*/
TimerNoCopy::Ms TimerNoCopy::getInterval() const {
    return this->timeoutInterval;
}

/*!
    \brief Returns the activity state of the timer. If the timer is currently tracking time, it is active it will return
    true. Otherwise it will return false
    \return true if active, otherwise false
*/
bool TimerNoCopy::isActive() const {
    return this->active;
}

/*!
    \brief Returns time remaining for the timeout to occur

    If the timer is not active or the timer has timed out it will return 0

    \return the time remaining in millisconds
*/
TimerNoCopy::Ms TimerNoCopy::timeRemaining() const {
    auto remaining = this->timeoutInterval - (std::chrono::steady_clock::now() - this->startTime);

    if (remaining < TimerNoCopy::Ms::zero() || !this->active) {
        return TimerNoCopy::Ms::zero(); /// returns zero if the time duration is negative or the timer is inactive

    } else {
        return std::chrono::duration_cast<std::chrono::milliseconds>(remaining);
    }
}

/*!
    \brief Checks to see if the TimerNoCopy has officially timed out

    If the timer is not active, it cannot time out.

    \return true if active and timed out, otherwise false
*/
bool TimerNoCopy::hasTimedOut() const {
    if (this->active == false) {
        return false; /// Can't timeout if the timer is not running
    }

    if (timeRemaining() == TimerNoCopy::Ms::zero()) {
        return true; /// The timeout has reached zero. It's timed out
    }

    return false; /// There's still time remaining on the timer
}

/*!
    \brief Sets the interval the timer will use in milliseconds
    \param the timeout value to set
*/
void TimerNoCopy::setInterval(const TimerNoCopy::Ms& value) {
    if (value >= TimerNoCopy::Ms::zero()) {
        this->timeoutInterval = value;

    } else {
        this->timeoutInterval = TimerNoCopy::Ms::zero();
    }
}

/*!
    \brief Has the timer start tracking time if the interval is greater than 0, otherwise it doesn't do anything
*/
void TimerNoCopy::start() {
    this->active = true;
    this->startTime = std::chrono::steady_clock::now();
}

/*!
    \brief Starts the timer using the value provided as the interval
    \param value the value to set as the interval
*/
void TimerNoCopy::start(const TimerNoCopy::Ms& value) {
    this->setInterval(value);
    this->active = true;
    this->startTime = std::chrono::steady_clock::now();
}

/*!
    \brief stops the timer from running the function
*/
void TimerNoCopy::stop() {
    this->active = false;
}
